///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : Svn
// File        : Delete.h
// Description : defines the Delete command class
// Author      : cedric.bresson@artcoder.com
///////////////////////////////////////////////////////////////////////////////
#ifndef __Delete_h__
#define __Delete_h__

#include <string>
#include "Config.h"
#include "SvnCommands.h"

class Delete : public SvnCommand
{
public:
	// -- Life-cycle ----------------------------------------------------------
	Delete();
		// Description : default constructor
		
	virtual ~Delete(); 	
		// Description : Destructor
		
	// -- Services ------------------------------------------------------------
	void Execute();
		// Description : executes the Delete command
		
	// -- Accessors -----------------------------------------------------------
	
private:
		
	TRACE_CLASS (CC_APPLICATION);
};

#endif //__Delete_h__

