///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : Svn
// File        : Status.h
// Description : defines the Status command class
// Author      : cedric.bresson@artcoder.com
///////////////////////////////////////////////////////////////////////////////
#ifndef __Status_h__
#define __Status_h__

#include <string>
#include "Config.h"
#include "SvnCommands.h"

class Status : public SvnCommand
{
public:
	// -- Life-cycle ----------------------------------------------------------
	Status();
		// Description : default constructor
		
	virtual ~Status(); 	
		// Description : Destructor
		
	// -- Services ------------------------------------------------------------
	void Execute();
		// Description : executes the Status command
		
	// -- Accessors -----------------------------------------------------------
	
private:
		
	TRACE_CLASS (CC_APPLICATION);
};

#endif //__Status_h__

