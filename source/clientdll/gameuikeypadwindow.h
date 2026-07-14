/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef GAMEUIKEYPADWINDOW_H
#define GAMEUIKEYPADWINDOW_H

#include "gameuielements.h"

enum keypadbutton_t
{
	KEYPADWINDOW_BUTTON_CLEAR = 0,
	KEYPADWINDOW_BUTTON_DELETE,
	KEYPADWINDOW_BUTTON_CANCEL,
	KEYPADWINDOW_BUTTON_OK
};

/*
====================
CGameUIKeypadWindow

====================
*/
class CGameUIKeypadWindow : public CGameUIWindow
{
public:
	// Width of the keypad window tab
	static const UInt32 KEYPADWINDOW_TAB_WIDTH;
	// Height of the keypad window tab
	static const UInt32 KEYPADWINDOW_TAB_HEIGHT;
	// Width of the keypad window tab
	static const UInt32 KEYPADWINDOW_TAB_DISPLAY_HEIGHT;
	// Spacing between the buttons and digits of the keypad window
	static const UInt32 KEYPADWINDOW_ELEMENT_SPACING;
	// Notes tab height
	static const UInt32 KEYPADWINDOW_NOTES_TAB_HEIGHT;
	// Default text color
	static const color32_t KEYPADWINDOW_TEXT_COLOR;
	// Default text color
	static const color32_t KEYPADWINDOW_NOTES_INFO_TEXT_COLOR;
	// Default text color
	static const color32_t KEYPADWINDOW_PROMPT_FAIL_TEXT_COLOR;
	// Default text color
	static const color32_t KEYPADWINDOW_PROMPT_SUCCESS_TEXT_COLOR;
	// Button y spacing for login window
	static const UInt32 KEYPADWINDOW_BUTTON_Y_SPACING;
	// Prompt text lifetime
	static const double KEYPADWINDOW_PROMPT_LIFETIME;
	// Keypad window button height
	static const UInt32 KEYPADWINDOW_BUTTON_HEIGHT;
	// Title text default schema set name
	static const char KEYPADWINDOW_TITLE_TEXTSCHEMA_NAME[];
	// Text default font schema name
	static const char KEYPADWINDOW_TEXTSCHEMA_NAME[];

public:
	CGameUIKeypadWindow( Int32 flags, Int32 originX, Int32 originY, UInt32 width, UInt32 height );
	~CGameUIKeypadWindow();

public:
	// Initializes the window
	void init( void ) override;
	// Initializes the data
	bool initData( const char* pstrPasscode, const char* pstrInput, bool stayTillNext );

	// Think function for window
	void think( void ) override;
	// Called when window is removed
	void onRemove( void ) override;
	// Mark for delayed removal
	void setDelayedRemoval( double delay ) override;

public:
	// Returns the current window information
	void getInformation( CString& passcode, CString& input, bool& stayTillNext ) const;
	// Returns the type of the window
	virtual gameui_windows_t getWindowType( void ) const override { return GAMEUI_KEYPADWINDOW; }

public:
	// Manages a button event
	void ManageButtonEvent( keypadbutton_t event );
	// Manages a digit input event
	void ManageDigitButtonEvent( char digit );

private:
	// Text for the input
	CGameUIText* m_pKeypadDisplayText;
	// Label for passcode in Notes
	CGameUIText* m_pNotesPasscodeLabel;
	// Label for passcode in Notes
	CGameUIText* m_pNotesPasscode;

	// Passcode
	CString m_passcode;
	// Input code
	CString m_inputCode;
	// true if login was successful
	bool m_codeAccepted;
	// Time until prompt text resets
	double m_promptTextTime;
	// true if we should stay till next window spawn
	bool m_stayTillNextWindow;
	// Message send time
	double m_messageSendTime;

	// Label for passcode
	CGameUIText* m_pInfoLabelPasscode;
	// Text for passcode itself
	CGameUIText* m_pTextPasscode;
};

/*
=================================
CGameUIKeypadWindowButtonCallbackEvent

=================================
*/
class CGameUIKeypadWindowButtonCallbackEvent : public CGameUICallbackEvent
{
public:
	CGameUIKeypadWindowButtonCallbackEvent( CGameUIKeypadWindow* kKeypadWindow, keypadbutton_t button ):
		m_pKeypadWindow(kKeypadWindow),
		m_button(button)
	{ 
	};
	virtual ~CGameUIKeypadWindowButtonCallbackEvent( void ) { };

public:
	// Performs the action
	virtual void PerformAction( float param ) override;
	// Handles a special key event
	virtual bool KeyEvent( Int32 button, Int16 mod, bool keyDown ) override { return false; }
	// Handles a mouse button event
	virtual bool MouseButtonEvent( Int32 mouseX, Int32 mouseY, Int32 button, bool keyDown ) override { return false; }

private:
	// Text window object
	CGameUIKeypadWindow* m_pKeypadWindow;
	// Event type
	keypadbutton_t m_button;
};

/*
=================================
CGameUIKeypadWindowDigitCallbackEvent

=================================
*/
class CGameUIKeypadWindowDigitCallbackEvent : public CGameUICallbackEvent
{
public:
	CGameUIKeypadWindowDigitCallbackEvent( CGameUIKeypadWindow* pKeypadWindow, char digit ):
		m_pKeypadWindow(pKeypadWindow),
		m_digit(digit)
	{ 
	};
	virtual ~CGameUIKeypadWindowDigitCallbackEvent( void ) { };

public:
	// Performs the action
	virtual void PerformAction( float param ) override;
	// Handles a special key event
	virtual bool KeyEvent( Int32 button, Int16 mod, bool keyDown ) override { return false; }
	// Handles a mouse button event
	virtual bool MouseButtonEvent( Int32 mouseX, Int32 mouseY, Int32 button, bool keyDown ) override { return false; }

private:
	// Text window object
	CGameUIKeypadWindow* m_pKeypadWindow;
	// Event type
	char m_digit;
};

#endif //GAMEUIKEYPADWINDOW_H