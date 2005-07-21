///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : UI
// File        : CheckoutWindow.cpp
// Description : implements window which will display checkout parameters
// Author      : cedric.bresson@artcoder.com
///////////////////////////////////////////////////////////////////////////////

#include "CheckoutWindow.h"
#include "../MoleSvnAddon.h"
#include "MessageCommands.h"
#include "ResultsWindow.h"

using namespace std;

#define CHECKOUT_OK             	'C_OK'
#define CHECKOUT_CANCEL         	'CCAN'
#define CHECKOUT_OPEN_DIRECTORY 	'CODI'
#define CHECKOUT_DIRECTORY_SELECTED 'CDSE'

///////////////////////////////////////////////////////////////////////////////
// -- CheckoutWindow
///////////////////////////////////////////////////////////////////////////////
CheckoutWindow::CheckoutWindow(Checkout* pCmd)
:BWindow(BRect(0,0,100,100), "Checkout", B_DOCUMENT_WINDOW, B_NOT_RESIZABLE | B_NOT_ZOOMABLE),
m_pFilePanel(NULL), m_pCmd(pCmd)
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));

	// In the future, we must retrieve the old position and size from preferences
	// Compute window position and size	
	BScreen screen;
	BRect screenFrame = screen.Frame();
	const float fWindowWidth = 500.0f;
	const float fWindowHeight = 220.0f;
	MoveTo((screenFrame.Width() - fWindowWidth) / 2.0f, (screenFrame.Height() - fWindowHeight) / 2.0f);
	ResizeTo(fWindowWidth, fWindowHeight);

	CreateView();
	
	Show();
	
	MoleSvnAddon::GetInstance()->AddThread(Thread());
}
	
CheckoutWindow::~CheckoutWindow()
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));

	MoleSvnAddon::GetInstance()->RemoveThread(Thread());
	
	if(m_pFilePanel)
	{
		delete m_pFilePanel;
	}
}

void CheckoutWindow::MessageReceived(BMessage *message)
{
	switch(message->what)
	{
		case CHECKOUT_OPEN_DIRECTORY:
		{
			TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Open checkout directory file panel"));
		
			if(!m_pFilePanel)
			{
				// Create file panel
				m_pFilePanel = new BFilePanel(B_OPEN_PANEL,
			  								  new BMessenger(NULL, this),
								 			  MoleSvnAddon::GetInstance()->GetCurrentDirectory(),
								 			  B_DIRECTORY_NODE,
								 			  false,
								 			  new BMessage(CHECKOUT_DIRECTORY_SELECTED),
								 			  NULL,
								 			  true);
			}
			m_pFilePanel->Show();
			
			break;
		}
		case CHECKOUT_DIRECTORY_SELECTED:
		{
			TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Hide checkout directory file panel"));
			m_pFilePanel->Hide();
			entry_ref ref;
			message->FindRef("refs", &ref);
			BPath path(&ref);
			m_pCheckoutDirectory->SetText(path.Path());
			break;
		}
		case MSG_CANCEL:
		{
			TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Cancel checkout parameters"));
			PostMessage(B_QUIT_REQUESTED);
			break;
		}
		case MSG_OK:
		{
			TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Check checkout parameters"));
			if(CheckParameters())
			{
				Hide();
				
				TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Checkout parameters OK !"));
/*				
				BMessenger messenger(m_pTarget);
				BMessage* msg = new BMessage(MSG_OK);
				msg->AddString("url", m_pUrlRepository->Text());
				msg->AddString("dir", m_pCheckoutDirectory->Text());
				messenger.SendMessage(msg);
*/
				ResultsWindow* pWindow = new ResultsWindow(m_pCmd->GetName());
				m_pCmd->SetTarget(pWindow);
				
				
				// Build the svn command line
				string strCmd("svn checkout ");
				
				// Check if we have entered a username/password
				string strUsername(m_pLogin->Text());
				string strPassword(m_pPassword->actualText());
				if(strUsername.size())
				{
					strCmd += string("--username \"") + strUsername + string("\" ");
					
					if(strPassword.size())
					{
						strCmd += string("--password \"") + strPassword + string("\" ");
					}	
				}
				
				// Add the URL repository and the path
				strCmd += string("\"") + m_pUrlRepository->Text() + string("\" \"") + m_pCheckoutDirectory->Text() + string("\"");
				
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
void CheckoutWindow::CreateView()
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));

	// View
	BRect ViewFrame(0.0f , 0.0f, Frame().Width(), Frame().Height());
	BView* pView = new BView(ViewFrame,
	                         "CheckoutWindowView",
						     B_FOLLOW_ALL_SIDES,
	   						 B_FRAME_EVENTS | B_FULL_UPDATE_ON_RESIZE);
	pView->SetViewColor(216, 216, 216);	   						 	

	// Repository bbox
	float fRepositoryBBoxWidth = ViewFrame.Width() - (2.0f * g_fSpaceToWindowBorder);
	BRect RepositoryBBoxFrame(g_fSpaceToWindowBorder,
		                      g_fSpaceToWindowBorder,
	       		              ViewFrame.Width() - (g_fSpaceToWindowBorder),
	              		      ViewFrame.Height() - (g_fSpaceToWindowBorder) );
	BBox* pRepositoryBBox = new BBox(RepositoryBBoxFrame,
									 "RepositoryBBox");
	pRepositoryBBox->SetLabel("Repository");
	pView->AddChild(pRepositoryBBox);
	
	// Url repository textcontrol
	BRect UrlRepoFrame(g_fControlSpace, g_fControlSpace, 
	                   fRepositoryBBoxWidth - g_fControlSpace, 0);		// We don't care about the height => 0
	m_pUrlRepository = new BTextControl(UrlRepoFrame,
									    "UrlRepositoryTextControl",
									    "URL of repository",
									    //"http://svn.collab.net/repos/tortoisesvn/trunk",
									    "http://tortoisesvn.tigris.org/svn/tortoisesvn/trunk",
									    //NULL,
									    NULL);
	m_pUrlRepository->SetDivider(UrlRepoFrame.Width() * 0.30f);
	pRepositoryBBox->AddChild(m_pUrlRepository);

	// Checkout directory textcontrol
	const float fSpace = 5.0f;
	const float fButtonWidth = 20.0f;
	BRect CheckoutDirFrame(g_fControlSpace, 
	                       g_fControlSpace + m_pUrlRepository->Frame().Height() + g_fControlSpace, 
	                       fRepositoryBBoxWidth - g_fControlSpace - (fSpace + fButtonWidth), 
	                       0);
	BPath path(MoleSvnAddon::GetInstance()->GetCurrentDirectory()); 
	m_pCheckoutDirectory = new BTextControl(CheckoutDirFrame,
						    		        "CheckoutDirTextControl",
											"Checkout directory",
											path.Path(),
											NULL);
	m_pCheckoutDirectory->SetDivider(CheckoutDirFrame.Width() * 0.32f);
	pRepositoryBBox->AddChild(m_pCheckoutDirectory);
	
	// Search directory button
	BRect DirectoryButtonFrame(CheckoutDirFrame.RightTop().x + fSpace,
	                           CheckoutDirFrame.RightTop().y - 3.0f,
	                           CheckoutDirFrame.RightTop().x + fSpace + fButtonWidth,
	                           m_pCheckoutDirectory->Frame().Height());
	BButton* pDirectory = new BButton(DirectoryButtonFrame,
									  "DirectoryButton",
									  "...",
									  new BMessage(CHECKOUT_OPEN_DIRECTORY));
	pRepositoryBBox->AddChild(pDirectory);
	
	// Resize repo bbox
	pRepositoryBBox->ResizeTo(RepositoryBBoxFrame.Width(),
	                          m_pUrlRepository->Frame().Height() + m_pCheckoutDirectory->Frame().Height() + 3.0f * g_fControlSpace);


	// Login
	BRect LoginFrame(pRepositoryBBox->Frame().left, 
	                 pRepositoryBBox->Frame().bottom + g_fControlSpace, 
	                 (pRepositoryBBox->Frame().right - g_fControlSpace) / 2.0f, 
	                 pRepositoryBBox->Frame().bottom + g_fControlSpace + 20);
	m_pLogin = new BTextControl(LoginFrame,
								"LoginTextControl",
								"Login :",
								"",
								NULL,
								B_FOLLOW_LEFT_RIGHT | B_FOLLOW_BOTTOM,
	                            B_WILL_DRAW | B_NAVIGABLE | B_FRAME_EVENTS | B_FULL_UPDATE_ON_RESIZE);
	m_pLogin->SetDivider(LoginFrame.Width() * 0.25f);
	pView->AddChild(m_pLogin);
					
	
	// Password						
	BRect PasswordFrame((pRepositoryBBox->Frame().right + g_fControlSpace) / 2.0f,
  	                    LoginFrame.top, 
 	                    Frame().Width() - g_fSpaceToWindowBorder,
	                    LoginFrame.bottom);
	m_pPassword = new PassControl(PasswordFrame,
								  "PasswordTextView",
								  "Password :",
								  "",
							  	  NULL,
								  B_FOLLOW_RIGHT | B_FOLLOW_BOTTOM,
	                              B_WILL_DRAW | B_NAVIGABLE | B_FRAME_EVENTS | B_FULL_UPDATE_ON_RESIZE);
							  	  
	m_pPassword->SetDivider(PasswordFrame.Width() * 0.25f);
	pView->AddChild(m_pPassword);

	// Ok button
	float fButtonX = Frame().IntegerWidth() - (g_fButtonWidth + g_fSpaceToWindowBorder);
	float fButtonY = Frame().IntegerHeight() - (g_fButtonHeight + g_fSpaceToWindowBorder);
	BButton* pOk = new BButton(BRect(fButtonX, fButtonY, fButtonX + g_fButtonWidth, fButtonY + g_fButtonHeight),
		    				  "CheckoutWindow_Ok", 
	                          "Ok",
	                          new BMessage(MSG_OK),
	                          B_FOLLOW_RIGHT | B_FOLLOW_BOTTOM);
	pOk->MakeDefault(true);
	pView->AddChild(pOk);

	// Cancel button
	fButtonX -= g_fButtonWidth + g_fButtonsSpace;
	BButton* pCancel = new BButton(BRect(fButtonX, fButtonY, fButtonX + g_fButtonWidth, fButtonY + g_fButtonHeight),
		    		            	     "CheckoutWindow_Cancel", 
	                          			 "Cancel",
	                          			  new BMessage(MSG_CANCEL),
	                          			  B_FOLLOW_RIGHT | B_FOLLOW_BOTTOM);
	pView->AddChild(pCancel);

	AddChild(pView);
}

bool CheckoutWindow::CheckParameters()
{
	string strUrl(m_pUrlRepository->Text());
	string strDir(m_pCheckoutDirectory->Text());
	
	bool bRes = true;
	if((strUrl.size() == 0) && (strDir.size() == 0))
	{
		ShowErrorWindow("URL repository and checkout directory are empty");
		bRes = false;
	}
	else if(strUrl.size() == 0)
	{
		ShowErrorWindow("URL repository is empty");
		bRes = false;
	}
	else if(strDir.size() == 0)
	{
		ShowErrorWindow("checkout directory is empty");
		bRes = false;
	}
	
	return bRes;
}

