///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : Svn
// File        : Cleanup.cpp
// Description : implements the Cleanup command class
// Author      : cedric.bresson@artcoder.com
#include "Cleanup.h"
#include "../UI/ResultsWindow.h"


using namespace std;

///////////////////////////////////////////////////////////////////////////////
// -- Life-cycle
///////////////////////////////////////////////////////////////////////////////
Cleanup::Cleanup()
:SvnCommand("Cleanup", MSG_CLEANUP, R_Cleanup)
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));
}

Cleanup::~Cleanup()
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));
}


///////////////////////////////////////////////////////////////////////////////
// -- Services
///////////////////////////////////////////////////////////////////////////////
void Cleanup::Execute()
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));
	
	m_pTarget = new ResultsWindow(GetName());
	
	ExecuteSvn(string("svn cleanup"));	
}


///////////////////////////////////////////////////////////////////////////////
// -- Accessors
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// -- Private
///////////////////////////////////////////////////////////////////////////////
