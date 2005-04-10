///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : 
// File        : MoleSvnAddon.cpp
// Description : implements the MoleSvnAddon class, the skeleton of the addon
// Author      : cedric.bresson@artcoder.com
///////////////////////////////////////////////////////////////////////////////
#include "MoleSvnAddon.h"

#include <AppKit.h>
#include <InterfaceKit.h>
#include <SupportKit.h>

#include "UI/IconMenuItem.h"

///////////////////////////////////////////////////////////////////////////////
// -- Life-cycle
///////////////////////////////////////////////////////////////////////////////
MoleSvnAddon::MoleSvnAddon(const entry_ref& rCurrentDirectory, 
                           const list<entry_ref>& lstEntry)
:m_CurrentDirectory(rCurrentDirectory), m_lstEntry(lstEntry)
{
	TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Nb entries = %i", m_lstEntry.size()));
}
		
MoleSvnAddon::~MoleSvnAddon()
{
	m_lstEntry.clear();
}


///////////////////////////////////////////////////////////////////////////////
// -- Services
///////////////////////////////////////////////////////////////////////////////
void MoleSvnAddon::ShowMenu(BPoint point)
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));

	// To get app file info for be_app. 
	app_info appInfo; 
	BAppFileInfo appFileInfo; 
	be_app->GetAppInfo(&appInfo); 

	image_id image = find_image(memAddr);
	image_info info;
	if (get_image_info(image, &info) == B_OK) {
#if _SUPPORTS_RESOURCES
		BFile file(&info.name[0], B_READ_ONLY);
#else
		BString name(&info.name[0]);

	BFile file; 
	//file.SetTo(&appInfo.ref, B_READ_WRITE); 
	file.SetTo("MoleSVN-M", B_READ_WRITE); 
	if(file.InitCheck() == B_OK)
	{
		throw FileNotFound(string("cannot open ressources"));	
	}
	
	BResources res;
	if( res.SetTo(&file) != B_OK)
	{
		throw FileNotFound(string("cannot open ressources"));	
	}
	
	
	size_t len;
	const void *data = res.LoadResource('ICON', "MOLESVN:L:LOGO", &len);	
	BBitmap logo(BRect(0, 0, 31, 31), B_RGB32);
	logo.SetBits(data);
		
	// Create the menu
	BPopUpMenu menu("menu");
	menu.AddItem(new BMenuItem("toto", NULL));
//	menu.AddItem(new IconMenuItem("toto", logo));
	menu.AddItem(new BMenuItem("MoleSVN", NULL));
	
	// Show the popup menu
	TRACE_OBJECT ((CC_APPLICATION, CR_OBJECT, &point, "Popup menu point"));
	BMenuItem* pSelectedItem = menu.Go(point);
}
