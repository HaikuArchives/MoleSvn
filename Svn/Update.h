///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : Svn
// File        : Update.h
// Description : defines the Update command class
// Author      : cedric.bresson@artcoder.com
///////////////////////////////////////////////////////////////////////////////
#ifndef __Update_h__
#define __Update_h__

#include <string>
#include "Config.h"
#include "SvnCommands.h"

class Update : public SvnCommand
{
public:
	// -- Life-cycle ----------------------------------------------------------
	Update();
		// Description : default constructor
		
	virtual ~Update(); 	
		// Description : Destructor
		
	// -- Services ------------------------------------------------------------
	void Execute();
		// Description : executes the update command
		
	// -- Accessors -----------------------------------------------------------
	
private:
		
	TRACE_CLASS (CC_APPLICATION);
};

#endif //__Update_h__

