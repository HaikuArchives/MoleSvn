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

class ResultsView : public BView
{
public:
	// -- Life-cycle ----------------------------------------------------------
	ResultsView(BRect frame);
		// Description : constructor
	
	virtual ~ResultsView();
		// Description : destructor
	
	// -- Hooks ---------------------------------------------------------------
	
	// -- Services ------------------------------------------------------------
	void AddItem(const std::string& strText);
private:
	BListView* m_pListView;
	
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
//	virtual bool QuitRequested();

private:
	ResultsView* m_pView;
		// Description : embedded view
		// Init        : By cons
};


#endif //__ResultsWindow_h__

