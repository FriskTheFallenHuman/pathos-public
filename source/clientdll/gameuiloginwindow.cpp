/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#include "includes.h"
#include "huddraw.h"
#include "r_interface.h"
#include "clientdll.h"
#include "fontset.h"

#include "gameuiloginwindow.h"
#include "gameuiwindows_shared.h"
#include "snd_shared.h"

// Object x inset for login window
const UInt32 CGameUILoginWindow::LOGINWINDOW_TAB_X_INSET = 30;
// Object y inset for login window
const UInt32 CGameUILoginWindow::LOGINWINDOW_TAB_Y_INSET = 60;
// Object y spacing for login window
const UInt32 CGameUILoginWindow::LOGINWINDOW_TAB_Y_SPACING = 30;
// Object x spacing for login window
const UInt32 CGameUILoginWindow::LOGINWINDOW_TAB_X_SPACING = 80;
// Space before info tab on y axis for login window
const UInt32 CGameUILoginWindow::LOGINWINDOW_INFO_TAB_Y_SPACING = 10;
// Input tab width
const UInt32 CGameUILoginWindow::LOGINWINDOW_INPUT_TAB_WIDTH = 300;
// Input tab height
const UInt32 CGameUILoginWindow::LOGINWINDOW_INPUT_TAB_HEIGHT = 100;
// Input tab text inset
const UInt32 CGameUILoginWindow::LOGINWINDOW_INPUT_TAB_TEXT_INSET = 15;
// Default text color
const color32_t CGameUILoginWindow::LOGINWINDOW_TEXT_COLOR = color32_t(255, 255, 255, 255);
// Default text color
const color32_t CGameUILoginWindow::LOGINWINDOW_NOTES_INFO_TEXT_COLOR = color32_t(30, 30, 255, 255);
// Default text color
const color32_t CGameUILoginWindow::LOGINWINDOW_PROMPT_FAIL_TEXT_COLOR = color32_t(255, 30, 30, 255);
// Default text color
const color32_t CGameUILoginWindow::LOGINWINDOW_PROMPT_SUCCESS_TEXT_COLOR = color32_t(30, 255, 30, 255);
// Button y spacing for login window
const UInt32 CGameUILoginWindow::LOGINWINDOW_BUTTON_X_SPACING = 20;
// Prompt text lifetime
const double CGameUILoginWindow::LOGINWINDOW_PROMPT_LIFETIME = 3;
// Title text default schema set name
const char CGameUILoginWindow::LOGINWINDOW_TITLE_TEXTSCHEMA_NAME[] = "logintitle";
// Text default font schema name
const char CGameUILoginWindow::LOGINWINDOW_TEXTSCHEMA_NAME[] = "logintext";

//====================================
//
//====================================
CGameUILoginWindow::CGameUILoginWindow( Int32 flags, Int32 originX, Int32 originY, UInt32 width, UInt32 height ):
	CGameUIWindow(flags, originX, originY, width, height),
	m_pUsernameField(nullptr),
	m_pPasswordField(nullptr),
	m_pPromptText(nullptr),
	m_promptTextTime(0),
	m_loginWindowTime(0),
	m_pInfoLabelUsername(nullptr),
	m_pTextUsername(nullptr),
	m_pInfoLabelPassword(nullptr),
	m_pTextPassword(nullptr),
	m_loginSuccessful(false),
	m_stayTillNextWindow(false),
	m_messageSendTime(0)
{
}

//====================================
//
//====================================
CGameUILoginWindow::~CGameUILoginWindow( void )
{
}

//====================================
//
//====================================
void CGameUILoginWindow::init( void )
{
	// Init basic window elements
	UInt32 verticalbarheight, middlebarwidth, barThickness;
	CGameUIWindow::initBackground(verticalbarheight, middlebarwidth, barThickness);

	UInt32 tabTopInset = gHUDDraw.ScaleX(GAMEUIWINDOW_TAB_TOP_INSET);
	UInt32 hBarYOrigin = gHUDDraw.ScaleY(GAMEUIWINDOW_H_BAR_Y_ORIGIN);
	UInt32 tabSideInset = gHUDDraw.ScaleX(GAMEUIWINDOW_TAB_SIDE_INSET);
	UInt32 mainTabMaxWidth = gHUDDraw.ScaleX(GAMEUIWINDOW_MAIN_TAB_MAX_WIDTH);
	UInt32 mainTabMaxHeight = gHUDDraw.ScaleY(GAMEUIWINDOW_MAIN_TAB_MAX_HEIGHT);
	UInt32 bottomInset = gHUDDraw.ScaleY(GAMEUIWINDOW_TAB_BOTTOM_INSET);
	UInt32 edgeThickness = gHUDDraw.ScaleX(GAMEUIWINDOW_EDGE_THICKNESS);
	UInt32 infoTabYSpacing = gHUDDraw.ScaleY(LOGINWINDOW_INFO_TAB_Y_SPACING);
	UInt32 inputTabWidth = gHUDDraw.ScaleX(LOGINWINDOW_INPUT_TAB_WIDTH);
	UInt32 tabYInset = gHUDDraw.ScaleY(LOGINWINDOW_TAB_Y_INSET);
	UInt32 inputTabHeight = gHUDDraw.ScaleY(LOGINWINDOW_INPUT_TAB_HEIGHT);
	UInt32 inputTabTextInset = gHUDDraw.ScaleY(LOGINWINDOW_INPUT_TAB_TEXT_INSET);
	UInt32 defaultButtonWidth = gHUDDraw.ScaleX(DEFAULT_BUTTON_WIDTH);
	UInt32 defaultButtonHeight = gHUDDraw.ScaleY(DEFAULT_BUTTON_HEIGHT);

	//
	// Create the title text object
	//
	UInt32 screenWidth, screenHeight;
	cl_renderfuncs.pfnGetScreenSize(screenWidth, screenHeight);

	const font_set_t* pTitleFont = cl_engfuncs.pfnGetResolutionSchemaFontSet(LOGINWINDOW_TITLE_TEXTSCHEMA_NAME, screenHeight);
	if(!pTitleFont)
		pTitleFont = gGameUIManager.GetDefaultFontSet();

	UInt32 textYOrigin = hBarYOrigin + tabTopInset/2.0f;
	CGameUIText *pTitleText = new CGameUIText(CGameUIObject::FL_ALIGN_CH, GAMEUIWINDOW_DEFAULT_TEXT_COLOR, pTitleFont, 0, textYOrigin);
	pTitleText->setParent(this);

	// Set default text
	pTitleText->setText("Log in to computer");

	//
	// Create the tab objects
	//
	UInt32 tabWidth = middlebarwidth - barThickness*2 - tabSideInset*2;
	if(tabWidth > mainTabMaxWidth)
		tabWidth = mainTabMaxWidth;

	UInt32 tabOriginX = m_width / 2.0 - tabWidth / 2.0;

	UInt32 tabTotalHeight = verticalbarheight - tabTopInset - bottomInset;
	if(tabTotalHeight > mainTabMaxHeight)
		tabTotalHeight = mainTabMaxHeight;

	UInt32 upperTabHeight = tabTotalHeight * 0.75;

	CGameUISurface* pMainTab = new CGameUISurface(CGameUIObject::FL_NONE,
		edgeThickness, 
		GAMEUIWINDOW_MAIN_TAB_COLOR,
		GAMEUIWINDOW_MAIN_TAB_BG_COLOR,
		tabOriginX,
		hBarYOrigin + barThickness + tabTopInset,
		tabWidth,
		upperTabHeight);
	pMainTab->setParent(this);

	UInt32 lowerTabHeight = tabTotalHeight - upperTabHeight;

	CGameUISurface* pNotesTab = new CGameUISurface(CGameUIObject::FL_NONE,
		edgeThickness, 
		GAMEUIWINDOW_MAIN_TAB_COLOR,
		GAMEUIWINDOW_MAIN_TAB_BG_COLOR,
		tabOriginX,
		hBarYOrigin + barThickness + tabTopInset + upperTabHeight + infoTabYSpacing,
		tabWidth,
		lowerTabHeight);
	pNotesTab->setParent(this);

	//
	// Create the username tab text
	//
	Int32 inputTabXOrigin = pMainTab->getWidth() / 2 - inputTabWidth / 2;
	Int32 inputTabYOrigin = tabYInset;

	const font_set_t* pFontSet = cl_engfuncs.pfnGetResolutionSchemaFontSet(LOGINWINDOW_TEXTSCHEMA_NAME, screenHeight);
	if(!pFontSet)
		pFontSet = gGameUIManager.GetDefaultFontSet();

	CGameUIText* pUsernameText = new CGameUIText(CGameUIObject::FL_NONE, LOGINWINDOW_TEXT_COLOR, pFontSet, inputTabXOrigin, inputTabYOrigin);
	pUsernameText->setParent(pMainTab);
	pUsernameText->setText("Username");

	inputTabYOrigin += pFontSet->fontsize;

	//
	// Create the username input tab
	//
	CGameUILoginWindowCallbackEvent *pUsernameEvent = new CGameUILoginWindowCallbackEvent(this, LOGINWINDOW_EVENT_USERNAMETAB);
	m_pUsernameField = new CGameUITextInputTab(CGameUIObject::FL_NONE, 
		pUsernameEvent, 
		inputTabTextInset,
		edgeThickness, 
		GAMEUIWINDOW_MAIN_TAB_COLOR,
		GAMEUIWINDOW_MAIN_TAB_BG_COLOR,
		GAMEUIWINDOW_BUTTON_HIGHLIGHT_COLOR,
		pFontSet,
		inputTabXOrigin,
		inputTabYOrigin,
		inputTabWidth,
		inputTabHeight);
	m_pUsernameField->setParent(pMainTab);

	inputTabYOrigin += inputTabHeight + LOGINWINDOW_TAB_Y_SPACING;

	//
	// Create the password tab text
	//
	CGameUIText* pPasswordText = new CGameUIText(CGameUIObject::FL_NONE, LOGINWINDOW_TEXT_COLOR, pFontSet, inputTabXOrigin, inputTabYOrigin);
	pPasswordText->setParent(pMainTab);
	pPasswordText->setText("Password");

	inputTabYOrigin += pFontSet->fontsize;

	//
	// Create the password input tab
	//
	CGameUILoginWindowCallbackEvent *pPasswordEvent = new CGameUILoginWindowCallbackEvent(this, LOGINWINDOW_EVENT_PASSWORDTAB);
	m_pPasswordField = new CGameUITextInputTab(CGameUIObject::FL_NONE, 
		pPasswordEvent, 
		inputTabTextInset,
		edgeThickness, 
		GAMEUIWINDOW_MAIN_TAB_COLOR,
		GAMEUIWINDOW_MAIN_TAB_BG_COLOR,
		GAMEUIWINDOW_BUTTON_HIGHLIGHT_COLOR,
		pFontSet,
		inputTabXOrigin,
		inputTabYOrigin,
		inputTabWidth,
		inputTabHeight);
	m_pPasswordField->setParent(pMainTab);

	Int32 promptTextYPos = inputTabYOrigin + inputTabHeight + LOGINWINDOW_TAB_Y_SPACING;
	m_pPromptText = new CGameUIText(CGameUIObject::FL_ALIGN_CH, 
		LOGINWINDOW_NOTES_INFO_TEXT_COLOR,
		pFontSet,
		0,
		promptTextYPos);
	m_pPromptText->setParent(pMainTab);
	m_pPromptText->setVisible(false);

	//
	// Create the "Login" button
	//
	CGameUILoginWindowCallbackEvent* pLoginEvent = new CGameUILoginWindowCallbackEvent(this, LOGINWINDOW_EVENT_LOGIN_BTN);

	Int32 buttonXOrigin = pMainTab->getWidth() / 2 - LOGINWINDOW_BUTTON_X_SPACING / 2 - defaultButtonWidth;
	Int32 buttonYOrigin = pMainTab->getHeight() - tabYInset - defaultButtonHeight;

	CGameUIButton* pLoginButton = new CGameUIButton(CGameUIObject::FL_NONE, 
		pLoginEvent, 
		SDLK_RETURN,
		edgeThickness,
		GAMEUIWINDOW_MAIN_TAB_COLOR,
		GAMEUIWINDOW_MAIN_TAB_BG_COLOR,
		GAMEUIWINDOW_BUTTON_HIGHLIGHT_COLOR,
		buttonXOrigin,
		buttonYOrigin,
		defaultButtonWidth,
		defaultButtonHeight);

	pLoginButton->setText("Log in");
	pLoginButton->setParent(pMainTab);

	//
	// Create the "Cancel" button
	//
	CGameUILoginWindowCallbackEvent* pCancelEvent = new CGameUILoginWindowCallbackEvent(this, LOGINWINDOW_EVENT_CANCEL_BTN);

	buttonXOrigin = pMainTab->getWidth() / 2 + LOGINWINDOW_BUTTON_X_SPACING / 2;

	CGameUIButton* pCancelButton = new CGameUIButton(CGameUIObject::FL_NONE, 
		pCancelEvent, 
		SDLK_ESCAPE,
		edgeThickness,
		GAMEUIWINDOW_MAIN_TAB_COLOR,
		GAMEUIWINDOW_MAIN_TAB_BG_COLOR,
		GAMEUIWINDOW_BUTTON_HIGHLIGHT_COLOR,
		buttonXOrigin,
		buttonYOrigin,
		defaultButtonWidth,
		defaultButtonHeight);

	pCancelButton->setText("Cancel");
	pCancelButton->setParent(pMainTab);

	//
	// Set the "Notes" tab objects
	//
	
	// Create notes title text
	CGameUIText* pNotesText = new CGameUIText(CGameUIObject::FL_ALIGN_CH, 
		LOGINWINDOW_TEXT_COLOR, 
		pTitleFont, 
		0, 
		pTitleFont->fontsize);
	pNotesText->setParent(pNotesTab);
	pNotesText->setText("Notes");

	// Create the "username" field label
	Int32 labelXPos = LOGINWINDOW_TAB_X_INSET;
	Int32 labelYPos = tabYInset + pNotesText->getHeight();

	m_pInfoLabelUsername = new CGameUIText(CGameUIObject::FL_NONE, 
		LOGINWINDOW_TEXT_COLOR,
		pFontSet, 
		labelXPos,
		labelYPos);
	m_pInfoLabelUsername->setParent(pNotesTab);
	m_pInfoLabelUsername->setText("Username: ");
	m_pInfoLabelUsername->setVisible(false);

	Int32 fieldXPos = labelXPos + m_pInfoLabelUsername->getWidth();

	// Create "username" data field
	m_pTextUsername = new CGameUIText(CGameUIObject::FL_NONE,
		LOGINWINDOW_NOTES_INFO_TEXT_COLOR,
		pFontSet, fieldXPos, labelYPos);
	m_pTextUsername->setParent(pNotesTab);
	m_pTextUsername->setVisible(false);

	// Create the "password" label
	labelXPos = LOGINWINDOW_TAB_X_INSET;
	labelYPos += m_pTextUsername->getHeight() + LOGINWINDOW_TAB_Y_SPACING;

	m_pInfoLabelPassword = new CGameUIText(CGameUIObject::FL_NONE, 
		LOGINWINDOW_TEXT_COLOR,
		pFontSet, 
		labelXPos,
		labelYPos);
	m_pInfoLabelPassword->setParent(pNotesTab);
	m_pInfoLabelPassword->setText("Password: ");
	m_pInfoLabelPassword->setVisible(false);

	fieldXPos = labelXPos + m_pInfoLabelPassword->getWidth();

	// Create "username" data field
	m_pTextPassword = new CGameUIText(CGameUIObject::FL_NONE,
		LOGINWINDOW_NOTES_INFO_TEXT_COLOR,
		pFontSet, fieldXPos, labelYPos);
	m_pTextPassword->setParent(pNotesTab);
	m_pTextPassword->setVisible(false);

	// Set input focus to username input tab
	setInputFocusObject(m_pUsernameField);
}

//====================================
//
//====================================
bool CGameUILoginWindow::initData( const char* pstrUsername, const char* pstrPassword, const char* pstrUsernameInput, const char* pstrPasswordInput, bool stayTillNext )
{
	// Set the info labels to be visible
	if(pstrUsername && qstrlen(pstrUsername) > 0 && pstrPassword && qstrlen(pstrPassword) > 0)
	{
		m_pInfoLabelUsername->setVisible(true);
		m_pTextUsername->setText(pstrUsername);
		m_pTextUsername->setVisible(true);

		m_username = pstrUsername;

		m_pInfoLabelPassword->setVisible(true);
		m_pTextPassword->setText(pstrPassword);
		m_pTextPassword->setVisible(true);

		m_password = pstrPassword;
	}

	if(pstrUsernameInput)
		m_pUsernameField->setText(pstrUsernameInput);

	if(pstrPasswordInput)
		m_pPasswordField->setText(pstrPasswordInput);

	m_stayTillNextWindow = stayTillNext;
	if(m_stayTillNextWindow)
		m_windowFlags |= FL_WINDOW_WAIT_TILL_NEXT;

	return true;
}

//====================================
//
//====================================
void CGameUILoginWindow::getInformation( CString& username, CString& password, CString& usernameInput, CString& passwordInput, bool& stayTillNext )
{
	username = m_username;
	password = m_password;
	stayTillNext = m_stayTillNextWindow;

	usernameInput = m_pUsernameField->getText();
	passwordInput = m_pPasswordField->getText();
}

//====================================
//
//====================================
void CGameUILoginWindow::ManageEvent( loginwindowevent_t event )
{
	switch(event)
	{
	case LOGINWINDOW_EVENT_USERNAMETAB:
		break;
	case LOGINWINDOW_EVENT_PASSWORDTAB:
		break;
	case LOGINWINDOW_EVENT_LOGIN_BTN:
		{
			double time = cl_engfuncs.pfnGetClientTime();
			const char* pstrInputUsername = m_pUsernameField->getText();
			const char* pstrInputPassword = m_pPasswordField->getText();

			if(!m_password.empty() && !qstrcmp(pstrInputUsername, m_username) && !qstrcmp(pstrInputPassword, m_password))
			{
				cl_engfuncs.pfnPlayAmbientSound(0, ZERO_VECTOR, SND_CHAN_AUTO, GAMEUI_OK_SOUND, VOL_NORM, ATTN_NORM, PITCH_NORM, SND_FL_2D, 0);

				m_pPromptText->setText("Login attempt successful.");
				m_pPromptText->setColor(LOGINWINDOW_PROMPT_SUCCESS_TEXT_COLOR);
				m_pPromptText->setVisible(true);
				m_promptTextTime = time + LOGINWINDOW_PROMPT_LIFETIME;

				setDelayedRemoval(GAMEUIWINDOW_REMOVE_DELAY_TIME);
				m_loginSuccessful = true;
				return;
			}
			else
			{
				cl_engfuncs.pfnPlayAmbientSound(0, ZERO_VECTOR, SND_CHAN_AUTO, GAMEUI_FAIL_SOUND, VOL_NORM, ATTN_NORM, PITCH_NORM, SND_FL_2D, 0);

				m_pPromptText->setText("Login attempt failed: Wrong username or password.");
				m_pPromptText->setColor(LOGINWINDOW_PROMPT_FAIL_TEXT_COLOR);
				m_pPromptText->setVisible(true);

				m_promptTextTime = time + LOGINWINDOW_PROMPT_LIFETIME;
				return;
			}
		}
		break;
	case LOGINWINDOW_EVENT_CANCEL_BTN:
		m_windowFlags |= CGameUIWindow::FL_WINDOW_KILLME;
		break;
	}
}

//====================================
//
//====================================
void CGameUILoginWindow::think( void )
{
	if(m_promptTextTime && m_promptTextTime <= cl_engfuncs.pfnGetClientTime())
	{
		m_pPromptText->setVisible(false);
		m_promptTextTime = 0;
	}

	if(m_messageSendTime && m_messageSendTime <= cl_engfuncs.pfnGetClientTime())
	{
		onRemove();
		m_messageSendTime = 0;
	}

	// Call base class to manage think functions
	CGameUIWindow::think();
}

//====================================
//
//====================================
void CGameUILoginWindow::setDelayedRemoval( double delay )
{
	if(m_windowFlags & FL_WINDOW_WAIT_TILL_NEXT)
		m_messageSendTime = cl_engfuncs.pfnGetClientTime() + delay;

	CGameUIWindow::setDelayedRemoval(delay);
}

//====================================
//
//====================================
void CGameUILoginWindow::onRemove( void ) 
{
	if(!m_loginSuccessful)
		return;

	// Send message to server
	UInt32 msgid = g_pGUIManager->GetServerUIMessageId();
	if(!msgid)
	{
		cl_engfuncs.pfnCon_Printf("%s - Message 'GameUIMessage' not registered on client.\n", __FUNCTION__);
		return;
	}

	// Just tell them which window sent it
	cl_engfuncs.pfnClientUserMessageBegin(msgid);
		cl_engfuncs.pfnMsgWriteByte(GAMEUIEVENT_CODE_MATCHES);
		cl_engfuncs.pfnMsgWriteByte(GAMEUI_LOGINWINDOW);
	cl_engfuncs.pfnClientUserMessageEnd();
}

//====================================
//
//====================================
bool CGameUILoginWindow::keyEvent( Int32 button, Int16 mod, bool keyDown )
{
	// Get SDL Keycode
	SDL_Keycode sdlKeycode = SDL_GetKeyFromScancode((SDL_Scancode)button);

	if(keyDown && sdlKeycode == SDLK_TAB)
	{
		if(m_pUsernameField->isInputFocusObject())
			setInputFocusObject(m_pPasswordField);
		else
			setInputFocusObject(m_pUsernameField);

		return true;
	}

	return CGameUIWindow::keyEvent(button, mod, keyDown);
}

//====================================
//
//====================================
void CGameUILoginWindowCallbackEvent::PerformAction( float param )
{
	if(!m_pLoginWindow)
		return;

	m_pLoginWindow->ManageEvent(m_eventType);
}