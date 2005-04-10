///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : UI
// File        : MenuItem.h
// Description : defines MenuItem with icon
// Author      : cedric.bresson@artcoder.com
///////////////////////////////////////////////////////////////////////////////

#include "MenuItem.h"

MenuItem::MenuItem(const char* strLabel, MenuItemCommand cmd)
:BMenuItem(strLabel, NULL), m_Command(cmd)
{
	// Empty
}
		
MenuItem::~MenuItem()
{

}
		
