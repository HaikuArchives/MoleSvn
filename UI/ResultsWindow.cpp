///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : UI
// File        : ResultsWindow.cpp
// Description : implements window which will display svn command results
// Author      : cedric.bresson@artcoder.com
///////////////////////////////////////////////////////////////////////////////

#include "ResultsWindow.h"
#include "../MoleSvnAddon.h"
#include "MessageCommands.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// -- ResultsWindow
///////////////////////////////////////////////////////////////////////////////
ResultsWindow::ResultsWindow(BRect frame, const string& strTitle)
:BWindow(frame, strTitle.c_str(), B_DOCUMENT_WINDOW, 0), m_pView(NULL)
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));

	m_pView = new ResultsView(BRect(0,0,frame.Width(), frame.Height()));
	m_pView->SetViewColor(216, 216, 216);
	
	AddChild(m_pView);
}
	
ResultsWindow::~ResultsWindow()
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));

}

void ResultsWindow::MessageReceived(BMessage *message)
{
	switch(message->what)
	{
		case MSG_Ok:
		{
			PostMessage(B_QUIT_REQUESTED);
			break;
		}
		default:
			BWindow::MessageReceived(message);
			break;
	}
}

bool ResultsWindow::QuitRequested()
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));
	be_app_messenger.SendMessage(B_QUIT_REQUESTED);
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// -- ResultsView
///////////////////////////////////////////////////////////////////////////////
ResultsView::ResultsView(BRect frame)
:BView(BRect(frame), 
	   "ResultsWindowView",
	   B_FOLLOW_ALL_SIDES,
	   B_FRAME_EVENTS | B_FULL_UPDATE_ON_RESIZE)
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));

	BMessage msgOk(MSG_Ok);
	BButton *pOk = new BButton(BRect(/*frame.Width() -*/ 50, /*frame.Height() -*/ 50, 50+80, 50+30),
							   "ResultsWindow_Ok", 
	                           "Ok",
	                           &msgOk);
	                          
	AddChild(pOk);
}
	
ResultsView::~ResultsView()
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));

}
	
void ResultsView::FrameResized(float width, float height)
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));
	BView::FrameResized(width, height);
}
