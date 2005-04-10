///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : UI
// File        : ResultsWindow.h
// Description : defines window which will display svn command results
// Author      : cedric.bresson@artcoder.com
///////////////////////////////////////////////////////////////////////////////
#ifndef __ResultsWindow_h__
#define __ResultsWindow_h__

#include <InterfaceKit.h>

class ResultsWindow : public BWindow
{
public:
	// -- Life-cycle ----------------------------------------------------------
	ResultsWindow();
	
	~ResultsWindow();
		
private:
};

class ResultsView : public BView
{
public:
	// -- Life-cycle ----------------------------------------------------------
	ResultsView();
	
	~ResultsView();

private:
};

#endif //__ResultsWindow_h__

