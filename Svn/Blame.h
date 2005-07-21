///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : Svn
// File        : Blame.h
// Description : defines the Blame command class
// Author      : cedric.bresson@artcoder.com
///////////////////////////////////////////////////////////////////////////////
#ifndef __Blame_h__
#define __Blame_h__

#include <string>
#include "Config.h"
#include "SvnCommands.h"

class Blame : public SvnCommand
{
public:
	// -- Life-cycle ----------------------------------------------------------
	Blame();
		// Description : default constructor
		
	virtual ~Blame(); 	
		// Description : Destructor
		
	// -- Services ------------------------------------------------------------
	void Execute();
		// Description : executes the Blame command
		
	// -- Accessors -----------------------------------------------------------
	
private:
		
	TRACE_CLASS (CC_APPLICATION);
};

#endif //__Blame_h__

