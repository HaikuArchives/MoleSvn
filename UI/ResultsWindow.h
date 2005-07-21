///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : UI
// File        : ResultsWindow.h
// Description : defines window which will display svn command results
// Author      : cedric.bresson@artcoder.com
///////////////////////////////////////////////////////////////////////////////
#ifndef __ResultsWindow_h__
#define __ResultsWindow_h__

#include "../Config.h"

#include <string>


//#define USE_CLV

#if defined(USE_CLV)
#	if defined(B_ZETA_VERSION)
#		include <interface/ColumnListView.h>
#	else // BEOS
#		include <experimental/ColumnListView.h>
#	endif // ZETA
#endif //USE_CLV


class ResultsView : public BView
{
public:
	// -- Life-cycle ----------------------------------------------------------
	ResultsView(BRect frame);
		// Description : constructor
	
	virtual ~ResultsView();
		// Description : destructor
	
	// -- Hooks ---------------------------------------------------------------
	
	// -- Accessors -----------------------------------------------------------
	BButton* GetOkButton();
	
	// -- Services ------------------------------------------------------------
	void AddItem(const std::string& strText);
		// Description : Add an item to the list
		// Remarks     : it will split the string and convert the string into 
		//               human readable string
	
private:
	// -- Misc ----------------------------------------------------------------
	bool CheckAction(std::string& strAction);
		// Description : check if the string strAction is an action 
		//               and convert it in a human readable string (U => Updated, ...)
		// Remakrs     : If it's not an actino, it returns false and strAction
		//	             is set to empty string 

#if defined(USE_CLV)
#	if defined(B_ZETA_VERSION)
		BColumnListView* m_pListView;
#	else // BEOS
		BExperimental::BColumnListView* m_pListView;
#	endif // ZETA
	
#else	
	BListView* m_pListView;
		// Temporary, must be CLV
#endif //USE_CLV		
	
	BButton* m_pOk;
		// Description : ok button
		// Init        : By cons
		
	BButton* m_pCancel;
		// Description : cancel button
		// Init        : By cons
};

class ResultsWindow : public BWindow
{
public:
	// -- Life-cycle ----------------------------------------------------------
	ResultsWindow(const std::string& strTitle);
		// Description : constructor
	
	virtual ~ResultsWindow();
		// Description : destructor
		
	// -- Hooks ---------------------------------------------------------------
	virtual void MessageReceived(BMessage *message);
	virtual bool QuitRequested();

private:
	ResultsView* m_pView;
		// Description : embedded view
		// Init        : By cons
};


#endif //__ResultsWindow_h__

