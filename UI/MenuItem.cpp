///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : UI
// File        : MenuItem.h
// Description : defines MenuItem with icon
// Author      : cedric.bresson@artcoder.com
///////////////////////////////////////////////////////////////////////////////

#include "MenuItem.h"

MenuItem::MenuItem(SvnCommand* pSvnCmd)
:BMenuItem(pSvnCmd->GetName().c_str(), NULL), m_pSvnCmd(pSvnCmd)
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));

}

MenuItem::~MenuItem()
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));

}

SvnCommand* MenuItem::GetSvnCommand()
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));
	return m_pSvnCmd;
}
