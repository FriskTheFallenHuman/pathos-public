/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef UISETTINGSWINDOW_H
#define UISETTINGSWINDOW_H

class CUISettingsWindow;

/*
=================================
CUISettingsEventBase

=================================
*/
class CUISettingsEventBase : public CUICallbackEvent
{
public:
	explicit CUISettingsEventBase( CUISettingsWindow* pWindow ):
		m_pWindow(pWindow)
	{ };
	virtual ~CUISettingsEventBase( void ) { };

protected:
	// Window that created this
	CUISettingsWindow* m_pWindow;
};

/*
=================================
CUISliderAdjustEvent

=================================
*/
class CUISliderAdjustEvent : public CUISettingsEventBase
{
public:
	CUISliderAdjustEvent( CUISettingsWindow* pWindow, const char* pstrCVarName, bool isInteger = false ):
		CUISettingsEventBase(pWindow),
		m_cvarName(pstrCVarName),
		m_isInteger(isInteger)
	{ };
	virtual ~CUISliderAdjustEvent( void ) { };
			
public:
	// Performs the action tied to this event
	virtual void PerformAction( float param );

protected:
	// CVar name that this toggles
	CString m_cvarName;
	// true if value is integer
	bool m_isInteger;
};

/*
=================================
CUITickBoxEvent

=================================
*/
class CUITickBoxEvent : public CUISettingsEventBase
{
public:
	CUITickBoxEvent( CUISettingsWindow* pWindow, const char* pstrCVarName ):
		CUISettingsEventBase(pWindow),
		m_cvarName(pstrCVarName)
	{ };
	virtual ~CUITickBoxEvent( void ) { };
			
public:
	// Performs the action tied to this event
	virtual void PerformAction( float param );

protected:
	// CVar name that this toggles
	CString m_cvarName;
};

/*
=================================
CUIScrollSurfaceDropListToggleEvent

=================================
*/
class CUIScrollSurfaceDropListToggleEvent : public CUISettingsEventBase
{
public:
	CUIScrollSurfaceDropListToggleEvent( CUISettingsWindow* pWindow, UInt32 rowIndex ):
		CUISettingsEventBase(pWindow),
		m_rowIndex(rowIndex)
	{ };
	virtual ~CUIScrollSurfaceDropListToggleEvent( void ) { };
			
public:
	virtual void PerformAction( float param );

protected:
	// Row index
	UInt32 m_rowIndex;
};

/*
=================================
CUIScrollSurfaceDropListSelectEvent

=================================
*/
class CUIScrollSurfaceDropListSelectEvent : public CUISettingsEventBase
{
public:
	CUIScrollSurfaceDropListSelectEvent( CUISettingsWindow* pWindow, UInt32 rowIndex ):
		CUISettingsEventBase(pWindow),
		m_rowIndex(rowIndex)
	{ };
	virtual ~CUIScrollSurfaceDropListSelectEvent( void ) { };
			
public:
	virtual void PerformAction( float param );

protected:
	// Row index
	UInt32 m_rowIndex;
};

/*
=================================
CUISettingsCancelEvent

=================================
*/
class CUISettingsCancelEvent : public CUISettingsEventBase
{
public:
	explicit CUISettingsCancelEvent( CUISettingsWindow* pWindow ):
		CUISettingsEventBase(pWindow)
	{ };
	virtual ~CUISettingsCancelEvent( void ) { };
			
public:
	virtual void PerformAction( float param );
};

/*
=================================
CUISettingsApplyEvent

=================================
*/
class CUISettingsApplyEvent : public CUISettingsEventBase
{
public:
	explicit CUISettingsApplyEvent( CUISettingsWindow* pWindow ):
		CUISettingsEventBase(pWindow)
	{ };
	virtual ~CUISettingsApplyEvent( void ) { };
			
public:
	virtual void PerformAction( float param );
};

/*
=================================
CUIBindsRowEvent

=================================
*/
class CUIBindsRowEvent : public CUISettingsEventBase
{
public:
	explicit CUIBindsRowEvent( CUISettingsWindow* pWindow ):
		CUISettingsEventBase(pWindow),
		m_rowIndex(-1),
		m_lastClickTime(0)
	{ };
	virtual ~CUIBindsRowEvent( void ) { };

public:
	// Performs the action
	virtual void PerformAction( float param ) { };
	// Handles a mouse button event
	virtual bool MouseButtonEvent( Int32 mouseX, Int32 mouseY, Int32 button, bool keyDown );

	// Sets the row index
	virtual void SetRowIndex( UInt32 rowIndex ) { m_rowIndex = rowIndex; }

protected:
	// Index of the row tied to this event
	Int32 m_rowIndex;
	// Last time this was clicked on
	float m_lastClickTime;
};

/*
=================================
CUITabSelectEvent

=================================
*/
class CUITabSelectEvent: public CUISettingsEventBase
{
public:
	explicit CUITabSelectEvent( CUISettingsWindow* pWindow ):
		CUISettingsEventBase(pWindow)
	{ };
	virtual ~CUITabSelectEvent( void ) { };

public:
	// Performs the action
	virtual void PerformAction( float param );
};

/*
=================================
CUIBindsClearBtnEvent

=================================
*/
class CUIBindsClearBtnEvent: public CUISettingsEventBase
{
public:
	explicit CUIBindsClearBtnEvent( CUISettingsWindow* pWindow ):
		CUISettingsEventBase(pWindow)
	{ };
	virtual ~CUIBindsClearBtnEvent( void ) { };

public:
	// Performs the action
	virtual void PerformAction( float param );
};

/*
=================================
CUIBindsRestoreButtonEvent

=================================
*/
class CUIBindsRestoreButtonEvent: public CUISettingsEventBase
{
public:
	explicit CUIBindsRestoreButtonEvent( CUISettingsWindow* pWindow ):
		CUISettingsEventBase(pWindow)
	{ };
	virtual ~CUIBindsRestoreButtonEvent( void ) { };

public:
	// Performs the action
	virtual void PerformAction( float param );
};

/*
=================================
CUIBindsBindBtnEvent

=================================
*/
class CUIBindsBindBtnEvent: public CUISettingsEventBase
{
public:
	explicit CUIBindsBindBtnEvent( CUISettingsWindow* pWindow ):
		CUISettingsEventBase(pWindow)
	{ };
	virtual ~CUIBindsBindBtnEvent( void ) { };

public:
	// Performs the action
	virtual void PerformAction( float param );
};

/*
=================================
CUIDeviceSelectEvent

=================================
*/
class CUIDeviceSelectEvent: public CUISettingsEventBase
{
public:
	explicit CUIDeviceSelectEvent( CUISettingsWindow* pWindow ):
		CUISettingsEventBase(pWindow)
	{ };
	virtual ~CUIDeviceSelectEvent( void ) { };

public:
	// Performs the action
	virtual void PerformAction( float param );
};

/*
=================================
CUIResolutionSelectEvent

=================================
*/
class CUIResolutionSelectEvent: public CUISettingsEventBase
{
public:
	explicit CUIResolutionSelectEvent( CUISettingsWindow* pWindow ):
		CUISettingsEventBase(pWindow)
	{ };
	virtual ~CUIResolutionSelectEvent( void ) { };

public:
	// Performs the action
	virtual void PerformAction( float param );
};

/*
=================================
CUIWindowModeSelectEvent

=================================
*/
class CUIWindowModeSelectEvent: public CUISettingsEventBase
{
public:
	explicit CUIWindowModeSelectEvent( CUISettingsWindow* pWindow ):
		CUISettingsEventBase(pWindow)
	{ };
	virtual ~CUIWindowModeSelectEvent( void ) { };

public:
	// Performs the action
	virtual void PerformAction( float param );
};

/*
=================================
CUIAnisotropySelectEvent

=================================
*/
class CUIAnisotropySelectEvent: public CUISettingsEventBase
{
public:
	explicit CUIAnisotropySelectEvent( CUISettingsWindow* pWindow ):
		CUISettingsEventBase(pWindow)
	{ };
	virtual ~CUIAnisotropySelectEvent( void ) { };

public:
	// Performs the action
	virtual void PerformAction( float param );
};

/*
=================================
CUIAntiAliasSelectEvent

=================================
*/
class CUIAntiAliasSelectEvent: public CUISettingsEventBase
{
public:
	explicit CUIAntiAliasSelectEvent( CUISettingsWindow* pWindow ):
		CUISettingsEventBase(pWindow)
	{ };
	virtual ~CUIAntiAliasSelectEvent( void ) { };

public:
	// Performs the action
	virtual void PerformAction( float param );
};

/*
=================================
CUIVerticalSyncSelectEvent

=================================
*/
class CUIVerticalSyncSelectEvent: public CUISettingsEventBase
{
public:
	explicit CUIVerticalSyncSelectEvent( CUISettingsWindow* pWindow ):
		CUISettingsEventBase(pWindow)
	{ };
	virtual ~CUIVerticalSyncSelectEvent( void ) { };

public:
	// Performs the action
	virtual void PerformAction( float param );
};

/*
=================================
CUIFramebufferObjectsSelectEvent

=================================
*/
class CUIFramebufferObjectsSelectEvent : public CUISettingsEventBase
{
public:
	explicit CUIFramebufferObjectsSelectEvent( CUISettingsWindow* pWindow ):
		CUISettingsEventBase(pWindow)
	{ };
	virtual ~CUIFramebufferObjectsSelectEvent( void ) { };

public:
	// Performs the action
	virtual void PerformAction( float param );
};

/*
=================================
CUISettingsWindow

=================================
*/
class CUISettingsWindow : public CUIWindow
{
private:
	struct adv_choice_t
	{
		CString name;
		CString value;
	};

	struct scrollsurf_option_t
	{
		scrollsurf_option_t():
			type(UI_OBJECT_UNDEFINED),
			minvalue(0),
			maxvalue(0)
			{}

		ui_object_type_t type;

		CString cvarname;
		CString optiondesc;

		CArray<adv_choice_t> choices;

		float minvalue;
		float maxvalue;

		CString defaultvalue;
	};

	struct setting_t
	{
		// Unique identifier
		CString id;
		// Command to execute on "apply"
		CString cmd;
	};

public:
	// Window description file
	static const char WINDOW_DESC_FILE[];
	// Window object name
	static const char WINDOW_OBJ_NAME[];
	// Apply button object name
	static const char APPLY_BUTTON_OBJ_NAME[];
	// Cancel button object name
	static const char CANCEL_BUTTON_OBJ_NAME[];
	// Settings tab object name
	static const char SETTINGS_TAB_OBJ_NAME[];
	// Binds list tab object name
	static const char BINDSTAB_LIST_OBJ_NAME[];
	// Binds tab clear button object name
	static const char BINDSTAB_CLEAR_BTN_OBJ_NAME[];
	// Binds tab bind button object name
	static const char BINDSTAB_BIND_BTN_OBJ_NAME[];
	// Binds tab restore defaults button object name
	static const char BINDSTAB_RESTORE_DEFAULTS_BTN_OBJ_NAME[];
	// Video tab display device label object name
	static const char VIDEOTAB_DISPLAY_DEVICE_LABEL_OBJ_NAME[];
	// Video tab display device label object name
	static const char VIDEOTAB_RESOLUTION_LABEL_OBJ_NAME[];
	// Video tab display device label object name
	static const char VIDEOTAB_WINDOW_MODE_LABEL_OBJ_NAME[];
	// Video tab anisotropy label object name
	static const char VIDEOTAB_ANISOTROPY_LABEL_OBJ_NAME[];
	// Video tab antialias label object name
	static const char VIDEOTAB_ANTIALIAS_LABEL_OBJ_NAME[];
	// Video tab vertical sync label object name
	static const char VIDEOTAB_VERTICAL_SYNC_LABEL_OBJ_NAME[];
	// Advance tab list object name
	static const char ADVANCED_TAB_LIST_OBJ_NAME[];
	// Video tab display device dropdown list object name
	static const char VIDEOTAB_DISPLAY_DEVICE_LIST_OBJ_NAME[];
	// Video tab display resolution dropdown list object name
	static const char VIDEOTAB_DISPLAY_RESOLUTION_LIST_OBJ_NAME[];
	// Video tab display resolution dropdown list object name
	static const char VIDEOTAB_DISPLAY_WINDOWMODE_LIST_OBJ_NAME[];
	// Video tab display gamma label object name
	static const char VIDEOTAB_GAMMA_LABEL_OBJ_NAME[];
	// Video tab display gamma slider object name
	static const char VIDEOTAB_GAMMA_SLIDER_OBJ_NAME[];
	// Video tab anisotropy dropdown list object name
	static const char VIDEOTAB_ANISOTROPY_LIST_OBJ_NAME[];
	// Video tab antialiasing dropdown list object name
	static const char VIDEOTAB_ANTIALIAS_LIST_OBJ_NAME[];
	// Video tab vertical sync dropdown list object name
	static const char VIDEOTAB_VERTICAL_SYNC_LIST_OBJ_NAME[];
	// Video tab framebuffer object label object name
	static const char VIDEOTAB_FRAMEBUFFER_OBJECTS_LABEL_OBJ_NAME[];
	// Video tab framebuffer object dropdown list object name
	static const char VIDEOTAB_FRAMEBUFFER_OBJECTS_LIST_OBJ_NAME[];
	// Video tab high dynamic range label object name
	static const char VIDEOTAB_HIGH_DYNAMIC_RANGE_LABEL_OBJ_NAME[];
	// Video tab high dynamic range dropdown list object name
	static const char VIDEOTAB_HIGH_DYNAMIC_RANGE_LIST_OBJ_NAME[];
	// Advanced tab options list file
	static const char ADVANCED_DESC_FILE[];
	// Scrollable options surface label object
	static const char SCROLLSURFACE_OPTION_LABEL_OBJ_NAME[];
	// Scrollable options surface list object
	static const char SCROLLSURFACE_OPTION_LIST_OBJ_NAME[];
	// Scrollable options surface tab object
	static const char SCROLLSURFACE_OPTION_TAB_OBJ_NAME[];

	// "Reverse Mouse" tickbox object name
	static const char MOUSE_TAB_REVERSE_MOUSE_BOX_OBJ_NAME[];
	// "Reverse Mouse" label object name
	static const char MOUSE_TAB_REVERSE_MOUSE_LABEL_OBJ_NAME[];
	// Auto-aim tickbox object name
	static const char MOUSE_TAB_FILTER_MOUSE_BOX_OBJ_NAME[];
	// Auto-aim label object name
	static const char MOUSE_TAB_FILTER_MOUSE_LABEL_OBJ_NAME[];
	// Auto-aim tickbox object name
	static const char MOUSE_TAB_AUTOAIM_BOX_OBJ_NAME[];
	// Auto-aim label object name
	static const char MOUSE_TAB_AUTOAIM_LABEL_OBJ_NAME[];
	// Raw input tickbox object name
	static const char MOUSE_TAB_RAWINPUT_BOX_OBJ_NAME[];
	// Raw input label object name
	static const char MOUSE_TAB_RAWINPUT_LABEL_OBJ_NAME[];
	// Mouse sensitivity slider object name
	static const char MOUSE_TAB_SENSITIVITY_SLIDER_OBJ_NAME[];
	// Mouse sensitivity slider object name
	static const char MOUSE_TAB_SENSITIVITY_LABEL_OBJ_NAME[];
	// Mouse sensitivity value tab object name
	static const char MOUSE_TAB_SENSITIVITY_TAB_OBJ_NAME[];
	// Mouse sensitivity value text object name
	static const char MOUSE_TAB_SENSITIVITY_TEXT_OBJ_NAME[];
	// Mouse filter frames slider object name
	static const char MOUSE_TAB_FILTER_FRAMES_SLIDER_OBJ_NAME[];
	// Mouse filter frames slider object name
	static const char MOUSE_TAB_FILTER_FRAMES_LABEL_OBJ_NAME[];
	// Mouse filter frames value tab object name
	static const char MOUSE_TAB_FILTER_FRAMES_TAB_OBJ_NAME[];
	// Mouse filter frames value text object name
	static const char MOUSE_TAB_FILTER_FRAMES_TEXT_OBJ_NAME[];
	// Mouse sensitivity value tab object name
	static const char AUDIO_TAB_MASTER_VOLUME_LABEL_OBJ_NAME[];
	// Mouse sensitivity value text object name
	static const char AUDIO_TAB_MASTER_VOLUME_SLIDER_OBJ_NAME[];
	// Game volume label object name
	static const char AUDIO_TAB_GAME_VOLUME_LABEL_OBJ_NAME[];
	// Game volume slider object name
	static const char AUDIO_TAB_GAME_VOLUME_SLIDER_OBJ_NAME[];
	// Mouse sensitivity value tab object name
	static const char AUDIO_TAB_MUSIC_VOLUME_LABEL_OBJ_NAME[];
	// Mouse sensitivity value text object name
	static const char AUDIO_TAB_MUSIC_VOLUME_SLIDER_OBJ_NAME[];
	// Sound occlusion text object name
	static const char AUDIO_TAB_OCCLUSION_LABEL_OBJ_NAME[];
	// Sound occlusion tick box object name
	static const char AUDIO_TAB_OCCLUSION_TICKBOX_OBJ_NAME[];
	// HRTF text object name
	static const char AUDIO_TAB_HRTF_LABEL_OBJ_NAME[];
	// HRTF tick box object name
	static const char AUDIO_TAB_HRTF_TICKBOX_OBJ_NAME[];
	// Subtitles text object name
	static const char AUDIO_TAB_SUBTITLES_LABEL_OBJ_NAME[];
	// Subtitles tick box object name
	static const char AUDIO_TAB_SUBTITLES_TICKBOX_OBJ_NAME[];
	// Binds file path
	static const char BINDS_FILE_PATH[];

	// View bob slider object name
	static const char GAMEPLAY_TAB_VIEWBOB_SLIDER_OBJ_NAME[];
	// View boby slider object name
	static const char GAMEPLAY_TAB_VIEWBOB_LABEL_OBJ_NAME[];
	// View bob value tab object name
	static const char GAMEPLAY_TAB_VIEWBOB_TAB_OBJ_NAME[];
	// View bob value text object name
	static const char GAMEPLAY_TAB_VIEWBOB_TEXT_OBJ_NAME[];

	// View roll slider object name
	static const char GAMEPLAY_TAB_VIEWROLL_SLIDER_OBJ_NAME[];
	// View roll slider object name
	static const char GAMEPLAY_TAB_VIEWROLL_LABEL_OBJ_NAME[];
	// View roll value tab object name
	static const char GAMEPLAY_TAB_VIEWROLL_TAB_OBJ_NAME[];
	// Gameplay tab list object name
	static const char GAMEPLAY_TAB_LIST_OBJ_NAME[];
	// View roll value text object name
	static const char GAMEPLAY_TAB_VIEWROLL_TEXT_OBJ_NAME[];

	// FOV slider object name
	static const char GAMEPLAY_TAB_FOV_SLIDER_OBJ_NAME[];
	// FOV slider object name
	static const char GAMEPLAY_TAB_FOV_LABEL_OBJ_NAME[];
	// FOV value tab object name
	static const char GAMEPLAY_TAB_FOV_TAB_OBJ_NAME[];
	// FOV value text object name
	static const char GAMEPLAY_TAB_FOV_TEXT_OBJ_NAME[];

	// Gameplay tab options list file
	static const char GAMEPLAY_DESC_FILE[];

private:
	CUISettingsWindow( Int32 flags, UInt32 width, UInt32 height, Int32 originx, Int32 originy );
public:
	~CUISettingsWindow( void );

public:
	// Creates an instance of the console window
	static CUISettingsWindow* CreateInstance( void );
	// Returns the current instance of the console window
	static CUISettingsWindow* GetInstance( void );
	// Destroys the current instance
	static void DestroyInstance( void );

public:
	// Applies all queued changes
	void ApplyChanges( void );
	// Sets the current tab's index
	void SetCurrentTabIndex( Int32 index ) { m_currentTabIndex = index; }

	// Deletes a key and it's binding
	void ClearSelectedKey( void );
	// Enters bind mode with the selected key
	void BindSelectedKey( void );

	// Manages a changed tick box
	void CVarChanged( const char* pstrCvarName, float value );

private:
	// Sets up the Binds tab
	CUITabBody* InitVideoTab( CUITabList* pTabList, const ui_windowdescription_t* pWinDesc, const ui_objectinfo_t* pTabObject );
	// Populates the resolutions tab
	void PopulateResolutions( Int32 deviceIndex );
	// Populates the MSAA list
	void PopulateMSAAList( void );

public:
	// Selects a display device
	void SelectDevice( Int32 deviceIndex );
	// Selects a resolution
	void SelectResolution( Int32 resIndex );
	// Selects a window mode
	void SelectWindowMode( Int32 modeIdx );
	// Selects an anisotropy setting
	void SelectAnisotropy( Int32 anisotropyIdx );
	// Selects an anti-alias setitng
	void SelectAntiAliasSetting( Int32 msaaSetting );
	// Selects a vsync setitng
	void SelectVerticalSyncSetting( Int32 setting );
	// Selects an FBO setting
	void SelectFramebufferObjectsSetting( Int32 setting );

private:
	// Sets up the Binds tab
	CUITabBody* InitBindsTab( CUITabList* pTabList, const ui_windowdescription_t* pWinDesc, const ui_objectinfo_t* pTabObject );
	// Loads the binds list
	void LoadBindsList( void );
	// Resets the binds list
	void ResetBindsList( void );

	// Sets the binding for a key on a row
	virtual void SetBind( const char* pstrKeyname, const char* pstrBind );

public:
	// Sets focus on a particular row
	void SetFocusOnBindsRow( UInt32 rowIndex );
	// Enters bind mode
	void EnterBindMode( UInt32 rowIndex );
	// Leaves bind mode
	void LeaveBindMode( void );
	// Restores default key binds
	void RestoreDefaultBinds( void );

private:
	// Inits the Advanced tab
	CUITabBody* InitAdvancedTab( CUITabList* pTabList, const ui_windowdescription_t* pWinDesc, const ui_objectinfo_t* pTabObject );
	// Inits the mouse tab
	CUITabBody* InitMouseTab( CUITabList* pTabList, const ui_windowdescription_t* pWinDesc, const ui_objectinfo_t* pTabObject );
	// Inits the audio tab
	CUITabBody* InitAudioTab( CUITabList* pTabList, const ui_windowdescription_t* pWinDesc, const ui_objectinfo_t* pTabObject );
	// Inits the gameplay tab
	CUITabBody* InitGameplayTab( CUITabList* pTabList, const ui_windowdescription_t* pWinDesc, const ui_objectinfo_t* pTabObject );

private:
	// Adds a checkbox object
	bool AddTickBox( CUITabBody* pTab, const ui_windowdescription_t* pWinDesc, const ui_objectinfo_t* pTabObject, const CString& tickBoxObjectName, const CString& labelObjectName, const CString& cvarName, const char* pstrConfigGrpName = nullptr, const char* pstrConfigValueName = nullptr );
	// Loads a scrollable options list
	bool LoadScrollableOptionsList( CUITabBody* pTab, const ui_windowdescription_t* pWinDesc, const ui_objectinfo_t* pTabObject, const char* pstrTabObjectName, const char* pstrOptionsFilename );

public:
	// Selects a resolution
	void AdvancedOptionSelect( UInt32 rowIndex, UInt32 selectionIndex );
	// Sets mouse sensitivity tab text
	void SetMouseSensitivityTabText( const char* pstrText );
	// Sets mouse filter frames tab text
	void SetMouseFilterFramesTabText( const char* pstrText );

	// Sets view roll tab text
	void SetViewBobTabText( const char* pstrText );
	// Sets view roll tab text
	void SetViewRollTabText( const char* pstrText );
	// Sets FOV tab text
	void SetFOVTabText( const char* pstrText );

public:
	// Toggles ontop flag for a row in the Advanced Options tab
	void SetAdvancedOptionFocus( UInt32 rowIndex, bool isOpen );

private:
	// Adds a pending setting to be executed later
	void AddPendingSetting( const char* pstrId, const char* pstrCmd );

public:
	// Loads the schema, and creates the sub-elements
	virtual bool init( const ui_windowdescription_t* pWinDesc, const ui_objectinfo_t* pWindowObject );
	// The settings window cannot be resized
	virtual bool isResizable( void ) { return false; }

	// Handles a mosue wheel event
	virtual bool mouseWheelEvent( Int32 mouseX, Int32 mouseY, Int32 button, bool keyDown, Int32 scroll );
	// Handles a mouse button event
	virtual bool mouseButtonEvent( Int32 mouseX, Int32 mouseY, Int32 button, bool keyDown );
	// Handles a keyboard input event
	virtual bool keyEvent( Int32 button, Int16 mod, bool keyDown );

	// Manages post-command think functionalities
	virtual void postThink( void );

private:
	// Resolution dropdown list
	CUIDropDownList* m_pResolutionDropList;
	// MSAA dropdown list
	CUIDropDownList* m_pMSAADropList;

private:
	// Binds list object
	CUIList* m_pBindsList;
	// Binds list info object
	const ui_objectinfo_t* m_pBindsListInfo;
	// true if we're in key bind mode
	bool m_isInBindMode;
	// Row we're about to bind a key to
	Int32 m_bindRowIndex;
	// Selected row index
	Int32 m_selectedRowIndex;

	// Actions tied to specific rows
	CArray<CString> m_bindsCommandArray;

private:
	// Binds tab index
	Int32 m_bindsTabIndex;
	// Current tab's index
	Int32 m_currentTabIndex;
	// Array of commands to run on "Apply"
	CArray<setting_t> m_queuedCommandsArray;
	// true if we need to reset next frame
	bool m_bReset;

	// Current display device index
	Int32 m_displayDeviceIndex;
	// Current resolution index
	Int32 m_resolutionIndex;
	// Current MSAA setting
	Int32 m_msaaIndex;

	// true if we need to reset the video
	bool m_bResetVideo;

private:
	// Array of advanced options
	CArray<scrollsurf_option_t> m_scrollSurfaceOptionsArray;
	// Advanced option object array
	CArray<CUIInteractiveObject*> m_scrollSurfaceOptionsRowObjects;

	// Array of advanced options
	CArray<scrollsurf_option_t> m_gameplayOptions;
	// Advanced option object array
	CArray<CUIInteractiveObject*> m_gameplayOptionRowObjects;

	// Mouse sensitivity display tab
	CUIText* m_pSensitivityValueText;
	// Mouse sensitivity display tab
	CUIText* m_pFilterFramesValueText;

	// View bob display tab
	CUIText* m_pViewBobValueText;
	// View roll display tab
	CUIText* m_pViewRollValueText;
	// FOV display tab
	CUIText* m_pFOVValueText;

public:
	// Current instance
	static CUISettingsWindow* m_pInstance;
};

#endif //UISETTINGSWINDOW_H