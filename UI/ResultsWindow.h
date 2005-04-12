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
	
	~ResultsView();
		// Description : destructor
	
	// -- Hooks ---------------------------------------------------------------
	void FrameResized(float width, float height);
	
private:

};

class ResultsWindow : public BWindow
{
public:
	// -- Life-cycle ----------------------------------------------------------
	ResultsWindow(BRect frame, const std::string& strTitle);
		// Description : constructor
	
	~ResultsWindow();
		// Description : destructor
		
	// -- Hooks ---------------------------------------------------------------
	void MessageReceived(BMessage *message);
	bool QuitRequested();

private:
	ResultsView* m_pView;
		// Description : embedded view
		// Init        : By cons
};


#endif //__ResultsWindow_h__

