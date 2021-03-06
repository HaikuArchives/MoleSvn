///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : Svn
// File        : Resolved.cpp
// Description : implements the Resolved command class
// Author      : cedric.bresson@artcoder.com
#include "Resolved.h"
#include "../UI/ResultsWindow.h"


using namespace std;

///////////////////////////////////////////////////////////////////////////////
// -- Life-cycle
///////////////////////////////////////////////////////////////////////////////
Resolved::Resolved()
:SvnCommand("Resolved", MSG_RESOLVED, R_Resolved)
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));
}

Resolved::~Resolved()
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));
}


///////////////////////////////////////////////////////////////////////////////
// -- Services
///////////////////////////////////////////////////////////////////////////////
void Resolved::Execute()
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));
	
	m_pTarget = new ResultsWindow(GetName());
	
	ExecuteSvn(string("svn resolved --recursive ") + MoleSvnAddon::GetInstance()->GetEntryNameList());	
}


///////////////////////////////////////////////////////////////////////////////
// -- Accessors
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// -- Private
///////////////////////////////////////////////////////////////////////////////
