///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : SVN
// File        : SvnEntry.h
// Description : defines the SvnEntry class, that represents stored informations
//               in entries file
// Author      : cedric.bresson@artcoder.com
///////////////////////////////////////////////////////////////////////////////
#ifndef __Svn_SvnEntry_h_
#define __Svn_SvnEntry_h_

#include <string>
#include "Config.h"

class SvnEntry
{
public:
	// -- Nested types --------------------------------------------------------
	enum Status
	{
		NonVersioned,
		FileMissing,
		Added,
		Modified,
		Deleted,
		Conflicted,
		Unmodified,
		Undefined,
	};
	
	// -- Life-cycle ----------------------------------------------------------
	SvnEntry(const BPath& path);
		// Description : constructor
		
	virtual ~SvnEntry();
		// Description : destructor
		
	// -- Hook functions ------------------------------------------------------
	virtual bool IsFile() const = 0;
		// Description : return true if the svn entry is a file, false if it's 
		//               a directory

	// -- Accessors -----------------------------------------------------------
	std::string GetName() const;
		// Description : return the svn entry name

	std::string GetRelativePath() const;
		// Description : return the path relative to the current path
		
	std::string GetPath() const;
		// Description : return the absolute path
		
	SvnEntry::Status GetStatus() const;
		// Description: return the status of the entry

	void SetStatus(SvnEntry::Status status);
		// Description: Set the status of the entry
		
	rgb_color GetStatusColor() const;
		// Description : return a color depending of the status of the entry
		// Remarks     : usefull to display text (red for deleted, blue for added, ...)
	
	std::string GetStatusString() const;
		// Description : return the status on a human readable string

private:
	BPath	m_Path;
		// Description : path (in the BeFS) of the svn entry
		// Init        : By cons
		
	SvnEntry::Status m_Status;
		// Description : status of the entry (added, non-versioned, ...)
		// Init        : Undefined
};


#endif //__Svn_SvnEntry_h_
