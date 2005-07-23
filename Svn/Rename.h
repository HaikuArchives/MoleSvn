///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : Svn
// File        : Rename.h
// Description : defines the Rename command class
// Author      : cedric.bresson@artcoder.com
///////////////////////////////////////////////////////////////////////////////
#ifndef __Rename_h__
#define __Rename_h__

#include <string>
#include "Config.h"
#include "SvnCommands.h"


class Rename : public SvnCommand
{
public:
	// -- Life-cycle ----------------------------------------------------------
	Rename();
		// Description : default constructor
		
	virtual ~Rename(); 	
		// Description : Destructor
		
	// -- Services ------------------------------------------------------------
	void Execute();
		// Description : executes the Rename command
		
	// -- Accessors -----------------------------------------------------------
	
private:
		
	TRACE_CLASS (CC_APPLICATION);
};

#endif //__Rename_h__

