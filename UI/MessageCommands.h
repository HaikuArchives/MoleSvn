///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : UI
// File        : MessageCommands.h
// Description : defines command id for all BMessage 
// Author      : cedric.bresson@artcoder.com
///////////////////////////////////////////////////////////////////////////////
#ifndef __MessageCommands_h__
#define __MessageCommands_h__

enum MessageCommand
{
	MSG_CHECKOUT 	  = 'MCHK',
	MSG_ADD      	  = 'MADD',
	MSG_UPDATE   	  = 'MUPD',
	MSG_COMMIT   	  = 'MCOM',
	MSG_STATUS   	  = 'MSTA',
	MSG_ABOUT    	  = 'MABO',
	MSG_DELETE        = 'MDEL',
	MSG_BLAME         = 'MBLA',
	MSG_CLEANUP       = 'MCLE',
	MSG_RESOLVED      = 'MRES',
	MSG_REVERT        = 'MREV',
	MSG_RENAME        = 'MREN',

	MSG_OK            = 'M_OK',
	MSG_CANCEL   	  = 'MCAN',

	MSG_EXECUTE_CMD   = 'MEXE',
	MSG_SVN_STDOUT    = 'MSTD',
	MSG_CMD_FINISHED  = 'MFNS',
};

#endif //__MessageCommands_h__

