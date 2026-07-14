/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef CONSOLE_H
#define CONSOLE_H

#include "cvar.h"

enum input_type_t
{
	INPUT_CVAR,
	INPUT_CMD
};

struct con_input_t
{
	con_input_t():
		type(INPUT_CVAR)
	{}

	CString name;
	CString description;
	input_type_t type;
};

// Datatype for the input list
typedef CLinkedList<con_input_t> ConList_t;

/*
=================================
CConsole

=================================
*/
class CConsole
{
public:
	// How much to increase the console's buffer by each time
	static const UInt32 CONSOLE_BUFFER_CHUNKSIZE;
	// Command name for the toggleconsole command
	static const char TOGGLECONSOLE_CMD_NAME[];
	// Max remembered last prints
	static const UInt32 MAX_DEBUG_PRINTS;
	// Print lifetime
	static const float DEBUG_PRINT_LIFETIME;

	// Print box reference offset for x axis
	static const UInt32 PRINT_BOX_REF_X_OFFSET;
	// Print box reference offset for y axis
	static const UInt32 PRINT_BOX_REF_Y_OFFSET;
	// Print box text inset
	static const UInt32 PRINT_BOX_INSET;

	// Console reference width
	static const UInt32 CONSOLE_REF_RESOLUTION_WIDTH;
	// Print box reference height
	static const UInt32 CONSOLE_REF_RESOLUTION_HEIGHT;

	// Print box reference width
	static const UInt32 PRINT_BOX_REF_WIDTH;
	// Print box reference height
	static const UInt32 PRINT_BOX_REF_HEIGHT;
	// Print box reference bar thickness
	static const UInt32 PRINT_BOX_REF_BAR_THICKNESS;

	// Print box color
	static const color32_t PRINT_BOX_BAR_COLOR;

	// Text schema name for console text box
	static const char TEXTBOX_TEXTSCHEMA_NAME[];

public:
	// Debug display prints
	struct debug_print_t
	{
		debug_print_t():
			time(0)
			{}

		CString text;
		double time;
	};

public:
	CConsole( void );
	CConsole( CConsole& src );
	~CConsole( void );

private:
	// Assignment operator
	CConsole& operator=( CConsole& src );

public:
	// Initializes the console
	void Init( void );
	// Initializes GL stuff
	bool InitGL( void );

	// Adds text to the history
	void AddTextHistory( const char* pstrText );
	// Returns a pointer to the console buffer
	const char* GetConsoleHistory( void ) const { return m_pConsoleBuffer; }

	// Processes a command input
	void ProcessInput( const char* pstrText );
	// Gets the current input from the history
	const char* GetCurrentInputHistory( void );
	// Advances along the text history
	void HistoryStepForward( void );
	// Backtraces along the text history
	void HistoryStepBack( void );
	// Tells if we've reached the end of the history
	DO_INLINE bool IsAtHistoryEnd( void ) const { return m_inputHistoryList.end(); }
	// Resets the history iterator
	DO_INLINE void ResetHistoryIterator( void ) { m_inputHistoryList.begin(); }

	// Spawns the console
	static void ShowConsole( void );
	// Hides the console
	static void HideConsole( void );
	// Tells if the console is active
	static bool IsConsoleVisible( void );
	// Toggles the console
	static void ToggleConsole( void );

	// Retrieves a cvar by name
	CCVar* GetCVar( const char* pstrName );
	// Creates a console variable
	CCVar* CreateCVar( cvar_type_t type, Int32 flags, const char* pstrName, const char* pstrValue, const char* pstrDescription = nullptr, pfnCVarCallback_t pfnCallback = nullptr );

	// Adds an input to the inputs list
	void AddInput( input_type_t type, const char* name, const char* description );
	// Attemps to process a command from the cmd buffer
	bool ProcessCommand( void );

	// Sets a float value on a cvar
	bool CVarSetFloatValue( const char* pstrName, float value );
	// Sets a string value on a cvar
	bool CVarSetStringValue( const char* pstrName, const char* pstrValue );

	// Sets the input list tabbing filter
	const char* GetBestInputChoice( const char* pstrFilterString, bool retry = true );
	// Resets the tabbing function
	void ResetTabbing( void );

	// Performs think functions
	void Think( void );
	// Draws debug strings
	bool Draw( void );

	// Updates text history, if it wasn't updated already
	void UpdateTextHistory( void );

public:
	// Clears the console history
	void CmdClearHistory( void );
	// Dumps a list of either input types to the console or to a file
	void CmdInputList( input_type_t type );
	// Dumps the contents of the console to a file
	void CmdConDump( void ) const;

public:
	// Buffer for all console text
	char* m_pConsoleBuffer;
	// Current buffer size
	UInt32 m_bufferSize;
	// Current buffer position
	UInt32 m_bufferPosition;

	// Linked list of input commands
	CLinkedList<CString> m_inputHistoryList;
	// true if we reached the end
	bool m_reachedHistoryEnd;

	// true if history text is up to date
	bool m_isHistoryUpdated;

private:
	// List of console variables
	CLinkedList<CCVar*> m_cvarList;
	// Alphabetically ordered list of all console inputs
	ConList_t m_inputList;

	// The input filter string for tabbing
	CString m_listFilterString;

	// Debug screen prints
	CLinkedList<debug_print_t> m_debugPrintList;

	// Cvar for toggling print box
	CCVar* m_pCvarDrawHistoryBox;

	// Saved commands for GL dependent cvars
	CArray<CString> m_glDependentCVarCommandsArray;

	// Font set used by console text
	const struct font_set_t* m_pFontSet;
};
extern CConsole gConsole;
#endif //CONSOLE_H