///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : UI
// File        : CheckoutWindow.h
// Description : defines window which will display checkout parameters, like
//               URL repository, revision
// Author      : cedric.bresson@artcoder.com
///////////////////////////////////////////////////////////////////////////////
#ifndef __CheckoutWindow_h__
#define __CheckoutWindow_h__

#include "../Config.h"
#include "../Svn/SvnCommands.h"
#include "../3rd/PassControl.h"

class CheckoutWindow : public BWindow
{
public:
	// -- Life-cycle ----------------------------------------------------------
	CheckoutWindow(Checkout* pCmd);
		// Description : constructor
	
	virtual ~CheckoutWindow();
		// Description : destructor
		
	// -- Hooks ---------------------------------------------------------------
	virtual void MessageReceived(BMessage *message);

private:
	void CreateView();
		// Description : build UI
		
	bool CheckParameters();
		// Description : returns true if the checkout parameters entered by the
		//               user are valid.

	BTextControl* m_pUrlRepository;
	BTextControl* m_pCheckoutDirectory;
	BFilePanel*   m_pFilePanel;
	Checkout* 	  m_pCmd;
	BTextControl* m_pLogin;
	PassControl*  m_pPassword;	
};


#endif //__CheckoutWindow_h__

