///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : Svn
// File        : Blame.cpp
// Description : implements the Blame command class
// Author      : cedric.bresson@artcoder.com
#include "Blame.h"
#include "../UI/ResultsWindow.h"


using namespace std;

///////////////////////////////////////////////////////////////////////////////
// -- Life-cycle
///////////////////////////////////////////////////////////////////////////////
Blame::Blame()
:SvnCommand("Blame", MSG_BLAME, R_Blame)
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));
}

Blame::~Blame()
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));
}


///////////////////////////////////////////////////////////////////////////////
// -- Services
///////////////////////////////////////////////////////////////////////////////
void Blame::Execute()
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));
	
	m_pTarget = new ResultsWindow(GetName());
	
	ExecuteSvn(string("svn blame"));	
}


///////////////////////////////////////////////////////////////////////////////
// -- Accessors
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// -- Private
///////////////////////////////////////////////////////////////////////////////
