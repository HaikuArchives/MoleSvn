///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : 
// File        : MoleSvnAddon.h
// Description : defines the MoleSvnAddon class, the skeleton of the addon
// Author      : cedric.bresson@artcoder.com
///////////////////////////////////////////////////////////////////////////////
#ifndef __MoleSvnAddon_h__
#define __MoleSvnAddon_h__

#include <list>
#include <set>
#include <hash_map>
#include "Config.h"
#include "Utils/MoleSvnResources.h"
#include "Svn/SvnEntry.h"

class MoleSvnAddon
{
private:
	// -- Life-cycle ----------------------------------------------------------
	MoleSvnAddon();
	MoleSvnAddon(const MoleSvnAddon& addon);
		// Description : private constructor, to avoid bad call
	
public:
	// -- Nested classes ------------------------------------------------------
	struct eqEntryRef
	{
  		bool operator()(entry_ref e1, entry_ref e2) const
  		{
		    return e1 == e2;
		};
	};

	struct hashEntryRef
	{
		size_t operator()(entry_ref e) const
		{
			std::hash<const char*> h;
			return h(e.name);
		}
	};

	// -- Life-cycle ----------------------------------------------------------
	static MoleSvnAddon* GetInstance();
		// Description : singleton accessor
		
	~MoleSvnAddon(); 	
		// Description : Destructor
		
	// -- Services ------------------------------------------------------------
	void SetParameters(const entry_ref& rCurrentDirectory, const std::list<entry_ref>& lstEntry);
		// Description : Constructor
		// Arguments   : rCurrentDirectory - the current directory
		//               lstEntry - The list of entry_ref that the user has selected
		// Remarks     : The parameters are those from the process_ref function
		
	bool HasRepository(const BDirectory& dir);
		// Description : returns True if the directory dir contains a svn repository (.svn directory)

	bool LoadRepository(const BDirectory& dir, BLooper* pLooper = NULL);
		// Description : load the repository of the directory dir
		
	SvnEntry* IsInRepository(const entry_ref& e);
		// Descrption : return a SvnEntry pointer if the entry ref is in the repository,
		//              null otherwise
		
	void ShowMenu(BPoint point);
		// Description : show the menu
		// Remarks     : the content of the menu depends of the files selected by the user
		
	void AddThread(thread_id id);
		// Description : add a thread id to the current list of running threads
		
	void RemoveThread(thread_id id);
		// Description : remove a thread id to the current list of running threads
		
	// -- Accessors -----------------------------------------------------------
	MoleSvnResources* GetResources();
		// Description : returns a pointer to the addon resources
	
	entry_ref* GetCurrentDirectory();
		// Description : returns the current working directory

	const std::list<entry_ref>& GetSelectedEntryList() const;
		// Description : return the entry_ref list that the user has selected

	std::string GetEntryNameList() const;
		// Description : returns the list name of all selected entries by the user
		
	const std::hash_map<entry_ref, SvnEntry*, hashEntryRef, eqEntryRef>& GetSvnEntries() const;
		// Description : return the hashmap of the entries infos
private:
	// -- UI ------------------------------------------------------------------
	BPopUpMenu* CreateMenu();
		// Description : create the addon menu, corresponding to svn commands

	// -- Misc ----------------------------------------------------------------
	image_id FindAddonImage();
		// Description : returns the current image_id of the addon
		// Remarks     : usefull to get the addon filename and retrieve ressource into this file 

	std::string GetAddonFilename();
		// Description : returns the addon filename
		// Remarks     : we must have this function to open ressource in the addon file, and the
		//               user can change the addon name (like for shortcut)
	
	BEntry GetEntriesEntry(const BDirectory& dir);
		// Description : return the BEntry of the file "entries" in tue svn subdirectory if dir
	
	entry_ref m_CurrentDirectory;
		// Description : entry_ref from where the user launchs the addon
		// Init        : By cons
		
	std::list<entry_ref> m_lstEntry;
		// Description : entry_ref list that the user has selected
		// Init        : By cons
	
	MoleSvnResources* m_pResources;
		// Description : pointer t the addon resource
		// Init        : By cons
	
	struct ltthread_id 
	{ 
		bool operator()(const thread_id id1, const thread_id id2) const 
  		{ 
    		return id1 < id2; 
	  	}; 
	};
	 	
	std::set<thread_id, ltthread_id> m_setThread;
		// Description : set of running threads (windows threads)

	std::hash_map<entry_ref, SvnEntry*, hashEntryRef, eqEntryRef> m_mapSvnEntries;
		// Description : hashmap that stores infos about svn entries
		
	TRACE_CLASS (CC_APPLICATION);
};

#endif //__MoleSvnAddon_h__

