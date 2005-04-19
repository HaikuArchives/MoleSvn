///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : Svn
// File        : Commit.h
// Description : defines the Commit command class
// Author      : cedric.bresson@artcoder.com
///////////////////////////////////////////////////////////////////////////////
#ifndef __Commit_h__
#define __Commit_h__

#include <string>
#include "Config.h"
#include "SvnCommands.h"

class Commit : public SvnCommand
{
public:
	// -- Life-cycle ----------------------------------------------------------
	Commit();
		// Description : default constructor
		
	virtual ~Commit(); 	
		// Description : Destructor
		
	// -- Services ------------------------------------------------------------
	void Execute();
		// Description : executes the Commit command
		
	// -- Accessors -----------------------------------------------------------
	
private:
		
	TRACE_CLASS (CC_APPLICATION);
};

#endif //__Commit_h__

