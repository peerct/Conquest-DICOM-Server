/*
19980321	Mvh	Changed ObjectFile and DeviceName field length to 250 for dbf compatibility
19980321	Mvh	Added define TRUNCATEFIELDNAMES for DBF compatibity (apply in makefile)
19980322	Mvh	Added run-time check on DbaseIII (should also be added in parse.cpp somehow)
19980325	Mvh	Added TruncateFieldNames entry in dicom.ini to allow DBF compatibility
19980327	Mvh	Made MaxFieldLength configurable
19980327	Mvh	Set default event notification to UDP (for personal pacs)
19980407	Mvh	Added FileCompressMode config
19980409	Mvh	Check vr!=NULL in MakeSafeString,MakeSafeDate
19990630	MvH	Remove also files from MIRROR disks
19990707	MvH	Added UpdateOrAddToTable to refresh database contents without first removing
19990707	MvH	Cache Updates; and AccessTime with ~31 to allow update times to be the same
19990707	MvH	Added fix for Philips PATID; fix cleaning of MIRROR device
19990708	MvH	Added (and disabled) stress code for SQL server
19990712	MvH	Fixed FIX_PHILIPS; atoi failed sometimes because vr->data not zero termimated
19990827	MvH	Added creation of key and link indices
19991117	ljz	Added a check on ini-file value of FileCompressMode
20000221	ljz	Changed layout of this update-history
			Fix: In 'SetString', type DT_UINT32 was treated as DT_UINT16
			Added TroubleLogFile and UserLogFile
			When updating PaientRecord, verify the new Name and BirthDate
20000629	ljz	Logging of trouble now starts with '***'
20000701 	mvh 	Remove *all* trailing spaces im MakeSafeString before enters database
20000703        mvh     Merged changes: made patient change verification table and record name 
                        independent and extended to other databases as well; removed trailing 
			spaces before comparison; show patid on all error messages
20000705        mvh     refuse inconsistent update of link: show error on operatorconsole
20000707        mvh     fixed above addition
20001104        mvh     Replaced _rmdir by equaly valid rmdir
20001106        mvh     Use delete [] operation for vr->Data
20001128	ljz	Fix: protected 'GetFileName' with a critical section.
20010415        mvh     Added KeepImages flag to RemoveFromPacs: clear from DB only
20010416        mvh     Added ChangeUID routine and UIDMODS table - to allow modification of images
20010418        mvh     Changed names of database fields in UIDMODS - did not work on msaccess
20010429        mvh     Renamed genuid routine and variables to allow compile in one big file
20010713        mvh     Reduced devicename to 32 chars to space space
20010902	mvh	Improved UpdateCache to be thread safe and made it longer, no test on image db
20011109        mvh     Made MAG check and database field consistency check case insensitive
20011115        mvh     Replaced 'LIKE' by faster '=' when possible
20011116        mvh     Fixed error handling of db entry. It was possible that db entry 
			failed without any message!
20011121        mvh     Create indices on ImagePat and SeriesPat if these fields exist
20020403	ljz	Do not overrrule the PatientTable with: empty data, or birthdate xxxx0101,
			or sex other than MmFf.
20020409        mvh     made LastPatid non-static
20020409        mvh     Removed non-thread safe caching of LastADBE
20020409        mvh     Moved entry into UpdateCache to after succesful Update
20020412        mvh     Made NCACHE configurable and changed it from 16 to 1024 (8 MB); 
                        Set lastfield (limit of #fields) to 20 (was 16)
                        Added checksum code in update cache to make it faster
20020412        mvh     Made key fields unique. reversed writing of db's. In this case
                        a db write fail will still result in a valid db
                        The db write code is not multi-user safe. A new record
                        may be written at the same time by two processes -> fail
20020413        mvh     Set NCACHE to 256, enough for single thread regen
                        Modified another non-thread safe construct
20020415        mvh     Fix display of PatientID in 'Inconsistent' error message
20020416	mvh	Made UID generator configurable through UIDPrefix in dicom.ini
                        Made all instances of time unsigned
                        Note: accesstime in the db is signed int: problem around 2038
20020418      mvh+ljz   Added TimeStamp, Flags, and Spare fields on all dbs for future use
20020430        mvh     Fix in spare fields: name was reserved in some odbc implementations
20020515        mvh     Process all db fields; enter (1) Modality into StudyModality
20020517        mvh     Modality is merged into StudyModality without size limit (enforced by sql server)
20020518	mvh	Skip missing VR's again; max nr fields to 30; fix reading of NULL fields (clear s[][])
20020519	mvh	Also skip writing empty VR's (vr->Length==0); made FixPhilips configurable (default 1)
                        Remove / from date to allow writing mm/dd/yyyy into sql server
20020522	ljz	Test on empty Modality vr
20020529        mvh     Added PRIMARY KEY to key DB fields (needed for replication)
20020529	mvh	InitializeTables now has mode parameter (0=normal, 1=simple); 
                        Do not make Index for primary keys (is done automatically)
20020609        mvh     Added compression modes 3 and 4
20020802        mvh     Simplified rmdir code and allow multiple subdirectories
20020804	mvh	Use PATHSEPCHAR where possible
20020806        mvh     Fix: cleanup entries of refused item in database
20020819        mvh     Added better UID generation
20021016        mvh     Use patid in SaveToDatabase and GetFileName query 
                        (both test for rev5 or higher of the database)
20021017	mvh	Allow set of UIDpostfix from extern (-c option of dgate)
                        Removed creation of unused tables
20021020        mvh     Added [ to MakeSafeString; removed "
                        Note: VR's containing ', ? give spurious inconsistency warning when rewritten
20021028        mvh     Also removed dropping of unused tables; reversed table search to image..pat in FindDBE
			Made inconsistent birtdate a severe error message (added ***)
20021110        mvh     Made date range inclusive (bug reported by Aaron Cann)
20030113        mvh     Added PatientQuerySortOrder etc overrides for sorting
20030205        mvh     Fix potential empty patient ID and SOP problems in GetFilename
20030321	ljz	Extra check on vr!=NULL in SaveToDatabase
20031104   	mvh     Added \\ to MakeSafeString
20040301	ljz	Do not double \\ when allready doubled
20030425   	mvh     Added DoubleBackSlashToDB control for \\
20040528	mvh	Pass patient ID in RemoveFromPacs and Enable KeyOnAll
20040529	mvh	Implemented faster delete from database
20040530	mvh	Pass a field to query in delete - obligatory for sql server
20040601        mvh     Removed enable KeyOnAll - added some more checks in NewDeleteFromDB
20040609        mvh     Check for DB revision for fast delete from database queries
20040610	mvh	Truncate too long VR's before putting into db; log to pacstrouble
20040623	ljz	Fix for non-DBASE datasources in 'UpdateOrAddToTable':
20040626	mvh	Added study and series UID to getfilename interface
20040713        mvh	Added FixKodak: replaces patid 0NNNNNNN with NNNNNNNN
20040722        mvh	Defaults for FixKodak and FixPhilips to 0 (!)
20040930        mvh	Added multiple UID matching: UID\UID\UID in BuildSearchString (list truncates at maximum length)
			SetString now returns a char * which is newed (with lots of extra space 
			for MakeSafeString which is done in-place) if Max length is passed 0
			DICOM2SQLQuery has no max length anymore
20041003        mvh     Trucated printfs of SqlStatement
20041029        mvh     Added MergeUIDs routine
20041101	mvh     Added NewDeleteSopFromDB
20041220	ljz	Fix: in 'RemoveFromPACS', an even PatientID was not zero-terminated !!
20050109        mvh     Adapted for linux compile
20050111        mvh     Added ctype.h (for mingw)
20050205	mvh	Added counters for database activity
20050206	mvh	Allow empty DBE in ConstructVRFromSQL: used to get ObjectFile and Device in query
20050401	mvh	Added WorkListDB and WorkListTableName
20050404	mvh	Dicom types DT_START/ENDSEQUENCE are ignored during table creation/adding to table
20050414	mvh	Allow undefined worklist database; 
			Delete patient will delete worklist entries as well (but needs at least one image)
20050417	mvh	Delete from DB will also delete worklist as patient goes
20050826	mvh	Added mode 2 for initializetables: clear/create worklist only
20050831	mvh	Mode 0 and 1 will now not delete worklist if it contains data
20050831	mvh	VerifyIsInDBE will not return DT_START/ENDSEQUENCE
20050901	mvh	Do not call FixImage in SaveToDataBase: is done in SaveToDisk before
20051121	mvh	Enabled SQLRealSize because SQLResultLength does not work in PostGres BindField
20051123	mvh	Fixed it, and only enable it when #ifdef POSTGRES
20051204	mvh	Disabled it, fixed postgres driver instead
20051210	mvh	GetFilename returns FALSE for an image that has no filename or device set
20051212	mvh	Clear update cache when any records deleted - drastic but safe
20051216	mvh	Small fix in above
20051217   	mvh   	Use new VR::ReAlloc method to replace data in VR
20051218   	mvh   	Fix study modality when DoubleBackSlashToDB=1; changed modality search
20051228	mvh	Truncate invalid trailing spaces (>1) from patient ID. 
20051228	mvh	Fiximage warns to SystemDebug; Renamed DebugVRs to DebugLevel
20060210	mvh	Removed order: first remove spaces and then fix the patient ID
			because patient ID consisting of 14 spaces caused huge troubles
20060220	mvh	Check max 50 fields when update; fix Inconsistent check for DoubleBackSlashToDB
20060607	mvh	Fix character translation for entering *?%[' into sql using MakeSafeStringValues
			Fix consistency check for these characters as well (thanks Robert Chrzan)
20060607	mvh	Added "not null" to "PRIMARY KEY" to satisfy Sybase (thanks Marcin Litoborski)
20060618	mvh	Added not null to UIDmods as well, unified case of DICOMWorkList table name
                        (may be done for other tables as well)(thanks Marcin Litoborski)
20060618	mvh	Remove '' added by MakeSafeStringValues prior to inconsistency check (thanks Robert Chrzan)
20060621	mvh	Increased size of s from [50][255] to [51][256] in UpdateOrAddToTable fixes VirtualQuery crash
20060628	mvh	AddToDatabase has JustAdd parameter: skip one unnecessary query
20060706	mvh	Replaced faulty new vr construct when doing consistency check: faulted on Linux
20061213	mvh	Protect Clear_UpdateCache with critical section
			Fixed nasty bug in NewDeleteFromDB. MergeUIDs, NewDeleteSopFromDB: Query without bindfield overwrites previous bound strings!
20070123	mvh	Fixed GetFileName for patientid with '
			Recoded some of the inconsistency checking: now no failure on patient ID (link) with '
20070131	mvh	Fixed GetFileName for all patientid's ;->>>>
20070201	mvh	Fixed (unused) UpdateAccessTimes for weird patient IDs
20070210	mvh	Added CheckDuplicates to UpdateOrAddToTable: used on DicomStudies to catch inconsistent patientID
			Enabled KeyOnAll on UpdateOrAddToTable: only delete exact records (needed if inconsistent patientID)
20070308	bcb 	Changed to set patient ID to 0 for anonymized patients
20070315	mvh	Merged; also noted that changed possible use of AND at start of sql where
20071027	mvh	Also truncate too long date fields with error message; added AllowTruncate: if sql name 
			in comma separated list: warning only else ***error
20071118	mvh	Adapted for 64 bits (use SQLLEN for BindField)
20080302	mvh	Fixed case of DICOM table names
20080319	mvh	Fixed typo in above change; fixed worklist delete for patients with space in ID
20080817	mvh	Added WorkListReturnsISO_IR_100 flag (default 1)
20080818	mvh 	DbaseIII check now uses DB flags, not PATHSEP in datasource name
			Added experimental DT_MSTR: multi-value entry, e.g. query on 'PET' matches 'PET\CT' 
			if studymodality is given type DT_MSTR instead of DT_STR. Note: not implemented for DBASEIII
20080819	mvh 	Added warning when querying DT_MSTR field on dbase
20080902	mvh	added EnableComputedFields (default 0)
*/

#define NCACHE 256

#ifndef	WHEDGE
#	include	"dgate.hpp"
#else
#	include	"master.h"
#endif

#ifndef UNIX
#	include	<direct.h>
#else
#include <unistd.h>
#include <ctype.h>
#include "gpps.hpp"
#define	stricmp(s1, s2)	strcasecmp(s1, s2)
#define EnterCriticalSection(a) pthread_mutex_lock(a)
#define LeaveCriticalSection(a) pthread_mutex_unlock(a)
#define CRITICAL_SECTION pthread_mutex_t
#define InitializeCriticalSection(a) pthread_mutex_init(a, NULL);
#define DeleteCriticalSection(a) pthread_mutex_destroy(a);
#endif
#	include	<time.h>
#	include	<stdlib.h>
#	include <ctype.h>

DBENTRY	*PatientDB = NULL, *StudyDB = NULL, *SeriesDB = NULL, *ImageDB = NULL, *WorkListDB = NULL;
DBENTRY	*LastADBE = NULL;

UINT	DebugVRs = 0;
UINT	Edition = E_WORKGROUP;
char	EditionText[128] = "Workgroup";
char	DataHost[128] = "localhost";
char	DataSource[128] = "LABRAD2";
char	UserName[128] = "Administrator";
char	Password[128] = "password";
char	PatientTableName [64] = "DICOMPatients";
char	StudyTableName [64] = "DICOMStudies";
char	SeriesTableName [64] = "DICOMSeries";
char	ImageTableName [64] = "DICOMImages";
char	WorkListTableName [64] = "DICOMWorkList";
char	DMarkTableName [64] = "DICOMAccessUpdates";
char	RegisteredMOPIDTableName [64] = "RegisteredMOPIDs";
char	UIDToMOPIDTableName [ 64 ] = "UIDToMOPID";
char	UIDToCDRIDTableName [ 64 ] = "UIDToCDRID";
BYTE	Port [ 64 ];
BYTE	KFACTORFILE [ 256 ] = "dicom.sql";
BYTE	MYACRNEMA [ 64 ] = "none";
char	SOPClassFile [ 128 ] = "dgatecls.lst";
#ifndef UNIX
char	OCPipeName[256] = "\\\\.\\pipe\\MicroPACSStatus";
char	ACPipeName[256] = "\\\\.\\pipe\\MicroPACSAccess";
#else
char	OCPipeName[256] = "/tmp/MicroPACSStatus";
char	ACPipeName[256] = "/tmp/MicroPACSAccess";
#endif
char	ServerName[256] = "Marks Machine";
char	UserLogFile[256] = "PacsUser.log";
char	TroubleLogFile[256] = "PacsTrouble.log";

int	SkippedCachedUpdates=0;
int	UpdateDatabase=0;
int	AddedDatabase=0;

#	define	DEBUG_MODE

#ifndef	RootConfig
extern	char	RootConfig[];
#endif
#ifndef	ConfigFile
extern	char	ConfigFile[];
#endif

static int	TruncateFieldNames=0;
static int	MaxFieldLength=0;
static int	FixPhilips=0;
static int	FixKodak=0;
static int	DoubleBackSlashToDB=0;

int	FileCompressMode=0;
char	PatientQuerySortOrder[256]="";
char	StudyQuerySortOrder[256]="";
char	SeriesQuerySortOrder[256]="";
char	ImageQuerySortOrder[256]="";
char	AllowTruncate[256]="";
int     WorkListReturnsISO_IR_100=0;
int     EnableComputedFields=0;

// Forward declaration

BOOL
UpdateOrAddToTable(
	Database		&DB,
	DBENTRY			*DCMGateDB,
	char			*TableName,
	DICOMDataObject		*DDOPtr,
	char			*ObjectFile,
	char			*DeviceName,
	char			*Patid,
	char			*Modality,
	BOOL			*Added,
	BOOL			JustAdd,
	BOOL			CheckDuplicates);

static
void
ConfigDBSpecials(void)
	{
	char		RootSC[64];
	char		Temp[128];

	GetPrivateProfileString ( RootConfig, "MicroPACS", RootConfig,
		(char*) RootSC, 64, ConfigFile);

	GetPrivateProfileString ( RootSC, "TruncateFieldNames", "0",
		(char*) Temp, 128, ConfigFile);
	TruncateFieldNames = atoi(Temp);

	GetPrivateProfileString ( RootSC, "MaxFieldLength", "0",
		(char*) Temp, 128, ConfigFile);
	MaxFieldLength = atoi(Temp);

	GetPrivateProfileString ( RootSC, "DoubleBackSlashToDB", "0",
		(char*) Temp, 128, ConfigFile);
	DoubleBackSlashToDB = atoi(Temp);

	GetPrivateProfileString ( RootSC, "FixPhilips", "0",
		(char*) Temp, 128, ConfigFile);
	FixPhilips = atoi(Temp);

	GetPrivateProfileString ( RootSC, "FixKodak", "0",
		(char*) Temp, 128, ConfigFile);
	FixKodak = atoi(Temp);

	GetPrivateProfileString ( RootSC, "WorkListReturnsISO_IR_100", "1",
		(char*) Temp, 128, ConfigFile);
	WorkListReturnsISO_IR_100 = atoi(Temp);

	GetPrivateProfileString ( RootSC, "EnableComputedFields", "0",
		(char*) Temp, 128, ConfigFile);
	EnableComputedFields = atoi(Temp);

	GetPrivateProfileString ( RootSC, "FileCompressMode", "0",
		(char*) Temp, 128, ConfigFile);
	FileCompressMode = atoi(Temp);
	if ((FileCompressMode < 0) || (FileCompressMode > 4))
	  FileCompressMode = 0;

	GetPrivateProfileString ( RootSC, "PatientQuerySortOrder", "",
		(char*) PatientQuerySortOrder, 256, ConfigFile);

	GetPrivateProfileString ( RootSC, "SeriesQuerySortOrder", "",
		(char*) SeriesQuerySortOrder, 256, ConfigFile);

	GetPrivateProfileString ( RootSC, "StudyQuerySortOrder", "",
		(char*) StudyQuerySortOrder, 256, ConfigFile);

	GetPrivateProfileString ( RootSC, "ImageQuerySortOrder", "",
		(char*) ImageQuerySortOrder, 256, ConfigFile);

	GetPrivateProfileString ( RootSC, "AllowTruncate", "",
		(char*) AllowTruncate, 256, ConfigFile);
	strcat(AllowTruncate, ",");
	}

BOOL
ConfigDebug (
	char	*ConfigSection,
	char	*ConfigFile,
	char	*Prefix,
	Debug	*Dbg )
	{
	char	ConfigString[128];
	char	Temp[128];
	char	Temp2[128];

	strcpy(ConfigString, Prefix);
	strcat(ConfigString, ".TransportType");
		
	GetPrivateProfileString ( ConfigSection, ConfigString,
		"UDP",
		(char*) Temp, 64, ConfigFile);
	if ( ! stricmp ( Temp, "File" ) )
		{
		strcpy(ConfigString, Prefix);
		strcat(ConfigString, ".FileName");
		GetPrivateProfileString ( ConfigSection, ConfigString,
			"nofile.log",
			(char*) Temp, 64, ConfigFile);
		Dbg->On(Temp);
		
		return ( TRUE );
		}
	else
	if ( ! stricmp ( Temp, "NamedPipe") )
		{
		strcpy(ConfigString, Prefix);
		strcat(ConfigString, ".NamedPipeName");
		GetPrivateProfileString ( ConfigSection, ConfigString,
			"\\\\.\\pipe\\nopipe",
			(char*) Temp, 64, ConfigFile);
		Dbg->OnMsgPipe(Temp);
		
		return ( TRUE );
		}
	else
	if ( ! stricmp ( Temp, "UDP" ) )
		{
		strcpy(ConfigString, Prefix);
		strcat(ConfigString, ".UDPHost");
		GetPrivateProfileString ( ConfigSection, ConfigString,
			"localhost",
			(char*) Temp, 64, ConfigFile);
		strcpy(ConfigString, Prefix);
		strcat(ConfigString, ".UDPPort");
		GetPrivateProfileString ( ConfigSection, ConfigString,
			"1111",
			(char*) Temp2, 64, ConfigFile);
		Dbg->OnUDP(Temp, Temp2);
		
		return ( TRUE );
		}
	return ( FALSE );
	}

/*	
BOOL
ConfigEventNotification (
	char	*ConfigSection,
	char	*ConfigFile )
	{
	ConfigDebug ( ConfigSection, ConfigFile, "MajorEvent", &MajorEvent );
	ConfigDebug ( ConfigSection, ConfigFile, "MinorEvent", &MinorEvent );
	return ( TRUE );		
	}
*/
	
BOOL	ConfigMicroPACS()
	{
	char	RootSC[64];
	char	Temp[128];

	GetPrivateProfileString ( RootConfig, "MicroPACS", RootConfig,
		(char*) RootSC, 64, ConfigFile);

	GetPrivateProfileString ( RootSC, "Edition", "Workgroup",
		(char*) EditionText, 64, ConfigFile);
	
	if ( !stricmp(EditionText, "Workgroup"))
		Edition = E_WORKGROUP;
	else
	if ( !stricmp(EditionText, "Personal"))
		Edition = E_PERSONAL;
	else
	if ( !stricmp(EditionText, "Enterprise"))
		Edition = E_ENTERPRISE;
	else
		Edition = E_WORKGROUP;
		

	GetPrivateProfileString ( RootSC, "TCPPort", "104",
		(char*) Port, 64, ConfigFile);

	GetPrivateProfileString ( RootSC, "DebugLevel", "0",
		(char*) Temp, 64, ConfigFile);DebugVRs = atoi(Temp);

	GetPrivateProfileString ( RootSC, "kFactorFile", "dicom.sql",
		(char*) KFACTORFILE, 64, ConfigFile);

	GetPrivateProfileString ( RootSC, "ACRNemaMap", "acrnema.map",
		(char*) ACRNEMAMAP, 64, ConfigFile);

	GetPrivateProfileString ( RootSC, "MyACRNema", "none",
		(char*) MYACRNEMA, 64, ConfigFile);

	GetPrivateProfileString ( RootSC, "SOPClassList", "dgatesop.lst",
		(char*) SOPClassFile, 128, ConfigFile);

	// SQL server network hostname

	GetPrivateProfileString ( RootSC, "SQLHost", "localhost",
		(char*) DataHost, 128, ConfigFile);

	if(strlen(DataHost) == 0)
		{
		strcpy(DataHost, "localhost");
		}

	GetPrivateProfileString ( RootSC, "SQLServer", "LABRAD2",
		(char*) DataSource, 128, ConfigFile);

	GetPrivateProfileString ( RootSC, "Username", "Administrator",
		(char*) UserName, 128, ConfigFile);

	GetPrivateProfileString ( RootSC, "Password", "password",
		(char*) Password, 128, ConfigFile);

	GetPrivateProfileString ( RootSC, "PatientTableName", "DICOMPatients",
		(char*) PatientTableName, 64, ConfigFile);
	GetPrivateProfileString ( RootSC, "WorkListTableName", "DICOMWorkList",
		(char*) WorkListTableName, 64, ConfigFile);
	GetPrivateProfileString ( RootSC, "StudyTableName", "DICOMStudies",
		(char*) StudyTableName, 64, ConfigFile);
	GetPrivateProfileString ( RootSC, "SeriesTableName", "DICOMSeries",
		(char*) SeriesTableName, 64, ConfigFile);
	GetPrivateProfileString ( RootSC, "ImageTableName", "DICOMImages",
		(char*) ImageTableName, 64, ConfigFile);
	GetPrivateProfileString ( RootSC, "DMarkTableName", "DICOMAccessUpdates",
		(char*) DMarkTableName, 64, ConfigFile);
	GetPrivateProfileString ( RootSC, "RegisteredMOPIDTableName", "RegisteredMOPIDs",
		(char*) RegisteredMOPIDTableName, 64, ConfigFile);
	GetPrivateProfileString ( RootSC, "UIDToMOPIDTableName", "UIDToMOPID",
		(char*) UIDToMOPIDTableName, 64, ConfigFile);
	GetPrivateProfileString ( RootSC, "UIDToCDRIDTableName", "UIDToCDRID",
		(char*) UIDToCDRIDTableName, 64, ConfigFile);
	GetPrivateProfileString ( RootSC, "OperatorConsole",
		"\\\\.\\pipe\\MicroPACSStatus", (char*)OCPipeName, 128, ConfigFile);
	GetPrivateProfileString ( RootSC, "AccessUpdates",
		"\\\\.\\pipe\\MicroPACSAccess", (char*)ACPipeName, 128, ConfigFile);
	GetPrivateProfileString ( RootSC, "PACSName", "MicroPACS",
		(char*) ServerName, 128, ConfigFile);
	GetPrivateProfileString ( RootSC, "UserLog", "PacsUser.log",
		(char*) UserLogFile, 128, ConfigFile);
	GetPrivateProfileString ( RootSC, "TroubleLog", "PacsTrouble.log",
		(char*) TroubleLogFile, 128, ConfigFile);

//	ConfigEventNotification ( RootSC, ConfigFile );
	
	ConfigDBSpecials();

	InitializeDeviceTable (RootSC);
	return ( TRUE );
	}



DWORD
CurrentTime()
	{
	return((DWORD)time(NULL) & (~31));
	}

char	*
UniqueKey(
	DBENTRY	*DBE)
	{
	if(!DBE)
		return ("null");
	return ( DBE[0].SQLColumn );
	}


char	*
UniqueLink(
	DBENTRY	*DBE)
	{
	if(!DBE)
		return( "null");

	return( DBE[LastDBE(DBE)].SQLColumn );
	}

BOOL
AddStudyInstanceUID (DICOMDataObject	*DDOPtr)
	{
	VR	*vr;

	// Search for the UID elsewere

	vr = DDOPtr->GetVR(0x0021, 0x1070);
	if(vr)
		{
		VR	*vrNew = new VR(0x0020, 0x000d, vr->Length, TRUE);
		memcpy(vrNew->Data, vr->Data, vr->Length);
		DDOPtr->Push(vrNew);
		return ( TRUE );
		}
	// not sure what to do.
	VR	*vrNew = new VR(0x0020, 0x000d, 10, TRUE);
	strcpy((char*)vrNew->Data, "undefined");
	DDOPtr->Push(vrNew);
	return ( TRUE );
	}
	
BOOL
AddSeriesInstanceUID (DICOMDataObject	*DDOPtr)
	{
	VR	*vr;

	// Search for the UID elsewere

	vr = DDOPtr->GetVR(0x0021, 0x1071);
	if(vr)
		{
		VR	*vrNew = new VR(0x0020, 0x000e, vr->Length, TRUE);
		memcpy(vrNew->Data, vr->Data, vr->Length);
		DDOPtr->Push(vrNew);
		return ( TRUE );
		}
	// not sure what to do.
	VR	*vrNew = new VR(0x0020, 0x000e, 10, TRUE);
	strcpy((char*)vrNew->Data, "undefined");
	DDOPtr->Push(vrNew);
	return ( TRUE );
	}
	
		
// Fix possible problems in an image.
BOOL
FixImage(DICOMDataObject *DDOPtr)
	{
	// This routine fixes some deficient images (sent from outdated
	//  modalities).

	VR	*vr;
	int	i, count;

	vr = DDOPtr->GetVR(0x0010, 0x0010);
	if(!vr)
		{
		vr = new VR(0x0010, 0x0010, 8, (BOOL)TRUE);
		memcpy(vr->Data, (void*)"NO NAME", 8);
		DDOPtr->Push(vr);
		SystemDebug.printf("Fiximage: Added patient name\n");
		}
			
	// truncate invalid trailing spaces (more than one) from patient ID
	
	vr = DDOPtr->GetVR(0x0010, 0x0020);
	if(vr)
		{
		count=0;
		for (i=vr->Length-1; i>=0; i--)
	        	if (((char*)(vr->Data))[i]==' ') count++; else break;
	        if (count > 0)
			{
			vr->Length -= count;
			if (vr->Length&1) vr->Length++, count--;
			if (count) SystemDebug.printf("Fiximage: truncated %d trailing spaces from patient ID\n", count);
			}
		}

	if(!vr)
		{
		vr = new VR(0x0010, 0x0020, 8, (BOOL)TRUE);
		memcpy(vr->Data, (void*)"00000000", 8);
		DDOPtr->Push(vr);
		SystemDebug.printf("Fiximage: Added patient ID\n");
		}

	else if (vr->Length < 2)
		{
		int		Length;
		char	*s;
		
		s = (char*)vr->Data;
		Length = vr->Length;
		
		while ( Length )
			{
			if (s[Length] == ' ')
				{
				--Length;
				continue;
				}
			if (s[Length] == '\0')
				{
				--Length;
				continue;
				}
			break;
			}
		vr->Length = Length;
		
		if ( vr->Length < 2)
			{
			vr->ReAlloc(8);
			memcpy(vr->Data, (void*)"00000000", 8);
			}
		SystemDebug.printf("Fiximage: Fixed empty patient ID\n");
		}

	else if (vr->Length==10 && vr->Data && FixPhilips)
		{
		char patid[11];
		int Length;

		memcpy(patid, (char *)(vr->Data), 10);
		patid[10]=0;

		if ( patid[0] == '0' && patid[1] == '0' && atoi(patid)>1000000 )
			{
			memset(patid, 0, 10);
			if      (((char *)(vr->Data))[2]=='0') memcpy(patid, ((char *)(vr->Data)) + 3, Length=7);
			else if (((char *)(vr->Data))[1]=='0') memcpy(patid, ((char *)(vr->Data)) + 2, Length=8);
			else if (((char *)(vr->Data))[0]=='0') memcpy(patid, ((char *)(vr->Data)) + 1, Length=9);
			else	                   memcpy(patid, (char *)(vr->Data) + 0, Length=10);
			if (Length&1) Length++;

			vr->ReAlloc(Length);
			memcpy(vr->Data, patid, Length);
	
			SystemDebug.printf("Fiximage: Fixed Philips patient ID\n");
			}
		}
	
	else if (vr->Length==8 && vr->Data && FixKodak)
		{
		char patid[11];
		int Length;

		memcpy(patid, (char *)(vr->Data), 8);
		patid[8]=0;

		if ( patid[0] == '0' && atoi(patid)>1000000 )
			{
			memset(patid, 0, 10);
			if (((char *)(vr->Data))[0]=='0') memcpy(patid, ((char *)(vr->Data)) + 1, Length=7);
			else	                          memcpy(patid,  (char *)(vr->Data)  + 0, Length=8);
			if (Length&1) Length++;

			vr->ReAlloc(Length);
			memcpy(vr->Data, patid, Length);

			SystemDebug.printf("Fiximage: Fixed Kodak patient ID\n");
			}
		}
	
        vr = DDOPtr->GetVR(0x0020, 0x000d);
	if(!vr)
		AddStudyInstanceUID ( DDOPtr );
	vr = DDOPtr->GetVR(0x0020, 0x000e);
	if(!vr)
		AddSeriesInstanceUID ( DDOPtr );

	return ( TRUE );
	}

/////////////////////////////////////////////////////////////////
/* This code forms a cache that saves the last NCACHE entries */
/* If the entry already exists, db writing can be skipped      */
/////////////////////////////////////////////////////////////////

char			UpdateCache[NCACHE][8192];
int			UpdateCheckSums[NCACHE];
CRITICAL_SECTION 	UpdateCritical;
int			UpdateTop=0, UpdateBottom=0;

int into_UpdateCache(char *in)
	{ 
	int i, sum, r;
	char *p = in;

	sum = 0;
	while(*p) sum+=*p++;

	if (UpdateTop==0 && UpdateBottom==0)
		InitializeCriticalSection(&UpdateCritical);

	EnterCriticalSection(&UpdateCritical);

	/* clear cache if it is empty */
	if (UpdateTop==0 && UpdateBottom==0)
		for (i=0; i<NCACHE; i++)
			UpdateCache[i][0]=0;

	if ((UpdateTop+1)%NCACHE == UpdateBottom)
		UpdateBottom = (UpdateBottom+1)%NCACHE;	// delete oldest entry

	strcpy(UpdateCache[UpdateTop], in);
        UpdateCheckSums[UpdateTop] = sum;
        r = UpdateTop;

      	UpdateTop = (UpdateTop+1)%NCACHE;

	LeaveCriticalSection(&UpdateCritical);

	return r;
  	}

int isin_UpdateCache(char *in)
	{
	int i, sum;
	char *p = in;

	if (UpdateTop==0 && UpdateBottom==0) return 0;

	sum = 0;
	while(*p) sum+=*p++;

	EnterCriticalSection(&UpdateCritical);

	for (i=UpdateTop; i!=UpdateBottom; i=(i==0 ? NCACHE-1 : i-1))
		{
		if (UpdateCheckSums[i] == sum)
			if (strcmp(UpdateCache[i], in)==0)
				{
				LeaveCriticalSection(&UpdateCritical);
				return 1;
				}
		}
				
	LeaveCriticalSection(&UpdateCritical);
	return 0;
	}

// clear entire cache
void clear_UpdateCache(void)
	{
	if (UpdateTop==0 && UpdateBottom==0) return;

	EnterCriticalSection(&UpdateCritical);
	for (int i=0; i<NCACHE; i++)
		{
		UpdateCache[i][0]=0;
		UpdateCheckSums[i] = -1;
		}
	LeaveCriticalSection(&UpdateCritical);
	}

BOOL
SaveToDataBase(
	Database		&DB,
	DICOMDataObject	*DDOPtr,
	char			*filename,
	char			*device,
	BOOL			JustAdd)
	{
	char LastPatid[65], Modality[17];
	char s1[128];
	BOOL AddedImage, AddedStudy, AddedSeries, AddedPatient;

	VR	*vr;

	memset(LastPatid, 0, 65);
	vr = DDOPtr->GetVR(0x0010, 0x0020);

	//Note: Some Anonymized patients have no Patient ID.
	//The DICOMPatients table requires an ID, So set it to 0.
	if(!vr) 
		{
		vr = new VR;
		vr->Group = 0x0010;
		vr->Element = 0x0020;
		vr->Length = 2;
		vr->ReAlloc(vr->Length);
		if ( !vr->Data ) return ( FALSE );	// memory error
		memcpy(vr->Data,"0 ", vr->Length);
		DDOPtr->Push(vr);
		}

	memcpy(LastPatid, vr->Data, vr->Length);
	if (vr && vr->Length)
        	if (LastPatid[vr->Length-1]==' ') LastPatid[vr->Length-1]=0;

	memset(Modality, 0, 17);
	vr = DDOPtr->GetVR(0x0008, 0x0060);
	if(vr)
		{
		memcpy(Modality, vr->Data, vr->Length);
		if (vr->Length)
			if (Modality[vr->Length-1]==' ')
				Modality[vr->Length-1] = 0;
		}
	// Modality[2] = 0;	// option to truncate all RT item to save StudyModality space

	// FixImage(DDOPtr);

	VR	*SOPInstance = DDOPtr->GetVR(0x0008, 0x0018);
	MakeSafeString(SOPInstance, s1);
	AccessUpdate.printf("%s", s1);

//	RemoveDuplicates(DB, PatientDB, PatientTableName, DDOPtr, FALSE);
//	AddToTable(DB, PatientDB, PatientTableName, DDOPtr, NULL, NULL);
//	RemoveDuplicates(DB, StudyDB, StudyTableName, DDOPtr, FALSE);
//	AddToTable(DB, StudyDB, StudyTableName, DDOPtr, NULL, NULL);
//	RemoveDuplicates(DB, SeriesDB, SeriesTableName, DDOPtr, FALSE);
//	AddToTable(DB, SeriesDB, SeriesTableName, DDOPtr, NULL, NULL);
//	RemoveDuplicates(DB, ImageDB, ImageTableName, DDOPtr, FALSE);
//	AddToTable(DB, ImageDB, ImageTableName, DDOPtr, filename, device);

	if (!UpdateOrAddToTable(DB, ImageDB,   ImageTableName,   DDOPtr, filename, device, LastPatid, NULL, &AddedImage, JustAdd, FALSE))
		return FALSE;

	if (!UpdateOrAddToTable(DB, SeriesDB,  SeriesTableName,  DDOPtr, filename, NULL,   LastPatid, NULL, &AddedSeries, FALSE, FALSE))
		{
	        if (AddedImage)  RemoveDuplicates(DB, ImageDB, ImageTableName, DDOPtr, TRUE);
		return FALSE;
		}

												// check for conflicting patid -------V */
	if (!UpdateOrAddToTable(DB, StudyDB,   StudyTableName,   DDOPtr, filename, NULL,   LastPatid, Modality, &AddedStudy, FALSE, TRUE))
		{
		if (AddedSeries) RemoveDuplicates(DB, SeriesDB, SeriesTableName, DDOPtr, TRUE);
	        if (AddedImage)  RemoveDuplicates(DB, ImageDB, ImageTableName, DDOPtr, TRUE);
		return FALSE;
		}

	if (!UpdateOrAddToTable(DB, PatientDB, PatientTableName, DDOPtr, filename, NULL,   LastPatid, NULL, &AddedPatient, FALSE, FALSE))
		{
		if (AddedStudy)  RemoveDuplicates(DB, StudyDB, StudyTableName, DDOPtr, TRUE);
		if (AddedSeries) RemoveDuplicates(DB, SeriesDB, SeriesTableName, DDOPtr, TRUE);
	        if (AddedImage)  RemoveDuplicates(DB, ImageDB, ImageTableName, DDOPtr, TRUE);
		return FALSE;
		}

	return ( TRUE );
	}

char *
SetString(VR	*vr, char	*s, int	Max)
	{
	int		Index;
	UINT16	*tuint16;
	UINT32	*tuint32;
	DBENTRY	*DBE;

	// when Max = 0 passed: alloc automatically at right size; pointer returned

	if (Max==0)
		{
		if (vr) Max = 2 * vr->Length + 3; else Max = 255;	// must allow MakeSafeString in-place (!)
		if (Max < 255) Max = 255;
		s = new char[Max];
		}

	memset((void*)s, 0, Max);

	if(vr)
		if(vr->Data)
			{
			DBE = FindDBE(vr);
			if(!DBE)
				{
				memcpy((void*)s, vr->Data, vr->Length%Max);
				return ( s );
				}
			switch(DBE->DICOMType)
				{
				case	DT_UI:
				case	DT_STR:
				case	DT_MSTR:
				case	DT_DATE:
					memcpy((void*)s, vr->Data, vr->Length%Max);
					Index = strlen(s);
					if(Index)
						{
						if(s[Index-1]==' ')
							{
							s[Index-1]='\0';
							}
						}
					return ( s );
				case	DT_UINT16:
					tuint16 = (UINT16*)vr->Data;
					sprintf(s, "%d", (*tuint16));
					return ( s );
				case	DT_UINT32:
//					tuint16 = (UINT16*)vr->Data;
//					sprintf(s, "%d", (*tuint16));
					tuint32 = (UINT32*)vr->Data;
					sprintf(s, "%d", (*tuint32));
					return ( s );
				default:
					memcpy((void*)s, vr->Data, vr->Length%Max);
					return ( s );
				}
			}
	return ( s );
	}


BOOL MakeSafeStringValues (VR *vr, char *string);

BOOL
AddToTable(
	Database		&DB,
	DBENTRY			*DCMGateDB,
	char			*TableName,
	DICOMDataObject	*DDOPtr,
	char			*ObjectFile,
	char			*DeviceName)
	{
	UINT		Index, CIndex;
	Array < VR * >	VRArray;
	VR				*vr;
	VR				FakeVR;
	char		Columns [ 4096 ];
	char		Values [ 4096 ];
	char		TempString [ 512 ];


	Index = 0;CIndex = 0;
	Columns [ 0 ] = '\0';
	while ( TRUE )
		{
		if( ! DCMGateDB[Index] . Element )
			break;
		if (DCMGateDB[Index].DICOMType==DT_STARTSEQUENCE || DCMGateDB[Index].DICOMType==DT_ENDSEQUENCE)
			vr = NULL;
		else
			vr = DDOPtr->GetVR(	DCMGateDB [ Index ] . Group,
						DCMGateDB [ Index ] . Element );
		LastADBE = &DCMGateDB[Index];
		VRArray.Add(vr);
		if(vr)
			{
			if(CIndex)
				strcat(Columns, ", ");
			strcat(Columns, DCMGateDB [ Index ] . SQLColumn);
			++CIndex;
			}
		++Index;
		}
	strcat( Columns, ", AccessTime" );
	if(ObjectFile)
		strcat ( Columns, ", ObjectFile" );
	if(DeviceName)
		strcat ( Columns, ", DeviceName" );

	Index = 0;CIndex = 0;
	Values [ 0 ] = '\0';

	while ( Index < VRArray.GetSize() )
		{
		if ( (vr = VRArray.Get ( Index ) ) )
			{
			if(CIndex)
				strcat ( Values, ", ");
			LastADBE = &DCMGateDB[Index];
			switch(DCMGateDB[Index].SQLType)
				{
				case	SQL_C_CHAR:
					MakeSafeStringValues ( vr, TempString );
					break;
				case	SQL_C_DATE:
					MakeSafeDate ( vr, TempString );
					break;
				default:
					SystemDebug.printf("Unknown SQL Type: %d\n",
						DCMGateDB[Index].SQLType);
				}
			strcat ( Values, TempString );
			++CIndex;
			}
		++Index;
		}
	sprintf(TempString, ", %u", CurrentTime() );
	strcat(Values, TempString );
	if(ObjectFile)
		{
		LastADBE = NULL;
		strcat(Values, ", ");
		FakeVR.Data = (void*)ObjectFile;
		FakeVR.Length = strlen(ObjectFile);
		MakeSafeStringValues ( &FakeVR, TempString );
		FakeVR.Data = NULL;
		FakeVR.Length = 0;
		strcat ( Values, TempString );
		}
	if(DeviceName)
		{
		LastADBE = NULL;
		strcat(Values, ", ");
		FakeVR.Data = (void*)DeviceName;
		FakeVR.Length = strlen(DeviceName);
		MakeSafeStringValues ( &FakeVR, TempString );
		FakeVR.Data = NULL;
		FakeVR.Length = 0;
		strcat ( Values, TempString );
		}

	if(!DB.AddRecord(TableName, Columns, Values))
		{
		SystemDebug.printf ( "***Unable to DB.Add()\n");
		SystemDebug.printf ( "***SQL: %.1000s\n", DB.SQLStatement);
		DB.PrintLastError();
		return ( FALSE );
		}
	return ( TRUE );
	}

BOOL
UpdateOrAddToTable(
	Database		&DB,
	DBENTRY			*DCMGateDB,
	char			*TableName,
	DICOMDataObject		*DDOPtr,
	char			*ObjectFile,
	char			*DeviceName,
	char			*Patid,
	char			*Modality,
	BOOL			*Added,
	BOOL			JustAdd,
	BOOL			CheckDuplicates)
	{
	UINT			Index, CIndex;
	Array < VR * >		VRArray;
	VR			*vr;
	VR			FakeVR;
	char			Columns [ 4096 ];
	char			Values [ 4096 ];
	char			Updates [ 8192 ];
	char			Where [512];
	char			TempString [ 512 ];
	SQLLEN			sdword;
	char			*pTmp;
	char			*pTmp2;
	int			i, j, len, lastfield=50, r;
	char			s[51][256];
	int			pm1=0, pm2=0, im=0, flag;
	char 			Temp2[256], Temp3[256];

	*Added = FALSE;

        if (LastDBE(DCMGateDB) < lastfield) lastfield = LastDBE(DCMGateDB);

	Index = 0; CIndex = 0;
	Columns [ 0 ] = '\0';

	while ( TRUE )
		{
		if( ! DCMGateDB[Index] . Element )
			break;
		if (DCMGateDB[Index].DICOMType==DT_STARTSEQUENCE || DCMGateDB[Index].DICOMType==DT_ENDSEQUENCE)
			vr = NULL;
		else
			vr = DDOPtr->GetVR(	DCMGateDB [ Index ] . Group,
						DCMGateDB [ Index ] . Element );
		LastADBE = &DCMGateDB[Index];
		VRArray.Add(vr);
		if ( vr || (DCMGateDB[Index].Group==0x0008 && DCMGateDB[Index].Element==0x0061 && Modality))
			if ( (vr && vr->Length != 0) || (DCMGateDB[Index].Group==0x0008 && DCMGateDB[Index].Element==0x0061 && Modality) )
			{
			if(CIndex)
				strcat(Columns, ", ");
			strcat(Columns, DCMGateDB [ Index ] . SQLColumn);
			++CIndex;
			}
		++Index;
		}

	strcat( Columns, ", AccessTime" );
	if(ObjectFile && DCMGateDB==ImageDB)
		strcat ( Columns, ", ObjectFile" );
	if(DeviceName)
		strcat ( Columns, ", DeviceName" );

	Index = 0; CIndex = 0;
	Values [ 0 ] = '\0';
	Updates[ 0 ] = '\0';
	Where  [ 0 ] = '\0';

	while ( Index < VRArray.GetSize() )
		{
		vr = VRArray.Get ( Index );
		if ( vr || (DCMGateDB[Index].Group==0x0008 && DCMGateDB[Index].Element==0x0061 && Modality))
			if ( (vr && vr->Length != 0) || (DCMGateDB[Index].Group==0x0008 && DCMGateDB[Index].Element==0x0061 && Modality) )
			{
			if(CIndex)
				{	
				strcat ( Values, ", ");
				strcat ( Updates, ", ");
				}

			LastADBE = &DCMGateDB[Index];
			switch(DCMGateDB[Index].SQLType)
				{
				case	SQL_C_CHAR:
					if (vr && DCMGateDB[Index].SQLLength < vr->Length)
						{
						int save = vr->Length;
						char name[80];
						vr->Length = DCMGateDB[Index].SQLLength;
						MakeSafeStringValues ( vr, TempString );
						vr->Length = save;
						strcpy(name, DCMGateDB[Index].SQLColumn);
						strcat(name, ",");
						if (strstr(AllowTruncate, name))
						  	OperatorConsole.printf("Truncated %s from %d to %d chars in file: %s\n", DCMGateDB[Index].SQLColumn, save, DCMGateDB[Index].SQLLength, ObjectFile);
						else
						  	OperatorConsole.printf("***Truncated %s from %d to %d chars in file: %s\n", DCMGateDB[Index].SQLColumn, save, DCMGateDB[Index].SQLLength, ObjectFile);
						}
					else
						MakeSafeStringValues ( vr, TempString );
					break;
				case	SQL_C_DATE:
					if (vr && DCMGateDB[Index].SQLLength < vr->Length)
						{
						int save = vr->Length;
						char name[80];
						vr->Length = DCMGateDB[Index].SQLLength;
						MakeSafeDate ( vr, TempString );
						vr->Length = save;
						strcpy(name, DCMGateDB[Index].SQLColumn);
						strcat(name, ",");
						if (strstr(AllowTruncate, name))
						  	OperatorConsole.printf("Truncated %s from %d to %d chars in file: %s\n", DCMGateDB[Index].SQLColumn, save, DCMGateDB[Index].SQLLength, ObjectFile);
						else
						  	OperatorConsole.printf("***Truncated %s from %d to %d chars in file: %s\n", DCMGateDB[Index].SQLColumn, save, DCMGateDB[Index].SQLLength, ObjectFile);
						}
					else
						MakeSafeDate ( vr, TempString );
					break;
				default:
					SystemDebug.printf("Unknown SQL Type: %d\n",
						DCMGateDB[Index].SQLType);
				}

			if (DCMGateDB[Index].Group==0x0008 && DCMGateDB[Index].Element==0x0061 && Modality)
				{
				strcat ( Values, "'" );
				strcat ( Values, Modality );
				strcat ( Values, "'" );
				}
			else
				strcat ( Values, TempString );

			strcat ( Updates, " ");
			strcat ( Updates, DCMGateDB [ Index ] . SQLColumn );
			strcat ( Updates, " = ");

			// enter incoming modality into studymodality
			if (DCMGateDB[Index].Group==0x0008 && DCMGateDB[Index].Element==0x0061 && Modality)
				{
				im = Index;
				strcat ( Updates, "'" ); pm1 = strlen(Updates);
				strcat ( Updates, Modality );
				strcat ( Updates, "'" ); pm2 = strlen(Updates);
				}
			else
				strcat ( Updates, TempString );

			if (Index==0)
				{
				strcat ( Where, DCMGateDB [ Index ] . SQLColumn );
				strcat ( Where, " = ");
				strcat ( Where, TempString );
				}

			// include (indexed) patient ID to query for speed (only active in rev5 db or higher) except when checking for duplicates
			if (!CheckDuplicates && Index && DCMGateDB[Index].Group==0x0010 && DCMGateDB[Index].Element==0x0020)
				{
				if(Where[0] != '\0')
					strcat ( Where, " AND "); // bcb Was putting an AND onto the beginning of Where
				strcat ( Where, DCMGateDB [ Index ] . SQLColumn );
				strcat ( Where, " = ");
				strcat ( Where, TempString );
				}

			++CIndex;
			}
		++Index;
		}

	sprintf(TempString, ", %u", CurrentTime() );
	strcat( Values, TempString );

	sprintf(TempString, "%u", CurrentTime() );
	strcat( Updates, ", AccessTime = " );
	strcat( Updates, TempString );

	if(ObjectFile && DCMGateDB==ImageDB)
		{
		LastADBE = NULL;
		strcat(Values, ", ");
		FakeVR.Data = (void*)ObjectFile;
		FakeVR.Length = strlen(ObjectFile);
		MakeSafeStringValues ( &FakeVR, TempString );
		FakeVR.Data = NULL;
		FakeVR.Length = 0;
		strcat ( Values, TempString );

		strcat ( Updates, ", ObjectFile = " );
		strcat ( Updates, TempString );
		}

	if(DeviceName)
		{
		LastADBE = NULL;
		strcat(Values, ", ");
		FakeVR.Data = (void*)DeviceName;
		FakeVR.Length = strlen(DeviceName);
		MakeSafeStringValues ( &FakeVR, TempString );
		FakeVR.Data = NULL;
		FakeVR.Length = 0;
		strcat ( Values, TempString );

		strcat ( Updates, ", DeviceName = " );
		strcat ( Updates, TempString );
		}

	// No need to keep on writing exactly the same data !

	if (DCMGateDB!=ImageDB && isin_UpdateCache(Updates))
		{
//		OperatorConsole.printf("Skipping Cached Update on Table %s\n", TableName);
		SkippedCachedUpdates++;
		return TRUE;
		}


	if (JustAdd)
		{
		AddedDatabase++;
		if(DB.AddRecord(TableName, Columns, Values))
			{
			*Added = TRUE;
			return ( TRUE );
			}
		else
			{
			SystemDebug.printf ( "***Unable to DB.Add()\n");
			SystemDebug.printf ( "***SQL: %.1000s\n", DB.SQLStatement);
			DB.PrintLastError();
			clear_UpdateCache();	// would be invalid
			return ( FALSE );
			}
		}

	/* Use UPDATE if the record exists; else use INSERT
 	   Check whether all existing records differ from the current update. 
           If so, log a warning, but update it anyway, showing patient ID
	*/

	strcpy(TempString, DCMGateDB[0].SQLColumn);
	for (i=1; i<=lastfield; i++)
	  	{
	  	strcat(TempString, ",");
	  	strcat(TempString, DCMGateDB[i].SQLColumn);
	  	}


	// the following code is not multi-user safe: the record might be in process of creation
	// in that case a query does not find it, but later there will be two records
        // to solve this problem, keys are now unique

	if(!DB.Query(TableName, TempString, Where, NULL)) 
		return FALSE;

	for (i=1; i<=lastfield; i++)
		{
		if(!DB.BindField (i+1, SQL_C_CHAR, s[i-1], 255, &sdword))
			return ( FALSE );
		s[i-1][0] = 0;
		}

	if (DB.NextRecord())
		{
		// remove trailing spaces from read database field
		for (i=1; i<=lastfield; i++)
			{
			len = strlen(s[i-1]);
		        for (j=len-1; j>=0; j--)
				if (s[i-1][j]==' ') 	s[i-1][j] = 0;
				else			break;
			}

		// merge incoming modality with study modality
		if (pm1)
			{
			if (DoubleBackSlashToDB)
				{
				pTmp = TempString;
				for (i=0; i<strlen(s[im-1]); i++) 
					if (s[im-1][i]=='\\') *pTmp++ = '\\', *pTmp++ = '\\';
					else		      *pTmp++ = s[im-1][i];
				*pTmp++ = 0;
				strcpy(s[im-1], TempString);
				}
			else
				strcpy(TempString, s[im-1]);
			
			// set flag if modality in studymodality string, but e.g., CT must not respond to RTSTRUCT
			flag = 0;
			if (strstr(TempString, Modality)!=NULL)
				{
				Temp2[0] = '\\';
				strcpy(Temp2+1, TempString);
				strcpy(Temp2+strlen(Temp2), "\\");

				Temp3[0] = '\\';
				strcpy(Temp3+1, Modality);
				strcpy(Temp3+strlen(Temp3), "\\");

				flag = strstr(Temp2, Temp3)!=NULL;
				}

			// modality is not present: append the new modality with the read modality string
			if (!flag)
				{
				len = strlen(TempString) + 1;
				if (DoubleBackSlashToDB) len++;
				memmove(Updates+pm2+len-1, Updates+pm2-1, sizeof(Updates)-pm2-len);
				Updates[pm2-1] = '\\';
				if (DoubleBackSlashToDB) Updates[pm2++]   = '\\';
				memcpy(Updates+pm2, TempString, strlen(TempString));
				}
			// modality is present: re-write the read modality string
			else
				{
				len = strlen(TempString) - strlen(Modality);
				memmove(Updates+pm2+len-1, Updates+pm2-1, sizeof(Updates)-pm2-len);
				memcpy(Updates+pm1, TempString, strlen(TempString));
				}
			}

		for (i=1; i<=lastfield; i++)
			{
			// extract and compare update value
  			strcpy(TempString, " ");
  			strcat(TempString, DCMGateDB[i].SQLColumn);
  			strcat(TempString, " = '");
	  		pTmp = strstr(Updates, TempString);
			if (pTmp)
	  			{ 
	  			pTmp2 = strchr(pTmp + strlen(TempString), '\'');

	  			while (pTmp2[1]=='\'') pTmp2 = strchr(pTmp2+2, '\'');	// 20060607 skip '' in string

	    			if (pTmp2 && strlen(s[i-1]))
	    				{ 
	    				*pTmp2 = 0;

	      				if (strnicmp(s[i-1], pTmp + strlen(TempString), strlen(s[i-1])) != 0)
						{

						// convert backslashes and check again if inconsistency was found
						char temp[512]; 
						VR FakeVR;

						FakeVR.Data = (void*)&s[i-1];
						FakeVR.Length = strlen(s[i-1]);
						MakeSafeStringValues ( &FakeVR, temp );
						FakeVR.Data = NULL;
						FakeVR.Length = 0;

						// Remove '' added by MakeSafeStringValues - 20060618
						temp[strlen(temp)-1]=0;
						strcpy(s[i-1], temp+1);

			      			if (strnicmp(s[i-1], pTmp + strlen(TempString), strlen(s[i-1])) != 0)
							{
							// check patient table entries
							if ((strcmp(TableName, PatientTableName) == 0) &&
							    (strlen(s[i-1]) > 0))
								{
								/* Do not overrule a non-empty with an empty value */
								if (strlen(pTmp + strlen(TempString)) == 0)
									goto cont; //return TRUE;
								/* Do not overrule birthdate with xxxx0101 */
								if ((DCMGateDB[i].Group == 0x0010) &&
								    (DCMGateDB[i].Element == 0x0030) &&
								    ((atoi(s[i-1]) % 10000) != 101) &&
								    ((atoi(pTmp + strlen(TempString)) % 10000) == 101))
									goto cont; //return TRUE;
								/* Do not overrule sex with something other than MmFf */
								if ((DCMGateDB[i].Group == 0x0010) &&
								    (DCMGateDB[i].Element == 0x0040) &&
								    ((pTmp + strlen(TempString))[0] != 'M') &&
								    ((pTmp + strlen(TempString))[0] != 'm') &&
								    ((pTmp + strlen(TempString))[0] != 'F') &&
								    ((pTmp + strlen(TempString))[0] != 'f'))
									goto cont; //return TRUE;
								}

							// check patient birthdate
							if (DCMGateDB[i].Group == 0x0010 && DCMGateDB[i].Element == 0x0030)
								{
								OperatorConsole.printf("***Inconsistent %s in %s: PatientID = '%s' %s, Old='%s', New='%s'\n",
				  				DCMGateDB[i].SQLColumn, TableName, Patid, Where, s[i-1], pTmp + strlen(TempString));
								}
							// check link
							else if (i==LastDBE(DCMGateDB) && strcmp(TableName, PatientTableName) != 0)
								{
								OperatorConsole.printf("***Refused to enter inconsistent link %s into %s: PatientID = '%s' %s, Old='%s', Refused='%s'\n",
		  						DCMGateDB[i].SQLColumn, TableName, Patid, Where, s[i-1], pTmp + strlen(TempString));
								return FALSE;	// fatal error
								}
							else
								TroubleLog.printf("Inconsistent %s in %s: PatientID = '%s' %s, Old='%s', New='%s'\n",
					  			DCMGateDB[i].SQLColumn, TableName, Patid, Where, s[i-1], pTmp + strlen(TempString));
							}

						}
cont:
	      				*pTmp2 = '\'';
	      				}
	    			}
	  		}

		if (CheckDuplicates)
			if (DB.NextRecord())
				{
				OperatorConsole.printf("***Duplicate found in %s WHERE %s\n", TableName, Where);
				return ( FALSE );
				}

		if(DB.UpdateRecords(TableName, Updates, Where))
			{
			UpdateDatabase++;
			if (DCMGateDB!=ImageDB)
				into_UpdateCache(Updates);
			return ( TRUE );
			}
		else
			{
			SystemDebug.printf ( "***Unable to update record\n");
			SystemDebug.printf ( "***SQL: %.1000s\n", DB.SQLStatement);
			DB.PrintLastError();
			clear_UpdateCache();	// would be invalid
			return ( FALSE );
			}
		}
	else
		{
		AddedDatabase++;
		if(DB.AddRecord(TableName, Columns, Values))
			{
			*Added = TRUE;
			return ( TRUE );
			}
		else
			{
			SystemDebug.printf ( "***Unable to DB.Add()\n");
			SystemDebug.printf ( "***SQL: %.1000s\n", DB.SQLStatement);
			DB.PrintLastError();
			clear_UpdateCache();	// would be invalid
			return ( FALSE );
			}
		}

	return ( FALSE );
	}

// Updates all the access times for all levels of the database, given only
// a connected database, and an SOP Instance.
// Called automatically from GetFileName

BOOL
UpdateAccessTimes(
	Database		&ConnectedDB,
	char	*SOPInstanceUID)
	{
	DWORD	CurTime;
	SQLLEN	sdword;
	char	s[255];
	char	s1[255];
	// Basic idea is we up all the access times for each level
	sprintf(s, "AccessTime = %u", CurTime = CurrentTime());
	sprintf(s1, "%s = %s", UniqueKey(ImageDB), SOPInstanceUID);
	if(!ConnectedDB.UpdateRecords(ImageTableName,s,s1))
		{
		SystemDebug.printf("***Could not update access time for Image level database\n");
		return ( FALSE );
		}
	if(!ConnectedDB.Query(ImageTableName, UniqueLink(ImageDB), s1, NULL))
		{
		SystemDebug.printf("***Could not obtain Series level link\n");
		return ( FALSE );
		}
	if(!ConnectedDB.BindField (1, SQL_C_CHAR,
			s, 255,
			&sdword))
			return ( FALSE );
	if(!ConnectedDB.NextRecord())
		return ( FALSE );

	// Perform search and update series level database
	sprintf(s1, "%s = '%s'", UniqueKey(SeriesDB), s);
	sprintf(s, "AccessTime = %u", CurTime);
	if(!ConnectedDB.UpdateRecords(SeriesTableName,s,s1))
		{
		SystemDebug.printf("***Could not update access time for Series level database\n");
		return ( FALSE );
		}
	if(!ConnectedDB.Query(SeriesTableName, UniqueLink(SeriesDB), s1, NULL))
		{
		SystemDebug.printf("***Could not obtain Series level link\n");
		return ( FALSE );
		}
	if(!ConnectedDB.BindField (1, SQL_C_CHAR,
			s, 255,
			&sdword))
			return ( FALSE );
	if(!ConnectedDB.NextRecord())
		return ( FALSE );

	// Study level
	sprintf(s1, "%s = '%s'", UniqueKey(StudyDB), s);
	sprintf(s, "AccessTime = %u", CurTime);
	if(!ConnectedDB.UpdateRecords(StudyTableName,s,s1))
		{
		SystemDebug.printf("***Could not update access time for Study level database\n");
		return ( FALSE );
		}
	if(!ConnectedDB.Query(StudyTableName, UniqueLink(StudyDB), s1, NULL))
		{
		SystemDebug.printf("***Could not obtain Study level link\n");
		return ( FALSE );
		}
	if(!ConnectedDB.BindField (1, SQL_C_CHAR,
			s, 255,
			&sdword))
			return ( FALSE );
	if(!ConnectedDB.NextRecord())
		return ( FALSE );

	// Patient Level

	DICOM2SQLQuery(s);	// 20070201
	sprintf(s1, "%s = %s", UniqueKey(PatientDB), s);
	sprintf(s, "AccessTime = %u", CurTime);
	if(!ConnectedDB.UpdateRecords(PatientTableName,s,s1))
		{
		SystemDebug.printf("***Could not update access time for Patient level database\n");
		return ( FALSE );
		}
	return ( TRUE );
	}

// Make a new UID for db use (prefix configurable via UIDPrefix in dicom.ini)
int UIDPostfix=0;
static char dbUIDPrefix[65] = "1.2.826.0.1.3680043.2.135.1066.7";	// default value
static BOOL dbLoadRoot = TRUE;
static BOOL
dbGenUID(char	*oString)
	{ 
	if (dbLoadRoot)
		{
		char szRootSC[64];
  		if (GetPrivateProfileString(RootConfig, "MicroPACS", RootConfig, szRootSC, 64, ConfigFile))
			{
			if (GetPrivateProfileString(szRootSC, "UIDPrefix", "1.2.826.0.1.3680043.2.135.1066", dbUIDPrefix, 64, ConfigFile))
				strcat(dbUIDPrefix, ".7");
			}
		dbLoadRoot = FALSE;
		}

#ifdef WIN32
	sprintf(oString, "%s.%u.%d.%u", dbUIDPrefix, time(NULL), GetTickCount()%1000, (UIDPostfix++)%100);
#else
	sprintf(oString, "%s.%u.%u", dbUIDPrefix, time(NULL), (UIDPostfix++)%10000);
#endif
	return ( TRUE );
	}

// Generates a new UID from an old one, but use UIDMODs table to maintain history of changes
// A new request to change the old UID returns the previously changed UID
BOOL
ChangeUID(char *OldUID, char *Type, char *NewUID)
	{
	char		s[255];
	char		Values[1024];
	Database	DB;
	SQLLEN		sdword;

	if (!DB.Open ( DataSource, UserName, Password, DataHost ) )
		{
		SystemDebug.printf("***Unable to connect to SQL\n");
		return ( FALSE );
		}

	sprintf(s, "OldUID = '%s'", OldUID);
	if(!DB.Query("UIDMODS", "NewUID", s, NULL))
		{
		SystemDebug.printf("***Unable to query UIDMODS table\n");
		return ( FALSE );
		}

	if(!DB.BindField (1, SQL_C_CHAR, NewUID, 255, &sdword))
		{
		SystemDebug.printf("***Unable to bind field of UIDMODS table\n");
		return ( FALSE );
		}

	if(!DB.NextRecord())
		{
		dbGenUID(NewUID);
		SystemDebug.printf("NewUID for %s = %s\n", Type, NewUID);

		sprintf(Values, "%u, '", time(NULL));
		strcat(Values, OldUID);
		strcat(Values, "', '");
		strcat(Values, Type);
		strcat(Values, "', '");
		strcat(Values, NewUID);
		strcat(Values, "'");
		if(!DB.AddRecord("UIDMODS", "MODTime, OldUID, MODType, NewUID", Values))
			{
			SystemDebug.printf("***Unable to add entry to UIDMODS table\n");
			return ( FALSE );
			}
		return TRUE;
		}
		else
			SystemDebug.printf("OldUID = %s, NewUID = %s\n", OldUID, NewUID);

	return ( TRUE );
	}

// Generates one new UID for multiple ones, uses UIDMODs table to maintain history of changes
// A following request to change the old UID returns the merged NewUID
BOOL
MergeUIDs(char *OldUID[], int n, char *Type, char *NewUID)
	{
	char		s[255];
	char		Values[1024];
	Database	DB;
	SQLLEN		sdword;
	int		i;

	if (!DB.Open ( DataSource, UserName, Password, DataHost ) )
		{
		SystemDebug.printf("***Unable to connect to SQL\n");
		return ( FALSE );
		}

	dbGenUID(NewUID);
	SystemDebug.printf("NewUID for merging %s = %s\n", Type, NewUID);

	for (i=0; i<n; i++)
		{
		sprintf(s, "OldUID = '%s'", OldUID[i]);
		if(!DB.Query("UIDMODS", "NewUID", s, NULL))
			{
			SystemDebug.printf("***Unable to query UIDMODS table\n");
			return ( FALSE );
			}

		DB.BindField (1, SQL_C_CHAR, Values, 255, &sdword);

		if(DB.NextRecord())
			DB.DeleteRecord("UIDMODS", s);
			
		sprintf(Values, "%u, '", time(NULL));
		strcat(Values, OldUID[i]);
		strcat(Values, "', '");
		strcat(Values, Type);
		strcat(Values, "', '");
		strcat(Values, NewUID);
		strcat(Values, "'");
		if(!DB.AddRecord("UIDMODS", "MODTime, OldUID, MODType, NewUID", Values))
			{
			SystemDebug.printf("***Unable to add entry to UIDMODS table\n");
			return ( FALSE );
			}

		SystemDebug.printf("OldUID = %s, NewUID = %s\n", OldUID[i], NewUID);
		}

	return ( TRUE );
	}

BOOL
MakeSafeString (
	VR	*vr,
	char	*string )
	{
	int		Length;
	char	*sout;
	char	*sin;
	char	*s;
	UINT	Index;

	(*string)='\'';

	s = SetString(vr, NULL, 0);
	Length = strlen(s);
	sin = (char*)s;
	sout = string + 1;

	if (vr)
		if(vr->Data)
		{
		Index = 0;
		while(Index < Length)
			{
			switch (*sin)
				{
				case	'*':
					(*sout) = '%';++sout;
					break;
				case	'?':
					(*sout) = '_';++sout;
					break;
				case	'%':
					(*sout) = '\\';++sout;
					(*sout) = '%';;++sout;
					break;
				case	'[':
					(*sout) = '\\';++sout;
					(*sout) = '[';;++sout;
					break;
				case	'_':
//					(*sout) = '\\';++sout;
					(*sout) = '_';;++sout;
					break;
				case	'\'':
					(*sout) = '\'';++sout;
					(*sout) = '\'';++sout;
					break;
				case	'\\':
					if (DoubleBackSlashToDB)
						{
						if ((Index > 0) && (sin[-1] != '\\'))
							{
							(*sout) = '\\';++sout;
							(*sout) = '\\';++sout;
							}
						}
					else
						{
						(*sout) = (*sin);
						++sout;
						}
					break;
				case	'\"':
//					(*sout) = '\"';++sout;
					(*sout) = '\"';++sout;
					break;
				case	0:	break;
				default:
					(*sout) = (*sin);
					++sout;
				}
			++sin;
			++Index;
			}
		}

        /* this code removed single trailing space ****
	--sout;
	if((*sout)==' ')
		;
	else
		++sout;
        **********************************************/

        /* new code removes all trailing spaces (no check on begin: sout always start with ') */
        sout--;
        while (*sout == ' ') sout--;
        sout++;

	(*sout) = '\'';++sout;
	(*sout) = '\0';
	
	delete s;
	return ( TRUE );
	}


// for values, not queries
BOOL
MakeSafeStringValues (
	VR	*vr,
	char	*string )
	{
	int	Length;
	char	*sout;
	char	*sin;
	char	*s;
	UINT	Index;

	(*string)='\'';

	s = SetString(vr, NULL, 0);
	Length = strlen(s);
	sin = (char*)s;
	sout = string + 1;

	if (vr)
		if(vr->Data)
		{
		Index = 0;
		while(Index < Length)
			{
			switch (*sin)
				{
				case	'\'':
					(*sout) = '\'';++sout;
					(*sout) = '\'';++sout;
					break;
				case	'\\':
					if (DoubleBackSlashToDB)
						{
						if ((Index > 0) && (sin[-1] != '\\'))
							{
							(*sout) = '\\';++sout;
							(*sout) = '\\';++sout;
							}
						}
					else
						{
						(*sout) = (*sin);
						++sout;
						}
					break;
				case	0:	break;
				default:
					(*sout) = (*sin);
					++sout;
				}
			++sin;
			++Index;
			}
		}

        /* new code removes all trailing spaces (no check on begin: sout always start with ') */
        sout--;
        while (*sout == ' ') sout--;
        sout++;

	(*sout) = '\'';++sout;
	(*sout) = '\0';
	
	delete s;
	return ( TRUE );
	}


BOOL
MakeSafeDate ( VR *vr, char	*string )
	{
	int		Length;
	char	*sout;
	char	*sin;
	char	s[256];
	UINT	Index;

	(*string)='\'';
	SetString(vr, s, 256);
	Length = strlen(s);
	sin = (char*)s;
	sout = string + 1;

	if (vr)
		if(vr->Data)
		{
		Index = 0;
		while(Index < Length)
			{
			switch (*sin)
				{
				case	'.':	// remove from ACR-NEMA v2 comp.
					break;
				case	'/':	// remove for safety
					break;
				case	'\'':
					(*sout) = '\'';++sout;
					(*sout) = '\'';++sout;
					break;
				case	'\"':
					(*sout) = '\"';++sout;
					(*sout) = '\"';++sout;
					break;
				case	0:	break;
				default:
					(*sout) = (*sin);
					++sout;
				}
			++sin;
			++Index;
			}
		}
	--sout;
	if((*sout)==' ')
		;
	else
		++sout;
	(*sout) = '\'';++sout;
	(*sout) = '\0';
	
	return ( TRUE );
	}

BOOL
GetFileName(VR	*vr, char	*filename, char	*dv, BOOL UpdateLRU, char *patid, char *study, char *series)
	{
	Database	DB;
	BOOL		Ret;

	if (!DB.Open ( DataSource, UserName, Password, DataHost ) )
		return ( FALSE );

	Ret = GetFileName(vr, filename, dv, DB, UpdateLRU, patid, study, series);
	DB.Close();
	return(Ret);
	}


BOOL
GetFileName(VR	*SOPInstance, char	*filename, char	*device, Database &ConnectedDB, BOOL UpdateLRU, char *patid, char *study, char *series)
	{
	SQLLEN	sdword;
	char	s [ 256 ];
	char	s2 [ 256 ];
	char	s1[70];
	int	Index;

	MakeSafeStringValues(SOPInstance, s1);
        if (s1[0]==0) return FALSE;

	sprintf(s, "SOPInstanceUID");
	if (TruncateFieldNames)
        	s[TruncateFieldNames] = 0;
	sprintf(s+strlen(s), " = %s", s1);

        // include patid (indexed) for speed; test for rev5 or higher of the database
	if (patid)
	  if (patid[0])
		{
		Index = 1;
        	while (ImageDB[Index].Element)
			{
			if (ImageDB[Index].Group==0x0010 && ImageDB[Index].Element==0x0020)
				{
				char newpatid[128];
				strcpy(newpatid, patid);
				DICOM2SQLQuery(newpatid);
				sprintf(s+strlen(s), " AND ImagePat = %s", newpatid);
				break;
        			}
			Index++;
			}
		}

	if (study)
	  if (study[0])
		{
		Index = 1;
        	while (ImageDB[Index].Element)
			{
			if (ImageDB[Index].Group==0x0020 && ImageDB[Index].Element==0x000d)
				{ 
				sprintf(s+strlen(s), " AND StudyInsta = '%s'", study);
				break;
        			}
			Index++;
			}
		}

	if (series)
	  if (series[0])
	    sprintf(s+strlen(s), " AND SeriesInst = '%s'", series);

	EnterCriticalSection(&ConnectedDB.m_Critical);
	if(!ConnectedDB.Query(ImageTableName, "ObjectFile, DeviceName", s, NULL))
	{
		LeaveCriticalSection(&ConnectedDB.m_Critical);
		return ( FALSE );
	}
	if(!ConnectedDB.BindField (1, SQL_C_CHAR,
			s, 255,
			&sdword))
	{
		LeaveCriticalSection(&ConnectedDB.m_Critical);
		return ( FALSE );
	}
	if(!ConnectedDB.BindField (2, SQL_C_CHAR,
			s2, 255,
			&sdword))
	{
		LeaveCriticalSection(&ConnectedDB.m_Critical);
		return ( FALSE );
	}
	if(!ConnectedDB.NextRecord())
	{
		LeaveCriticalSection(&ConnectedDB.m_Critical);
		return ( FALSE );
	}
	LeaveCriticalSection(&ConnectedDB.m_Critical);

	strcpy(filename, s);
	strcpy(device, s2);
	// Used to update the AU list
	//	AccessUpdate.printf("%s", s1);
	//UpdateAccessTimes(ConnectedDB, s1);

	if (filename[0]==0 || device[0]==0) return FALSE;	// virtual image that has no filename yet

	return ( TRUE );
	}

// Makes a copy of a DICOM Object
DICOMDataObject	*MakeCopy(
	DICOMDataObject	*DO)
	{
	// Simple "Copy" procedure
	DICOMDataObject	DO2;
	VR				*vr;
	VR				*newVR;

	DICOMDataObject	*DO3 = new DICOMDataObject;
	if(!DO3)
		return ( NULL );

	while ( vr = DO->Pop() )
		{
		newVR = new VR(vr->Group, vr->Element, vr->Length, (BOOL) TRUE);
		memcpy(newVR->Data, vr->Data, vr->Length);
		DO2.Push(vr);
		DO3->Push(newVR);
		}
	DO->Reset();
	while ( vr = DO2.Pop() )
		{
		DO->Push(vr);
		}
	return ( DO3 );
	}

// Faster delete image from database
BOOL
NewDeleteFromDB(DICOMDataObject	*pDDO, Database	&aDB)
	{
	char			pat[256], study[256], series[256], sop[256];
	char 			QueryString[512], DeleteString[512], Dum[256];
	int			ImageHasPat=0, SeriesHasPat=0, Index;
	SQLLEN			sdword;

	if (!pDDO->GetVR(0x0010, 0x0020) || 
            !pDDO->GetVR(0x0020, 0x000d) ||
            !pDDO->GetVR(0x0020, 0x000e) ||
            !pDDO->GetVR(0x0008, 0x0018))
		{
		OperatorConsole.printf("***[NewDeleteFromDB] -FAILED: DDO does not contain correct UIDs\n");
		return ( FALSE );
		}

	MakeSafeString(pDDO->GetVR(0x0010, 0x0020), pat);
	MakeSafeString(pDDO->GetVR(0x0020, 0x000d), study);
	MakeSafeString(pDDO->GetVR(0x0020, 0x000e), series);
	MakeSafeString(pDDO->GetVR(0x0008, 0x0018), sop);


        // include patid (indexed) for speed; test for presence in database at series and image level (optional)
	Index=0;
       	while (ImageDB[Index].Element)
		{
		if (ImageDB[Index].Group==0x0010 && ImageDB[Index].Element==0x0020)
				{ 
				ImageHasPat=1;
				break;
        			}
		Index++;
		}

	Index=0;
       	while (SeriesDB[Index].Element)
		{
		if (SeriesDB[Index].Group==0x0010 && SeriesDB[Index].Element==0x0020)
				{ 
				SeriesHasPat=1;
				break;
	       			}
		Index++;
		}

	// Delete entry from image database (would not remove duplicates - but these should not occur)
	if (ImageHasPat)
		{
		sprintf(QueryString, 	"DICOMImages.SopInstanc = %s and DICOMImages.SeriesInst = %s and DICOMImages.ImagePat = %s", sop, series, pat);
		sprintf(DeleteString, 	"DICOMImages.SopInstanc = %s and DICOMImages.SeriesInst = %s and DICOMImages.ImagePat = %s", sop, series, pat);
		}
	else
		{
		sprintf(QueryString, 	"DICOMImages.SopInstanc = %s and DICOMImages.SeriesInst = %s", sop, series);
		sprintf(DeleteString, 	"DICOMImages.SopInstanc = %s and DICOMImages.SeriesInst = %s", sop, series);
		}
	if (!aDB.Query(ImageTableName, "DICOMImages.SopInstanc", QueryString, NULL)) return FALSE;
	aDB.BindField (1, SQL_C_CHAR, Dum, 255, &sdword);
	if (aDB.NextRecord())
		aDB.DeleteRecord(ImageTableName, DeleteString);

	// Delete series if last image of series deleted (would not remove duplicates - but these should not occur)
	if (ImageHasPat)
		sprintf(QueryString, 	"DICOMImages.SeriesInst = %s and DICOMImages.ImagePat = %s", series, pat);
	else
		sprintf(QueryString, 	"DICOMImages.SeriesInst = %s", series);
	if (SeriesHasPat)
		sprintf(DeleteString, 	"DICOMSeries.SeriesInst = %s and DICOMSeries.StudyInsta = %s and DICOMSeries.SeriesPat = %s", series, study, pat);
	else
		sprintf(DeleteString, 	"DICOMSeries.SeriesInst = %s and DICOMSeries.StudyInsta = %s", series, study);
	if (!aDB.Query(ImageTableName, "DICOMImages.SeriesInst", QueryString, NULL)) return FALSE;
	aDB.BindField (1, SQL_C_CHAR, Dum, 255, &sdword);
	if (!aDB.NextRecord())
		aDB.DeleteRecord(SeriesTableName, DeleteString);

	// Delete study if last series deleted (would not remove duplicates - but these should not occur)
	if (SeriesHasPat)
		sprintf(QueryString, 	"DICOMSeries.StudyInsta = %s and DICOMSeries.SeriesPat = %s", study, pat);
	else
		sprintf(QueryString, 	"DICOMSeries.StudyInsta = %s", study);
	sprintf(DeleteString, 	"DICOMStudies.StudyInsta = %s and DICOMStudies.PatientID = %s", study, pat);
	if (!aDB.Query(SeriesTableName, "DICOMSeries.StudyInsta", QueryString, NULL)) return FALSE;
	aDB.BindField (1, SQL_C_CHAR, Dum, 255, &sdword);
	if (!aDB.NextRecord())
		aDB.DeleteRecord(StudyTableName, DeleteString);

	// Delete patient/worklist if last study deleted (would not remove duplicates - but these should not occur)
	sprintf(QueryString, 	"DICOMStudies.PatientID = %s", pat);
	sprintf(DeleteString, 	"DICOMPatients.PatientID = %s", pat);
	if (!aDB.Query(StudyTableName, "DICOMStudies.PatientID", QueryString, NULL)) return FALSE;
	aDB.BindField (1, SQL_C_CHAR, Dum, 255, &sdword);
	if (!aDB.NextRecord())
		{
		aDB.DeleteRecord(PatientTableName, DeleteString);

		// worklist defined ?
	       	if (WorkListDB[0].Element)
			{
			sprintf(QueryString, 	"DICOMWorkList.PatientID = %s", pat);
			sprintf(DeleteString, 	"DICOMWorkList.PatientID = %s", pat);
			if (aDB.Query(WorkListTableName, "DICOMWorkList.PatientID", QueryString, NULL))
			        {
				aDB.BindField (1, SQL_C_CHAR, Dum, 255, &sdword);

				while (aDB.NextRecord())
					aDB.DeleteRecord(WorkListTableName, DeleteString);
			        }
		         }
		}

	clear_UpdateCache();
	return ( TRUE );
	}

// Delete SOP from database (no image required - useful for orphaned db entries)
BOOL
NewDeleteSopFromDB(char *pat, char *study, char *series, char *sop, Database &aDB)
	{
	char 			QueryString[512], DeleteString[512], PatString[512], Dum[256];
	int			ImageHasPat=0, SeriesHasPat=0, Index;
	SQLLEN			sdword;

	strcpy(PatString, pat);
	DICOM2SQLQuery(PatString);

        // include patid (indexed) for speed; test for presence in database at series and image level (optional)
	Index=0;
       	while (ImageDB[Index].Element)
		{
		if (ImageDB[Index].Group==0x0010 && ImageDB[Index].Element==0x0020)
				{ 
				ImageHasPat=1;
				break;
        			}
		Index++;
		}

	Index=0;
       	while (SeriesDB[Index].Element)
		{
		if (SeriesDB[Index].Group==0x0010 && SeriesDB[Index].Element==0x0020)
				{ 
				SeriesHasPat=1;
				break;
	       			}
		Index++;
		}



	// Delete entry from image database (would not remove duplicates - but these should not occur)
	if (ImageHasPat)
		{
		sprintf(QueryString, 	"DICOMImages.SopInstanc = '%s' and DICOMImages.SeriesInst = '%s' and DICOMImages.ImagePat = %s", sop, series, PatString);
		sprintf(DeleteString, 	"DICOMImages.SopInstanc = '%s' and DICOMImages.SeriesInst = '%s' and DICOMImages.ImagePat = %s", sop, series, PatString);
		}
	else
		{
		sprintf(QueryString, 	"DICOMImages.SopInstanc = '%s' and DICOMImages.SeriesInst = '%s'", sop, series);
		sprintf(DeleteString, 	"DICOMImages.SopInstanc = '%s' and DICOMImages.SeriesInst = '%s'", sop, series);
		}
	if (!aDB.Query(ImageTableName, "DICOMImages.SopInstanc", QueryString, NULL)) return FALSE;
	aDB.BindField (1, SQL_C_CHAR, Dum, 255, &sdword);
	if (aDB.NextRecord())
		aDB.DeleteRecord(ImageTableName, DeleteString);

	// Delete series if last image of series deleted (would not remove duplicates - but these should not occur)
	if (ImageHasPat)
		sprintf(QueryString, 	"DICOMImages.SeriesInst = '%s' and DICOMImages.ImagePat = %s", series, PatString);
	else
		sprintf(QueryString, 	"DICOMImages.SeriesInst = '%s'", series);
	if (SeriesHasPat)
		sprintf(DeleteString, 	"DICOMSeries.SeriesInst = '%s' and DICOMSeries.StudyInsta = '%s' and DICOMSeries.SeriesPat = %s", series, study, PatString);
	else
		sprintf(DeleteString, 	"DICOMSeries.SeriesInst = '%s' and DICOMSeries.StudyInsta = '%s'", series, study);
	if (!aDB.Query(ImageTableName, "DICOMImages.SeriesInst", QueryString, NULL)) return FALSE;
        aDB.BindField (1, SQL_C_CHAR, Dum, 255, &sdword);
        if (!aDB.NextRecord())
		aDB.DeleteRecord(SeriesTableName, DeleteString);

	// Delete study if last series deleted (would not remove duplicates - but these should not occur)
	if (SeriesHasPat)
		sprintf(QueryString, 	"DICOMSeries.StudyInsta = '%s' and DICOMSeries.SeriesPat = %s", study, PatString);
	else
		sprintf(QueryString, 	"DICOMSeries.StudyInsta = '%s'", study);
	sprintf(DeleteString, 	"DICOMStudies.StudyInsta = '%s' and DICOMStudies.PatientID = %s", study, PatString);
	if (!aDB.Query(SeriesTableName, "DICOMSeries.StudyInsta", QueryString, NULL)) return FALSE;
	aDB.BindField (1, SQL_C_CHAR, Dum, 255, &sdword);
	if (!aDB.NextRecord())
		aDB.DeleteRecord(StudyTableName, DeleteString);

	// Delete patient if last study deleted (would not remove duplicates - but these should not occur)
	sprintf(QueryString, 	"DICOMStudies.PatientID = %s", PatString);
	sprintf(DeleteString, 	"DICOMPatients.PatientID = %s", PatString);
	if (!aDB.Query(StudyTableName, "DICOMStudies.PatientID", QueryString, NULL)) return FALSE;
        aDB.BindField (1, SQL_C_CHAR, Dum, 255, &sdword);
        if (!aDB.NextRecord())
		{
		aDB.DeleteRecord(PatientTableName, DeleteString);

		// worklist defined ?
	       	if (WorkListDB[0].Element)
			{
			sprintf(QueryString, 	"DICOMWorkList.PatientID = %s", PatString);
			sprintf(DeleteString, 	"DICOMWorkList.PatientID = %s", PatString);
			if (aDB.Query(WorkListTableName, "DICOMWorkList.PatientID", QueryString, NULL))
			        {
				 aDB.BindField (1, SQL_C_CHAR, Dum, 255, &sdword);

				while (aDB.NextRecord())
					aDB.DeleteRecord(WorkListTableName, DeleteString);
			        }
			}
		}

	clear_UpdateCache();
	return ( TRUE );
	}

BOOL
RemoveFromWorld(
	DICOMDataObject	*DDO,
	Database		&DB)	// Connected DB
	{
	VR			*vr;
	DICOMDataObject	*TempPatientDDO, *TempStudyDDO, *TempSeriesDDO;
	Array < DICOMDataObject * >	ImageADDO;
	Array < DICOMDataObject * >	SeriesADDO;
	Array < DICOMDataObject * >	StudyADDO;
	Array < DICOMDataObject * >	PatientADDO;
	UINT		PatientIndex, StudyIndex, SeriesIndex, ImageIndex;

	return NewDeleteFromDB(DDO, DB);

        ////////////////////////////////////////////////
        // The rest is unused - left for reference only
        ////////////////////////////////////////////////

	SystemDebug.printf("RemoveFromWorld\n");

	// Step 1: Remove Image(s) from database.

	RemoveDuplicates(DB, ImageDB, ImageTableName, DDO, FALSE);

	// Step 2: Query on the Patient and work *down* to the image level.
	// This is conceptually backwards from how one might think we should
	// do this; But, it allows us to "repair" a damaged delete operation
	// (one that failed part way though).

	DICOMDataObject	*DDO2 = MakeCopy(DDO);
	QueryOnPatient(DDO, &PatientADDO);
	if(!PatientADDO.GetSize())
		{
		SystemDebug.printf("PatientADDO : GetSize := 0\n");
		QueryOnStudy(DDO2, &PatientADDO);
		SystemDebug.printf("PatientADDO (via Study) : GetSize := %d\n",
			PatientADDO.GetSize());
		if(!PatientADDO.GetSize())
			{
			delete	DDO2;
			return ( FALSE );
			}
		}
	delete DDO2;
	PatientIndex = 0;
	while ( PatientADDO.GetSize() )
		{
		if(!PatientADDO.Get(0)->GetVR(StudyDB[0].Group, StudyDB[0].Element))
			{
			VR	*vr = new VR(StudyDB[0].Group, StudyDB[0].Element, 0, (BOOL) FALSE );
			PatientADDO.Get(0)->Push(vr);
			}
		TempPatientDDO = MakeCopy(PatientADDO.Get(0));
		QueryOnStudy(PatientADDO.Get(0), &StudyADDO);
		if(!StudyADDO.GetSize())
			{
			SystemDebug.printf("Removing Patient from database\n");
			RemoveDuplicates(DB, PatientDB, PatientTableName,
				TempPatientDDO, FALSE);
			SystemDebug.printf("Patient Gone!\n");
			delete PatientADDO.Get(0);
			PatientADDO.RemoveAt(0);
			delete TempPatientDDO;
			continue;
			}
		StudyIndex = 0;
		while(StudyADDO.GetSize())
			{
			if(!StudyADDO.Get(0)->GetVR(SeriesDB[0].Group, SeriesDB[0].Element))
				{
				VR	*vr = new VR(SeriesDB[0].Group, SeriesDB[0].Element, 0, (BOOL) FALSE );
				StudyADDO.Get(0)->Push(vr);
				}
			TempStudyDDO = MakeCopy(StudyADDO.Get(0));
			QueryOnSeries(StudyADDO.Get(0), &SeriesADDO);
			if(!SeriesADDO.GetSize())
				{
				SystemDebug.printf("Removing Study from database\n");
				RemoveDuplicates(DB, StudyDB, StudyTableName,
					TempStudyDDO, FALSE);
				delete StudyADDO.Get(0);
				StudyADDO.RemoveAt(0);
				delete TempStudyDDO;
				continue;
				}
			SeriesIndex = 0;
			while ( SeriesADDO.GetSize() )
				{
				if(!SeriesADDO.Get(0)->GetVR(SeriesDB[0].Group, SeriesDB[0].Element))
					{
					VR	*vr = new VR(SeriesDB[0].Group, SeriesDB[0].Element, 0, (BOOL) FALSE );
					SeriesADDO.Get(0)->Push(vr);
					}

				TempSeriesDDO = MakeCopy(SeriesADDO.Get(0));
				QueryOnImage(SeriesADDO.Get(0), &ImageADDO);
				if(!ImageADDO.GetSize())
					{
					SystemDebug.printf("Removing Series from database\n");
					RemoveDuplicates(DB, SeriesDB, SeriesTableName,
						TempSeriesDDO, FALSE);
					delete	SeriesADDO.Get(0);
					SeriesADDO.RemoveAt(0);
					delete TempSeriesDDO;
					continue;
					}
				else
					{
					while ( ImageADDO.GetSize() )
						{
						delete ImageADDO.Get(0);
						ImageADDO.RemoveAt(0);
						}
					}
				++SeriesIndex;
				delete SeriesADDO.Get(0);
				SeriesADDO.RemoveAt(0);
				delete TempSeriesDDO;
				}
			if(!SeriesIndex)
				{
				SystemDebug.printf("Removing Study From Database\n");
				RemoveDuplicates(DB, StudyDB, StudyTableName,
					TempStudyDDO, FALSE);
				delete StudyADDO.Get(0);
				StudyADDO.RemoveAt(0);
				delete TempStudyDDO;
				continue;
				}
			++StudyIndex;
			delete StudyADDO.Get(0);
			StudyADDO.RemoveAt(0);
			delete TempStudyDDO;
			}
		if(!StudyIndex)
			{
			SystemDebug.printf("Removing Patient from database\n");
			RemoveDuplicates(DB, PatientDB, PatientTableName,
				TempPatientDDO, FALSE);
			delete PatientADDO.Get(0);
			PatientADDO.RemoveAt(0);
			delete TempPatientDDO;
			continue;
			}
		++PatientIndex;
		delete PatientADDO.Get(0);
		PatientADDO.RemoveAt(0);
		delete TempPatientDDO;
		}
	return ( TRUE );
	}

BOOL
RemoveFromPACS(
	DICOMDataObject	*DDO, BOOL KeepImages)
	{
	Database			DB;
	Array < DICOMDataObject * >	ADDO;
	DICOMDataObject			*qDDO;
	DICOMDataObject			*DDOCopy;
	int				Index;
	VR				*vr, *vr2;
	char				fn[260];
	char				dv[260];
	char				filename[260];
	char				MirrorDevice[260];

	// Make sure the unique keys are in place for each hierachy of the
	// database
	if(!DDO->GetVR(PatientDB[0].Group, PatientDB[0].Element))
		{
		VR	*vr = new VR(PatientDB[0].Group, PatientDB[0].Element, 0, (BOOL) FALSE );
		DDO->Push(vr);
		}
	if(!DDO->GetVR(StudyDB[0].Group, StudyDB[0].Element))
		{
		VR	*vr = new VR(StudyDB[0].Group, StudyDB[0].Element, 0, (BOOL) FALSE );
		DDO->Push(vr);
		}
	if(!DDO->GetVR(SeriesDB[0].Group, SeriesDB[0].Element))
		{
		VR	*vr = new VR(SeriesDB[0].Group, SeriesDB[0].Element, 0, (BOOL) FALSE );
		DDO->Push(vr);
		}
	if(!DDO->GetVR(ImageDB[0].Group, ImageDB[0].Element))
		{
		VR	*vr = new VR(ImageDB[0].Group, ImageDB[0].Element, 0, (BOOL) FALSE );
		DDO->Push(vr);
		}
	DDOCopy = MakeCopy(DDO);
	QueryOnImage (DDO, &ADDO);
	if (!DB.Open ( DataSource, UserName, Password, DataHost ) )
		{
		SystemDebug.printf("***Unable to connect to SQL\n");
		delete DDOCopy;
		return ( FALSE );
		}
	Index = 0;
	if (KeepImages)
		SystemDebug.printf("RemoveFromPACS %d image database entries\n", ADDO.GetSize());
	else
		SystemDebug.printf("RemoveFromPACS %d images\n", ADDO.GetSize());

	if(!ADDO.GetSize())
		{
		RemoveFromWorld(DDOCopy,DB);
		delete DDOCopy;
		return ( TRUE );
		}
	delete DDOCopy;
	while ( Index < ADDO.GetSize() )
		{
		qDDO = ADDO.Get(Index);
		if(!qDDO)
			return ( FALSE );
		vr = qDDO->GetVR(0x0008, 0x0018);
		if(!vr)
			return ( FALSE );

		char pat[66];				/* get the patient ID */
        	pat[0]=0;
		vr2 = qDDO->GetVR(0x0010, 0x0020);
		if (vr2) 
        		{ 
			memcpy(pat, vr2->Data, vr2->Length);
  			if (pat[vr2->Length-1]==' ')
				pat[vr2->Length-1] = 0;
			else
				pat[vr2->Length] = 0;
			}

		if(GetFileName(vr, fn, dv, DB, FALSE, pat))
			{
			int	sIndex, devlen;

			if (!KeepImages) OperatorConsole.printf("Removed file: [%s:%s]\n", dv, fn);
			GetPhysicalDevice(dv, filename); 
			devlen = strlen(filename);
			strcat(filename, fn);

			SystemDebug.printf("IOD File being removed: %s\n", filename);

			if(!KeepImages)
				{
				if (remove(filename)!=0)
					{
					OperatorConsole.printf("***Could not remove IOD %s\n", filename);
					}

				for (sIndex = strlen(filename); sIndex>=devlen; sIndex--)
					if (filename[sIndex]==PATHSEPCHAR)
						{
						filename[sIndex]='\0';
						rmdir(filename);
						}
				}


			MirrorDevice[0]=0;
			if (memicmp(dv, "MAG", 3)==0)
				{
				sprintf(MirrorDevice, "MIRROR%d", atoi(dv+3));
				if (!GetPhysicalDevice(MirrorDevice, filename))
					MirrorDevice[0]=0;
				else
					{
					devlen = strlen(filename);
					strcat(filename, fn);
					}
				}
				

			if (MirrorDevice[0])
				{
				if(!KeepImages)
					{
					if (remove(filename)!=0)
						{
						OperatorConsole.printf("***Could not remove mirror file %s\n", filename);
						}

					for (sIndex = strlen(filename); sIndex>=devlen; sIndex--)
						if (filename[sIndex]==PATHSEPCHAR)
							{
							filename[sIndex]='\0';
							rmdir(filename);
							}
					}

				}

			RemoveFromWorld(qDDO, DB);
			}
		else
			SystemDebug.printf("***Unable to locate FILENAME for image\n");
		++Index;
		}


	while (ADDO.GetSize())
		{
		delete ADDO.Get(0);
		ADDO.RemoveAt(0);
		}

	return ( TRUE );
	}

BOOL
RemoveDuplicates (
	Database	&DB,
	DBENTRY		*DBE,
	char		*TableName,
	DICOMDataObject	*DDOPtr,
	BOOL		KeyOnAll)
	{
	UINT	Index, CIndex;
	VR	*vr;
	char	s0 [ 256 ], s [ 512 ], s1[4096];

	Index = 0;CIndex = 0;
	s1[0] = '\0';

	while ( TRUE )
		{
		if(!DBE[Index].Element)
			{
			DB.DeleteRecord (TableName, s1);
			return ( TRUE );
			}
		vr = DDOPtr->GetVR(DBE[Index].Group, DBE[Index].Element);
		if(vr)
			{
			if(CIndex)
				{
				// This code makes the 1st field a "key" field
				if (!KeyOnAll)
					{
					DB.DeleteRecord (TableName, s1);
					return ( TRUE );
					}
				strcat(s1, " and " );
				}
			MakeSafeString(vr, s0);
			sprintf(s, " %s = %s ", DBE[Index].SQLColumn, s0);
			strcat(s1, s);
			++CIndex;
			}
		++Index;
		}

	clear_UpdateCache();
	return ( FALSE );
	}


BOOL
PrintTable(DBENTRY	*DBT, char	*name)
	{
	UINT	Index;

	if(!DBT)
		{
		SystemDebug.printf("(null table) %s\n", name);
		return ( FALSE );
		}
	Index = 0;
	while(DBT[Index].Group)
		{
		SystemDebug.printf("(%4.4x, %4.4x) %s, %d\n",
			DBT[Index].Group, DBT[Index].Element,
			DBT[Index].SQLColumn, DBT[Index].SQLLength);
		++Index;
		}
	return ( TRUE );
	}

BOOL
MakeTableString ( DBENTRY	*DBE, char	*s, int mode )
	{
	UINT	Index;
	char	TempString [ 128 ];
		
	s[0] = '\0';

	Index = 0;
	while ( TRUE )
		{
		if(!DBE [ Index ].Element)
			return ( TRUE );

		if (DBE[Index].DICOMType!=DT_STARTSEQUENCE && DBE[Index].DICOMType!=DT_ENDSEQUENCE)
			{
			if(Index)
				strcat(s, ", ");

			strcat ( s, DBE [ Index ].SQLColumn);
			}

		switch ( DBE [ Index ].SQLType)
			{
			case	SQL_C_CHAR:
				if (DBE[Index].DICOMType==DT_STARTSEQUENCE || DBE[Index].DICOMType==DT_ENDSEQUENCE)
					{
					TempString[0]=0;
					break;
					}
				sprintf(TempString, "  varchar(%d)", DBE[Index].SQLLength);
				strcat(s, TempString);
				break;
			case	SQL_C_DATE:
				sprintf(TempString, " char(8) ");
				strcat(s, TempString);
				break;
			default:
				if (DBE[Index].DICOMType==DT_STARTSEQUENCE || DBE[Index].DICOMType==DT_ENDSEQUENCE)
					{
					TempString[0]=0;
					break;
					}
				SystemDebug.printf("Unknown SQL Type: %d\n", DBE[Index].SQLType);
				exit(1);
			}

		if (Index==0 && mode!=1)
			strcat(s, " PRIMARY KEY not null");
			
		++Index;
		}

	return ( FALSE );
	}
			
	
// mode=0: default; mode=1: without indexes; mode=2: worklist only
BOOL
InitializeTables(int mode)
	{
	Database	DB;
	char		s [2048];
	int		HasWorklist=0;
	SQLLEN		sdword;

	if (!DB.Open ( DataSource, UserName, Password, DataHost ) )
		return ( FALSE );

	if (DB.Query(WorkListTableName, "DICOMWorkList.PatientID", NULL, NULL))
	        {
  	        DB.BindField (1, SQL_C_CHAR, s, 255, &sdword);
		if (DB.NextRecord())
			HasWorklist = 1;
	        }

	fprintf(stderr, "Dropping Existing tables (if-any)\n");

	if (!HasWorklist)
		fprintf(stderr, "Worklist is empty\n");
	else
		fprintf(stderr, "Worklist contains data\n");

	if (!HasWorklist || mode==2)
		{
		fprintf(stderr, "Dropping worklist\n");
		DB.DeleteTable ( WorkListTableName );
		}

        if (mode!=2)
		{
		fprintf(stderr, "Dropping other tables\n");
		DB.DeleteTable ( PatientTableName );
		DB.DeleteTable ( StudyTableName );
		DB.DeleteTable ( SeriesTableName );
		DB.DeleteTable ( ImageTableName );
#if 0
		DB.DeleteTable ( RegisteredMOPIDTableName );
		DB.DeleteTable ( UIDToMOPIDTableName );
		DB.DeleteTable ( UIDToCDRIDTableName );
#endif
		DB.DeleteTable ( "UIDMODS" );
		}

	if (!HasWorklist || mode==2)
		if (WorkListDB && WorkListDB[0].Group )
		{
		fprintf(stderr, "WorkList Database\n");
		MakeTableString ( WorkListDB, s, mode );
		strcat(s, ", AccessTime  int" );
		strcat(s, ", qTimeStamp   int" );
	        strcat(s, ", qFlags       int" );
		strcat(s, ", qSpare       varchar(64)" );
		DB.CreateTable ( WorkListTableName, s );
		}
	if (mode==2) return FALSE;

	fprintf(stderr, "Patient Database\n");
	MakeTableString ( PatientDB, s, mode );
	strcat(s, ", AccessTime  int" );
	strcat(s, ", qTimeStamp   int" );
        strcat(s, ", qFlags       int" );
	strcat(s, ", qSpare       varchar(64)" );
	DB.CreateTable ( PatientTableName, s );

	fprintf(stderr, "Study Database\n");
	MakeTableString ( StudyDB, s, mode );
	strcat(s, ", AccessTime  int" );
	strcat(s, ", qTimeStamp   int" );
        strcat(s, ", qFlags       int" );
	strcat(s, ", qSpare       varchar(64)" );
	DB.CreateTable ( StudyTableName, s );
	if (mode==0)
		{
		DB.CreateIndex ( StudyTableName, "study_lnk", UniqueLink(StudyDB));
		}

	fprintf(stderr, "Series Database\n");
	MakeTableString ( SeriesDB, s, mode );
	strcat(s, ", AccessTime  int" );
	strcat(s, ", qTimeStamp   int" );
        strcat(s, ", qFlags       int" );
	strcat(s, ", qSpare       varchar(64)" );
	DB.CreateTable ( SeriesTableName, s );
	if (mode==0)
		{
		DB.CreateIndex ( SeriesTableName, "series_lnk", UniqueLink(SeriesDB));
		if (strstr(s, " SeriesPat "))
			DB.CreateIndex ( SeriesTableName, "series_pat", "SeriesPat");
		}

	fprintf(stderr, "Image Database\n");
	MakeTableString ( ImageDB, s, mode);
	strcat(s, ", AccessTime  int" );
	strcat(s, ", qTimeStamp   int" );
        strcat(s, ", qFlags       int" );
	strcat(s, ", qSpare       varchar(64)" );

	if (MaxFieldLength==0 || MaxFieldLength>255)
	  strcat(s, ", ObjectFile  varchar(255)");
	else
	  sprintf(s+strlen(s), ", ObjectFile  varchar(%d)", MaxFieldLength);

        strcat(s, ", DeviceName  varchar(32)");

	if(!DB.CreateTable ( ImageTableName, s ))
		{
		DB.PrintLastError();
		}

	if (mode==0)
		{
		DB.CreateIndex ( ImageTableName, "images_lnk", UniqueLink(ImageDB));
		if (strstr(s, " ImagePat "))
			DB.CreateIndex ( ImageTableName, "images_pat", "ImagePat");
		}

#if 0
	// Create Registered MOP Device Table
	sprintf(s, "MOPID varchar(20), MOPTotalSize varchar(20), MOPUsedSize varchar(20)");
	DB.CreateTable ( RegisteredMOPIDTableName, s );

	// Create SOPInstanceUID => MOPID Table
	sprintf(s, "SOPInstanceUID");
	if (TruncateFieldNames)
	        s[TruncateFieldNames] = 0;
	sprintf(s+strlen(s), " varchar(64), MOPID varchar(20)");
	DB.CreateTable ( UIDToMOPIDTableName, s );

	// Create SOPInstanceUID => CDR Table
	sprintf(s, "SOPInstanceUID");
	if (TruncateFieldNames)
	        s[TruncateFieldNames] = 0;
	sprintf(s+strlen(s), " varchar(64), CDRID varchar(20)");
	DB.CreateTable ( UIDToCDRIDTableName, s );
#endif

	// Create table to register UID modifications
	if (mode==0)
		DB.CreateTable ( "UIDMODS", "MODTime int, OldUID varchar(64) PRIMARY KEY not null, MODType varchar(32), NewUID varchar(64)" );
	else
		DB.CreateTable ( "UIDMODS", "MODTime int, OldUID varchar(64), MODType varchar(32), NewUID varchar(64)" );

	return ( FALSE );
	}

BOOL	VerifyIsInDBE(
	VR	*vr,
	DBENTRY	*DBE,
	DBENTRY	* &TempDBEPtr
	)
	{
	UINT	Index;

	TempDBEPtr = NULL;
	
	Index = 0;
	if(!vr)
		return ( FALSE );
		
	while ( TRUE )
		{
		if (!DBE[Index].Element)
			return ( FALSE );
		if(DBE[Index].Group == vr->Group)
			if(DBE[Index].Element == vr->Element)
				if (DBE[Index].DICOMType!=DT_STARTSEQUENCE && DBE[Index].DICOMType!=DT_ENDSEQUENCE)
				{
				LastADBE = &DBE[Index];

				// NOT THREAD SAFE:
				// TempDBEPtr = LastADBE;
				TempDBEPtr = &DBE[Index];
				return ( TRUE );
				}
		++Index;
		}
	return ( FALSE );
	}

UINT
LastDBE(DBENTRY	*DBE)
	{
	UINT	Index;

	Index = 0;
	while ( TRUE )
		{
		if ( !DBE[Index].Element )
			{
			if(Index)
				return(Index-1);
			}
		++Index;
		}
	return ( 0 );
	}

BOOL	DICOM2SQLQuery (
	char	*s )
	{
	VR		vr;
	char	*s1;

	if(*s)
		{
		vr.Data = (void*)s;
		vr.Length = strlen(s);
		s1 = (char *)malloc(vr.Length*2 + 3);
		MakeSafeString(&vr, s1);
		strcpy(s, s1);
		free(s1);
		vr.Data = NULL;
		vr.Length = 0;
		}

	return ( TRUE );
	}

UINT
DBEIndex(DBENTRY	*DBE, VR	*vr)
	{
	UINT	Index = 0;

	while ( TRUE )
		{
		if(!DBE[Index].Element)
			return ( 0 );
		if(DBE[Index].Group == vr->Group)
		if(DBE[Index].Element == vr->Element)
			return ( Index );
		++Index;
		}
	return ( 0 );
	}

DBENTRY	*
FindDBE(VR	*vr)
	{
	UINT	Index;

// NOT THREAD SAFE! :
//	if(LastADBE)
//		{
//		if(LastADBE->Group==vr->Group)
//			if(LastADBE->Element==vr->Element)
//				return(LastADBE);
//		}

	Index = DBEIndex(ImageDB, vr);
	if(Index)
		return (&ImageDB[Index]);
	else
		{
		if(ImageDB[Index].Group == vr->Group)
		if(ImageDB[Index].Element == vr->Element)
			return ( &ImageDB[Index] );
		}

	Index = DBEIndex(SeriesDB, vr);
	if(Index)
		return (&SeriesDB[Index]);
	else
		{
		if(SeriesDB[Index].Group == vr->Group)
		if(SeriesDB[Index].Element == vr->Element)
			return ( &SeriesDB[Index] );
		}

	Index = DBEIndex(StudyDB, vr);
	if(Index)
		return (&StudyDB[Index]);
	else
		{
		if(StudyDB[Index].Group == vr->Group)
		if(StudyDB[Index].Element == vr->Element)
			return ( &StudyDB[Index] );
		}

	Index = DBEIndex(PatientDB, vr);
	if(Index)
		return (&PatientDB[Index]);
	else
		{
		if(PatientDB[Index].Group == vr->Group)
		if(PatientDB[Index].Element == vr->Element)
			return ( &PatientDB[Index] );
		}

	return ( NULL );
	}

BOOL
BuildSearchString(Database *DB, DBENTRY	*DBE, char	*TableName, VR	*vr, char	*Search,
	char	*TempString, 	int maxlen)
	{
	char	*s, *t;
	char	ch;
	char	TempString1[64];
	char	TempString2[64];
	UINT	Index = DBEIndex(DBE, vr);
	int	len;

	if(vr->Length)
		{
		if(DBE[Index].DICOMType==DT_DATE)
			{
			if(s=strchr(Search, '-'))
				{
				// Date Range
				if((*(s+1))=='\'')
					{
					(*(s+1)) = '\0';
					(*s) = '\'';

					sprintf(TempString, "%s.%s >= %s", TableName, DBE[Index].SQLColumn,
						Search);

					}
				else if((*(s-1))=='\'')
					{
					(*s) = '\'';
					sprintf(TempString, "%s.%s <= %s", TableName, DBE[Index].SQLColumn,
						s);
					}
				else
					{
					// Bummer format is 'date-date'
					ch = (*(s+1));
					(*(s+1)) = '\0';
					(*s) = '\'';

					sprintf(TempString1, "%s.%s >= %s", TableName, DBE[Index].SQLColumn,
						Search);

					(*(s+1)) = ch;
					sprintf(TempString2, "%s.%s <= %s", TableName, DBE[Index].SQLColumn,
						s);

					sprintf(TempString, "%s and %s", TempString1, TempString2);
					}
				}
			else
				{
				if (strchr(Search, '_') || strchr(Search, '%'))
					sprintf(TempString, "%s.%s LIKE %s", TableName, DBE[Index].SQLColumn,
						Search);
				else
					sprintf(TempString, "%s.%s = %s", TableName, DBE[Index].SQLColumn,
						Search);
				}
			}

		// Multiple UID matching
		else if(DBE[Index].DICOMType==DT_UI)
			{
			BOOL dbiii = (DB->db_type == DT_DBASEIII);

			s = strchr(Search, '\\');

			if (s && !dbiii)
				{
				// Multiple UID matching sql server style with syntax: field in ('a','b','c')
				// requires 3 characters per UID, e.g., 8192-512 fits about 110 UIDs
				sprintf(TempString, "%s.%s in (", TableName, DBE[Index].SQLColumn);

				t = Search + 1;		// skip '

				while (s)		// before each \ is an UID
					{
					*s = 0;
					if (s[1] == '\\')	// also process double backslash correctly
						{
						s++;
						*s = 0;
						}

					len = strlen(TempString);
					if (len<maxlen)
  					  sprintf(TempString + len, "'%s',", t);

					t = s + 1;
					s = strchr(t, '\\');
					}

				// the last UID ends with a '
				sprintf(TempString + strlen(TempString), "'%s)", t);
				}

			else if (s && dbiii)
				{
				// Multiple UID matching built-in dbaseIII style with | syntax: field in 'a|b|c'
				// requires 1 character per UID, e.g., 8192-512 fit max about 115 UIDs
				sprintf(TempString, "%s.%s in '", TableName, DBE[Index].SQLColumn);

				t = Search + 1;		// skip '

				while (s)		// before each \ is an UID
					{
					*s = 0;
					if (s[1] == '\\')	// also process double backslash correctly
						{
						s++;
						*s = 0;
						}

					len = strlen(TempString);
					if (len<maxlen)
					  sprintf(TempString + len, "%s|", t);

					t = s + 1;
					s = strchr(t, '\\');
					}

				// the last UID ends with a '
				sprintf(TempString + strlen(TempString), "%s", t);
				}

			else
				{
				if (strchr(Search, '_') || strchr(Search, '%'))
					sprintf(TempString, "%s.%s LIKE %s", TableName, DBE[Index].SQLColumn,
						Search);
				else
					sprintf(TempString, "%s.%s = %s", TableName, DBE[Index].SQLColumn,
						Search);
				}
			}
		// DT_MSTR: PET matches 'PET', 'PET\CT', 'MR\PET\CT', and 'CT\PET'
		// not implemented yet for DBASEIII, also wildcards give original query
		else if((DBE[Index].DICOMType==DT_MSTR) && (DB->db_type != DT_DBASEIII))
			{
			if (strchr(Search, '_') || strchr(Search, '%'))
				sprintf(TempString, "%s.%s LIKE %s", TableName, DBE[Index].SQLColumn,
					Search);
			else
				{
				char *p = Search + strlen(Search) - 1;
				char *d;
				if (DoubleBackSlashToDB) d = "\\\\"; else d = "\\";
				sprintf(TempString, "(%s.%s = %s or ", TableName, DBE[Index].SQLColumn, Search);

				*p = 0;
				sprintf(TempString + strlen(TempString), "%s.%s LIKE '%s%s%%' or ", TableName, DBE[Index].SQLColumn, Search+1, d);
				sprintf(TempString + strlen(TempString), "%s.%s LIKE '%%%s%s%s%%' or ", TableName, DBE[Index].SQLColumn, d, Search+1, d);
				sprintf(TempString + strlen(TempString), "%s.%s LIKE '%%%s%s')", TableName, DBE[Index].SQLColumn, d, Search+1);
				*p = '\'';
				}
			}
		else
			{
			if (strchr(Search, '_') || strchr(Search, '%'))
				sprintf(TempString, "%s.%s LIKE %s", TableName, DBE[Index].SQLColumn,
					Search);
			else
				{
				sprintf(TempString, "%s.%s = %s", TableName, DBE[Index].SQLColumn,
					Search);

				if (DBE[Index].DICOMType==DT_MSTR)
					SystemDebug.printf("warning: query for this multi-valued item (%s) will not test individual values\n", DBE[Index].SQLColumn);
				}

			}

		return (TRUE);
		}
	return ( FALSE );
	}

BOOL
BuildColumnString(DBENTRY	*DBE, char	*TableName, VR	*vr,	char	*TempString)
	{
	UINT	Index = DBEIndex(DBE, vr);

	strcpy(TempString, TableName);
	strcat(TempString, ".");
	strcat(TempString, DBE[Index].SQLColumn);
	return ( TRUE );
	}

UINT32
SQLRealSize(char	*Str, SDWORD	Max)
	{
	UINT32	Index = 0;
	UINT32	RSize = 0;

	if(Max<0) return 0;
	return Max;
#if 0
	while (Index < Max)				// mvh 20051123
		{
		if(Str[Index]== 0 ) break;
		if(Str[Index]!=' ') RSize = Index+1;
		++Index;
		}
	return ( RSize );
#endif
	}

VR	*
ConstructVRFromSQL (
	DBENTRY		*DBE,
	UINT16		Group,
	UINT16		Element,
	UINT32		Length,
	char		*SQLResultString )
	{
	LE_UINT16	tuint16;
	LE_UINT32	tuint32;
	VR			*vr = NULL;
	
	SQLResultString[Length] = '\0';
		
	if(Length&0x01)
		++Length;
	

	switch ( DBE?DBE->DICOMType:DT_STR )
		{
		case	DT_UI:	
			vr = new VR (Group, Element, Length, (BOOL) TRUE );
			if(Length)
				{
				memset(vr->Data, 0, vr->Length);
				memcpy(vr->Data, (void*)SQLResultString, strlen(SQLResultString));
				}
			break;
		case	DT_STR:
		case	DT_MSTR:
		case	DT_DATE:
			vr = new VR (Group, Element, Length, (BOOL) TRUE );
			if(Length)
				{
				memset(vr->Data, ' ', vr->Length);
				memcpy(vr->Data, (void*)SQLResultString, strlen(SQLResultString));
				}
			break;
		case	DT_UINT16:
			vr = new VR (Group, Element, 2, (BOOL) TRUE );
			tuint16 = (LE_UINT16) atoi(SQLResultString);
			memcpy(vr->Data, (void*)&tuint16, 2);
			break;
		case	DT_UINT32:
			vr = new VR (Group, Element, 2, (BOOL) TRUE );
			tuint32 = (LE_UINT32) atoi(SQLResultString);
			memcpy(vr->Data, (void*)&tuint32, 2);
			break;
		}
	return ( vr );
	}

VR	*
ConstructAE ()
	{
	VR		*vr = new VR( 0x0008, 0x0054, 16, (BOOL) TRUE );
	
	memset(vr->Data, ' ', 16);
	memcpy(vr->Data, MYACRNEMA, strlen((char*)MYACRNEMA)%16);
	return ( vr );
	}
	
