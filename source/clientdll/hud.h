/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef HUD_H
#define HUD_H

#include "constants.h"
#include "weapons_shared.h"
#include "matrix.h"

class CCVar;
struct en_texture_t;
struct font_set_t;
class CGameHUD;

struct subtitle_t
{
	subtitle_t():
		delay(0),
		r(0),
		g(0),
		b(0)
		{}

	CString szname;
	CString subtitle;

	float delay;
	float r;
	float g;
	float b;
};

struct active_subtitle_t
{
	active_subtitle_t():
		psubtitle(nullptr),
		holdtime(0),
		timeout(0),
		spawntime(0)
		{}

	subtitle_t* psubtitle;
	double holdtime;
	double timeout;
	double spawntime;
};

struct weapon_t
{
	weapon_t():
		ammotype(0),
		maxammo(0),
		maxclip(0),
		slot(0),
		slotposition(0),
		flags(0),
		weaponid(0),
		clip(0),
		dualclipleft(0),
		dualclipright(0),
		count(0),
		cone(0)
	{
	}

	CString		name;
	Int32		ammotype;
	Int32		maxammo;
	Int32		maxclip;
	UInt32		slot;
	Int32		slotposition;
	Int32		flags;
	Int32		weaponid;
	Int32		clip;

	Int32		dualclipleft;
	Int32		dualclipright;

	Int32		count;
	Int32		cone;
};

struct radiomessage_t
{
	radiomessage_t():
		life(0),
		spawntime(0),
		entindex(NO_ENTITY_INDEX)
		{}

	CString callername;
	color32_t color;
	float life;
	double spawntime;
	entindex_t entindex;
};

/*
====================
CWeaponInfo

====================
*/
class CWeaponInfo
{
public:
	CWeaponInfo( void );
	~CWeaponInfo( void );

public:
	// Resets the class
	void Reset( void );

	// Adds a new weapon to the info structure
	void AddWeapon( const weapon_t& weapon );
	// Assigns a weapon to a slot
	void AssignWeapon( weapon_t* pweapon );
	// Returns a weapon for an ID
	weapon_t* GetWeapon( UInt32 id );
	// Removes a weapon from it's slot
	void RemoveWeapon( weapon_t* pweapon );
	// Removes all weapons from their slots
	void RemoveAllWeapons( void );

	// Returns a weapon at a specific slot and slot position
	weapon_t* GetWeaponFromSlot( UInt32 slot, UInt32 position );
	// Returns the first weapon in a slot
	weapon_t* GetSlotFirstWeapon( UInt32 slot );
	// Returns the next available weapon in the slot
	weapon_t* GetNextSlotWeapon( UInt32 slot, UInt32 position );

	// Tells if a weapon has any ammy
	bool WeaponHasAmmo( weapon_t* pweapon ) const;
	// Returns the ammo count for an ammo type
	UInt32 GetAmmoCount( Int32 ammoId ) const;
	// Sets ammo count for an ammo type
	void SetAmmoCount( Int32 ammoId, UInt32 count );

private:
	// Array of weapons
	weapon_t	m_weaponsArray[MAX_WEAPONS];

	// Slot assignments
	weapon_t*	m_pSlotsArray[MAX_WEAPON_SLOTS][MAX_SLOT_POSITIONS];
	// Ammo counts
	UInt32		m_ammoCounts[MAX_AMMO_TYPES];
};

/*
====================
CHUDHistory

====================
*/
class CHUDHistory
{
public:
	enum history_type_t
	{
		HISTORY_AMMO = 0,
		HISTORY_WEAPON,
		HISTORY_ITEM,
		HISTORY_CUSTOM_MSG
	};

public:
	// Time an item spends active
	static const float HUD_HISTORY_DRAW_TIME;
	// History spacing
	static const UInt32 HISTORY_SPACING;
	// Max history height
	static const float MAX_HISTORY_HEIGHT;
	// Text color
	static color32_t HISTORY_TEXT_COLOR;
	// Fade time for history texts
	static const float HISTORY_FADE_TIME;

private:
	struct hudhistory_t
	{
		hudhistory_t():
			die(0)
			{}

		float die;
		CString description;
	};

public:
	CHUDHistory( CGameHUD& mainHUD );
	~CHUDHistory( void );

public:
	// Resets the list
	void Reset( void );

	// Adds a history element
	void AddElement( UInt32 type, UInt32 id, UInt32 count = 0 );
	// Adds a history element
	void AddElement( UInt32 type, const char* pstrname, UInt32 count );
	// Adds a history element
	void AddElement( UInt32 type, const char* pstrmsg );

	// Tells if we have any elements to draw
	bool HasActiveElements( void );

	// Draws the history
	bool Draw( void );

private:
	// HUD onbject using us
	CGameHUD& m_hud;
	// List of history objects
	CLinkedList<hudhistory_t> m_historyList;
};

/*
====================
CGameHUD

====================
*/
class CGameHUD
{
public:
	friend class CHUDHistory;

public:
	// Default HUD alpha value
	static const float HUD_DEFAULT_ALPHA;
	// HUD white color
	static const Vector HUD_COLOR_WHITE;
	// HUD gray color
	static const Vector HUD_COLOR_GRAY;
	// HUD black color
	static const Vector HUD_COLOR_BLACK;
	// HUD red color
	static const Vector HUD_COLOR_RED;
	// HUD blue color
	static const Vector HUD_COLOR_BLUE;
	// HUD orange color
	static const Vector HUD_COLOR_ORANGE;

	// Tilt amount
	static const UInt32 TILT_AMOUNT;
	// Generic tab size
	static const UInt32 TAB_GENERIC_SIZE_X;
	static const UInt32 TAB_GENERIC_SIZE_Y;
	static const UInt32 TAB_MOVENOISE_SIZE_X;
	// Radio message tab width
	static const UInt32 RADIO_MSGTAB_SIZE_X;
	static const UInt32 RADIO_MSGTAB_SIZE_Y;
	static const UInt32 RADIO_MSGTAB_SPACING;
	static const float RADIO_MSG_FADETIME;
	// Tab label size
	static const UInt32 TAB_LABEL_SIZE_X;
	// Heal tab width
	static const UInt32 TAB_HEAL_SIZE_X;
	// Healthkit tab width
	static const UInt32 TAB_HEALTHKIT_SIZE_X;
	// Tactical icon width
	static const UInt32 TACTICAL_ICON_X;
	// Tactical icon height
	static const UInt32 TACTICAL_ICON_Y;
	// Tactical tab width
	static const UInt32 TAB_TACTICAL_SIZE_X;
	// Weapon tab width
	static const UInt32 TAB_WEAPON_SIZE_X;
	// Clip label width
	static const UInt32 LABEL_CLIP_SIZE_X;
	// Percentage bar height
	static const UInt32 PERCENTAGE_BAR_HEIGHT;
	// Icon size
	static const UInt32 ICON_SIZE;
	// Ammo icon width
	static const float AMMOICON_SIZE_X;
	// Ammo icon height
	static const float AMMOICON_SIZE_Y;
	// Weapon rubicle width
	static const UInt32 RUBICLE_WEAPONINFO_SIZE_X;
	// List label T width
	static const UInt32 LIST_LABEL_T_X;
	// List label T height
	static const UInt32 LIST_LABEL_T_Y;
	// List label S width
	static const UInt32 LIST_LABEL_S_X;
	// List label S height
	static const UInt32 LIST_LABEL_S_Y;
	// Weapon tab X
	static const UInt32 LIST_WEAPONTAB_X;
	// Weapon tab Y
	static const UInt32 LIST_WEAPONTAB_Y;
	// List edge size
	static const UInt32 LIST_EDGE_SIZE;
	// Subtitle tab width
	static const UInt32 SUBTITLE_TAB_SIZE_X;
	// Subtitle tab height
	static const UInt32 SUBTITLE_TAB_SIZE_Y;
	// Subtitle timeout duration
	static const float SUBTITLE_TAB_TIMEOUT;
	// Subtitle tab fade out time
	static const float	SUBTITLE_TAB_FADETIME;
	// Subtitle tab fade in time
	static const float	SUBTITLE_TAB_FADEINTIME;
	// Ammo bar height
	static const UInt32 AMMOBAR_SIZE_Y;
	// Ammo bar width
	static const UInt32 AMMOBAR_SIZE_X;
	// Stamina fade time
	static const UInt32 STAMINA_FADE_TIME;
	// Subtitle spacing
	static const float SUBTITLE_GAP;
	// Subtitle inset
	static const float SUBTITLE_INSET;

	// HUD description script path
	static const char HUD_DESCRIPTION_SCRIPT_PATH[];
	
	// Font set for HUD
	static const char HUD_FONT_SCHEMA_FILENAME[];
	// Font set for counters
	static const char HUD_COUNTER_FONT_SCHEMA_FILENAME[];
	// Font set for subtitles
	static const char HUD_SUBTITLE_FONT_SCHEMA_FILENAME[];

public:
	struct hud_iconinfo_t
	{
		hud_iconinfo_t():
			ptexture(nullptr)
			{}

		CString name;
		en_texture_t* ptexture;
	};

	struct hud_weaponinfo_t
	{
		hud_weaponinfo_t():
			weaponid(WEAPON_NONE),
			pweapon_icon(nullptr),
			pammo_icon(nullptr)
			{}

		weaponid_t weaponid;
		en_texture_t* pweapon_icon;
		en_texture_t* pammo_icon;

		CString description;
		CString description_dual;
		CString description_ammo;
	};

	struct hud_iteminfo_t
	{
		hud_iteminfo_t():
			weaponid(WEAPON_NONE)
			{}

		CString name;
		weaponid_t weaponid;
		CString description;
		CString unitname_singular;
		CString unitname_plural;
	};

	struct hud_infopair_t
	{
		CString key;
		CString value;
	};

public:
	CGameHUD( void );
	~CGameHUD( void );

public:
	// Initializes the class
	void Init( void );
	// Shuts down the class
	void Shutdown( void );

	// Initializes the class's GL stuff
	bool InitGL( void );
	// Shuts down the class's GL stuff
	void ClearGL( void );

	// Initializes game objects
	bool InitGame( void );
	// Clears game objects
	void ClearGame( void );

	// Draws the HUD
	bool Draw( void );
	// Performs think functions
	void Think( void );

	// Called from DrawNormal
	bool DrawNormal( void );

	// Tells if the HUD is active
	bool IsActive( void ) const;

public:
	// Returns the stamina amount
	float GetStamina( void ) const { return m_stamina/100.0f; }
	// Returns the health amount
	float GetHealth( void ) const { return m_health; }
	// Returns the flashlight battery charge
	float GetFlashlightBattery( void ) const { return m_tacticalAmount; }
	// Returns the weapon selection
	Int32 GetWeaponSelect( void ) const { return m_weaponSelection; }
	// Sets the weapon selection
	void SetWeaponSelect( Int32 select ) { m_weaponSelection = select; }
	// Selects a weapon slot
	void SelectWeaponSlot( UInt32 slot, bool advance, Int32 direction );

	// Adds a subtitle
	bool AddSubtitle( const char *szname, float holdtime );
	// Removes a playing subtitle
	void RemoveSubtitle( const char *szname );
	// Adds a radio message
	void AddRadioMessage( const char* pstrcallername, const color32_t& color, float lifetime, entindex_t entindex );

	// Sets the stamina amount
	void SetStamina( float stamina );
	// Sets the health amount
	void SetHealth( float health );
	// Sets the kevlar amount
	void SetKevlar( float kevlar );
	// Sets the number of healthkits
	void SetHealthkitNumber( UInt32 numhealthkits );
	// Sets the healing progress amount
	void SetHealProgress( float progress );
	// Sets current weapon information
	void SetCurrentWeapon( Int32 state, Int32 id, UInt32 clip, UInt32 clipright, UInt32 clipleft, UInt32 cone );
	// Sets data for a weapon
	void AddWeaponList( const char* pstrname, Int32 ammotype, Int32 maxammo, Int32 maxclip, UInt32 slot, UInt32 slotposition, UInt32 weaponid, Int32 flags );
	// Sets ammo count
	void SetAmmoCount( UInt32 ammoIndex, UInt32 ammoCount );
	// Manages an ammo pickup event
	void AmmoPickup( const char* pstrentityname, UInt32 count );
	// Manages a weapon pickup event
	void WeaponPickup( Int32 id, UInt32 ammoCount );
	// Manages an item pickup event
	void ItemPickup( const char* pstrentityname );
	// Custom pickup message
	void CustomPickupMessage( const char* pstrpickuptext );
	// Sets active state for HUD
	void SetActive( bool active );
	// Sets tactical battery value and state
	void SetTacticalBattery( bool ison, float amount );
	// Sets the movement noise
	void SetMovementNoise( float noise );
	// Sets the movement noise
	void SetNPCAwareness( float awareness, color24_t& color );
	// Sets new objective flag
	void SetNewObjective( bool newObjective );
	// Sets usable object mins/maxs
	void SetUsableObjectMinsMaxs( const Vector& mins, const Vector& maxs, usableobject_type_t type );
	// Sets countdown timer
	void SetCountdownTime( double endTime, const char* pstrTitle );
	// Set autoaim vector
	void SetAutoaimVector( float autoAimX, float autoAimY, bool isOnTarget );

private:
	// Draws a bar tab
	bool DrawTab_Bar( float x, float y, char *sztext, en_texture_t *picon, float bar, Int32 width, float alpha, float *ox = nullptr, float *oy = nullptr, bool reverseColor = false, color24_t* pcolor = nullptr );
	// Draws the weapon tab
	bool DrawWeaponTab( void );
	// Draws the healthkit tab
	bool DrawHealthkitTab( float x, float y );
	// Draws the tactical tab
	bool DrawTacticalTab( float x, float y );
	// Draws the weapons list
	bool DrawWeaponList( void );
	// Draws the crosshair
	bool DrawCrosshair( void );
	// Draws radio messages
	bool DrawRadioMessages( void );
	// Draws the noise tab
	bool DrawNoiseTab( void );
	// Draws the NPC awareness tab
	bool DrawNPCAwarenessTab( void );
	// Draws usable object reticle
	bool DrawUsableObjectReticle( void );
	// Draws countdowntimer
	bool DrawCountdownTimer( void );

	// Draws subtitles
	bool DrawSubtitles( void );
	// Initializes subtitles
	bool InitSubtitles( void );

	// Loads the HUD script
	bool LoadHUDScript( void );
	// Returns value for a key
	const char* GetValueForKey( const CArray<hud_infopair_t>& srcArray, const char* pstrKey );

	// Returns an icon texture by name 
	en_texture_t* GetIconTextureByName( const char* pstrName );
	// Returns an item description by name
	bool GetItemDescriptionByName( const char* pstrName, CString& outDescription, CString& outUnitName, bool singular );
	// Returns an item description by weapon id
	bool GetItemDescriptionByWeaponId( weaponid_t weaponid, CString& outDescription, CString& outUnitName, bool singular );
	// Returns a weapon info structure based on id
	const hud_weaponinfo_t* GetWeaponInfoById( weaponid_t weaponid );
	// Returns a weapon icon texture based on id
	en_texture_t* GetWeaponIconById( weaponid_t weaponid );

	// Returns information for a weapon
	void GetWeaponInfo( Int32 id, bool dual, en_texture_t *&picon, CString& name, CString& cartridge ) const;
	// Retrieves the cone size for a weapon
	Vector GetConeSize( Int32 coneindex ) const;

	// Adds an active subtitle
	void AddActiveSubtitle( subtitle_t* psubtitle, float holdtime, float timeout );

	// Plays a sound
	static void PlaySound( const char* pstrfilepath );

	// Tells if we have any weapons
	bool HasAnyWeapons( void ) const;

public:
	// Processes a slot input
	void SlotInput( Int32 iSlot );
	// Closes the weapon tab
	void UserCmd_Close( void );
	// Gets the next weapon
	void UserCmd_NextWeapon( void );
	// Gets the previous weapon
	void UserCmd_PrevWeapon( void );

private:
	en_texture_t *m_pHealthIcon;
	en_texture_t *m_pKevlarIcon;
	en_texture_t *m_pTacticalIcon;
	en_texture_t *m_pMedkitIcon;
	en_texture_t *m_pStaminaIcon;
	en_texture_t *m_pNoiseIcon;
	en_texture_t *m_pAwarenessIcon;
	en_texture_t *m_pRadioIcon;
	en_texture_t *m_pNewObjectivesIcon;

	const hud_weaponinfo_t* m_pActiveWeaponInfo;

public:
	// Active subtitle header
	CLinkedList<active_subtitle_t> m_activeSubtitlesList;

	// Array of subtitles
	CArray<subtitle_t>	m_subtitlesArray;

	// Controls rendering of subtitles
	CCVar*		m_pCvarDrawSubtitles;

public:
	weapon_t	*m_pActiveSelection;
	weapon_t	*m_pLastSelection;
	weapon_t	*m_pWeapon;

	Int32		m_weaponSelection;
	bool		m_isDrySelection;

	// Linked list of radio messages
	CLinkedList<radiomessage_t> m_radioMessagesList;

public:
	CWeaponInfo	m_weaponInfo;
	CHUDHistory* m_pHistory;

public:
	const font_set_t *m_pFontSet;
	const font_set_t *m_pSubtitleSet;
	const font_set_t *m_pCounterFont;

private:
	float	m_stamina;
	float	m_health;
	float	m_kevlar;
	double	m_staminaFadeTime;

	bool	m_isTacticalOn;
	float	m_tacticalAmount;

	float	m_healProgress;
	Int32	m_numMedkits;

	float	m_movementNoise;
	float	m_npcAwareness;
	color24_t m_npcAwarenessColor;

	bool	m_newObjective;

	CString	m_countdownTimerTitle;
	double	m_countdownTimerTime;

	// Ideal autoaim vector
	Vector m_idealAutoAimVector;
	// Previous autoaim vector
	Vector m_currentAutoAimVector;
	// true if locked onto a target
	bool m_isOnTarget;

private:
	// Usable object world mins
	Vector m_usableObjectMins;
	// Usable object maxs
	Vector m_usableObjectMaxs;
	// Modelview matrix
	CMatrix m_modelviewMatrix;
	// Projection matrix
	CMatrix m_projectionMatrix;
	// Usable object type
	usableobject_type_t m_usableObjectType;

	// Controls rendering of subtitles
	CCVar* m_pCvarDrawUseReticle;

private:
	// Old weapon bits
	Int32 m_prevWeaponBits;
	// Current weapon bits
	Int32 m_weaponBits;
	// Last key bits
	Int32 m_keyBits;
	// true if HUD is active
	bool m_isActive;
	// Weapon select usermsg id
	UInt32 m_weaponSelectUserMSGId;

	// Screen width
	UInt32 m_screenWidth;
	// Screen Height
	UInt32 m_screenHeight;

	// Array of icons
	CArray<hud_iconinfo_t> m_iconInfoArray;
	// Array of weapons
	CArray<hud_weaponinfo_t> m_weaponInfoArray;
	// Array of items
	CArray<hud_iteminfo_t> m_itemInfoArray;

	// Last time think was called
	double m_lastThinkTime;
};
extern CGameHUD gHUD;
#endif //HUD_H