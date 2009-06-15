/*
20050129	mvh	Made tables public
20080819	mvh	Made CanYouHandleTransferSyntax public
*/
/****************************************************************************
          Copyright (C) 1995, University of California, Davis

          THIS SOFTWARE IS MADE AVAILABLE, AS IS, AND THE UNIVERSITY
          OF CALIFORNIA DOES NOT MAKE ANY WARRANTY ABOUT THE SOFTWARE, ITS
          PERFORMANCE, ITS MERCHANTABILITY OR FITNESS FOR ANY PARTICULAR
          USE, FREEDOM FROM ANY COMPUTER DISEASES OR ITS CONFORMITY TO ANY
          SPECIFICATION. THE ENTIRE RISK AS TO QUALITY AND PERFORMANCE OF
          THE SOFTWARE IS WITH THE USER.

          Copyright of the software and supporting documentation is
          owned by the University of California, and free access
          is hereby granted as a license to use this software, copy this
          software and prepare derivative works based upon this software.
          However, any distribution of this software source code or
          supporting documentation or derivative works (source code and
          supporting documentation) must include this copyright notice.
****************************************************************************/

/***************************************************************************
 *
 * University of California, Davis
 * UCDMC DICOM Network Transport Libraries
 * Version 0.1 Beta
 *
 * Technical Contact: mhoskin@ucdavis.edu
 *
 ***************************************************************************/

/***********************************************************************
 *
 * Cheked (Verified) PDU_Service Class.
 *
 ***********************************************************************/
class	CheckedPDU_Service	:
	public		PDU_Service
	{
		BOOL	ShouldIAcceptRemoteApTitle(BYTE *);
		BOOL	ShouldIAcceptLocalApTitle(BYTE *);
		BOOL	ShouldIAcceptApplicationContext(ApplicationContext &);
		BOOL	ShouldIAcceptAbstractSyntax(AbstractSyntax &);
	public:
		BOOL	CanYouHandleTransferSyntax(TransferSyntax	&);	
		UINT	SOPUIDListCount;
		UINT	TransferUIDListCount;
		UINT	ApplicationUIDListCount;
		UINT	RemoteAEListCount;
		UINT	LocalAEListCount;
		char	**SOPUIDList;
		char	**SOPUIDListNames;
		char	**TransferUIDList;
		char	**TransferUIDListNames;
		char	**ApplicationUIDList;
		char	**ApplicationUIDListNames;
		char	**RemoteAEList;
		char	**RemoteAEListNames;
		char	**LocalAEList;
		char	**LocalAEListNames;
		CheckedPDU_Service (char	*filename);
		~CheckedPDU_Service ();
		BOOL	InitializeFrom ( char *filename );
		BOOL	ReleaseMemory ();
	};
				
