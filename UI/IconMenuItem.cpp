///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : UI
// File        : IconMenuItem.h
// Description : defines MenuItem with icon
// Author      : cedric.bresson@artcoder.com
///////////////////////////////////////////////////////////////////////////////

#include "IconMenuItem.h"
#include "../MoleSvnAddon.h"

IconMenuItem::IconMenuItem(SvnCommand* pSvnCmd)
:MenuItem(pSvnCmd)
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));

}

IconMenuItem::~IconMenuItem()
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));
}
		
void IconMenuItem::DrawContent()
{
	BPoint drawPoint(ContentLocation());
	drawPoint.x += 20;
	Menu()->MovePenTo(drawPoint);
	BMenuItem::DrawContent();
	
	BPoint where(ContentLocation());
	where.y = Frame().top;
	
	if (IsEnabled())
		Menu()->SetDrawingMode(B_OP_OVER);
	else
		Menu()->SetDrawingMode(B_OP_BLEND);	
		
	Menu()->DrawBitmapAsync(m_pSvnCmd->GetMiniIcon(), where);
}
