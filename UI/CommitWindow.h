///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : UI
// File        : CommitWindow.h
// Description : defines window which will display Commit parameters, like
//               URL repository, revision
// Author      : cedric.bresson@artcoder.com
///////////////////////////////////////////////////////////////////////////////
#ifndef __CommitWindow_h__
#define __CommitWindow_h__

#include "../Config.h"
#include "../Svn/SvnCommands.h"
#include "../3rd/PassControl.h"

class CommitWindow : public BWindow
{
public:
	// -- Life-cycle ----------------------------------------------------------
	CommitWindow(Commit* pCmd);
		// Description : constructor
	
	virtual ~CommitWindow();
		// Description : destructor
		
	// -- Hooks ---------------------------------------------------------------
	virtual void MessageReceived(BMessage *message);

private:
	void CreateView();
		// Description : build UI
		
	Commit* 	  m_pCmd;
	BTextView* 	  m_pTextView;
	BTextControl* m_pLogin;
	PassControl*  m_pPassword;
};


#endif //__CommitWindow_h__

