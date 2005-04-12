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
	MSG_Checkout = 'MCHK',
	MSG_Add      = 'MADD',
	MSG_Update   = 'MUPD',
	MSG_Commit   = 'MCOM',
	MSG_About    = 'MABO',
	MSG_Ok       = 'M_OK'
};

#endif //__MessageCommands_h__

