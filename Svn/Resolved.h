///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : Svn
// File        : Resolved.h
// Description : defines the Resolved command class
// Author      : cedric.bresson@artcoder.com
///////////////////////////////////////////////////////////////////////////////
#ifndef __Resolved_h__
#define __Resolved_h__

#include <string>
#include "Config.h"
#include "SvnCommands.h"

class Resolved : public SvnCommand
{
public:
	// -- Life-cycle ----------------------------------------------------------
	Resolved();
		// Description : default constructor
		
	virtual ~Resolved(); 	
		// Description : Destructor
		
	// -- Services ------------------------------------------------------------
	void Execute();
		// Description : executes the Resolved command
		
	// -- Accessors -----------------------------------------------------------
	
private:
		
	TRACE_CLASS (CC_APPLICATION);
};

#endif //__Resolved_h__

