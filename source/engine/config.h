/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef CONFIG_H
#define CONFIG_H

enum cf_status_t
{
	CONF_ERR_NONE = 0,
	CONF_ERR_FIELD_MISSING,
	CONF_ERR_GROUP_MISSING,
	CONF_ERR_TYPE_MISMATCH
};

enum field_type_t
{
	CONF_FIELD_UNDEFINED = -1,
	CONF_FIELD_INT,
	CONF_FIELD_FLOAT,
	CONF_FIELD_STRING,
	CONF_FIELD_KEYBIND
};

enum group_type_t
{
	CONF_GRP_UNDEFINED = -1,
	CONF_GRP_SYSTEM,
	CONF_GRP_USERCONFIG
};

struct conf_field_t
{
	conf_field_t():
		value_int(0),
		value_fl(0),
		archive(false),
		type(CONF_FIELD_UNDEFINED)
	{}

	CString name;

	Int32 value_int;
	float value_fl;
	CString value_str;

	bool archive;
	field_type_t type;
};

struct conf_group_t
{
	conf_group_t():
		type(CONF_GRP_UNDEFINED),
		updatefile(false)
	{}

	CString name;
	CString filename;
	group_type_t type;
	bool updatefile;

	CArray<conf_field_t> fields;
};

/*
=================================
-Class: CConfig
-Description:

=================================
*/
class CConfig
{
public:
	// Default bind file filename
	static const char DEFAULT_BINDS_FILENAME[];
	// System config filename
	static const char SYSTEM_CONFIG_FILENAME[];
	// System config filename
	static const char USER_CONFIG_FILENAME[];
	// Name of the group that holds keybinds
	static const char USER_CONFIG_GRP_NAME[];

public:
	CConfig( void );
	~CConfig( void );

	void Init( void );

	void PostThink( void );
	const cf_status_t GetStatus( void ) const;

public:
	conf_group_t* FindGroup( const char* name );
	conf_group_t* CreateGroup( const char* name, const char* pstrFilename, group_type_t type );
	conf_field_t* CreateField( conf_group_t* pgroup, const char* name, field_type_t type );

	static bool DeleteField( conf_group_t* pgroup, const char* name );
	bool DeleteField( const char* grpName, const char* name );

	bool SetValue( conf_group_t* pgroup, const char* field, Int32 value, bool archive = false );
	bool SetValue( const char* grpName, const char* field, Int32 value, bool archive = false );
	bool SetValue( conf_group_t* pgroup, const char* field, float value, bool archive = false );
	bool SetValue( const char* grpName, const char* field, float value, bool archive = false );
	bool SetValue( conf_group_t* pgroup, const char* field, const char* value, bool archive = false, field_type_t type = CONF_FIELD_STRING );
	bool SetValue( const char* grpName, const char* field, const char* value, bool archive = false, field_type_t type = CONF_FIELD_STRING );

	const Int32 GetInt( conf_group_t* pgroup, const char* field );
	const float GetFloat( conf_group_t* pgroup, const char* field );
	const char* GetString( conf_group_t* pgroup, const char* field );

public:
	void CmdExecuteScript( void );

private:
	void WriteConfigFile( conf_group_t* pgroup, const char* pstrFilename ) const;
	void ReadSystemConfigFile( void );
	static void ReadUserConfigFile( const char* pstrFilename );

private:
	static void FlagRewrite( conf_group_t* pgroup );
	void ResetStatus( void );

private:
	conf_field_t* FindField( conf_group_t* pgroup, const char* field );

private:
	// Error status of config class
	cf_status_t m_configStatus;

	// Available config groups
	CArray<conf_group_t*> m_configGroups;
};
extern CConfig gConfig;
#endif