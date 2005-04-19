///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : UI
// File        : MenuItem.h
// Description : defines specific MenuItem 
// Author      : cedric.bresson@artcoder.com
///////////////////////////////////////////////////////////////////////////////
#ifndef __MenuItem_h__
#define __MenuItem_h__

#include "../Config.h"
#include "../Svn/SvnCommands.h"

class MenuItem : public BMenuItem
{
public:
	MenuItem(SvnCommand* pSvnCmd);
		// Description : contructor
		
	virtual ~MenuItem();
		// Description : destructor
		
	SvnCommand* GetSvnCommand();
		// Description : returns the svn command of the menu item
		
protected:
	SvnCommand* m_pSvnCmd;
		// Description : svn command that the menu item must execute
};

#endif //__IconMenuItem_h__

