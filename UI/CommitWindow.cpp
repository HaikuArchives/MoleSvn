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

//#define COMMIT_OK             	'C_OK'
//#define COMMIT_CANCEL         	'CCAN'
#define COMMIT_ADDENTRY         'CENT'

///////////////////////////////////////////////////////////////////////////////
// -- CommitWindow
///////////////////////////////////////////////////////////////////////////////
int32 LoadEntriesThreadFunc(void* data)
{
	return ((CommitWindow *)data)->LoadEntries();
}

CommitWindow::CommitWindow(Commit* pCmd)
:BWindow(BRect(0,0,100,100), "Commit", B_DOCUMENT_WINDOW, 0),
m_pCmd(pCmd)
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));

	// In the future, we must retrieve the old position and size from preferences
	// Compute window position and size	
	BScreen screen;
	BRect screenFrame = screen.Frame();
	const float fWindowWidth = 700.0f;
	const float fWindowHeight = 600.0f;
	MoveTo((screenFrame.Width() - fWindowWidth) / 2.0f, (screenFrame.Height() - fWindowHeight) / 2.0f);
	ResizeTo(fWindowWidth, fWindowHeight);

	CreateView();
	
	Show();
	
	MoleSvnAddon::GetInstance()->AddThread(Thread());
	
	// Create a new thread
	thread_id id = spawn_thread(LoadEntriesThreadFunc, "LoadEntries", B_NORMAL_PRIORITY, this);
	resume_thread(id);
	MoleSvnAddon::GetInstance()->AddThread(id);
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
		case COMMIT_ADDENTRY:
		{
			TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Add entry"));
			AddItem("toto");
			break;
		}
		
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
			
			string cmd = string("svn commit --message \"") + string(m_pTextView->Text()) + string("\" --force-log");
			
			// Check login and password
			string strLogin(m_pLogin->Text());
			string strPassword(m_pPassword->Text());
			if(strLogin.size())
			{
				cmd += string(" --username \"") + strLogin + string("\""); 
				
				if(strPassword.size())
				{
					cmd += string(" --password \"") + strPassword + string("\""); 
				}
			}
			
			cmd +=  string(" ") + MoleSvnAddon::GetInstance()->GetEntryNameList();
			
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

	// Commit bbox
	float fCommitBBoxWidth = ViewFrame.Width() - (2.0f * g_fSpaceToWindowBorder);
	BRect CommitBBoxFrame(g_fSpaceToWindowBorder,
		                  g_fSpaceToWindowBorder,
	       		          ViewFrame.Width() - (g_fSpaceToWindowBorder),
	              		  300 );
	BBox* pCommitBBox = new BBox(CommitBBoxFrame,
								 "CommitBBox",
								 B_FOLLOW_LEFT_RIGHT | B_FOLLOW_TOP_BOTTOM,
								 B_WILL_DRAW | B_FULL_UPDATE_ON_RESIZE);
	pCommitBBox->SetLabel("Files to commit");
	pView->AddChild(pCommitBBox);

	// ColumnListView
	BRect ColumnListViewRect(g_fControlSpace, g_fControlSpace,
					         fCommitBBoxWidth - g_fControlSpace, CommitBBoxFrame.Height() - g_fControlSpace);
	m_pFilesToCommitView = new BColumnListView(ColumnListViewRect, 
	                      	      	     "CommitWindow_CLV",
	                                     B_FOLLOW_LEFT_RIGHT | B_FOLLOW_TOP_BOTTOM,
	                                     B_WILL_DRAW | B_NAVIGABLE | B_FRAME_EVENTS | B_FULL_UPDATE_ON_RESIZE,
	                                     B_FANCY_BORDER);

	BColumn* pColumn1 = new BStringColumn("File", 50.0f, 10.0f, 1000.0f, 0);
	BColumn* pColumn2 = new BStringColumn("Status", 300.0f, 10.0f, 1000.0f, 0);
	m_pFilesToCommitView->AddColumn(pColumn1,0);
	m_pFilesToCommitView->AddColumn(pColumn2,1);
	m_pFilesToCommitView->SetSortingEnabled(false);
	pCommitBBox->AddChild(m_pFilesToCommitView);

	// Log message bbox
	float fLogMessageBBoxHeight = 120;
	BRect LogMessageBBoxFrame(CommitBBoxFrame.left,
		                      CommitBBoxFrame.bottom + g_fSpaceToWindowBorder,
	       		              CommitBBoxFrame.right,
	              		      CommitBBoxFrame.bottom + g_fSpaceToWindowBorder + fLogMessageBBoxHeight );
	BBox* pLogMessageBBox = new BBox(LogMessageBBoxFrame,
								     "LogMessageBBox",
								     B_FOLLOW_LEFT_RIGHT | B_FOLLOW_BOTTOM,
								     B_WILL_DRAW | B_FULL_UPDATE_ON_RESIZE);
	pLogMessageBBox->SetLabel("Log message");
	pView->AddChild(pLogMessageBBox);

	// TextView
	BRect TextViewRect(g_fSpaceToWindowBorder,
	                   g_fSpaceToWindowBorder,
	                   LogMessageBBoxFrame.Width() - (g_fSpaceToWindowBorder + B_V_SCROLL_BAR_WIDTH),
	                   LogMessageBBoxFrame.Height() - (g_fSpaceToWindowBorder + B_H_SCROLL_BAR_HEIGHT) );
	BRect TextRect(0,0,TextViewRect.Width(), TextViewRect.Height());
	m_pTextView = new BTextView(TextViewRect, 
	                      		"CommitWindow_TextView",
	                            TextRect,
	                            B_FOLLOW_LEFT_RIGHT | B_FOLLOW_TOP_BOTTOM,
	                            B_WILL_DRAW | B_NAVIGABLE | B_FRAME_EVENTS | B_FULL_UPDATE_ON_RESIZE);
	m_pTextView->MakeSelectable(true);
	m_pTextView->MakeFocus(true);

	pLogMessageBBox->AddChild(new BScrollView("CommitWindow_ScrollView", 
	       		                              m_pTextView,
	                                 		  B_FOLLOW_LEFT_RIGHT | B_FOLLOW_TOP_BOTTOM,
	                            		      B_FRAME_EVENTS | B_FULL_UPDATE_ON_RESIZE,
	                            		      true,
	                         	    	      true));
	// Authentication bbox
	float fAuthenticationBBoxHeight = 45;
	BRect AuthenticationBBoxFrame(LogMessageBBoxFrame.left,
		                      	  LogMessageBBoxFrame.bottom + g_fSpaceToWindowBorder,
	       		              	  LogMessageBBoxFrame.right,
	              		      	  LogMessageBBoxFrame.bottom + g_fSpaceToWindowBorder + fAuthenticationBBoxHeight );
	BBox* pAuthenticationBBox = new BBox(AuthenticationBBoxFrame,
								     	 "AuthenticationBBox",
								     	 B_FOLLOW_LEFT_RIGHT | B_FOLLOW_BOTTOM,
								     	 B_WILL_DRAW | B_FULL_UPDATE_ON_RESIZE);
	pAuthenticationBBox->SetLabel("Authentication");
	pView->AddChild(pAuthenticationBBox);

	// Login
	BRect LoginFrame(g_fControlSpace, 
	                 g_fControlSpace, 
	                 g_fControlSpace + (AuthenticationBBoxFrame.Width() - g_fControlSpace * 3.0f) / 2.0f, 
	                 g_fControlSpace + 20);
	                 
	m_pLogin = new BTextControl(LoginFrame,
								"LoginTextControl",
								"Login :",
								"",
								NULL,
								B_FOLLOW_LEFT_RIGHT | B_FOLLOW_BOTTOM,
	                            B_WILL_DRAW | B_NAVIGABLE | B_FRAME_EVENTS | B_FULL_UPDATE_ON_RESIZE);
	m_pLogin->SetDivider(LoginFrame.Width() * 0.25f);
	pAuthenticationBBox->AddChild(m_pLogin);
	
	// Password						
	BRect PasswordFrame(LoginFrame.right + g_fControlSpace,
  	                    LoginFrame.top, 
 	                    AuthenticationBBoxFrame.Width() - g_fControlSpace,
	                    LoginFrame.bottom);
	m_pPassword = new BTextControl(PasswordFrame,
								  "PasswordTextView",
								  "Password :",
								  "",
							  	  NULL,
								  B_FOLLOW_RIGHT | B_FOLLOW_BOTTOM,
	                              B_WILL_DRAW | B_NAVIGABLE | B_FRAME_EVENTS | B_FULL_UPDATE_ON_RESIZE);
							  	  
	m_pPassword->SetDivider(PasswordFrame.Width() * 0.25f);
	m_pPassword->TextView()->HideTyping(true);
	pAuthenticationBBox->AddChild(m_pPassword);

	// Ok button
	float fButtonX = Frame().Width() - (g_fButtonWidth + g_fSpaceToWindowBorder);
	float fButtonY = Frame().Height() - (g_fButtonHeight + g_fSpaceToWindowBorder);
	BButton* pOk = new BButton(BRect(fButtonX, fButtonY, fButtonX + g_fButtonWidth, fButtonY + g_fButtonHeight),
		    				  "ResultsWindow_Ok", 
	                          "Ok",
	                          new BMessage(MSG_OK),
	                          B_FOLLOW_RIGHT | B_FOLLOW_BOTTOM);
	//pOk->MakeDefault(true);	                          
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

void CommitWindow::AddItem(const string& strText)
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));
	
	// ColumnListView
	BRow* pRow = new BRow();
	pRow->SetField(new BStringField(strText.c_str()), 0);
	pRow->SetField(new BStringField("status"), 1);
	m_pFilesToCommitView->AddRow(pRow);
}

int32 CommitWindow::LoadEntries()
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));
/*
	BMessage msg(COMMIT_ADDENTRY);
	
	// For each selected entry for which infos have already been loaded
	const list<entry_ref> lstSelectedEntry& = MoleSvnAddon::GetInstance()->GetSelectedEntryList();
	list<entry_ref>::const_iterator ite = lstSelectedEntry.begin();
	while(ite != lstSelectedEntry.end())
	{
		msg	
		++ite;
	}
	*/
/*
	// For each entry selected, check if it's a directory
	const list<entry_ref> lstSelectedEntry& = MoleSvnAddon::GetInstance()->GetSelectedEntryList();
	const std::hash_map<entry_ref, SvnEntry*, hashEntryRef, eqEntryRef>& GetSvnEntries();
	
	list<entry_ref> lstEntry = lstSelectedEntry;
	
	list<entry_ref>::const_iterator ite = lstSelectedEntry.begin();
	while(ite != lstSelectedEntry.end())
	{
		// Is it a directory ?
		if()
	}
*/
	BMessage msg(COMMIT_ADDENTRY);

	for(int i=0; i<10; ++i)
	{
		PostMessage(&msg);
	}

	return 0;
}
