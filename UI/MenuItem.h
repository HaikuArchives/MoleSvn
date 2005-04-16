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

enum MenuItemCommand
{
	C_Checkout = 0,
	C_Add,
	C_Update,
	C_Commit,
	C_Status,
	C_About,
};

class MenuItem : public BMenuItem
{
public:
	MenuItem(const char* strLabel, MenuItemCommand cmd);
		// Description : contructor
		
	virtual ~MenuItem();
		// Description : destructor
		
	MenuItemCommand GetCommand() const;
		// Description: return the command of the menu item
private:
	MenuItemCommand m_Command;
		// Description : svn commant for this menu item
		// Init        : By cons
};

#endif //__IconMenuItem_h__

