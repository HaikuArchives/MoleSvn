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
#include <queue>

using namespace std;

//#define COMMIT_OK             	'C_OK'
//#define COMMIT_CANCEL         	'CCAN'
#define COMMIT_ADDENTRY         'CENT'

#include "BCLV/EntryTypes.h"
#include "BCLV/ColoredStringTypes.h"

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
	const float fWindowHeight = 550.0f;
	MoveTo((screenFrame.Width() - fWindowWidth) / 2.0f, (screenFrame.Height() - fWindowHeight) / 2.0f);
	ResizeTo(fWindowWidth, fWindowHeight);

	CreateView();
	
	Show();
	
	// For all entries for which infos has already been loaded
	const std::hash_map<entry_ref, SvnEntry*, MoleSvnAddon::hashEntryRef, MoleSvnAddon::eqEntryRef>& mapSelectedEntry = MoleSvnAddon::GetInstance()->GetSvnEntries();
	std::hash_map<entry_ref, SvnEntry*, MoleSvnAddon::hashEntryRef, MoleSvnAddon::eqEntryRef>::const_iterator ite = mapSelectedEntry.begin();
	while(ite != mapSelectedEntry.end())
	{
		BMessage msg(COMMIT_ADDENTRY);
		msg.AddPointer("ref", (*ite).second);
		PostMessage(&msg);
		++ite;
	}
	
	MoleSvnAddon::GetInstance()->AddThread(Thread());
	
	// Create a new thread
	//thread_id id = spawn_thread(LoadEntriesThreadFunc, "LoadEntries", B_NORMAL_PRIORITY, this);
	//resume_thread(id);
	LoadEntries();
	//MoleSvnAddon::GetInstance()->AddThread(id);
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
			SvnEntry* pEntry;
			message->FindPointer("ref", (void**)(&pEntry));
			AddItem(pEntry);
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
	float fCommitBBoxWidth = ViewFrame.Width() - (2.0f * g_fSpaceToWindowBorder);
	BRect ColumnListViewRect(g_fControlSpace, g_fControlSpace,
					         fCommitBBoxWidth - g_fControlSpace, CommitBBoxFrame.Height() - g_fControlSpace);
	m_pFilesToCommitView = new BColumnListView(ColumnListViewRect, 
	                      	      	     "CommitWindow_CLV",
	                                     B_FOLLOW_LEFT_RIGHT | B_FOLLOW_TOP_BOTTOM,
	                                     B_WILL_DRAW | B_NAVIGABLE | B_FRAME_EVENTS | B_FULL_UPDATE_ON_RESIZE,
	                                     B_FANCY_BORDER);

	BColumn* pColumn1 = new BEntryColumn("File", 200.0f, 10.0f, 1000.0f, 0);
	BColumn* pColumn2 = new BColoredStringColumn("Status", 100.0f, 10.0f, 1000.0f, 0);
	BColumn* pColumn3 = new BColoredStringColumn("Kind", 150.0f, 50.0f, 1000.0f, 0);
	m_pFilesToCommitView->AddColumn(pColumn1,0);
	m_pFilesToCommitView->AddColumn(pColumn2,1);
	m_pFilesToCommitView->AddColumn(pColumn3,2);
	m_pFilesToCommitView->SetColumnVisible(pColumn3, false);
	m_pFilesToCommitView->SetSortingEnabled(true);
	m_pFilesToCommitView->SetSortColumn(pColumn1, false, true);
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

void CommitWindow::AddItem(const SvnEntry* pEntry)
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));
	
	// ColumnListView
	BRow* pRow = new BRow(16+2);	// Height = 16 + 2 for space
	rgb_color color(pEntry->GetStatusColor());

	// Name of the file
	pRow->SetField(new BEntryField(*pEntry, false), 0);
	
	// Status of the file
	pRow->SetField(new BColoredStringField(pEntry->GetStatusString().c_str(), color), 1);
	
	// Kind of the file
	char tmp[B_FILE_NAME_LENGTH];
	tmp[0] = 0;
	BNode node(pEntry->GetPath().c_str());
	if(node.InitCheck() == B_OK)
	{
		BNodeInfo infos(&node);
		infos.GetType(tmp);
	}
	pRow->SetField(new BColoredStringField(tmp, color), 2);
	m_pFilesToCommitView->AddRow(pRow);
}


int32 CommitWindow::LoadEntries()
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));

	hash_map<entry_ref, SvnEntry*, MoleSvnAddon::hashEntryRef, MoleSvnAddon::eqEntryRef>& CurDirEntriesMap = MoleSvnAddon::GetInstance()->GetSvnEntries();
	
	hash_map<entry_ref, SvnEntry*, MoleSvnAddon::hashEntryRef, MoleSvnAddon::eqEntryRef>::const_iterator ite = CurDirEntriesMap.begin();
	queue<BPath> subdir;
	
	// Get the subdirectories that are actually in the hasmap
	while(ite != CurDirEntriesMap.end())
	{
		if( !(*ite).second->IsFile() )
		{
			subdir.push(BPath((*ite).second->GetPath().c_str()));
		}
		++ite;
	}
	
	while(!subdir.empty())
	{
		BPath path(subdir.front());
		BDirectory curdir(path.Path());
		
		if(MoleSvnAddon::GetInstance()->HasRepository(curdir))
		{
			// Load repository of the current directory
			hash_map<entry_ref, SvnEntry*, MoleSvnAddon::hashEntryRef, MoleSvnAddon::eqEntryRef> hashTmp;
			MoleSvnAddon::GetInstance()->LoadEntriesFile(curdir, hashTmp);
		
			list<entry_ref> lstTmpEntry;
			list<BDirectory> lstTmpSubDir;
			MoleSvnAddon::GetInstance()->GetEntriesList(curdir, lstTmpEntry, lstTmpSubDir);

			// We apply a filter with the content of the directory
			MoleSvnAddon::GetInstance()->UpdateEntriesFromList(hashTmp, lstTmpEntry);
			
			// Send a message to the interface
			hash_map<entry_ref, SvnEntry*, MoleSvnAddon::hashEntryRef, MoleSvnAddon::eqEntryRef>::const_iterator iteHashTmp = hashTmp.begin();
			while(iteHashTmp != hashTmp.end())
			{
				BMessage msg(COMMIT_ADDENTRY);
				msg.AddPointer("ref", (*iteHashTmp).second);
				PostMessage(&msg);
				++iteHashTmp;
			}
			
			// Add the temporary hasmap to the global hasmap
			CurDirEntriesMap.insert(hashTmp.begin(), hashTmp.end()); 

			// Add new subdirs to the queue
			list<BDirectory>::const_iterator iteDir = lstTmpSubDir.begin();
			while(iteDir != lstTmpSubDir.end())
			{
				BEntry entry;
				(*iteDir).GetEntry(&entry);
				BPath curPath;
				entry.GetPath(&curPath);
				subdir.push(curPath);
				++iteDir;
			}
		}
		
		subdir.pop();
	}

	return 0;
}
