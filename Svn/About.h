///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : Svn
// File        : About.h
// Description : defines the About command class
// Author      : cedric.bresson@artcoder.com
///////////////////////////////////////////////////////////////////////////////
#ifndef __About_h__
#define __About_h__

#include <string>
#include "Config.h"
#include "SvnCommands.h"

class About : public SvnCommand
{
public:
	// -- Life-cycle ----------------------------------------------------------
	About();
		// Description : default constructor
		
	virtual ~About(); 	
		// Description : Destructor
		
	// -- Services ------------------------------------------------------------
	void Execute();
		// Description : executes the About command
		
	// -- Accessors -----------------------------------------------------------
	
private:
		
	TRACE_CLASS (CC_APPLICATION);
};

#endif //__About_h__

