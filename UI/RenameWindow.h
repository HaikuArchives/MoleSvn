///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : UI
// File        : RenameWindow.h
// Description : defines window which will display Rename parameters, like
//               URL repository, revision
// Author      : cedric.bresson@artcoder.com
///////////////////////////////////////////////////////////////////////////////
#ifndef __RenameWindow_h__
#define __RenameWindow_h__

#include "../Config.h"
#include "../Svn/SvnCommands.h"


class RenameWindow : public BWindow
{
public:
	// -- Life-cycle ----------------------------------------------------------
	RenameWindow(Rename* pCmd);
		// Description : constructor
	
	virtual ~RenameWindow();
		// Description : destructor
		
	// -- Hooks ---------------------------------------------------------------
	virtual void MessageReceived(BMessage *message);

private:
	void CreateView();
		// Description : build UI
		
	bool CheckParameters();
		// Description : returns true if the Rename parameters entered by the
		//               user are valid.
		
	string m_strOldName;
		// Description : name to rename

	BTextControl* m_pRename;
	Rename* 	  m_pCmd;
};


#endif //__RenameWindow_h__

