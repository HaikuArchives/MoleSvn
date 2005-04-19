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
	IconMenuItem(SvnCommand* pSvnCmd);
		// Description : contructor
		
	virtual ~IconMenuItem();
		// Description : destructor
		
	void DrawContent();
		// Description : overrides default method, draws icon
};

#endif //__IconMenuItem_h__

