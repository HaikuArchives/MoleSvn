///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : Svn
// File        : Cleanup.h
// Description : defines the Cleanup command class
// Author      : cedric.bresson@artcoder.com
///////////////////////////////////////////////////////////////////////////////
#ifndef __Cleanup_h__
#define __Cleanup_h__

#include <string>
#include "Config.h"
#include "SvnCommands.h"

class Cleanup : public SvnCommand
{
public:
	// -- Life-cycle ----------------------------------------------------------
	Cleanup();
		// Description : default constructor
		
	virtual ~Cleanup(); 	
		// Description : Destructor
		
	// -- Services ------------------------------------------------------------
	void Execute();
		// Description : executes the Cleanup command
		
	// -- Accessors -----------------------------------------------------------
	
private:
		
	TRACE_CLASS (CC_APPLICATION);
};

#endif //__Cleanup_h__

