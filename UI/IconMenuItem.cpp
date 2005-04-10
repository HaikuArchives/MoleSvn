///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : UI
// File        : IconMenuItem.h
// Description : defines MenuItem with icon
// Author      : cedric.bresson@artcoder.com
///////////////////////////////////////////////////////////////////////////////

#include "IconMenuItem.h"
#include "../MoleSvnAddon.h"

IconMenuItem::IconMenuItem(const char* strLabel, MenuItemCommand cmd, MoleSvnIcons iconId)
:MenuItem(strLabel, cmd), m_pIcon(NULL)
{
	MoleSvnAddon::GetInstance()->GetResources()->LoadIcon('MICN', iconId, &m_pIcon);
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
