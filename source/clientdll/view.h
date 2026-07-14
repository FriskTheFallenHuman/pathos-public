/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef VIEW_H
#define VIEW_H

struct ref_params_t;
struct cache_model_t;

class CCVar;

extern Vector g_viewOrigin;

/*
====================
CNormalSmoothing

====================
*/
class CDefaultView
{
public:
	// Flashlight fade speed
	static const float FLASHLIGHT_FADE_SPEED;
	// Flashlight sprite file
	static const char FLASHLIGHT_SPRITE_FILE[];

	// Values for view model lag calculations
	static const float VIEWMODEL_LAG_MULT;
	static const float VIEWMODEL_LAG_SPEED;

	// Values for view bob calculations
	static const float BOB_CYCLE_MIN;
	static const float BOB_CYCLE_MAX;
	static const float BOB;
	static const float BOB_UP;

	// Values for stair step smoothing
	static const float V_SM_REF_VEL;
	static const float V_SM_BLEND_VEL;

public:
	CDefaultView();
	~CDefaultView();

public:
	// Initializes the class
	bool Init( void );

	// Initializes for game
	bool InitGame( void );
	// Clears game data
	void ClearGame( void );

	// Calculates view position
	void CalcRefDef( ref_params_t& params );

	// Returns the lean offset
	Vector GetLeanOffset( void ) const;

	// Resets view roll
	void ResetViewRoll( void );
	// Resets view idling
	void ResetViewIdle( void );
	// Resets view model lag
	void ResetViewModelLag( void );

	// Calculates the view model angle
	void CalcViewModelAngle( cl_entity_t* pviewmodel, const ref_params_t& params );

	// Sets the FOV value
	void SetFOV( float newFOV );
	// Sets the FOV override value
	void SetFOVOverride( float overrideFOV );
	// Sets the fov zoom
	void SetFOVZoom( float desiredFOV, float blenddelta );

	// Blends field of view values
	void CalculateFOV( ref_params_t& params );
	// Returns the current FOV value
	float GetFOV( void ) const;

	// Sets up all player flashlight types
	void SetupFlashlights( const ref_params_t& params );

	// Sets the view entity
	void SetViewEntity( entindex_t viewentity );
	// Returns the view entity
	entindex_t GetViewEntity( void ) const;

	// Updates autoaim
	void SetAutoAim( float autoAimX, float autoAimY );

private:
	// Calculates the view bob
	void CalcBob( cl_entity_t* pplayer, ref_params_t& params );
	// Calculates view roll
	static float CalcRoll( const Vector& angles, const Vector& velocity, float rollangle, float rollspeed );
	// Calculates interpolated rolling
	static float CalcSmoothRolling( float cur_roll, float target_roll, float speed, double frametime );
	// Calculates view rolling
	void CalcViewRoll( cl_entity_t* pplayer, ref_params_t& params );
	// Calculates leaning
	void CalcLeaning( cl_entity_t* pplayer, cl_entity_t *pviewmodel, ref_params_t& params );

	// Estimates footstep time
	static float EstimateStepTime( cl_entity_t* pplayer, ref_params_t& params );
	// Smooths out up-down steps
	void SmoothSteps( cl_entity_t* pplayer, cl_entity_t* pviewmodel, ref_params_t& params );

	// Adds viewmodel bob
	void AddViewModelBob( cl_entity_t* pviewmodel, ref_params_t& params );
	// Calculates view model lag
	void CalcViewModelLag( const ref_params_t& params, Vector& origin, const Vector& angles, const Vector& orig_angles );

	// Adds idle breathing movement
	void AddIdle( cl_entity_t* pplayer, ref_params_t& params );
	// Calculates swim floating
	void CalcSwimFloat( cl_entity_t* pplayer, ref_params_t& params );

	// Sets up player flashlights
	void SetupFlashlightForType( const ref_params_t& params, float* pstrengths, Int32 effectbit );

private:
	// Bob time
	double m_bobTime;
	// Last bob time
	double m_lastBobTime;
	// Vertical bob amount
	float m_verticalBob;
	// Lateral bob amount
	float m_lateralBob;

	// Last facing of view model
	Vector m_viewModelLastFacing;
	// Last viewmodel lag time
	double m_flLastViewModelLagTime;

	// Time we started breathing
	double m_breathingTime;

	// Current view roll
	float m_currentViewRoll;

	// Last lean time
	double m_leanTime;
	// Previous buttons when calculating leaning
	Int32 m_prevLeanButtons;
	// Previous player flags
	Int64 m_prevPlayerFlags;
	// Leaning state
	bool m_leaningState;

	// Lean angles
	Vector m_prevLeanAngles;
	Vector m_idealLeanAngles;
	Vector m_curLeanAngles;

	// Lean offset
	Vector m_prevLeanOffset;
	Vector m_idealLeanOffset;
	Vector m_curLeanOffset;

	// Last time we calculated step smoothing
	double m_lastStepSmoothTime;
	// Last Z value used for step smoothing
	float m_prevStepSmoothZ;
	// Stair-step smoothing speed
	float m_stepSmoothSpeed;
	// Last origin at step smoothing
	Vector m_lastStepSmoothOrigin;
	// Last view offset used in step smoothing
	Vector m_lastStepSmoothViewOffset;

	// Last swim float time
	double m_lastSwimFloatTime;

private:
	// Current field of view value
	float m_fovValue;
	// FOV override value
	float m_fovOverrideValue;

	// FOV previous value
	float m_prevFOVValue;
	// FOV desired value
	float m_desiredFOVValue;

	// Blend duration for FOV
	float m_fovBlendDelta;
	// FOV blend time
	double m_fovBlendTime;

private:
	// Ideal autoaim vector
	Vector m_idealAutoAimVector;
	// Previous autoaim vector
	Vector m_currentAutoAimVector;

private:
	// Tactical flashlight strengths
	float m_tacticalLightStrengths[MAX_PLAYERS];
	// Shoulder flashlight strengths
	float m_shoulderLightStrengths[MAX_PLAYERS];
	// Local player's dimlight strength
	float m_localPlayerDimLightStrength;

	// Flashlight sprite model
	const cache_model_t* m_pFlashlightSprite;

private:
	// View entity
	entindex_t m_viewEntity;

private:
	// View roll angle cvar
	CCVar* m_pCvarRollAngle;
	// View roll speed cvar
	CCVar* m_pCvarRollSpeed;
	// Default FOV cvar ptr
	CCVar* m_pCvarReferenceFOV;
	// View bob cvar
	CCVar* m_pCvarViewBob;
	// View X offset
	CCVar* m_pCvarViewXOffset;
	// View Y offset
	CCVar* m_pCvarViewYOffset;
	// View Z offset
	CCVar* m_pCvarViewZOffset;
};
extern CDefaultView gDefaultView;

extern cl_entity_t* V_GetViewModel( void );
extern void V_CalcRefDef( ref_params_t& params );
extern void V_GetViewInfo( Vector& vOrigin, Vector& vAngles );
#endif //VIEW_H