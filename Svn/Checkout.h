///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : Svn
// File        : Checkout.h
// Description : defines the Checkout command class
// Author      : cedric.bresson@artcoder.com
///////////////////////////////////////////////////////////////////////////////
#ifndef __Checkout_h__
#define __Checkout_h__

#include <string>
#include "Config.h"
#include "SvnCommands.h"

class Checkout : public SvnCommand
{
public:
	// -- Life-cycle ----------------------------------------------------------
	Checkout();
		// Description : default constructor
		
	virtual ~Checkout(); 	
		// Description : Destructor
		
	// -- Services ------------------------------------------------------------
	void Execute();
		// Description : executes the Checkout command
		
	// -- Hooks ---------------------------------------------------------------
	virtual void MessageReceived(BMessage *message);
		
	// -- Accessors -----------------------------------------------------------
	
private:
		
	TRACE_CLASS (CC_APPLICATION);
};

#endif //__Checkout_h__

