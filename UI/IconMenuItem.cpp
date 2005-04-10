///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : UI
// File        : IconMenuItem.h
// Description : defines MenuItem with icon
// Author      : cedric.bresson@artcoder.com
///////////////////////////////////////////////////////////////////////////////

#include "IconMenuItem.h"

IconMenuItem::IconMenuItem(const char* strLabel, const BBitmap& rIcon)
:BMenuItem(strLabel, NULL), m_pIcon(NULL)
{
	m_pIcon = new BBitmap(rIcon);
	if(!m_pIcon->IsValid())
	{
		delete m_pIcon;
		m_pIcon = NULL;
	}
}
		
IconMenuItem::~IconMenuItem()
{
	if(m_pIcon)
	{
		delete m_pIcon;
	}
}
		
void IconMenuItem::DrawContent()
{
	BPoint drawPoint(ContentLocation());
	drawPoint.x += 20;
	Menu()->MovePenTo(drawPoint);
	BMenuItem::DrawContent();
	
	BPoint where(ContentLocation());
	where.y = Frame().top;
	
	if (m_pIcon)
	{
		if (IsEnabled())
			Menu()->SetDrawingMode(B_OP_OVER);
		else
			Menu()->SetDrawingMode(B_OP_BLEND);	
		
		Menu()->DrawBitmapAsync(m_pIcon, where);
	}
}
