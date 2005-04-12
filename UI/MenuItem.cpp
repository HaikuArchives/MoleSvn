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
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));

}
		
MenuItem::~MenuItem()
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));

}
		
MenuItemCommand MenuItem::GetCommand() const
{
	return m_Command;
}
