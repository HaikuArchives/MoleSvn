///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : UI
// File        : CheckoutWindow.cpp
// Description : implements window which will display checkout parameters
// Author      : cedric.bresson@artcoder.com
///////////////////////////////////////////////////////////////////////////////

#include "CheckoutWindow.h"

#include <stdlib.h>	// atoi

#include "../MoleSvnAddon.h"
#include "MessageCommands.h"
#include "ResultsWindow.h"
//#define BOOST_NO_STRINGSTREAM
//#include <boost/lexical_cast.hpp>

using namespace std;
//using namespace boost;

#define CHECKOUT_OK             	'C_OK'
#define CHECKOUT_CANCEL         	'CCAN'
#define CHECKOUT_OPEN_DIRECTORY 	'CODI'
#define CHECKOUT_DIRECTORY_SELECTED 'CDSE'
#define CHECKOUT_HEAD_SELECTED      'CHEA'
#define CHECKOUT_REVISION_SELECTED  'CREV'

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
	const float fWindowHeight = 290.0f;
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
		case CHECKOUT_HEAD_SELECTED:
		{
			m_pRevision->SetEnabled(false);
			break;
		}
		case CHECKOUT_REVISION_SELECTED:
		{
			m_pRevision->SetEnabled(true);
			break;
		}
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
				// Hide the current window
				Hide();
				
				TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Checkout parameters OK !"));

				ResultsWindow* pWindow = new ResultsWindow(m_pCmd->GetName());
				m_pCmd->SetTarget(pWindow);
				
				
				// Build the svn command line
				string strCmd("svn checkout ");
				
				// Check if we have entered a username/password
				string strUsername(m_pLogin->Text());
				string strPassword(m_pPassword->Text());
				if(strUsername.size())
				{
					strCmd += string("--username \"") + strUsername + string("\" ");
					
					if(strPassword.size())
					{
						strCmd += string("--password \"") + strPassword + string("\" ");
					}	
				}
				
				// Check if we have selected a revision number, otherwise it takes the head revision
				if(m_pRevision->IsEnabled())
				{
					strCmd += string("--revision ") + string(m_pRevision->Text()) + string(" ");
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
	              		      130 );
	BBox* pRepositoryBBox = new BBox(RepositoryBBoxFrame,
									 "RepositoryBBox");
	pRepositoryBBox->SetLabel("Repository");
	pView->AddChild(pRepositoryBBox);
	
	// Url repository BStringView
	BRect pUrlRepStringViewFrame(g_fControlSpace, g_fControlSpace, 
	                   			 fRepositoryBBoxWidth - g_fControlSpace, g_fControlSpace + g_fStringViewHeight);
	BStringView* pUrlRepStringView = new BStringView(pUrlRepStringViewFrame,
												    "UrlRepositoryStringView",
												    "URL of repository : ");
	pRepositoryBBox->AddChild(pUrlRepStringView);
	
	// Url repository textcontrol
	BRect UrlRepoFrame(g_fControlSpace, pUrlRepStringViewFrame.bottom + 5, 
	                   fRepositoryBBoxWidth - g_fControlSpace, 0);
	m_pUrlRepository = new BTextControl(UrlRepoFrame,
									    "UrlRepositoryTextControl",
									    "URL of repository",
									    //"http://svn.collab.net/repos/tortoisesvn/trunk",
									    //"http://tortoisesvn.tigris.org/svn/tortoisesvn/trunk",
									    "svn://localhost/base1",
									    //NULL,
									    NULL);
	m_pUrlRepository->SetDivider(0.0f);
	pRepositoryBBox->AddChild(m_pUrlRepository);

	// Checkout directroy BStringView
	BRect CheckoutDirStringViewFrame(g_fControlSpace, UrlRepoFrame.top + g_fControlSpace + 10, 
	                       			 fRepositoryBBoxWidth - g_fControlSpace, UrlRepoFrame.top + g_fControlSpace + 10 + g_fStringViewHeight);
	BStringView* pCheckoutDirStringView = new BStringView(CheckoutDirStringViewFrame,
													      "CheckoutDirStringView",
												    	  "Checkout directory : ");
	pRepositoryBBox->AddChild(pCheckoutDirStringView);
	
	// Checkout directory textcontrol
	const float fSpace = 5.0f;
	const float fButtonWidth = 50.0f;
	BRect CheckoutDirFrame(g_fControlSpace, CheckoutDirStringViewFrame.bottom + 5, 
	                       fRepositoryBBoxWidth - g_fControlSpace - (fSpace + fButtonWidth), 
	                       0);
	BPath path(MoleSvnAddon::GetInstance()->GetCurrentDirectory());
	if(MoleSvnAddon::GetInstance()->GetSelectedEntryList().size() == 1)
	{
		// Checkout in the selected dir
		path.Append(MoleSvnAddon::GetInstance()->GetSelectedEntryList().front().name);
	}
	
	m_pCheckoutDirectory = new BTextControl(CheckoutDirFrame,
						    		        "CheckoutDirTextControl",
											"Checkout directory",
											path.Path(),
											NULL);
	m_pCheckoutDirectory->SetDivider(0.0f);
	pRepositoryBBox->AddChild(m_pCheckoutDirectory);

	// Search directory button
	BRect DirectoryButtonFrame(CheckoutDirFrame.RightTop().x + fSpace,
	                           CheckoutDirFrame.RightTop().y - 3.0f,
	                           CheckoutDirFrame.RightTop().x + fSpace + fButtonWidth,
	                           m_pCheckoutDirectory->Frame().Height());
	BButton* pDirectory = new BButton(DirectoryButtonFrame,
									  "DirectoryButton",
									  "Browse...",
									  new BMessage(CHECKOUT_OPEN_DIRECTORY));
	pRepositoryBBox->AddChild(pDirectory);

	// Authentication bbox
	float fAuthenticationBBoxWidth = (ViewFrame.Width() - (2.0f * g_fSpaceToWindowBorder + g_fControlSpace)) * 0.60f;
	BRect AuthenticationBBoxFrame(RepositoryBBoxFrame.left,
   		                          RepositoryBBoxFrame.bottom + g_fControlSpace,
	       		              	  fAuthenticationBBoxWidth,
	              		          RepositoryBBoxFrame.bottom + g_fControlSpace + 85 );
	BBox* pAuthenticationBBox = new BBox(AuthenticationBBoxFrame, "AuthenticationBBox");
	pAuthenticationBBox->SetLabel("Authentication");
	pView->AddChild(pAuthenticationBBox);

	// Login
	BRect LoginFrame(g_fControlSpace, g_fControlSpace, 
	                 (AuthenticationBBoxFrame.Width() - g_fControlSpace), 0);
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
	BRect PasswordFrame(LoginFrame.left, m_pLogin->Frame().bottom + g_fControlSpace, 
 	                    LoginFrame.right, 0);
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

	// Revision bbox
	BRect RevisionBBoxFrame(AuthenticationBBoxFrame.right + g_fControlSpace,
   		                          AuthenticationBBoxFrame.top,
	       		              	  ViewFrame.Width() - g_fSpaceToWindowBorder,
	              		          AuthenticationBBoxFrame.bottom );
	BBox* pRevisionBBox = new BBox(RevisionBBoxFrame, "RevisionBBox");
	pRevisionBBox->SetLabel("Revision");
	pView->AddChild(pRevisionBBox);
	
	// Head radio button
	BRect HeadFrame(g_fControlSpace, g_fControlSpace,
	                RevisionBBoxFrame.Width() - g_fControlSpace, g_fStringViewHeight);
	BRadioButton* pHeadButton = new BRadioButton(HeadFrame, 
	         									 "HeadRadioButton",
	         									 "Head",
	         									 new BMessage(CHECKOUT_HEAD_SELECTED));
	pHeadButton->SetValue(1);
	pRevisionBBox->AddChild(pHeadButton);

	// Revision radio button
	BRect NumberRevisionFrame(g_fControlSpace, PasswordFrame.top,
	                          RevisionBBoxFrame.Width() * 0.4f, g_fStringViewHeight);
	BRadioButton* pNumberRevisionButton = new BRadioButton(NumberRevisionFrame, 
	         									 "NumberRevisionButton",
	         									 "Revision : ",
	         									 new BMessage(CHECKOUT_REVISION_SELECTED));
	pRevisionBBox->AddChild(pNumberRevisionButton);

	// Revision textcontrol
	BRect RevisionFrame(NumberRevisionFrame.right + g_fControlSpace, NumberRevisionFrame.top, 
	                    RevisionBBoxFrame.Width() - g_fControlSpace, 0);
	m_pRevision = new BTextControl(RevisionFrame,
								"RevisionTextControl",
								"Revision :",
								"",
								NULL,
								B_FOLLOW_LEFT_RIGHT | B_FOLLOW_BOTTOM,
	                            B_WILL_DRAW | B_NAVIGABLE | B_FRAME_EVENTS | B_FULL_UPDATE_ON_RESIZE);
	m_pRevision->SetDivider(0.0f);
	m_pRevision->SetEnabled(false);			// Disable by default
	pRevisionBBox->AddChild(m_pRevision);
	


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
	
	// Check if the user has selected a revision
	if(m_pRevision->IsEnabled())
	{
		// Retrieve the revision number
		try
		{
			int nRevision = atoi(m_pRevision->Text());
			TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Revision number : %d", nRevision));
			
			if(nRevision <= 0)
			{
				ShowErrorWindow("invalid revision number");
				bRes = false;
			}
		}
		catch(...)
		{
			ShowErrorWindow("invalid revision number");
			bRes = false;
		}
	}
	
	return bRes;
}

