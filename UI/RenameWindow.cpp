///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : UI
// File        : RenameWindow.cpp
// Description : implements window which will display Rename parameters
// Author      : cedric.bresson@artcoder.com
///////////////////////////////////////////////////////////////////////////////

#include "RenameWindow.h"
#include "../MoleSvnAddon.h"
#include "MessageCommands.h"
#include "ResultsWindow.h"

using namespace std;

#define RENAME_OK             		'R_OK'
#define RENAME_CANCEL         		'RCAN'

///////////////////////////////////////////////////////////////////////////////
// -- RenameWindow
///////////////////////////////////////////////////////////////////////////////
RenameWindow::RenameWindow(Rename* pCmd)
:BWindow(BRect(0,0,100,100), "Rename", B_DOCUMENT_WINDOW, B_NOT_RESIZABLE | B_NOT_ZOOMABLE),
 m_pCmd(pCmd)
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));

	// In the future, we must retrieve the old position and size from preferences
	// Compute window position and size	
	BScreen screen;
	BRect screenFrame = screen.Frame();
	const float fWindowWidth = 300.0f;
	const float fWindowHeight = 100.0f;
	MoveTo((screenFrame.Width() - fWindowWidth) / 2.0f, (screenFrame.Height() - fWindowHeight) / 2.0f);
	ResizeTo(fWindowWidth, fWindowHeight);

	CreateView();
	
	Show();
	
	MoleSvnAddon::GetInstance()->AddThread(Thread());
}
	
RenameWindow::~RenameWindow()
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));

	MoleSvnAddon::GetInstance()->RemoveThread(Thread());
}

void RenameWindow::MessageReceived(BMessage *message)
{
	switch(message->what)
	{
		case MSG_CANCEL:
		{
			TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Cancel Rename parameters"));
			PostMessage(B_QUIT_REQUESTED);
			break;
		}
		case MSG_OK:
		{
			TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Check Rename parameters"));
			if(CheckParameters())
			{
				Hide();
				
				TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Rename parameters OK !"));
/*				
				BMessenger messenger(m_pTarget);
				BMessage* msg = new BMessage(MSG_OK);
				msg->AddString("url", m_pUrlRepository->Text());
				msg->AddString("dir", m_pRenameDirectory->Text());
				messenger.SendMessage(msg);
*/
				ResultsWindow* pWindow = new ResultsWindow(m_pCmd->GetName());
				m_pCmd->SetTarget(pWindow);
				
				
				// Build the svn command line
				string strCmd("svn rename ");
				
				// Add the old name
				strCmd += MoleSvnAddon::GetInstance()->GetEntryNameList();
				
				// And the new name
				strCmd += string(" \"") + string(m_pRename->Text()) + string("\"");
				
				// Execute the command
				/*int nError = */m_pCmd->ExecuteSvn(strCmd);
								
				PostMessage(B_QUIT_REQUESTED);
			}
			
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
void RenameWindow::CreateView()
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));

	// View
	BRect ViewFrame(0.0f , 0.0f, Frame().Width(), Frame().Height());
	BView* pView = new BView(ViewFrame,
	                         "RenameWindowView",
						     B_FOLLOW_ALL_SIDES,
	   						 B_FRAME_EVENTS | B_FULL_UPDATE_ON_RESIZE);
	pView->SetViewColor(216, 216, 216);	   						 	
	
	// Rename textcontrol
	BRect renameFrame(g_fSpaceToWindowBorder,
					  g_fSpaceToWindowBorder,
		              ViewFrame.Width() - (g_fSpaceToWindowBorder),
          		      ViewFrame.Height() - (g_fSpaceToWindowBorder) );

	// We must retrieve only one name here !!
	// If the user has selected more than one file, the "rename" command is not available
	m_strOldName = MoleSvnAddon::GetInstance()->GetEntryNameList();
	// We delete the " and the beginning and at the end of the name
	m_strOldName.erase(m_strOldName.begin());
	m_strOldName.erase(m_strOldName.size() - 2, m_strOldName.size() - 1);
	m_pRename = new BTextControl(renameFrame,
								"RenameTextControl",
								"New name ",
							    m_strOldName.c_str(),
							    NULL);
	m_pRename->SetDivider(renameFrame.Width() * 0.25f);
	pView->AddChild(m_pRename);

	// Ok button
	float fButtonX = Frame().IntegerWidth() - (g_fButtonWidth + g_fSpaceToWindowBorder);
	float fButtonY = Frame().IntegerHeight() - (g_fButtonHeight + g_fSpaceToWindowBorder);
	BButton* pOk = new BButton(BRect(fButtonX, fButtonY, fButtonX + g_fButtonWidth, fButtonY + g_fButtonHeight),
		    				  "RenameWindow_Ok", 
	                          "Ok",
	                          new BMessage(MSG_OK),
	                          B_FOLLOW_RIGHT | B_FOLLOW_BOTTOM);
	pOk->MakeDefault(true);
	pView->AddChild(pOk);

	// Cancel button
	fButtonX -= g_fButtonWidth + g_fButtonsSpace;
	BButton* pCancel = new BButton(BRect(fButtonX, fButtonY, fButtonX + g_fButtonWidth, fButtonY + g_fButtonHeight),
		    		            	     "RenameWindow_Cancel", 
	                          			 "Cancel",
	                          			  new BMessage(MSG_CANCEL),
	                          			  B_FOLLOW_RIGHT | B_FOLLOW_BOTTOM);
	pView->AddChild(pCancel);

	AddChild(pView);
}

bool RenameWindow::CheckParameters()
{
	string strRename(m_pRename->Text());
	
	bool bRes = true;
	if(!strRename.size())
	{
		ShowErrorWindow("you must specify a name");
		bRes = false;
	}
	else if(strRename == m_strOldName)
	{
		ShowErrorWindow("This is the same name !!");
		bRes = false;
	}
	
	return bRes;
}

