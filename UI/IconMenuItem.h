///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : UI
// File        : IconMenuItem.h
// Description : defines MenuItem with icon
// Author      : cedric.bresson@artcoder.com
///////////////////////////////////////////////////////////////////////////////
#ifndef __IconMenuItem_h__
#define __IconMenuItem_h__

#include "MenuItem.h"
#include "MoleSvnIcons.h"
#include "../Config.h"

class IconMenuItem : public MenuItem
{
public:
	IconMenuItem(const char* strLabel, MenuItemCommand cmd, MoleSvnIcons iconId);
		// Description : contructor
		
	virtual ~IconMenuItem();
		// Description : destructor
		
	void DrawContent();
		// Description : overrides default method, draws icon

private:
	BBitmap* m_pIcon;
		// Description : icon of the menu item
		// Init        : By cons
};

#endif //__IconMenuItem_h__

