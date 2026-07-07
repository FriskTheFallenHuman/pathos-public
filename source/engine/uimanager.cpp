/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#include "includes.h"
#include "file.h"
#include "window.h"
#include "input.h"

#include "texturemanager.h"
#include "r_main.h"
#include "r_vbo.h"
#include "r_glsl.h"
#include "r_basicdraw.h"
#include "r_text.h"
#include "r_interface.h"
#include "r_interfacefuncs.h"
#include "cl_utils.h"
#include "cl_main.h"

#include "uielements.h"
#include "uimanager.h"
#include "uiconsolewindow.h"
#include "system.h"
#include "enginestate.h"
#include "enginefuncs.h"
#include "textschemas.h"

// Default font schema of the game UI
const Char CUIManager::DEFAULT_TEXT_SCHEMA[] = "uidefault";

// Class definition
CUIManager gUIManager;

//=============================================
// @brief Constructor
//
//=============================================
CUIManager::CUIManager( void ):
	m_schemaManager(FL_GetInterface(), R_GetDummyTexture, R_LoadTexture),
	m_pFocusWindow(nullptr),
	m_currentFocusIndex(0),
	m_windowFilterFlags(CUIWindow::UIW_FL_NONE),
	m_pFontSet(nullptr)
{
}

//=============================================
// @brief Destructor
//
//=============================================
CUIManager::~CUIManager( void )
{
	Shutdown();
}

//=============================================
// @brief Initializes interfaces
//
//=============================================
void CUIManager::Init( void )
{
	m_pFontSet = gTextSchemas.GetResolutionSchemaFontSet(DEFAULT_TEXT_SCHEMA, gWindow.GetHeight());
	if(!m_pFontSet)
		m_pFontSet = gText.GetDefaultFont();

	// TODO: Get rid of this
	ui_engine_interface_t uiFuncs;

	// Set the interface
	uiFuncs.pfnGetEngineTime = Engine_GetEngineTime;
	uiFuncs.pfnCon_Printf = Con_Printf;
	uiFuncs.pfnCon_DPrintf = Con_DPrintf;
	uiFuncs.pfnCon_VPrintf = Con_VPrintf;
	uiFuncs.pfnCon_WPrintf = Con_WPrintf;
	uiFuncs.pfnCon_EPrintf = Con_EPrintf;
	uiFuncs.pfnGetMousePosition = CL_GetMousePosition;
	uiFuncs.pfnUILoadSchemaFile = CL_UILoadSchemaFile;
	uiFuncs.pfnBasicDrawIsActive = R_BasicDrawIsActive;
	uiFuncs.pfnEnableBasicDraw = R_EnableBasicDraw,
	uiFuncs.pfnDisableBasicDraw = R_DisableBasicDraw;
	uiFuncs.pfnBasicDrawEnableTextures = R_BasicDrawEnableTextures;
	uiFuncs.pfnBasicDrawDisableTextures = R_BasicDrawDisableTextures;
	uiFuncs.pfnBasicDrawBegin = R_BasicDrawBegin;
	uiFuncs.pfnBasicDrawEnd = R_BasicDrawEnd;
	uiFuncs.pfnBasicDrawColor4f = R_BasicDrawColor4f;
	uiFuncs.pfnBasicDrawColor4fv = R_BasicDrawColor4fv;
	uiFuncs.pfnBasicDrawTexCoord2f = R_BasicDrawTexCoord2f;
	uiFuncs.pfnBasicDrawTexCoord2fv = R_BasicDrawTexCoord2fv;
	uiFuncs.pfnBasicDrawVertex3f = R_BasicDrawVertex3f;
	uiFuncs.pfnBasicDrawVertex3fv = R_BasicDrawVertex3fv;
	uiFuncs.pfnBasicDrawSetProjection = R_BasicDrawSetProjection;
	uiFuncs.pfnBasicDrawSetModelView = R_BasicDrawSetModelView;
	uiFuncs.pfnBind2DTexture = R_Bind2DTexture;
	uiFuncs.pfnGetDefaultFontSet = R_GetDefaultFontSet;
	uiFuncs.pfnLoadFontSet = R_LoadFontSet;
	uiFuncs.pfnDrawSimpleString = R_DrawString;
	uiFuncs.pfnDrawStringBox = R_DrawStringBox;
	uiFuncs.pfnBeginTextRendering = R_BeginTextRendering;
	uiFuncs.pfnFinishTextRendering = R_FinishTextRendering;
	uiFuncs.pfnSetStringRectangle = R_SetStringRectangle;
	uiFuncs.pfnDrawCharacter = R_DrawCharacter;
	uiFuncs.pfnGetStringSize = R_GetStringSize;
	uiFuncs.pfnEstimateStringHeight = R_EstimateStringHeight;
	uiFuncs.pfnGetProjectionMatrix = R_GetProjectionMatrix;
	uiFuncs.pfnGetModelViewMatrix = R_GetModelViewMatrix;
	uiFuncs.pfnGetWindowSize = R_GetScreenSize;
	uiFuncs.pfnValidateBasicDraw = R_IF_ValidateBasicDraw;

	CUIObject::SetRenderInterface(uiFuncs);
}

//=============================================
// @brief Initializes interfaces
//
//=============================================
void CUIManager::OnGLInitialization( void )
{
	m_windowList.begin();
	while(!m_windowList.end())
	{
		CUIWindow* pWindow = m_windowList.get();
		pWindow->onGLInitialization();

		m_windowList.next();
	}
}

//=============================================
// @brief Destroys all active windows
//
//=============================================
void CUIManager::Shutdown( void )
{
	if(!m_windowList.empty())
	{
		m_windowList.begin();
		while(!m_windowList.end())
		{
			CUIObject* pfree = m_windowList.get();
			delete pfree;

			m_windowList.next();
		}
	}

	if(!m_windowDescriptionArray.empty())
	{
		for(Uint32 i = 0; i < m_windowDescriptionArray.size(); i++)
			delete m_windowDescriptionArray[i];

		m_windowDescriptionArray.clear();
	}

	m_schemaManager.Clear();
}

//=============================================
// @brief  Performs think functions
//
//=============================================
void CUIManager::Think( void )
{
	m_windowList.begin();
	while(!m_windowList.end())
	{
		CUIWindow* pWindow = m_windowList.get();
		pWindow->think();

		m_windowList.next();
	}
}

//=============================================
// @brief  Performs post-command think functions
//
//=============================================
void CUIManager::PostThink( void )
{
	m_windowList.begin();
	while(!m_windowList.end())
	{
		CUIWindow* pWindow = m_windowList.get();
		pWindow->postThink();

		// Destroy any flagged windows
		Int32 flags = pWindow->getWindowFlags();
		if(flags & CUIWindow::UIW_FL_KILLME)
			DestroyWindow(pWindow);

		m_windowList.next();
	}
}

//=============================================
// @brief Draws the active windows
//
//=============================================
bool CUIManager::Draw( void )
{
	// Set modelview
	rns.view.modelview.PushMatrix();
	rns.view.modelview.LoadIdentity();
	rns.view.modelview.Scale(1.0f/gWindow.GetWidth(), 1.0f/gWindow.GetHeight(), 1.0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Set it in the shader
	CBasicDraw* pDraw = CBasicDraw::GetInstance();
	pDraw->SetModelview(rns.view.modelview.GetMatrix());

	// Track render errors
	bool result = true;

	// Windows are sorted by focus index
	m_windowList.rbegin();
	while(!m_windowList.end())
	{
		CUIWindow* pWindow = m_windowList.get();

		if(m_windowFilterFlags && !(pWindow->getWindowFlags() & m_windowFilterFlags))
		{
			m_windowList.prev();
			continue;
		}

		if(pWindow->isVisible())
		{
			result = pWindow->draw();
			if(!result)
				break;
		}

		m_windowList.prev();
	}

	// Restore modelview
	rns.view.modelview.PopMatrix();

	glDisable(GL_BLEND);

	return result;
}

//=============================================
// @brief Draws the active windows
//
//=============================================
bool CUIManager::KeyEvent( Int32 button, Int16 mod, bool keyDown )
{
	if(!m_pFocusWindow)
		return false;

	if(m_pFocusWindow->keyEvent(button, mod, keyDown))
		return true;

	return false;
}

//=============================================
// @brief Draws the active windows
//
//=============================================
bool CUIManager::MouseButtonEvent( Int32 button, bool keyDown )
{
	Int32 cursorX, cursorY;
	gInput.GetMousePosition(cursorX, cursorY);

	m_windowList.begin();
	while(!m_windowList.end())
	{
		// See if we hit this window
		CUIWindow* pWindow = m_windowList.get();
		if(pWindow->isVisible()
			&& pWindow->isMouseOver(cursorX, cursorY) 
			&& pWindow->mouseButtonEvent(cursorX, cursorY, button, keyDown))
		{
			// Set as focus window if it's not already in focus
			if(keyDown && (!m_pFocusWindow || m_pFocusWindow != pWindow))
				SetFocusWindow(pWindow);

			// Release any press states
			if(!keyDown && m_pFocusWindow)
				m_pFocusWindow->releaseClickStates();

			return true;
		}

		m_windowList.next();
	}

	if(m_pFocusWindow)
	{
		// Release any clicked buttons
		if(button == SDL_BUTTON_LEFT && !keyDown)
			m_pFocusWindow->releaseClickStates();

		// We clicked away from any windows, so release focus
		if(button == SDL_BUTTON_LEFT && keyDown)
			SetFocusWindow(nullptr);
	}

	return false;
}

//=============================================
// @brief Draws the active windows
//
//=============================================
bool CUIManager::MouseWheelEvent( Int32 button, bool keyDown, Int32 scroll )
{
	Int32 cursorX, cursorY;
	gInput.GetMousePosition(cursorX, cursorY);

	m_windowList.begin();
	while(!m_windowList.end())
	{
		// See if we hit this window
		CUIWindow* pWindow = m_windowList.get();
		if(pWindow->isVisible()
			&& pWindow->isMouseOver(cursorX, cursorY) 
			&& pWindow->mouseWheelEvent(cursorX, cursorY, button, keyDown, scroll))
		{
			// Set as focus window if it's not already in focus
			if(keyDown && (!m_pFocusWindow || m_pFocusWindow != pWindow))
				SetFocusWindow(pWindow);

			// Release any press states
			if(!keyDown && m_pFocusWindow)
				m_pFocusWindow->releaseClickStates();

			return true;
		}

		m_windowList.next();
	}

	if(m_pFocusWindow)
	{
		// Release any clicked buttons
		if(button == SDL_BUTTON_LEFT && !keyDown)
			m_pFocusWindow->releaseClickStates();

		// We clicked away from any windows, so release focus
		if(button == SDL_BUTTON_LEFT && keyDown)
			SetFocusWindow(nullptr);
	}

	return false;
}


//=============================================
// @brief Sets the current focus window
//
//=============================================
void CUIManager::SetFocusWindow( CUIWindow* pWindow )
{
	if(m_pFocusWindow == pWindow)
		return;

	// Reset previous focus window
	if(m_pFocusWindow)
		m_pFocusWindow->setFocusState(false);

	// Raise focus index
	if(pWindow)
	{
		pWindow->setFocusIndex(m_currentFocusIndex);
		m_currentFocusIndex++;

		// Set window as current focus window
		m_pFocusWindow = pWindow;
		m_pFocusWindow->setFocusState(true);

		// Reorder the windows
		ReorderWindows();
	}
	else if(m_pFocusWindow)
	{
		// No focus on any window
		m_pFocusWindow = nullptr;
		m_currentFocusIndex++;
	}
}

//=============================================
// @brief Hides windows with a specific flag shows the rest
//
//=============================================
void CUIManager::HideWindows( Int32 windowFlags )
{
	if(m_windowList.empty())
		return;

	m_windowList.begin();
	while(!m_windowList.end())
	{
		// See if we hit this window
		CUIWindow* pWindow = m_windowList.get();
		if(pWindow->getWindowFlags() & windowFlags)
		{
			if(pWindow == m_pFocusWindow)
				SetFocusWindow(nullptr);

			// Hide the window
			pWindow->setVisible(false);
		}

		m_windowList.next();
	}
}

//=============================================
// @brief Show windows with a specific flag
//
//=============================================
void CUIManager::ShowWindows( Int32 windowFlags )
{
	if(m_windowList.empty())
		return;

	m_windowList.begin();
	while(!m_windowList.end())
	{
		// See if we hit this window
		CUIWindow* pWindow = m_windowList.get();
		if(pWindow->getWindowFlags() & windowFlags)
		{
			if(!m_pFocusWindow)
			{
				SetFocusWindow(pWindow);
				ShowWindows(windowFlags);
				return;
			}

			// Hide the window
			pWindow->setVisible(true);
		}

		m_windowList.next();
	}
}

//=============================================
// @brief Sorts the windows by focus indexes
//
//=============================================
void CUIManager::ReorderWindows( void )
{
	// Probably not the most efficient setup
	Uint32 currentFocusIdx = m_currentFocusIndex;

	// Temporary list to hold vars
	CLinkedList<CUIWindow*> tmpList;

	while(TRUE)
	{
		// Last nearest value to focus index
		Int32 lastNearest = -1;
		CUIWindow* pLastWindow = nullptr;

		m_windowList.begin();
		while(!m_windowList.end())
		{
			CUIWindow* pWindow = m_windowList.get();
			Uint32 focusIndex = pWindow->getFocusIndex();
			
			if(focusIndex < currentFocusIdx 
				&& lastNearest < static_cast<Int32>(focusIndex))
			{
				pLastWindow = pWindow;
				lastNearest = static_cast<Int32>(focusIndex);
			}

			m_windowList.next();
		}

		// Check if we reached the end
		if(lastNearest == -1)
			break;

		// Set current focus index
		currentFocusIdx = lastNearest;
		tmpList.add(pLastWindow);
	}

	// Shouldn't happen, but still
	assert(tmpList.size() == m_windowList.size());

	// Fill the list with the new values
	m_windowList.clear();

	tmpList.begin();
	while(!tmpList.end())
	{
		m_windowList.add(tmpList.get());
		tmpList.next();
	}
}

//=============================================
// @brief Sorts the windows by focus indexes
//
//=============================================
void CUIManager::RepositionWindows( void )
{
	if(m_windowList.empty())
		return;

	Uint32 winWidth = gWindow.GetWidth();
	Uint32 winHeight = gWindow.GetHeight();

	m_windowList.begin();
	while(!m_windowList.end())
	{
		CUIWindow* pWindow = m_windowList.get();

		Int32 originX, originY;
		pWindow->getAbsPosition(originX, originY);

		Uint32 width, height;
		pWindow->getSize(width, height);

		Int32 newOriginX = originX;
		if(originX + width > winWidth)
			newOriginX = winWidth - width;

		Int32 newOriginY = originY;
		if(originY + height > winHeight)
			newOriginY = winHeight - height;

		// Reposition to new location
		pWindow->setPosition(newOriginX, newOriginY);

		m_windowList.next();
	}

}

//=============================================
// @brief Adds a window to the list
//
//=============================================
void CUIManager::AddWindow( CUIWindow* pWindow )
{
	// Add it to the list
	m_windowList.add(pWindow);
	SetFocusWindow(pWindow);
}

//=============================================
// @brief Destroys a window and removes it from the list
//
//=============================================
void CUIManager::DestroyWindow( CUIWindow* pWindow )
{
	// Remove it from the list first
	m_windowList.remove(pWindow);

	// Remove it from focus
	if(m_pFocusWindow == pWindow)
	{
		// Find window with the highest focus
		Int32 lastHighest = -1;
		CUIWindow* pBestWindow = nullptr;

		m_windowList.begin();
		while(!m_windowList.end())
		{
			CUIWindow* pListWnd = m_windowList.get();
			if(pListWnd != pWindow)
			{
				Uint32 focusIndex = pWindow->getFocusIndex();
				if(static_cast<Int32>(focusIndex) > lastHighest || lastHighest == -1)
				{
					pBestWindow = pListWnd;
					lastHighest = static_cast<Int32>(focusIndex);
				}
			}

			m_windowList.next();
		}

		// Set this as the focus window
		if(pBestWindow)
			SetFocusWindow(pBestWindow);
		else
			m_pFocusWindow = nullptr;
	}

	// Delete this object
	delete pWindow;
}

//=============================================
// @brief
//
//=============================================
bool CUIManager::HasActiveWindows( void )
{
	if(m_windowList.empty())
		return false;

	m_windowList.begin();
	while(!m_windowList.end())
	{
		CUIWindow* pListWnd = m_windowList.get();
		if(pListWnd->isVisible())
			return true;

		m_windowList.next();
	}

	return false;
}

//=============================================
// @brief Loads in a schema file
//
// @param pstrFilename Name of the UI scheme file
// @return Pointer to scheme object
//=============================================
ui_schemeinfo_t* CUIManager::LoadSchemaFile( const Char* pstrFilename )
{
	ui_schemeinfo_t* presult = m_schemaManager.LoadSchemaFile(pstrFilename);
	if(!presult)
	{
		const CString& errorStr = m_schemaManager.GetErrorString();
		if(!errorStr.empty())
			Con_EPrintf(errorStr.c_str());

		return nullptr;
	}
	else
	{
		Uint32 nbWarnings = m_schemaManager.GetNbWarnings();
		if(nbWarnings > 0)
		{
			for(Uint32 i = 0; i < nbWarnings; i++)
				Con_Printf(m_schemaManager.GetWarning(i).c_str());

			m_schemaManager.ClearWarnings();
		}

		return presult;
	}
}

//=============================================
// @brief Loads in a schema file
//
// @param pstrFilename Name of the UI scheme file
// @return Pointer to scheme object
//=============================================
ui_windowdescription_t* CUIManager::LoadWindowDescriptionFile( const Char* pstrWindowName, const Char* pstrFilename )
{
	// Try to find it in the cache first
	for(Uint32 i = 0; i < m_windowDescriptionArray.size(); i++)
	{
		if(!qstrcmp(m_windowDescriptionArray[i]->windowName, pstrWindowName))
			return m_windowDescriptionArray[i];
	}

	// Load in the file
	CString scriptPath;
	scriptPath << "resources/windows/" << pstrFilename;

	Uint32 fileSize = 0;
	const Char* pfile = reinterpret_cast<const Char*>(FL_LoadFile(scriptPath.c_str(), &fileSize));
	if(!pfile)
	{
		Con_EPrintf("Failed to load UI schema script %s.\n", scriptPath.c_str());
		return nullptr;
	}

	// Convert file content to string
	CString jsonStr(reinterpret_cast<const Char*>(pfile));
	FL_FreeFile(pfile);

	// Parse JSON
	parse_options opts;
	opts.throw_exception = false;  // we handle errors manually
	opts.strict = false; // relax

	TJValue* root = TJ::parse(jsonStr.c_str(), opts);
	if(!root)
	{
		Con_EPrintf("%s - Failed to parse JSON in '%s'.\n", __FUNCTION__, scriptPath.c_str());
		delete root;
		return nullptr;
	}

	if(!root->is_object())
	{
		Con_EPrintf("%s - Root must be an object in '%s'.\n", __FUNCTION__, scriptPath.c_str());
		delete root;
		return nullptr;
	}

	const TJValueObject* obj = static_cast<const TJValueObject*>(root);
	const TJValue* objects = obj->try_get_value("objects");

	if(!objects || !objects->is_array())
	{
		Con_EPrintf("%s - Missing or invalid 'objects' array in '%s'.\n", __FUNCTION__, scriptPath.c_str());
		delete root;
		return nullptr;
	}

	const TJValueArray* array = static_cast<const TJValueArray*>(objects);

	// Allocate new object
	ui_windowdescription_t* pNewWindowDesc = new ui_windowdescription_t;
	pNewWindowDesc->windowName = pstrWindowName;

	for( unsigned int i = 0; i < array->get_number_of_items(); ++i )
	{
		const TJValue* item = array->at(i);
		if (!item || !item->is_object())
		{
			Con_EPrintf("%s - Invalid object at index %u in '%s'.\n", __FUNCTION__, i, scriptPath.c_str());
			continue;
		}


		const TJValueObject* itemObj = static_cast<const TJValueObject*>(item);

		const TJCHAR* typeStr = itemObj->try_get_string("type");
		if (!typeStr)
		{
			Con_EPrintf("%s - Missing 'type' for object at index %u in '%s'.\n", __FUNCTION__, i, scriptPath.c_str());
			delete root;
			delete pNewWindowDesc;
			return nullptr;
		}

		// read the name
		const TJCHAR* nameStr = itemObj->try_get_string("name");
		if (!nameStr)
		{
			Con_EPrintf("%s - Missing 'name' for object at index %u in '%s'.\n", __FUNCTION__, i, scriptPath.c_str());
			delete root;
			delete pNewWindowDesc;
			return nullptr;
		}

		CString objStr(typeStr);
		CString objName(nameStr);

		// Lambda to map type string to enum
		auto GetObjectTypeFromString = [](const CString& typeStr) -> ui_object_type_t {
			if(typeStr == "window")
			{
				return UI_OBJECT_WINDOW;
			}
			if(typeStr == "button")
			{
				return UI_OBJECT_BUTTON;
			}
			if(typeStr == "text")
			{
				return UI_OBJECT_TEXT;
			}
			if(typeStr == "tab")
			{
				return UI_OBJECT_TAB;
			}
			if(typeStr == "list")
			{
				return UI_OBJECT_LIST;
			}
			if(typeStr == "tickbox")
			{
				return UI_OBJECT_TICKBOX;
			}
			if(typeStr == "slider")
			{
				return UI_OBJECT_SLIDER;
			}
			return UI_OBJECT_UNDEFINED;
		};

		ui_object_type_t type = GetObjectTypeFromString(objStr);
		if (type == UI_OBJECT_UNDEFINED)
		{
			Con_EPrintf("Unknown object type '%s' in '%s'.\n", objStr.c_str(), scriptPath.c_str());
			delete root;
			delete pNewWindowDesc;
			return nullptr;
		}

		// Create the new object
		ui_objectinfo_t newObject;
		newObject.objectName = objName;
		newObject.type = type;

		// Helper lambdas with correct types
		auto readString = [&](const char* key) -> CString {
			if (itemObj->has_key(key)) {
				const TJValue* val = itemObj->try_get_value(key);
				if (val && val->is_string()) {
					return CString(val->get_string());
				}
			}
			return CString();
		};

		// Read numbers into int, then assign to Uint32
		auto readInt = [&](const char* key, Uint32& out) -> bool {
			if (itemObj->has_key(key)) {
				const TJValue* val = itemObj->try_get_value(key);
				if (val && val->is_number()) {
					out = static_cast<Uint32>(val->get_number());
					return true;
				}
			}
			return false;
		};

		auto readFloat = [&](const char* key, float& out) -> bool {
			if (itemObj->has_key(key)) {
				const TJValue* val = itemObj->try_get_value(key);
				if (val && val->is_number()) {
					out = static_cast<float>(val->get_float());
					return true;
				}
			}
			return false;
		};

		auto readBool = [&](const char* key, bool& out) -> bool {
			if (itemObj->has_key(key)) {
				const TJValue* val = itemObj->try_get_value(key);
				if (val && (val->is_true() || val->is_false())) {
					out = val->get_boolean();
					return true;
				}
			}
			return false;
		};

		Uint32 tempInt;
		if(readInt("width", tempInt))
		{
			newObject.width = tempInt;
		}
		if(readInt("height", tempInt))
		{
			newObject.height = tempInt;
		}

		newObject.text = readString("text");
		newObject.schema = readString("schema");

		Float tempFloat;
		if(readFloat("alpha", tempFloat))
		{
			newObject.alpha = tempFloat;
		}

		if(readInt("insetx", tempInt))
		{
			newObject.insetx = tempInt;
		}
		if(readInt("insety", tempInt))
		{
			newObject.insety = tempInt;
		}
		if(readInt("originx", tempInt))
		{
			newObject.originx = tempInt;
		}
		if(readInt("originy", tempInt))
		{
			newObject.originy = tempInt;
		}
		if(readInt("titleinsetx", tempInt))
		{
			newObject.title_insetx = tempInt;
		}
		if(readInt("titleinsety", tempInt))
		{
			newObject.title_insety = tempInt;
		}
		if(readInt("textinset", tempInt))
		{
			newObject.text_inset = tempInt;
		}
		if(readInt("rowheight", tempInt))
		{
			newObject.listrowheight = tempInt;
		}

		newObject.title = readString("title");

		bool tempBool;
		if(readBool("dragger", tempBool))
		{
			newObject.dragger = tempBool;
		}
		if(readBool("resizable", tempBool))
		{
			newObject.resizable = tempBool;
		}

		CString textschema = readString("textschema");
		if(readFloat("minvalue", tempFloat))
		{
			newObject.minvalue = tempFloat;
		}
		if(readFloat("maxvalue", tempFloat))
		{
			newObject.maxvalue = tempFloat;
		}
		if(readFloat("markerdistance", tempFloat))
		{
			newObject.markerdistance = tempFloat;
		}

		newObject.flags = 0;
		if(itemObj->has_key("flags"))
		{
			const TJValue* flagsVal = itemObj->try_get_value("flags");
			if(flagsVal && flagsVal->is_array())
			{
				const TJValueArray* flagsArr = static_cast<const TJValueArray*>(flagsVal);
				for(unsigned int f = 0; f < flagsArr->get_number_of_items(); ++f)
				{
					const TJValue* flagVal = flagsArr->at(f);
					if(flagVal && flagVal->is_string())
					{
						CString flagStr(flagVal->get_string());
						if(flagStr == "fixed_width")
							newObject.flags |= CUIObject::UIEL_FL_FIXED_W;
						else if(flagStr == "fixed_height")
							newObject.flags |= CUIObject::UIEL_FL_FIXED_H;
						else if(flagStr == "align_left")
							newObject.flags |= CUIObject::UIEL_FL_ALIGN_L;
						else if(flagStr == "align_right")
							newObject.flags |= CUIObject::UIEL_FL_ALIGN_R;
						else if(flagStr == "align_top")
							newObject.flags |= CUIObject::UIEL_FL_ALIGN_T;
						else if(flagStr == "align_bottom")
							newObject.flags |= CUIObject::UIEL_FL_ALIGN_B;
						else if(flagStr == "align_center_horizontal")
							newObject.flags |= CUIObject::UIEL_FL_ALIGN_CH;
						else if(flagStr == "align_center_vertical")
							newObject.flags |= CUIObject::UIEL_FL_ALIGN_CV;
						else if(flagStr == "wrap_word")
							newObject.flags |= CUIObject::UIEL_FL_WRAP_WORD;
						else if(flagStr == "fixed_xpos")
							newObject.flags |= CUIObject::UIEL_FL_FIXED_XPOS;
						else if(flagStr == "fixed_ypos")
							newObject.flags |= CUIObject::UIEL_FL_FIXED_YPOS;
						else if(flagStr == "ontop")
							newObject.flags |= CUIObject::UIEL_FL_ONTOP;
						else if(flagStr == "scroller_reverse")
							newObject.flags |= CUIObject::UIEL_FL_SCR_REVERSE;
						else if(flagStr == "expand_width")
							newObject.flags |= CUIObject::UIEL_FL_EXPAND_W;
						else if(flagStr == "expand_height")
							newObject.flags |= CUIObject::UIEL_FL_EXPAND_H;
						else if(flagStr == "noheader")
							newObject.flags |= CUIObject::UIEL_FL_NO_HEADER;
						else if(flagStr == "hover_highlight")
							newObject.flags |= CUIObject::UIEL_FL_HOVER_HIGHLIGHT;
						else
							Con_EPrintf("Unknown flag '%s' in '%s', discarding.\n", flagStr.c_str(), scriptPath.c_str());
					}
				}
			}
		}

		// Verify that we have valid sizes for non-text objects
		if(newObject.type != UI_OBJECT_TEXT && newObject.type != UI_OBJECT_TICKBOX)
		{
			if(!newObject.width)
			{
				Con_EPrintf("Object '%s' in '%s' has no width, discarding.\n", newObject.objectName.c_str(), scriptPath.c_str());
				continue;
			}
			if(!newObject.height)
			{
				Con_EPrintf("Object '%s' in '%s' has no height, discarding.\n", newObject.objectName.c_str(), scriptPath.c_str());
				continue;
			}
		}

		// Make sure sliders have the necessary values set
		if(newObject.type == UI_OBJECT_SLIDER)
		{
			if(!newObject.maxvalue)
			{
				Con_EPrintf("Object '%s' in '%s' has no maxvalue, discarding.\n", newObject.objectName.c_str(), scriptPath.c_str());
				continue;
			}
			if(!newObject.markerdistance)
			{
				Con_EPrintf("Object '%s' in '%s' has no markerdistance, discarding.\n", newObject.objectName.c_str(), scriptPath.c_str());
				continue;
			}
		}

		// Check for valid row height
		if(newObject.type == UI_OBJECT_LIST)
		{
			if(!newObject.listrowheight)
			{
				Con_EPrintf("Object '%s' in '%s' has no row height set, discarding.\n", newObject.objectName.c_str(), scriptPath.c_str());
				continue;
			}
		}

		// Load any custom fonts
		if(!textschema.empty())
		{
			newObject.pfont = gTextSchemas.GetSchemaFontSet(textschema.c_str());
			if(!newObject.pfont)
			{
				Con_EPrintf("Object '%s' in '%s' - Schema '%s' not found.\n", newObject.objectName.c_str(), scriptPath.c_str(), textschema.c_str());
				newObject.pfont = m_pFontSet;
			}
		}
		else
		{
			// Set default
			newObject.pfont = m_pFontSet;
		}

		if(!newObject.alpha)
			newObject.alpha = 255;
		else if(newObject.alpha > 255)
			newObject.alpha = 255;

		pNewWindowDesc->objectsArray.push_back(newObject);
	}

	// Add it to the list
	m_windowDescriptionArray.push_back(pNewWindowDesc);

	delete root;
	return pNewWindowDesc;
}

//=============================================
// @brief Sets a window flag for draw filtering
//
//=============================================
void CUIManager::SetDrawFilter( Int32 windowFlags )
{
	m_windowFilterFlags |= windowFlags;
}

//=============================================
// @brief Sets a window flag for draw filtering
//
//=============================================
void CUIManager::RemoveDrawFilter( Int32 windowFlags )
{
	m_windowFilterFlags &= ~windowFlags;
}

//=============================================
// @brief Tells if mouse is over any active window
//
//=============================================
bool CUIManager::IsMouseOverAnyWindow( void )
{
	if(m_windowList.empty())
		return false;

	Int32 cursorX, cursorY;
	gInput.GetMousePosition(cursorX, cursorY);

	m_windowList.begin();
	while(!m_windowList.end())
	{
		CUIWindow* pWindow = m_windowList.get();
		if(pWindow->isMouseOver(cursorX, cursorY))
			return true;

		m_windowList.next();
	}

	return false;
}