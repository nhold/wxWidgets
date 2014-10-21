/////////////////////////////////////////////////////////////////////////////
// Name:        aui/aui.h
// Purpose:     interface of wxAuiManager
// Author:      wxWidgets team
// RCS-ID:      $Id: framemanager.h 61464 2009-07-19 12:40:03Z MJM $
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////


/**
    @todo wxAuiPaneInfo dock direction types used with wxAuiManager.
*/
enum wxAuiManagerDock
{
    wxAUI_DOCK_NONE = 0,
    wxAUI_DOCK_TOP = 1,
    wxAUI_DOCK_RIGHT = 2,
    wxAUI_DOCK_BOTTOM = 3,
    wxAUI_DOCK_LEFT = 4,
    wxAUI_DOCK_CENTER = 5,
    wxAUI_DOCK_CENTRE = wxAUI_DOCK_CENTER
};


/**
    wxAuiManager behaviour and visual effects style flags.
*/
enum wxAuiManagerOption
{
    /// When a notebook is created, set the tabs on the top of the book.
    /// @since 3.1
    wxAUI_MGR_NB_TOP                   = 1 << 0,
    /// When a notebook is created, set the tabs on the left of the book.
    /// @since 3.1    
    wxAUI_MGR_NB_LEFT                  = 1 << 1,
    /// When a notebook is created, set the tabs on the right of the book.
    /// @since 3.1       
    wxAUI_MGR_NB_RIGHT                 = 1 << 2,
    /// When a notebook is created, set the tabs at the bottom of the book.
    /// @since 3.1       
    wxAUI_MGR_NB_BOTTOM                = 1 << 3,
    /// Allow to reorder tabs within notebooks by dragging them.
    /// @since 3.1
    wxAUI_MGR_NB_TAB_MOVE              = 1 << 4,
    /// Allow moving panes to other managers.
    /// @since 3.1
    wxAUI_MGR_ALLOW_EXTERNAL_MOVE      = 1 << 5,
    /// When this flag is set, all the tabs of a notebook have the same size.
    /// Otherwise, the with of a tab depends on the width of it's label.
    /// @since 3.1
    wxAUI_MGR_NB_TAB_FIXED_WIDTH       = 1 << 6,
    /// Show arrow buttons to scroll notebook tabs when they overflow the available space.
    /// @since 3.1
    wxAUI_MGR_NB_SCROLL_BUTTONS        = 1 << 7,
    /// Show a drop down button on the notebooks that displays the list of the tabs.
    /// @since 3.1
    wxAUI_MGR_NB_WINDOWLIST_BUTTON     = 1 << 8,
    /// Allow closing the selected tab of a notebook using a dedicated button placed next to the tabs.
    /// @since 3.1
    wxAUI_MGR_NB_CLOSE_BUTTON          = 1 << 9,
    /// In a notebook, show the close button only on the currently selected tab.
    /// @since 3.1
    wxAUI_MGR_NB_CLOSE_ON_ACTIVE_TAB   = 1 << 10,
    /// In a notebook, show the close button on all tabs.
    /// @since 3.1
    wxAUI_MGR_NB_CLOSE_ON_ALL_TABS     = 1 << 11,
    /// Allow to split a notebook by dragging the selected tab. 
    /// This is for internal use inside wxAuiNotebook. Do not use.
    /// @since 3.1
    wxAUI_MGR_NB_TAB_SPLIT             = 1 << 12,
    /// Always allow panes to dock over other panes and to create automatically new notebooks.
    /// It's possible to override the default behaviour defined by this flag on a per pane basis using events to allow or veto
    /// notebooks creation.
    /// @since 3.1
    wxAUI_MGR_NB_ALLOW_NOTEBOOKS       = 1 << 13,
    
    
    /// Allow a pane to be undocked to take the form of a wxMiniFrame.
    wxAUI_MGR_ALLOW_FLOATING           = 1 << 16,
    /// Change the color of the title bar of the pane when it is activated.
    wxAUI_MGR_ALLOW_ACTIVE_PANE        = 1 << 17,
    /// Make the pane transparent during its movement.
    wxAUI_MGR_TRANSPARENT_DRAG         = 1 << 18,
    /// The possible location for docking is indicated by a translucent area.
    wxAUI_MGR_TRANSPARENT_HINT         = 1 << 19,
    /// The possible location for docking is indicated by a gradually appearing
    /// partially transparent area.
    wxAUI_MGR_VENETIAN_BLINDS_HINT     = 1 << 20,
    /// The possible location for docking is indicated by a rectangular outline.
    wxAUI_MGR_RECTANGLE_HINT           = 1 << 21,
    /// The translucent area where the pane could be docked appears gradually.
    wxAUI_MGR_HINT_FADE                = 1 << 22,
    /// Used in complement of wxAUI_MGR_VENETIAN_BLINDS_HINT to show the hint immediately.
    wxAUI_MGR_NO_VENETIAN_BLINDS_FADE  = 1 << 23,
    /// When a docked pane is resized, its content is refreshed in live (instead of moving
    /// the border alone and refreshing the content at the end).
    wxAUI_MGR_LIVE_RESIZE              = 1 << 24,
    /// When the user click on a tab with the middle mouse button, close the pane.
    /// @since 3.1
    wxAUI_MGR_MIDDLE_CLICK_CLOSE       = 1 << 25,
    
    /// The default behaviour.
    wxAUI_MGR_DEFAULT = wxAUI_MGR_ALLOW_FLOATING |
                        wxAUI_MGR_TRANSPARENT_HINT |
                        wxAUI_MGR_HINT_FADE |
                        wxAUI_MGR_NO_VENETIAN_BLINDS_FADE |
                        wxAUI_MGR_NB_TOP |
                        wxAUI_MGR_NB_TAB_MOVE |
                        wxAUI_MGR_NB_TAB_SPLIT |
                        wxAUI_MGR_NB_SCROLL_BUTTONS |
                        wxAUI_MGR_NB_CLOSE_ON_ACTIVE_TAB |
                        wxAUI_MGR_MIDDLE_CLICK_CLOSE
};

/**
    @class wxAuiManager

    wxAuiManager is the central class of the wxAUI class framework.

    wxAuiManager manages the panes associated with it for a particular wxFrame,
    using a pane's wxAuiPaneInfo information to determine each pane's docking
    and floating behaviour.

    wxAuiManager uses wxWidgets' sizer mechanism to plan the layout of each
    frame. It uses a replaceable dock art class to do all drawing, so all
    drawing is localized in one area, and may be customized depending on an
    application's specific needs.

    wxAuiManager works as follows: the programmer adds panes to the class,
    or makes changes to existing pane properties (dock position, floating
    state, show state, etc.). To apply these changes, wxAuiManager's
    Update() function is called. This batch processing can be used to avoid
    flicker, by modifying more than one pane at a time, and then "committing"
    all of the changes at once by calling Update().

    Panes can be added quite easily:

    @code
    wxTextCtrl* text1 = new wxTextCtrl(this, -1);
    wxTextCtrl* text2 = new wxTextCtrl(this, -1);
    m_mgr.AddPane(text1, wxLEFT, "Pane Caption");
    m_mgr.AddPane(text2, wxBOTTOM, "Pane Caption");
    m_mgr.Update();
    @endcode

    Later on, the positions can be modified easily. The following will float
    an existing pane in a tool window:

    @code
    m_mgr.GetPane(text1).Float();
    @endcode


    @section auimanager_layers Layers, Rows and Directions, Positions

    Inside wxAUI, the docking layout is figured out by checking several pane
    parameters. Five of these are important for determining where a pane will
    end up:

    @li Direction: Each docked pane has a direction, Top, Bottom, Left, Right,
        or Center. This is fairly self-explanatory. The pane will be placed in
        the location specified by this variable.
    @li Position: More than one pane can be placed inside of a dock. Imagine
        two panes being docked on the left side of a window. One pane can be
        placed next another. In proportionally managed docks, the pane
        position indicates its sequential position, starting with zero. So, in
        our scenario with two panes docked on the left side, the top pane in
        the dock would have position 0, and the second one would occupy
        position 1.
    @li Row: A row can allow for two docks to be placed next to each other.
        One of the most common places for this to happen is in the toolbar.
        Multiple toolbar rows are allowed, the first row being row 0, and the
        second row 1. Rows can also be used on vertically docked panes.
    @li Layer: A layer is akin to an onion. Layer 0 is the very center of the
        managed pane. Thus, if a pane is in layer 0, it will be closest to the
        center window (also sometimes known as the "content window").
        Increasing layers "swallow up" all layers of a lower value. This can
        look very similar to multiple rows, but is different because all panes
        in a lower level yield to panes in higher levels. The best way to
        understand layers is by running the wxAUI sample.
    @li Page: More then one pane can be docked in the exact same Direction,
        Position, Row and Layer. When this happens a tabbed notebook will be formed.
        Tab position will be decided based on the Page values of the panes with
        those that have a lower value appearing on the left, with 0 being the
        absolute left. By default, pages are not enabled.

    @beginStyleTable
    @style{wxAUI_MGR_ALLOW_FLOATING}
           Allow a pane to be undocked to take the form of a wxMiniFrame.
    @style{wxAUI_MGR_ALLOW_ACTIVE_PANE}
           Change the colour of the title bar of the pane when it is activated.
    @style{wxAUI_MGR_TRANSPARENT_DRAG}
           Make the pane transparent during its movement.
    @style{wxAUI_MGR_TRANSPARENT_HINT}
           The possible location for docking is indicated by a translucent area.
    @style{wxAUI_MGR_VENETIAN_BLINDS_HINT}
           The possible location for docking is indicated by gradually
           appearing partially transparent hint.
    @style{wxAUI_MGR_RECTANGLE_HINT}
           The possible location for docking is indicated by a rectangular
           outline.
    @style{wxAUI_MGR_HINT_FADE}
           The translucent area where the pane could be docked appears gradually.
    @style{wxAUI_MGR_NO_VENETIAN_BLINDS_FADE}
           Used in complement of wxAUI_MGR_VENETIAN_BLINDS_HINT to show the
           docking hint immediately.
    @style{wxAUI_MGR_LIVE_RESIZE}
           When a docked pane is resized, its content is refreshed in live (instead of moving
    @style{wxAUI_MGR_MIDDLE_CLICK_CLOSE}       
           the border alone and refreshing the content at the end).
           When the user click on a tab with the middle mouse button, close the pane.
           @since 3.1
    @style{wxAUI_MGR_NB_TOP}       
           When a notebook is created, set the tabs on the top of the book.
           @since 3.1
    @style{wxAUI_MGR_NB_LEFT}
           When a notebook is created, set the tabs on the left of the book.
           @since 3.1    
    @style{wxAUI_MGR_NB_RIGHT}
           When a notebook is created, set the tabs on the right of the book.
           @since 3.1       
    @style{wxAUI_MGR_NB_BOTTOM}
           When a notebook is created, set the tabs at the bottom of the book.
           @since 3.1       
    @style{wxAUI_MGR_NB_TAB_MOVE}
           Allow to reorder tabs within notebooks by dragging them.
           @since 3.1
    @style{wxAUI_MGR_ALLOW_EXTERNAL_MOVE}
           Allow moving panes to other managers.
           @since 3.1
    @style{wxAUI_MGR_NB_TAB_FIXED_WIDTH}
           When this flag is set, all the tabs of a notebook have the same size. Otherwise, the with of a tab depends on the width of it's label.
           @since 3.1
    @style{wxAUI_MGR_NB_SCROLL_BUTTONS}
           Show arrow buttons to scroll notebook tabs when they overflow the available space.
           @since 3.1
    @style{wxAUI_MGR_NB_WINDOWLIST_BUTTON}
           Show a drop down button on the notebooks that displays the list of the tabs.
           @since 3.1
    @style{wxAUI_MGR_NB_CLOSE_BUTTON}
           Allow closing the selected tab of a notebook using a dedicated button placed next to the tabs.
           @since 3.1
    @style{wxAUI_MGR_NB_CLOSE_ON_ACTIVE_TAB}
           In a notebook, show the close button only on the currently selected tab.
           @since 3.1
    @style{wxAUI_MGR_NB_CLOSE_ON_ALL_TABS}
           In a notebook, show the close button on all tabs.
           @since 3.1
    @style{wxAUI_MGR_NB_TAB_SPLIT}
           Allow to split a notebook by dragging the selected tab. 
           This is for internal use inside wxAuiNotebook. Do not use.
           @since 3.1
    @style{wxAUI_MGR_NB_ALLOW_NOTEBOOKS}
           Always allow panes to dock over other panes and to create @style{automatically new notebooks.
           It's possible to override the default behaviour defined by this flag on a per pane basis using events to allow or veto
           notebooks creation.
           @since 3.1
     @style{wxAUI_MGR_DEFAULT}
           Default behaviour, combines: 
            wxAUI_MGR_ALLOW_FLOATING |
            wxAUI_MGR_TRANSPARENT_HINT |
            wxAUI_MGR_HINT_FADE |
            wxAUI_MGR_NO_VENETIAN_BLINDS_FADE |
            wxAUI_MGR_NB_TOP |
            wxAUI_MGR_NB_TAB_MOVE |
            wxAUI_MGR_NB_TAB_SPLIT |
            wxAUI_MGR_NB_SCROLL_BUTTONS |
            wxAUI_MGR_NB_CLOSE_ON_ACTIVE_TAB |
            wxAUI_MGR_MIDDLE_CLICK_CLOSE.                        
    @endStyleTable

    @beginEventEmissionTable{wxAuiManagerEvent}
    @event{EVT_AUI_PANE_BUTTON(func)}
        Triggered when any button is pressed for any docked panes.
    @event{EVT_AUI_PANE_CLOSE(func)}
        Triggered when a docked or floating pane is closed.
    @event{EVT_AUI_PANE_MAXIMIZE(func)}
        Triggered when a pane is maximized.
    @event{EVT_AUI_PANE_RESTORE(func)}
        Triggered when a pane is restored.
    @event{EVT_AUI_PANE_ACTIVATED(func)}
        Triggered when a pane is made 'active'. This event is new since
        wxWidgets 2.9.4.
    @event{EVT_AUI_RENDER(func)}
        This event can be caught to override the default renderer in order to
        custom draw your wxAuiManager window (not recommended).
    @event{EVT_AUI_PANE_DOCK_OVER(func)}
        This event is triggered when wxAui is about to create a notebook by docking a pane over another one. You may Allow() or Veto() it explicitly to override the default behaviour defined by the wxAUI_MGR_NB_ALLOW_NOTEBOOKS style flag.
        @since 3.1
    @event{EVT_AUI_FIND_MANAGER(func)}
        This event is used internally to implement the wxAuiManager::GetManager() method.
        Do not use. 
        @since 3.1
    @event{EVT_AUI_ALLOW_DND(func)}   
        This event can be caught to accept transferring a pane dragged from another manager.
        @since 3.1
    @endEventTable

    @library{wxaui}
    @category{aui}

    @see @ref overview_aui, wxAuiNotebook, wxAuiDockArt, wxAuiPaneInfo
*/
class wxAuiManager : public wxEvtHandler
{
public:
    /**
        Constructor.

        @param managed_wnd
            Specifies the wxFrame which should be managed.
        @param flags
            Specifies the frame management behaviour and visual effects
            with the ::wxAuiManagerOption's style flags.
    */
    wxAuiManager(wxWindow* managed_wnd = NULL,
                 unsigned int flags = wxAUI_MGR_DEFAULT);

    /**
        Dtor.
    */
    virtual ~wxAuiManager();

    //@{
    /**
        AddPane() tells the frame manager to start managing a child window.
        There are several versions of this function. The first version allows
        the full spectrum of pane parameter possibilities. The second version is
        used for simpler user interfaces which do not require as much configuration.
        The last version allows a drop position to be specified, which will determine
        where the pane will be added.
    */
    bool AddPane(wxWindow* window, const wxAuiPaneInfo& pane_info);
    bool AddPane(wxWindow* window, int direction = wxLEFT,
                 const wxString& caption = wxEmptyString);
    bool AddPane(wxWindow* window,
                 const wxAuiPaneInfo& pane_info,
                 const wxPoint& drop_pos);
    //@}
    
    /**
        CalculateHintRect() calculates the drop hint rectangle.  The method
        first calls DoDrop() to determine the exact position the pane would
        be at were if dropped.  If the pane would indeed become docked at the
        specified drop point, the rectangle hint will be returned in
        screen coordinates.  Otherwise, an empty rectangle is returned.
        |paneWindow| is the window pointer of the pane being dragged, |pt| is
        the mouse position, in client coordinates.  |offset| describes the offset
        that the mouse is from the upper-left corner of the item being dragged
        
        @since 3.1
        
        @remark Do not use as this may be removed from the public interface later.
    */
    wxRect CalculateHintRect(wxWindow* paneWindow, const wxPoint& pt, const wxPoint& offset);    
    
    /**
        CanDockPanel() returns true if a dragged panel is allowed to be docked. The default implementation returns
        true unless the CTRL key or the ALT key is pressed. This may be overloaded to suit your needs.
        @since 3.1
    */
    virtual bool CanDockPanel(const wxAuiPaneInfo& p);
    
    /**
        ClosePane() closes a pane. It returns true if successful or false if the close event has been vetoed.
        No further call to Update() is needed.
        @since 3.1
    */
    bool ClosePane(wxAuiPaneInfo& paneInfo);
    
    /**
        Creates a new frame window for a floating pane. This method may be overloaded to 
        customize the floating frame with one of your own.
        @since 3.1
    */
    virtual wxAuiFloatingFrame* CreateFloatingFrame(wxWindow* parent, const wxAuiPaneInfo& p);    
    

    /**
        Tells the wxAuiManager to stop managing the pane specified by window.
        The window, if in a floated frame, is reparented to the frame managed
        by wxAuiManager.
    */
    bool DetachPane(wxWindow* window);
    
    /**
        DrawHintRect() calculates the hint rectangle by calling
        CalculateHintRect().  If there is a rectangle, it shows it
        by calling ShowHint(), otherwise it hides any hint
        rectangle currently shown.
        
        @since 3.1        
        @remark Do not use as this may be removed from the public interface later.        
        
    */
    void DrawHintRect(wxWindow* paneWindow, const wxPoint& pt, const wxPoint& offset);      
    
    /**
        FindTab() finds the tab control that currently contains the window as well
        as the index of the window in the tab control.  It returns true if the
        window was found, otherwise false.
        @since 3.1
    */
    bool FindTab(wxWindow* page, wxAuiTabContainer** ctrl, int* idx);
    
    /**
        Returns the index of the active pane in this manager. The active pane is defined as the one that manages the focus window, or, if the window is NULL,
        the pane marked as active. If no suitable pane is found, wxNOT_FOUND is returned.
        @since 3.1
    */
    int GetActivePane(wxWindow* focus) const;
    
    /**
        Returns an array of all panes managed by the frame manager.
    */
    wxAuiPaneInfoArray& GetAllPanes();

    /**
        Returns the current art provider being used.
        @see wxAuiDockArt.
    */
    wxAuiDockArt* GetArtProvider() const;

    /**
        Returns the current tab art provider being used.
        @see wxAuiTabArt.
    */
    wxAuiTabArt* GetTabArtProvider() const;

    /**
        Returns the current dock constraint values.
        See SetDockSizeConstraint() for more information.
    */
    void GetDockSizeConstraint(double* widthpct, double* heightpct) const;

    /**
        Returns the current ::wxAuiManagerOption's flags.
    */
    unsigned int GetFlags() const;

    /**
        Returns the frame currently being managed by wxAuiManager.
    */
    wxWindow* GetManagedWindow() const;

    /**
        Calling this method will return the wxAuiManager for a given window.
        The @a window parameter should specify any child window or sub-child
        window of the frame or window managed by wxAuiManager.

        The @a window parameter need not be managed by the manager itself, nor does it
        even need to be a child or sub-child of a managed window. It must however
        be inside the window hierarchy underneath the managed window.
    */
    static wxAuiManager* GetManager(wxWindow* window);

    //@{
    /**
        GetPane() is used to lookup a wxAuiPaneInfo object either by window pointer
        or by pane name, which acts as a unique id for a window pane.
        
        @since 3.1
        The indexed overload can be used to retrieve directly a pane from it's index in the internal panes list.
        paneIndex spans from 0 to GetPaneCount()-1.

        The returned wxAuiPaneInfo object may then be modified to change a pane's
        look, state or position. After one or more modifications to wxAuiPaneInfo,
        wxAuiManager::Update() should be called to commit the changes to the user
        interface. If the lookup failed (meaning the pane could not be found in the
        manager), a call to the returned wxAuiPaneInfo's IsOk() method will return @false.
    */
    wxAuiPaneInfo& GetPane(wxWindow* window) const;
    wxAuiPaneInfo& GetPane(const wxString& name) const;
    wxAuiPaneInfo& GetPane(size_t paneIndex) const;
    //@}
    
    /** 
        GetPaneCount() returns the number of managed panes. @see GetPane(size_t)
        @since 3.1
    */
    size_t GetPaneCount() const;
    
    /**
        Tells if a single flag from ::wxAuiManagerOption is set.
        @since 3.1
    */
    bool HasFlag(int flag) const;
   

    /**
        HideHint() hides any docking hint that may be visible.
    */
    virtual void HideHint();

    /**
        This method is used to insert either a previously unmanaged pane window
        into the frame manager, or to insert a currently managed pane somewhere
        else. InsertPane() will push all panes, rows, or docks aside and
        insert the window into the position specified by @a insert_location.

        Because @a insert_location can specify either a pane, dock row, or dock
        layer, the @a insert_level parameter is used to disambiguate this.
        The parameter @a insert_level can take a value of wxAUI_INSERT_PANE,
        wxAUI_INSERT_ROW or wxAUI_INSERT_DOCK.
    */
    bool InsertPane(wxWindow* window,
                    const wxAuiPaneInfo& insert_location,
                    int insert_level = wxAUI_INSERT_PANE);

    /**
        LoadPaneInfo() is similar to LoadPerspective, with the exception that it
        only loads information about a single pane.  It is used in combination with
        SavePaneInfo().
    */
    void LoadPaneInfo(wxString pane_part, wxAuiPaneInfo& pane);

    /**
        Loads a saved perspective. If update is @true, wxAuiManager::Update()
        is automatically invoked, thus realizing the saved perspective on screen.
    */
    bool LoadPerspective(const wxString& perspective,
                         bool update = true);
                         
    /**
        MaximizePane() maximize the given pane. No call to Update() is needed.
        @since 3.1
    */
    void MaximizePane(wxAuiPaneInfo& paneInfo);
    
    /*!
       OnHintActivate() 

       @since 3.1
       @remark Do not use: this is an implementation only method that may be removed from public interface
    */
    void OnHintActivate(wxActivateEvent& event);
    
    /**
        RestoreMaximizedPane() restore the maximized pane if any
        @since 3.1
    */
    void RestoreMaximizedPane();
    
    /** 
        RestorePane() restore the given pane assuming it's maximized.    
        @since 3.1
        
        @remark
        This function should not be used and may be removed from public interface quickly. use RestoreMaximizedPane() instead.
    */
    void RestorePane(wxAuiPaneInfo& paneInfo);
    
    /** 
        SetActivePane() sets the pane handling the given window as active, as well as cycles through
        every other pane and makes sure that all others' active flags
        are turned off. It always returns 0.
        @since 3.1
    */
    int SetActivePane(wxWindow* activePane);
    
   
    /**
        SavePaneInfo() is similar to SavePerspective, with the exception that it only
        saves information about a single pane.  It is used in combination with
        LoadPaneInfo().
    */
    wxString SavePaneInfo(wxAuiPaneInfo& pane);

    /**
        Saves the entire user interface layout into an encoded wxString, which
        can then be stored by the application (probably using wxConfig).

        When a perspective is restored using LoadPerspective(), the entire user
        interface will return to the state it was when the perspective was saved.
    */
    wxString SavePerspective();
    
    /**
        Instructs wxAuiManager to use art provider specified by parameter
        @a art_provider for all drawing calls.
        This allows pluggable look-and-feel features. The previous art provider object,
        if any, will be deleted by wxAuiManager.

        @see wxAuiDockArt.
    */
    void SetArtProvider(wxAuiDockArt* art_provider);

    /**
        Instructs wxAuiManager to use art provider specified by parameter
        @a art_provider for all notebook drawing calls.
        This allows pluggable look-and-feel features. The previous tab art provider object,
        if any, will be deleted by wxAuiManager.

        @see wxAuiTabArt.
    */
    void SetTabArtProvider(wxAuiTabArt* art_provider);

    /**
        When a user creates a new dock by dragging a window into a docked position,
        often times the large size of the window will create a dock that is unwieldy
        large. wxAuiManager by default limits the size of any new dock to 1/3 of the
        window size.  For horizontal docks, this would be 1/3 of the window height.
        For vertical docks, 1/3 of the width.

        Calling this function will adjust this constraint value. The numbers must be
        between 0.0 and 1.0.  For instance, calling SetDockSizeContraint with
        0.5, 0.5 will cause new docks to be limited to half of the size of the
        entire managed window.
    */
    void SetDockSizeConstraint(double widthpct, double heightpct);

    /**
        This method allow to set or clear a single flag from ::wxAuiManagerOption.
        @since 3.1
    */
    void SetFlag(int flag, bool optionState);
    
    /**
        This method is used to specify ::wxAuiManagerOption's flags. @a flags
        specifies options which allow the frame management behaviour to be modified.
    */
    void SetFlags(unsigned int flags);

    /**
        Called to specify the frame or window which is to be managed by wxAuiManager.
        Frame management is not restricted to just frames.  Child windows or custom
        controls are also allowed.
    */
    void SetManagedWindow(wxWindow* managed_wnd);

    /**
        This function is used by controls to explicitly show a hint window at the
        specified rectangle. It is rarely called, and is mostly used by controls
        implementing custom pane drag/drop behaviour.
        The specified rectangle should be in screen coordinates.
    */
    virtual void ShowHint(const wxRect& rect);
    
    /**
        Initiate a dragging action onto the given window. This is usually called automatically by the mouse event handler.
        The offset is the window relative position of the "pointer" when the action starts.
        @since 3.1
        
        @remark Do not use as this may be removed from the public interface later.
    */
    void StartPaneDrag(wxWindow* paneWindow, const wxPoint& offset);
    
    
    /**
        Uninitializes the framework and should be called before a managed frame or
        window is destroyed. UnInit() is usually called in the managed wxFrame's
        destructor.  It is necessary to call this function before the managed frame
        or window is destroyed, otherwise the manager cannot remove its custom event
        handlers from a window.
    */
    void UnInit();

    /**
        This method is called after any number of changes are
        made to any of the managed panes. Update() must be invoked after
        AddPane() or InsertPane() are called in order to "realize" or "commit"
        the changes. In addition, any number of changes may be made to
        wxAuiPaneInfo structures (retrieved with wxAuiManager::GetPane), but to
        realize the changes, Update() must be called. This construction allows
        pane flicker to be avoided by updating the whole layout at one time.
    */
    void Update();

protected:

    /**
        ProcessDockResult() is a protected member of the wxAUI layout manager.
        It can be overridden by derived classes to provide custom docking calculations.
    */
    virtual bool ProcessDockResult(wxAuiPaneInfo& target,
                                   const wxAuiPaneInfo& new_pos);
};



/**
    @class wxAuiPaneInfo

    wxAuiPaneInfo is part of the wxAUI class framework.
    See also @ref overview_aui.

    wxAuiPaneInfo specifies all the parameters for a pane.
    These parameters specify where the pane is on the screen, whether it is docked
    or floating, or hidden.
    In addition, these parameters specify the pane's docked position, floating
    position, preferred size, minimum size, caption text among many other parameters.
    
    @remark
    Prior to version 3.1 of wxWidgets, it was allowed to directly modify the attributes of this class. This is now
    strongly discouraged. You should use the access methods to get and set the attributes values.
    The direct access to attributes may be removed in the future.

    @library{wxaui}
    @category{aui}

    @see wxAuiManager, wxAuiDockArt
*/
class wxAuiPaneInfo
{
public:
    wxAuiPaneInfo();

    /**
        Copy constructor.
    */
    wxAuiPaneInfo(const wxAuiPaneInfo& c);
    
    /**
        The pane flags.
        @see HasFlag(), SetFlag(), SetFlags(), GetFlags()
        @remark In most case, you do not have to deal directly with these flags. Use the supplied 
        methods to test the various pane states instead of testing the flags directly.
    */
    enum wxAuiPaneState
    {
        /// The pane is floating
        optionFloating             = 1 << 0,
        /// The pane is hidden
        optionHidden               = 1 << 1,
        /// The pane can be docked to the left
        optionLeftDockable         = 1 << 2,
        /// The pane can be docked to the right
        optionRightDockable        = 1 << 3,
        /// The pane can be docked to the top
        optionTopDockable          = 1 << 4,
        /// The pane can be docked to the bottom
        optionBottomDockable       = 1 << 5,
        /// The pane can be floated
        optionFloatable            = 1 << 6,
        /// The pane can be moved
        optionMovable              = 1 << 7,
        /// The pane can be resized
        optionResizable            = 1 << 8,
        /// The pane shall have a border
        optionPaneBorder           = 1 << 9,
        /// The pane has a caption
        optionCaption              = 1 << 10,
        /// The pane has a gripper
        optionGripper              = 1 << 11,
        /// The pane shall be destroyed when closed instead of being hidden
        optionDestroyOnClose       = 1 << 12,
        /// The pane contains a toolbar window
        optionToolbar              = 1 << 13,
        /// The pane is the active one
        optionActive               = 1 << 14,
        /// The pane gripper is on the pane's top
        optionGripperTop           = 1 << 15,
        /// The pane is maximized
        optionMaximized            = 1 << 16,
        /// The pane shall be in a fixed dock
        optionDockFixed            = 1 << 17,
        /// ?
        /// @since 3.1
        optionActiveNotebook       = 1 << 18,
        /// The pane shall always be docked in a notebook, even if alone.
        /// @since 3.1
        optionAlwaysDockInNotebook = 1 << 19,
        /// The pane can be docked to the center
        /// @since 3.1
        optionCenterDockable       = 1 << 20,
        /// The pane has a close button
        buttonClose                = 1 << 21,
        /// The pane has a maximize button
        buttonMaximize             = 1 << 22,
        /// The pane has a minimize button
        buttonMinimize             = 1 << 23,
        /// The pane has a pin button
        buttonPin                  = 1 << 24,
        /// ?
        buttonCustom1              = 1 << 26,
        /// ?
        buttonCustom2              = 1 << 27,
        /// ?
        buttonCustom3              = 1 << 28,
        /// Used internally to save the hidden state when a pane is maximized
        savedHiddenState           = 1 << 30, // used internally
        /// Used internally
        actionPane                 = 1 << 31  // used internally
    };    
    
    //@{
    /**
        GetInfo() serializes the layout information for this pane into a wxString.
        This panes state can then be restored by calling GetInfo() on the same string.
        @since 3.1
    */
    wxString GetInfo() const;
    /**
        LoadInfo() sets the layout information for this pane to the values stored in a serialized wxString.
        A serialized wxString containing this information can be generated by calling GetInfo().
        @since 3.1
    */
    void LoadInfo(wxString& info);
    //@}   

    /**
        GetWindow() returns the pointer to the window associated to the pane.
        @since 3.1
    */
    wxWindow* GetWindow() const;
    
    //@{
    /**
        GetFrame() returns the floating frame window that holds the pane.
    */
    wxFrame* GetFrame() const;
    /**
        Frame() sets the floating frame window that holds the pane.
    */
    wxAuiPaneInfo& Frame(wxFrame* frame);
    //@}
    

    //@{
    /**
        BestSize() sets the ideal size for the pane. The docking manager will attempt
        to use this size as much as possible when docking or floating the pane.
    */
    wxAuiPaneInfo& BestSize(const wxSize& size);
    wxAuiPaneInfo& BestSize(int x, int y);
    
    /**
        GetBestSize() returns the best size of the pane.
        @see BestSize()
        @since 3.1
    */
    wxSize GetBestSize() const;    
    //@}

    /**
        Bottom() sets the pane dock position to the bottom side of the frame. This is
        the same thing as calling Direction(wxAUI_DOCK_BOTTOM).
    */
    wxAuiPaneInfo& Bottom();

    /**
        BottomDockable() indicates whether a pane can be docked at the bottom of the
        frame.
    */
    wxAuiPaneInfo& BottomDockable(bool b = true);

    /** 
        GetCaption() returns the caption of the pane
        @since 3.1
    */
    wxString GetCaption() const;
    
    /**
        Caption() sets the caption of the pane.
    */
    wxAuiPaneInfo& Caption(const wxString& c);

    /**
        CaptionVisible indicates that a pane caption should be visible. If @false, no
        pane caption is drawn.
    */
    wxAuiPaneInfo& CaptionVisible(bool visible = true);

    //@{
    /**
        Center() sets the pane dock position to the left side of the frame.
        The centre pane is the space in the middle after all border panes (left, top,
        right, bottom) are subtracted from the layout.
        This is the same thing as calling Direction(wxAUI_DOCK_CENTRE).
    */
    wxAuiPaneInfo& Centre();
    wxAuiPaneInfo& Center();
    //@}

    /**
        CenterDockable() allows (or forbid if the parameter is @false) the pane to be docked in the centre area of the managed window.
        @since 3.1
    */
    wxAuiPaneInfo& CenterDockable(bool b = true);
    
    
    //@{
    /**
        CentrePane() specifies that the pane should adopt the default centre pane
        settings. Centre panes usually do not have caption bars.
        This function provides an easy way of preparing a pane to be displayed in
        the centre dock position.
    */
    wxAuiPaneInfo& CentrePane();
    wxAuiPaneInfo& CenterPane();
    //@}

    /**
        CloseButton() indicates that a close button should be drawn for the pane.
    */
    wxAuiPaneInfo& CloseButton(bool visible = true);

    /**
        DefaultPane() specifies that the pane should adopt the default pane settings.
    */
    wxAuiPaneInfo& DefaultPane();

    //@{
    /**
        HasDestroyOnClose() returns @true if a pane should be destroyed when it is closed.
        Normally a pane is simply hidden when the close button is clicked.
        @since 3.1
    */
    bool HasDestroyOnClose() const;
       
    /**
        DestroyOnClose() indicates whether a pane should be destroyed when it is closed.
        Normally a pane is simply hidden when the close button is clicked.
        Setting DestroyOnClose to @true will cause the window to be destroyed when
        the user clicks the pane's close button.
    */
    wxAuiPaneInfo& DestroyOnClose(bool b = true);

    /**
        Direction() determines the direction of the docked pane. It is functionally the
        same as calling Left(), Right(), Top() or Bottom(), except that docking direction
        may be specified programmatically via the parameter.
    */
    wxAuiPaneInfo& Direction(int direction);
    
    /**
        GetDirection() returns the docking direction of pane.
        @see Direction()
        @since 3.1
    */
    int GetDirection() const;    

    /**
        Dock() indicates that a pane should be docked.  It is the opposite of Float().
    */
    wxAuiPaneInfo& Dock();

    /**
        DockFixed() causes the containing dock to have no resize sash.  This is useful
        for creating panes that span the entire width or height of a dock, but should
        not be resizeable in the other direction.
    */
    wxAuiPaneInfo& DockFixed(bool b = true);
    
    /** 
        IsDockFixed() returns true if the dock cannot be resized.
        @see DockFixed()
        @since 3.1
    */
    bool IsDockFixed() const;
    
    /**
        Fixed() forces a pane to be fixed size so that it cannot be resized. After
        calling Fixed(), IsFixed() will return @true.
    */
    wxAuiPaneInfo& Fixed();
    
    /**
        Dockable() specifies whether a frame can be docked or not. It is the same as
        specifying TopDockable(b).BottomDockable(b).LeftDockable(b).RightDockable(b).CentreDockable(b)
    */
    wxAuiPaneInfo& Dockable(bool b = true);
    
    /**
        AlwaysDockInNotebook() force the pane to always dock in a notebook, even if it's alone.
        @since 3.1
    */
    wxAuiPaneInfo &AlwaysDockInNotebook(bool b = true);
    
    /**
        IsAlwaysDockInNotebook() return @true if the pane always docs in a notebook, even if alone.
        @see AlwaysDockInNotebook()
        @since 3.1
    */
    bool IsAlwaysDockInNotebook() const;
    
    /**
        MoveOver() moves a pane over another one, creating a notebook if allowed when wxAuiManager::Update() is called.
        The pane is set in the page immediately after the targeted one.
        @since 3.1
    */
    wxAuiPaneInfo &MoveOver(const wxAuiPaneInfo &target);

    /**
        Float() indicates that a pane should be floated.  It is the opposite of Dock().
    */
    wxAuiPaneInfo& Float();

    /**
        Floatable() sets whether the user will be able to undock a pane and turn it
        into a floating window.
    */
    wxAuiPaneInfo& Floatable(bool b = true);

    //@{
    /**
        FloatingPosition() sets the position of the floating pane.
    */
    wxAuiPaneInfo& FloatingPosition(const wxPoint& pos);
    wxAuiPaneInfo& FloatingPosition(int x, int y);
    
    /**
        GetFloatingPosition() return the position of the pane when it's floating.
        @see FloatingPosition()
        @since 3.1
    */
    wxPoint GetFloatingPosition() const;
    
    //@}

    //@{
    /**
        FloatingSize() sets the size of the floating pane.
    */
    wxAuiPaneInfo& FloatingSize(const wxSize& size);
    wxAuiPaneInfo& FloatingSize(int x, int y);
    
    /**
        GetFloatingSize() return the size of the pane when it's floating.
        @see FloatingSize()
        @since 3.1
    */
    wxPoint GetFloatingSize() const;    
    
    //@}

    /**
        Gripper() indicates that a gripper should be drawn for the pane.
    */
    wxAuiPaneInfo& Gripper(bool visible = true);

    /**
        GripperTop() indicates that a gripper should be drawn at the top of the pane.
    */
    wxAuiPaneInfo& GripperTop(bool attop = true);

    /**
        HasBorder() returns @true if the pane displays a border.
    */
    bool HasBorder() const;

    /**
        HasCaption() returns @true if the pane displays a caption.
    */
    bool HasCaption() const;

    /**
        HasCloseButton() returns @true if the pane displays a button to close the pane.
    */
    bool HasCloseButton() const;

    //@{
    /**
        HasFlag() returns @true if the property specified by flag is active for
        the pane.
    */
    bool HasFlag(int flag) const;
    
    /**
        Flags() set all the pane flags as a wxAuiPaneState flags combination.
        @since 3.1
    */
    wxAuiPaneInfo& Flags(unsigned int f);
    
    
    /**
        GetFlags() returns the combined flags set for the pane.
        @see Flags()
        @since 3.1
    */
    unsigned int GetFlags() const;
    
    //@}

    /**
        HasGripper() returns @true if the pane displays a gripper.
    */
    bool HasGripper() const;

    /**
        HasGripper() returns @true if the pane displays a gripper at the top.
    */
    bool HasGripperTop() const;

    /**
        HasMaximizeButton() returns @true if the pane displays a button to maximize the
        pane.
    */
    bool HasMaximizeButton() const;

    /**
        HasMinimizeButton() returns @true if the pane displays a button to minimize the
        pane.
    */
    bool HasMinimizeButton() const;

    /**
        HasPinButton() returns @true if the pane displays a button to float the pane.
    */
    bool HasPinButton() const;
    
    /**
        GetButtons() returns all the buttons defined for the pane
        @since 3.1
    */
    wxAuiPaneButtonArray& GetButtons();

    /**
        Hide() indicates that a pane should be hidden.
    */
    wxAuiPaneInfo& Hide();

    /**
        Icon() sets the icon of the pane.

        Notice that the height of the icon should be smaller than the value
        returned by wxAuiDockArt::GetMetric(wxAUI_DOCKART_CAPTION_SIZE) to
        ensure that it appears correctly.

        @since 2.9.2
    */
    wxAuiPaneInfo& Icon(const wxBitmap& b);
    
    /** 
        GetIcon() returns the icon representing the pane.
        @see Icon()
        @since 3.1
    */
    const wxBitmap &GetIcon() const;
    
    //@{
    /**
        GetProportion() gets the proportion of the docked pane.
        @see Proportion()
        @since 3.1
    */
    int GetProportion() const;
    
    /**
        Proportion() sets the proportion of the docked pane.
        @since 3.1
    */
    wxAuiPaneInfo& Proportion(int proportion);
    //@}    

    /**
        IsBottomDockable() returns @true if the pane can be docked at the bottom of the
        managed frame.

        @see IsDockable()
    */
    bool IsBottomDockable() const;
    
    /**
        IsCenterDockable() returns @true if the pane can be docked in the centre area of the managed frame.
        
        @see IsDockable()
        @since 3.1

    /**
        Returns @true if the pane can be docked at any side.

        @see IsTopDockable(), IsBottomDockable(), IsLeftDockable(), IsRightDockable(), IsCentreDockable()

        @since 2.9.2
    */
    bool IsDockable() const;

    /**
        IsDocked() returns @true if the pane is currently docked.
    */
    bool IsDocked() const;

    /**
        IsFixed() returns @true if the pane cannot be resized.
    */
    bool IsFixed() const;

    /**
        IsFloatable() returns @true if the pane can be undocked and displayed as a
        floating window.
    */
    bool IsFloatable() const;

    /**
        IsFloating() returns @true if the pane is floating.
    */
    bool IsFloating() const;

    /**
        IsLeftDockable() returns @true if the pane can be docked on the left of the
        managed frame.

        @see IsDockable()
    */
    bool IsLeftDockable() const;
    
    //@{
    /**
        IsMaximized() returns @true if the pane is maximized.
        @since 3.1
    */
    bool IsMaximized() const;
    /**
        Maximize() sets a pane to display as maximized. Only one pane should be marked as
        maximized at a time.
        @since 3.1
    */
    wxAuiPaneInfo& Maximize();
    /**
        Restore() restores a pane to its previous(non maximized) size.
        @since 3.1
    */
    wxAuiPaneInfo& Restore();
    //@}

    /**
        IsMoveable() returns @true if the docked frame can be undocked or moved to
        another dock position.
    */
    bool IsMovable() const;

    /**
        IsOk() returns @true if the wxAuiPaneInfo structure is valid. A pane structure
        is valid if it has an associated window.
    */
    bool IsOk() const;
    
    /**
        IsValid() returns true if the pane is valid. The pane is valid either if it's not
        a toolbar, or if it's a toolbar pane with settings suitable for the contained toolbar.
    */
    bool IsValid() const;
        
    
    /** 
        IsActive() return @true if the pane is marked as the active one.
        @since 3.1
    */
    bool IsActive() const;
   
    /**
        IsResizable() returns @true if the pane can be resized.
    */
    bool IsResizable() const;

    /**
        IsRightDockable() returns @true if the pane can be docked on the right of the
        managed frame.

        @see IsDockable()
    */
    bool IsRightDockable() const;

    /**
        IsShown() returns @true if the pane is currently shown.
    */
    bool IsShown() const;

    /**
        IsToolbar() returns @true if the pane contains a toolbar.
    */
    bool IsToolbar() const;

    /**
        IsTopDockable() returns @true if the pane can be docked at the top of the
        managed frame.

        @see IsDockable()
    */
    bool IsTopDockable() const;

    /**
        Layer() determines the layer of the docked pane. The dock layer is similar to
        an onion, the inner-most layer being layer 0. Each shell moving in the outward
        direction has a higher layer number. This allows for more complex docking layout
        formation.
    */
    wxAuiPaneInfo& Layer(int layer);
    
    /**
        GetLayer() returns the current layer of the pane.
        @see Layer()
        @since 3.1
    */
    int GetLayer() const;

    /**
        Left() sets the pane dock position to the left side of the frame. This is the
        same thing as calling Direction(wxAUI_DOCK_LEFT).
    */
    wxAuiPaneInfo& Left();

    /**
        LeftDockable() indicates whether a pane can be docked on the left of the frame.
    */
    wxAuiPaneInfo& LeftDockable(bool b = true);

    //@{
    /**
        MaxSize() sets the maximum size of the pane.
    */
    wxAuiPaneInfo& MaxSize(const wxSize& size);
    wxAuiPaneInfo& MaxSize(int x, int y);
    
    /**
        GetMaxSize() return the maximum size of the pane.
        @see MaxSize()
        @since 3.1
    */
    wxSize GetMaxSize() const; 
    //@}

    /**
        MaximizeButton() indicates that a maximize button should be drawn for the pane.
    */
    wxAuiPaneInfo& MaximizeButton(bool visible = true);

    //@{
    /**
        MinSize() sets the minimum size of the pane. Please note that this is only
        partially supported as of this writing.
    */
    wxAuiPaneInfo& MinSize(const wxSize& size);
    wxAuiPaneInfo& MinSize(int x, int y);
    
    /**
        GetMinSize() return the minimum size of the pane.
        @see MinSize()
        @since 3.1
    */
    wxSize GetMinSize() const;    
    //@}

    /**
        MinimizeButton() indicates that a minimize button should be drawn for the pane.
    */
    wxAuiPaneInfo& MinimizeButton(bool visible = true);

    /**
        Movable indicates whether a frame can be moved.
    */
    wxAuiPaneInfo& Movable(bool b = true);

    //@{
    /**
        Name() sets the name of the pane so it can be referenced in lookup functions.
        If a name is not specified by the user, a random name is assigned to the pane
        when it is added to the manager.
    */
    wxAuiPaneInfo& Name(const wxString& n);
    
    /**
        GetName() returns the identifier name assigned to the pane.
        @since 3.1
    */
    wxString GetName() const;
    
    

    //@}
    
    /**
        PaneBorder indicates that a border should be drawn for the pane.
    */
    wxAuiPaneInfo& PaneBorder(bool visible = true);

    /**
        PinButton() indicates that a pin button should be drawn for the pane.
    */
    wxAuiPaneInfo& PinButton(bool visible = true);

    /**
        Position() determines the position of the docked pane.
    */
    wxAuiPaneInfo& Position(int pos);
    
    /**
        GetPosition() returns the dock position of the pane.
        @see Position()
        @since 3.1
    */
    int GetPosition() const;
    
    //@{
    /**
        GetPage() sets the tab position of the docked pane.
        @see Page()
        @since 3.1
    */
    int GetPage() const;
    /**
        Page() gets the tab position of the docked pane.
        @since 3.1
    */
    wxAuiPaneInfo& Page(int page);
    //@}    
    
    //@{
    /**
        GetRect() returns the current rectangle of the pane. The rectangle
        is updated by the manager each time the layout changes.
        @see Rect()
        @since 3.1
    */
    wxRect GetRect() const;
    
    /**
        Rect() defines the rectangle enclosing the pane. This is updated
        by the wxAui framework and you should not use this.
        @since 3.1
    */
    wxAuiPaneInfo& Rect(const wxRect& rect);
    //@}
    

    /**
        Resizable() allows a pane to be resized if the parameter is @true, and forces it
        to be a fixed size if the parameter is @false. This is simply an antonym for Fixed().
    */
    wxAuiPaneInfo& Resizable(bool resizable = true);

    /**
        Right() sets the pane dock position to the right side of the frame.
    */
    wxAuiPaneInfo& Right();

    /**
        RightDockable() indicates whether a pane can be docked on the right of the
        frame.
    */
    wxAuiPaneInfo& RightDockable(bool b = true);

    /**
        Row() determines the row of the docked pane.
    */
    wxAuiPaneInfo& Row(int row);
    
    /**
        GetRow() returns the row number of the pane.
        @see Row()
        @since 3.1
    */
    int GetRow() const;
    

    /**
        Write the safe parts of a newly loaded PaneInfo structure "source" into "this"
        used on loading perspectives etc.
    */
    void SafeSet(wxAuiPaneInfo source);

    /**
        SetFlag() turns the property given by flag on or off with the option_state
        parameter.
    */
    wxAuiPaneInfo& SetFlag(int flag, bool option_state);

    /**
        Show() indicates that a pane should be shown.
    */
    wxAuiPaneInfo& Show(bool show = true);

    /**
        ToolbarPane() specifies that the pane should adopt the default toolbar pane
        settings.
    */
    wxAuiPaneInfo& ToolbarPane();

    /**
        Top() sets the pane dock position to the top of the frame.
    */
    wxAuiPaneInfo& Top();

    /**
        TopDockable() indicates whether a pane can be docked at the top of the frame.
    */
    wxAuiPaneInfo& TopDockable(bool b = true);
    
    /**
        ToolTip() sets the tooltip to display for the pane when docked in a notebook.
        @since 3.1
    */
    wxAuiPaneInfo& ToolTip(const wxString& t);
    
    /**
        Returns the current tooltip of the pane
        @see ToolTip()
        @since 3.1
    */
    wxString GetToolTip() const;
        

    /**
        Window() assigns the window pointer that the wxAuiPaneInfo should use.
        This normally does not need to be specified, as the window pointer is
        automatically assigned to the wxAuiPaneInfo structure as soon as it is added
        to the manager.
    */
    wxAuiPaneInfo& Window(wxWindow* w);

    /**
        Makes a copy of the wxAuiPaneInfo object.
    */
    wxAuiPaneInfo& operator=(const wxAuiPaneInfo& c);
};



/**
    @class wxAuiManagerEvent

    Event used to indicate various actions taken with wxAuiManager.

    See wxAuiManager for available event types.

    @beginEventTable{wxAuiManagerEvent}
    @event{EVT_AUI_PANE_BUTTON(func)}
        Triggered when any button is pressed for any docked panes.
    @event{EVT_AUI_PANE_CLOSE(func)}
        Triggered when a docked or floating pane is closed.
    @event{EVT_AUI_PANE_MAXIMIZE(func)}
        Triggered when a pane is maximized.
    @event{EVT_AUI_PANE_RESTORE(func)}
        Triggered when a pane is restored.
    @event{EVT_AUI_PANE_ACTIVATED(func)}
        Triggered when a pane is made 'active'. This event is new since
        wxWidgets 2.9.4.
    @event{EVT_AUI_RENDER(func)}
        This event can be caught to override the default renderer in order to
        custom draw your wxAuiManager window (not recommended).
    @event{EVT_AUI_PANE_DOCK_OVER(func)}
        This event is triggered when wxAui is about to create a notebook by docking a pane over another one. You may Allow() or Veto() it explicitly to override the default behaviour defined by the wxAUI_MGR_NB_ALLOW_NOTEBOOKS style flag.         
    @event{EVT_AUI_FIND_MANAGER(func)}
        This event is used internally to implement the wxAuiManager::GetManager() method.
        Do not use. 
        @since 3.1    
    @event{EVT_AUI_ALLOW_DND(func)}
        This event can be caught to accept transferring a pane dragged from another manager.
        @since 3.1    
    @endEventTable

    @library{wxaui}
    @category{events,aui}

    @see wxAuiManager, wxAuiPaneInfo
*/
class wxAuiManagerEvent : public wxEvent
{
public:
    /**
        Constructor.
    */
    wxAuiManagerEvent(wxEventType type = wxEVT_NULL);

    /**
        Allow (or forbid if parameter is @false) the event to be processed.
        The use of the parameter to negate the action is strongly discouraged. Use Veto() instead.
        @since 3.1
    */
    void Allow(bool allow = true);

    /**
        @return @true if this event can be vetoed.

        @see Veto()
    */
    bool CanVeto() const;

    /**
        @return The ID of the button that was clicked.
    */
    int GetButton() const;

    /**
        @return The device context where to draw when handling the EVT_AUI_RENDER event.
    */
    wxDC* GetDC() const;

    /**
        @return @true if this event was vetoed.

        @see Veto()
    */
    bool GetVeto() const;

    /**
        @return The wxAuiManager this event is associated with.
    */
    wxAuiManager* GetManager() const;

    /**
        @return The pane this event is associated with.
    */
    wxAuiPaneInfo* GetPane() const;
    
    /**
        @return the target pane
        @since 3.1
    */
    wxAuiPaneInfo* GetTargetPane() const;
    
    /**
        @return @true if the event action is allowed.
        @since 3.1
    */
    bool IsAllowed() const;

    /**
        Sets the ID of the button clicked that triggered this event.
    */
    void SetButton(int button);

    /**
        Sets whether or not this event can be vetoed.
    */
    void SetCanVeto(bool can_veto);

    /**
        Set the device context where to draw when handling the EVT_AUI_RENDER event.
    */
    void SetDC(wxDC* pdc);

    /**
        Sets the wxAuiManager this event is associated with.
    */
    void SetManager(wxAuiManager* manager);

    /**
        Sets the pane this event is associated with.
    */
    void SetPane(wxAuiPaneInfo* pane);
    
    /**
        Sets the target pane onto which a pane is being dropped to 
        create a notebook in the EVT_PANE_DOCK_OVER event.
        @since 3.1
    */
    void SetTargetPane(wxAuiPaneInfo *pane);

    /**
        Cancels the action indicated by this event if CanVeto() is @true.
        The use of the parameter to negate the action is strongly discouraged. Use Allow() instead.
    */
    void Veto(bool veto = true);
};

