///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : UI
// File        : CommitWindow.cpp
// Description : implements window which will display Commit parameters
// Author      : cedric.bresson@artcoder.com
///////////////////////////////////////////////////////////////////////////////

#include "CommitWindow.h"
#include "../MoleSvnAddon.h"
#include "MessageCommands.h"
#include "ResultsWindow.h"

using namespace std;

#define Commit_OK             	'C_OK'
#define Commit_CANCEL         	'CCAN'

///////////////////////////////////////////////////////////////////////////////
// -- CommitWindow
///////////////////////////////////////////////////////////////////////////////
CommitWindow::CommitWindow(Commit* pCmd)
:BWindow(BRect(0,0,100,100), "Commit", B_DOCUMENT_WINDOW, 0),
m_pCmd(pCmd)
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));

	// In the future, we must retrieve the old position and size from preferences
	// Compute window position and size	
	BScreen screen;
	BRect screenFrame = screen.Frame();
	const float fWindowWidth = 600.0f;
	const float fWindowHeight = 250.0f;
	MoveTo((screenFrame.Width() - fWindowWidth) / 2.0f, (screenFrame.Height() - fWindowHeight) / 2.0f);
	ResizeTo(fWindowWidth, fWindowHeight);

	CreateView();
	
	Show();
	
	MoleSvnAddon::GetInstance()->AddThread(Thread());
}
	
CommitWindow::~CommitWindow()
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));

	MoleSvnAddon::GetInstance()->RemoveThread(Thread());
}

void CommitWindow::MessageReceived(BMessage *message)
{
	switch(message->what)
	{
		case MSG_CANCEL:
		{
			TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Cancel Commit parameters"));
			PostMessage(B_QUIT_REQUESTED);
			break;
		}
		case MSG_OK:
		{
			Hide();
				
			ResultsWindow* pWindow = new ResultsWindow(m_pCmd->GetName());
			m_pCmd->SetTarget(pWindow);

			string cmd = string("svn commit -m \"") + string(m_pTextView->Text()) + string("\"");
			/*int nError = */m_pCmd->ExecuteSvn(string(cmd.c_str()));
								
			PostMessage(B_QUIT_REQUESTED);
			break;
		}
		default:
			BWindow::MessageReceived(message);
			break;
	}
}

///////////////////////////////////////////////////////////////////////////////
// -- ResultsView
///////////////////////////////////////////////////////////////////////////////
void CommitWindow::CreateView()
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));

	// View
	BRect ViewFrame(0.0f , 0.0f, Frame().Width(), Frame().Height());
	BView* pView = new BView(ViewFrame,
	                         "CommitWindowView",
						     B_FOLLOW_ALL_SIDES,
	   						 B_FRAME_EVENTS | B_FULL_UPDATE_ON_RESIZE);
	pView->SetViewColor(216, 216, 216);	   						 	

	// StringView
	BRect StringViewRect(g_fSpaceToWindowBorder,
						 g_fSpaceToWindowBorder,
	                     Frame().Width() - g_fSpaceToWindowBorder,
	                     g_fSpaceToWindowBorder + g_fStringViewHeight);
	BStringView* pStringView = new BStringView(StringViewRect,
											   "CommitWindow_StringView",
											   "Message :",
											   B_FOLLOW_LEFT | B_FOLLOW_TOP,
											   B_WILL_DRAW | B_FRAME_EVENTS | B_FULL_UPDATE_ON_RESIZE);
	pView->AddChild(pStringView);

	// TextView
	BRect TextViewRect(g_fSpaceToWindowBorder,
	                   pStringView->Frame().bottom + g_fControlSpace,
	                   Frame().Width() - (g_fSpaceToWindowBorder + B_V_SCROLL_BAR_WIDTH),
	                   Frame().Height() - (g_fSpaceToWindowBorder + g_fButtonHeight + g_fSpaceToWindowBorder + B_H_SCROLL_BAR_HEIGHT) );
	BRect TextRect(0,0,TextViewRect.Width(), TextViewRect.Height());                   
	m_pTextView = new BTextView(TextViewRect, 
	                      		"CommitWindow_TextView",
	                            TextRect,
	                            B_FOLLOW_LEFT_RIGHT | B_FOLLOW_TOP_BOTTOM,
	                            B_WILL_DRAW | B_NAVIGABLE | B_FRAME_EVENTS | B_FULL_UPDATE_ON_RESIZE);
	m_pTextView->MakeFocus(true);
	m_pTextView->MakeSelectable(true);

	pView->AddChild(new BScrollView("CommitWindow_ScrollView", 
	       		                    m_pTextView,
	                         		B_FOLLOW_LEFT_RIGHT | B_FOLLOW_TOP_BOTTOM,
	                         		B_FRAME_EVENTS | B_FULL_UPDATE_ON_RESIZE,
	                         		true,
	                         		true));

	// Ok button
	float fButtonX = Frame().IntegerWidth() - (g_fButtonWidth + g_fSpaceToWindowBorder);
	float fButtonY = Frame().IntegerHeight() - (g_fButtonHeight + g_fSpaceToWindowBorder);
	BButton* pOk = new BButton(BRect(fButtonX, fButtonY, fButtonX + g_fButtonWidth, fButtonY + g_fButtonHeight),
		    				  "ResultsWindow_Ok", 
	                          "Ok",
	                          new BMessage(MSG_OK),
	                          B_FOLLOW_RIGHT | B_FOLLOW_BOTTOM);
	pView->AddChild(pOk);

	// Cancel button
	fButtonX -= g_fButtonWidth + g_fButtonsSpace;
	BButton* pCancel = new BButton(BRect(fButtonX, fButtonY, fButtonX + g_fButtonWidth, fButtonY + g_fButtonHeight),
		    				  "ResultsWindow_Cancel", 
	                          "Cancel",
	                          new BMessage(MSG_CANCEL),
	                          B_FOLLOW_RIGHT | B_FOLLOW_BOTTOM);
	pView->AddChild(pCancel);
	AddChild(pView);	
}

