/////////////////////////////////////////////////////////////////////////////
// Name:        src/gtk/dialog.cpp
// Purpose:
// Author:      Robert Roebling
// Id:          $Id$
// Copyright:   (c) 1998 Robert Roebling
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#include "wx/dialog.h"

#ifndef WX_PRECOMP
    #include "wx/cursor.h"
#endif // WX_PRECOMP

#include "wx/evtloop.h"

#include "wx/scopedptr.h"
#include "wx/testing.h"

#include <gtk/gtk.h>
#include "wx/gtk/private/gtk2-compat.h"

// this is defined in src/gtk/toplevel.cpp
extern int wxOpenModalDialogsCount;

wxDEFINE_TIED_SCOPED_PTR_TYPE(wxGUIEventLoop)


//-----------------------------------------------------------------------------
// wxDialog
//-----------------------------------------------------------------------------

void wxDialog::Init()
{
    m_modalLoop = NULL;
    m_returnCode = 0;
    m_modalShowing = false;
    m_themeEnabled = true;
}

wxDialog::wxDialog( wxWindow *parent,
                    wxWindowID id, const wxString &title,
                    const wxPoint &pos, const wxSize &size,
                    long style, const wxString &name )
{
    Init();

    (void)Create( parent, id, title, pos, size, style, name );
}

bool wxDialog::Create( wxWindow *parent,
                       wxWindowID id, const wxString &title,
                       const wxPoint &pos, const wxSize &size,
                       long style, const wxString &name )
{
    SetExtraStyle(GetExtraStyle() | wxTOPLEVEL_EX_DIALOG);

    // all dialogs should have tab traversal enabled
    style |= wxTAB_TRAVERSAL;

    return wxTopLevelWindow::Create(parent, id, title, pos, size, style, name);
}

bool wxDialog::Show( bool show )
{
    if (!show && IsModal())
    {
        EndModal( wxID_CANCEL );
    }

    if (show && CanDoLayoutAdaptation())
        DoLayoutAdaptation();

    bool ret = wxDialogBase::Show(show);

    if (show)
        InitDialog();

    return ret;
}

wxDialog::~wxDialog()
{
    // if the dialog is modal, this will end its event loop
    if ( IsModal() )
        EndModal(wxID_CANCEL);
}

bool wxDialog::IsModal() const
{
    return m_modalShowing;
}

void wxDialog::SetModal( bool WXUNUSED(flag) )
{
    wxFAIL_MSG( wxT("wxDialog:SetModal obsolete now") );
}

// Workaround for Ubuntu overlay scrollbar, which adds our GtkWindow to a
// private window group in a GtkScrollbar realize handler. This breaks the grab
// done by gtk_window_set_modal(), and allows menus and toolbars in the parent
// frame to remain active. So, we install an emission hook on the "realize"
// signal while showing a modal dialog. For any realize on a GtkScrollbar,
// we check the top level parent to see if it has an explicitly set window
// group that is not the same as its transient parent. If we find this, we
// put the top level back in the same window group as its transient parent, and
// re-add the grab.
// Ubuntu 12.04 and 12.10 are known to have this problem.

// need 2.10 for gtk_window_get_group()
#if GTK_CHECK_VERSION(2,10,0)
extern "C" {
static gboolean
realize_hook(GSignalInvocationHint*, unsigned, const GValue* param_values, void*)
{
    void* p = g_value_peek_pointer(param_values);
    if (GTK_IS_SCROLLBAR(p))
    {
        GtkWindow* toplevel = GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(p)));
        GtkWindow* transient_parent = gtk_window_get_transient_for(toplevel);
        if (transient_parent && gtk_window_has_group(toplevel))
        {
            GtkWindowGroup* group = gtk_window_get_group(toplevel);
            GtkWindowGroup* group_parent = gtk_window_get_group(transient_parent);
            if (group != group_parent)
            {
                gtk_window_group_add_window(group_parent, toplevel);
                gtk_grab_add(GTK_WIDGET(toplevel));
            }
        }
    }
    return true;
}
}
#endif // GTK 2.10

int wxDialog::ShowModal()
{
    WX_TESTING_SHOW_MODAL_HOOK();

    wxASSERT_MSG( !IsModal(), "ShowModal() can't be called twice" );

    // release the mouse if it's currently captured as the window having it
    // will be disabled when this dialog is shown -- but will still keep the
    // capture making it impossible to do anything in the modal dialog itself
    wxWindow * const win = wxWindow::GetCapture();
    if ( win )
        win->GTKReleaseMouseAndNotify();

    wxWindow * const parent = GetParentForModalDialog();
    if ( parent )
    {
        gtk_window_set_transient_for( GTK_WINDOW(m_widget),
                                      GTK_WINDOW(parent->m_widget) );
    }

    wxBusyCursorSuspender cs; // temporarily suppress the busy cursor

#if GTK_CHECK_VERSION(2,10,0)
    unsigned sigId = 0;
    gulong hookId = 0;
#ifndef __WXGTK3__
    // Ubuntu overlay scrollbar uses at least GTK 2.24
    if (gtk_check_version(2,24,0) == NULL)
#endif
    {
        sigId = g_signal_lookup("realize", GTK_TYPE_WIDGET);
        hookId = g_signal_add_emission_hook(sigId, 0, realize_hook, NULL, NULL);
    }
#endif

    Show( true );

    m_modalShowing = true;

    wxOpenModalDialogsCount++;

    // NOTE: gtk_window_set_modal internally calls gtk_grab_add() !
    gtk_window_set_modal(GTK_WINDOW(m_widget), TRUE);

    // Run modal dialog event loop.
    {
        wxGUIEventLoopTiedPtr modal(&m_modalLoop, new wxGUIEventLoop());
        m_modalLoop->Run();
    }

#if GTK_CHECK_VERSION(2,10,0)
    if (sigId)
        g_signal_remove_emission_hook(sigId, hookId);
#endif

    gtk_window_set_modal(GTK_WINDOW(m_widget), FALSE);

    wxOpenModalDialogsCount--;

    return GetReturnCode();
}

void wxDialog::EndModal( int retCode )
{
    SetReturnCode( retCode );

    if (!IsModal())
    {
        wxFAIL_MSG( "either wxDialog:EndModal called twice or ShowModal wasn't called" );
        return;
    }

    m_modalShowing = false;

    // Ensure Exit() is only called once. The dialog's event loop may be terminated
    // externally due to an uncaught exception.
    if (m_modalLoop && m_modalLoop->IsRunning())
        m_modalLoop->Exit();

    Show( false );
}
