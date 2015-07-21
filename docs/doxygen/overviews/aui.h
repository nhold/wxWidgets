/////////////////////////////////////////////////////////////////////////////
// Name:        aui.h
// Purpose:     topic overview
// Author:      wxWidgets team
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

/**

@page overview_aui wxAUI Overview

@tableofcontents

wxAUI stands for Advanced User Interface. It aims to give the user a cutting
edge interface with floatable windows, and a user-customizable layout. The
original wxAUI sources have kindly been made available under the wxWindows
licence by Kirix Corp. and they have since then been integrated into wxWidgets
and further improved.

@see @ref group_class_aui



@section overview_aui_frame Frame Management

Frame management provides the means to open, move and hide common controls that
are needed to interact with the document, and allow these configurations to be
saved into different perspectives and loaded at a later time.

If you want correct loading of perspectives make sure you set wxAuiPaneInfo::DestroyOnClose(false);
so that the pane is not destroyed when it is closed, otherwise you will be missing panes if the user
has closed them.



@section overview_aui_toolbar Toolbars

Toolbars are a specialized subset of the frame management system and should
behave similarly to other docked components. However, they also require
additional functionality, such as "spring-loaded" rebar support, "chevron"
buttons and end-user customizability.



@section overview_aui_modeless Modeless Controls

Modeless controls expose a tool palette or set of options that float above the
application content while allowing it to be accessed. Usually accessed by the
toolbar, these controls disappear when an option is selected, but may also be
"torn off" the toolbar into a floating frame of their own.



@section overview_aui_lnf Look and Feel

Look and feel encompasses the way controls are drawn, both when shown
statically as well as when they are being moved. This aspect of user interface
design incorporates "special effects" such as transparent window dragging as
well as frame animation.

wxAUI adheres to the following principles: Use native floating frames to obtain
a native look and feel for all platforms. Use existing wxWidgets code where
possible, such as sizer implementation for frame management. Use classes
included in @ref page_libs_wxcore and @ref page_libs_wxbase only.

@section Known incompatibilities and bugs in 3.1 compared to 3.0

    All items listed here are subject to fixes/changes before 3.2.

    @li The perspective string returned by wxAuiManager::SavePerspective() in 3.1 is not compatible with the 3.0 one.
    @li The numeric values of several wxAuiManager flags have changed.
    @li The wxAuiTabContainer, wxAuiNotebookPage and wxAuiNotebookPageArray classes no more actually exist and are aliased to wxAuiTabCtrl, wxAuiPaneInfo and wxAuiPaneInfoArray. These later classes have not the same interface than the former classes.
    @li The wxAuiNotebook events wxEVT_COMMAND_AUINOTEBOOK_BG_DCLICK, wxEVT_COMMAND_AUINOTEBOOK_TAB_RIGHT_UP, wxEVT_AUINOTEBOOK_PAGE_CHANGING and wxEVT_AUINOTEBOOK_PAGE_CHANGED have the wxAuiNotebook itself as event object and no more the wxAuiTabCtrl (tab container).
    @li Drop hints over floating panels are not always correctly sized.

*/
