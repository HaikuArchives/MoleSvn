///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : 
// File        : MoleSvnAddon.h
// Description : defines the MoleSvnAddon class, the skeleton of the addon
// Author      : cedric.bresson@artcoder.com
///////////////////////////////////////////////////////////////////////////////
#ifndef __MoleSvnAddon_h__
#define __MoleSvnAddon_h__

#include <StorageKit.h> 
#include <list>
#include "Config.h"

class MoleSvnAddon
{
public:
	// -- Life-cycle ----------------------------------------------------------
	MoleSvnAddon(const entry_ref& rCurrentDirectory, const std::list<entry_ref>& lstEntry);
		// Description : Constructor
		// Arguments   : rCurrentDirectory - the current directory
		//               lstEntry - The list of entry_ref that the user has selected
		// Remarks     : The parameters are those from the process_ref function
		
	~MoleSvnAddon(); 	
		// Description : Destructor
	
	// -- Services ------------------------------------------------------------
	void ShowMenu(BPoint point);
		// Description : show the menu
		// Remarks     : the content of the menu depends of the files selected by the user
		
private:
	entry_ref m_CurrentDirectory;
		// Description : entry_ref from where the user launchs the addon
		// Init        : By cons
		
	list<entry_ref> m_lstEntry;
		// Description : entry_ref list that the user has selected
		// Init        : By cons
		
	TRACE_CLASS (CC_APPLICATION);
};

#endif //__MoleSvnAddon_h__

