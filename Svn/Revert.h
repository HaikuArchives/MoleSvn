///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : Svn
// File        : Revert.h
// Description : defines the Revert command class
// Author      : cedric.bresson@artcoder.com
///////////////////////////////////////////////////////////////////////////////
#ifndef __Revert_h__
#define __Revert_h__

#include <string>
#include "Config.h"
#include "SvnCommands.h"

class Revert : public SvnCommand
{
public:
	// -- Life-cycle ----------------------------------------------------------
	Revert();
		// Description : default constructor
		
	virtual ~Revert(); 	
		// Description : Destructor
		
	// -- Services ------------------------------------------------------------
	void Execute();
		// Description : executes the Revert command
		
	// -- Accessors -----------------------------------------------------------
	
private:
		
	TRACE_CLASS (CC_APPLICATION);
};

#endif //__Revert_h__

