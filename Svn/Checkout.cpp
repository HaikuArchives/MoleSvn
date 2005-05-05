///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : Svn
// File        : Checkout.cpp
// Description : implements the Checkout command class
// Author      : cedric.bresson@artcoder.com
#include "Checkout.h"
#include "../UI/ResultsWindow.h"
#include "../UI/CheckoutWindow.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// -- Life-cycle
///////////////////////////////////////////////////////////////////////////////
Checkout::Checkout()
:SvnCommand("Checkout", MSG_CHECKOUT, R_Checkout)
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));
}

Checkout::~Checkout()
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));
}


///////////////////////////////////////////////////////////////////////////////
// -- Services
///////////////////////////////////////////////////////////////////////////////
void Checkout::Execute()
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));
	
	new CheckoutWindow(this);
}

///////////////////////////////////////////////////////////////////////////////
// -- Hooks
///////////////////////////////////////////////////////////////////////////////
void Checkout::MessageReceived(BMessage *message)
{
	switch(message->what)
	{
	case MSG_OK:
	{
/*	
		ResultsWindow* pWindow = new ResultsWindow(GetName());
		m_pTarget = pWindow;

		BString tmp;	
		message->FindString("url", &tmp);
		string url = string(tmp.String());
		message->FindString("dir", &tmp);
		string dir = string(tmp.String());
		string cmd = string("svn checkout ") + url + " " + dir;
		int nError = ExecuteSvn(string(cmd.c_str()));
		TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Execute error = %d", nError));

		if(nError)
		{
			ShowErrorWindow(string("checkout failed"));
			pWindow->Quit();
		}
*/		
		break;
	}
	case MSG_CANCEL:
	{
		break;
	}
	default:
		SvnCommand::MessageReceived(message);
		break;
	}
}

///////////////////////////////////////////////////////////////////////////////
// -- Accessors
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// -- Private
///////////////////////////////////////////////////////////////////////////////
