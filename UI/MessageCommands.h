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

	MSG_OK            = 'M_OK',
	MSG_CANCEL   	  = 'MCAN',

	MSG_EXECUTE_CMD   = 'MEXE',
	MSG_SVN_STDOUT    = 'MSTD',
};

#endif //__MessageCommands_h__

