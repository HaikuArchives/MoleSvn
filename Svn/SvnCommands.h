///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : Svn
// File        : SvnCommands.h
// Description : defines the SvnCommands class, the commands send to svn
// Author      : cedric.bresson@artcoder.com
///////////////////////////////////////////////////////////////////////////////
#ifndef __SvnCommands_h__
#define __SvnCommands_h__

#include <list>
#include "Config.h"

class SvnCommands
{
public:
	// -- Life-cycle ----------------------------------------------------------
	SvnCommands();
		// Description : constructor
	
	~SvnCommands(); 	
		// Description : Destructor
		
	// -- Services ------------------------------------------------------------
		
	// -- Accessors -----------------------------------------------------------
	
private:
		
	TRACE_CLASS (CC_APPLICATION);
};

#endif //__SvnCommands_h__

