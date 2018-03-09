///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : 
// File        : main.cpp
// Description : defines the entry point of the add-on 
// Author      : cedric.bresson@artcoder.com
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h> 
#include <string.h> 
#include <list>

#include <add-ons/tracker/TrackerAddOn.h>
#include "Config.h"
#include "MoleSvnAddon.h"

using namespace std;

void process_refs(entry_ref dir_ref, BMessage *msg, void *) 
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD, "MoleSvn v%d.%d starts here!", MOLESVN_MAJOR_VERSION,MOLESVN_MINOR_VERSION));
	
	try
	{
		// check if the user has selected files...
		int nRefs; 
		entry_ref file_ref; 
		list<entry_ref> lstEntry;	
		char name[B_FILE_NAME_LENGTH]; 
		for (nRefs=0; msg->FindRef("refs", nRefs, &file_ref) == B_NO_ERROR; ++nRefs)
		{
			// Check if the entry is a .svn directory
			BEntry svnentry(&file_ref);
			svnentry.GetName(name); 	
			if(string(".svn") != name)
			{
				lstEntry.push_back(file_ref);
			}
		}

		// Set parameters to the instance of the addon
		MoleSvnAddon::GetInstance()->SetParameters(dir_ref, lstEntry);
	
		// Retrieve mouse position
		// I don't know a much safer method...
		// Create a fake window and an embedded view, to get mouse position... yep
		BWindow* pWindow = new BWindow(BRect(0, 0, 100, 100), "MoleSVN", B_TITLED_WINDOW, B_NO_WORKSPACE_ACTIVATION);
		BView* pView = new BView(BRect(0, 0, 100, 100), "MoleSVN", B_FOLLOW_H_CENTER, B_WILL_DRAW);
		pWindow->AddChild(pView);
		BPoint MousePosition;
		uint32 nButtons;
		pView->GetMouse(&MousePosition, &nButtons);
		pView->ConvertToScreen(&MousePosition);
		pWindow->Quit();
		// See the talkback of BiPolar about the MoleSVN call from the shortcut
		//MousePosition.x -= 10;
		//MousePosition.y -= 10;
		TRACE_OBJECT ((CC_APPLICATION, CR_OBJECT, &MousePosition, "Mouse position"));
		
		// Show the menu, depending of the selected files 
		MoleSvnAddon::GetInstance()->ShowMenu(MousePosition);
	}
	catch(MoleSvnException e)
	{
		ShowErrorWindow(e.what());
	}
	catch(...)
	{
		ShowErrorWindow(string("unhandled exception"));
	}
} 

int main() 
{ 
	new BApplication("application/x-molesvn-add-on"); 
	
	// Show a tiny message ;)
	ShowAboutWindow();
	
	delete be_app; 
	return 0;
}
