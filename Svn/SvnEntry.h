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
	// -- Life-cycle ----------------------------------------------------------
	SvnEntry(std::string strName);
		// Description : constructor
		
	virtual ~SvnEntry();
		// Description : destructor
		
	// -- Hook functions ------------------------------------------------------
	virtual bool IsFile() = 0;
		// Description : return true if the svn entry is a file, false if it's 
		//               a directory

	// -- Accessors -----------------------------------------------------------
	const std::string& GetName() const;
		// Description : return the svn entry name
	
private:
	std::string m_strName;
		// Description : name of the svn entry
};


#endif //__Svn_SvnEntry_h_
