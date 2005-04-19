///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : Svn
// File        : Add.h
// Description : defines the Add command class
// Author      : cedric.bresson@artcoder.com
///////////////////////////////////////////////////////////////////////////////
#ifndef __Add_h__
#define __Add_h__

#include <string>
#include "Config.h"
#include "SvnCommands.h"

class Add : public SvnCommand
{
public:
	// -- Life-cycle ----------------------------------------------------------
	Add();
		// Description : default constructor
		
	virtual ~Add(); 	
		// Description : Destructor
		
	// -- Services ------------------------------------------------------------
	void Execute();
		// Description : executes the Add command
		
	// -- Accessors -----------------------------------------------------------
	
private:
		
	TRACE_CLASS (CC_APPLICATION);
};

#endif //__Add_h__

