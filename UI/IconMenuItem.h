///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : UI
// File        : IconMenuItem.h
// Description : defines MenuItem with icon
// Author      : cedric.bresson@artcoder.com
///////////////////////////////////////////////////////////////////////////////
#ifndef __IconMenuItem_h__
#define __IconMenuItem_h__

#include <InterfaceKit.h>

class IconMenuItem : public BMenuItem
{
public:
	IconMenuItem(const char* strLabel, const BBitmap& rIcon);
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

