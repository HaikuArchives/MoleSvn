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
/*
bool ResultsWindow::QuitRequested()
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));
	//be_app_messenger.SendMessage(B_QUIT_REQUESTED);
	return true;
}
*/
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
	
	// ListView
	BRect ListViewRect(g_fSpaceToWindowBorder,
	                   g_fSpaceToWindowBorder,
	                   frame.Width() - (g_fSpaceToWindowBorder + B_V_SCROLL_BAR_WIDTH),
	                   frame.Height() - (g_fSpaceToWindowBorder + g_fButtonHeight + g_fSpaceToWindowBorder + B_H_SCROLL_BAR_HEIGHT) );
	BListView* pListView = new BListView(ListViewRect, 
	                                     "ResultWindow_ListView",
	                                     B_SINGLE_SELECTION_LIST,
	                                     B_FOLLOW_LEFT_RIGHT | B_FOLLOW_TOP_BOTTOM,
	                                     B_WILL_DRAW | B_NAVIGABLE | B_FRAME_EVENTS | B_FULL_UPDATE_ON_RESIZE);
	pListView->AddItem(new BStringItem("Toto"));
	pListView->AddItem(new BStringItem("Titi"));
	AddChild(new BScrollView("ResultWindows_ScrollView", 
	                         pListView,
	                         B_FOLLOW_LEFT_RIGHT | B_FOLLOW_TOP_BOTTOM,
	                         B_FRAME_EVENTS | B_FULL_UPDATE_ON_RESIZE,
	                         true,
	                         true));

	// Ok button
	float fButtonX = frame.IntegerWidth() - (g_fButtonWidth + g_fSpaceToWindowBorder);
	float fButtonY = frame.IntegerHeight() - (g_fButtonHeight + g_fSpaceToWindowBorder);
	m_pOk = new BButton(BRect(fButtonX, fButtonY, fButtonX + g_fButtonWidth, fButtonY + g_fButtonHeight),
		    				  "ResultsWindow_Ok", 
	                          "Ok",
	                          new BMessage(MSG_Ok),
	                          B_FOLLOW_RIGHT | B_FOLLOW_BOTTOM);
	m_pOk->MakeDefault(true);
	AddChild(m_pOk);

	// Cancel button
	fButtonX -= g_fButtonWidth + g_fButtonsSpace;
	m_pCancel = new BButton(BRect(fButtonX, fButtonY, fButtonX + g_fButtonWidth, fButtonY + g_fButtonHeight),
		    				  "ResultsWindow_Cancel", 
	                          "Cancel",
	                          new BMessage(MSG_Cancel),
	                          B_FOLLOW_RIGHT | B_FOLLOW_BOTTOM);
	m_pCancel->SetEnabled(false);
	AddChild(m_pCancel);
}
	
ResultsView::~ResultsView()
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));

}

