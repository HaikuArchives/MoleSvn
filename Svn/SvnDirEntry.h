///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : SVN
// File        : SvnDirEntry.h
// Description : defines the SvnDirEntry class, that represents stored informations
//               in entries file
// Author      : cedric.bresson@artcoder.com
///////////////////////////////////////////////////////////////////////////////
#ifndef __Svn_SvnDirEntry_h_
#define __Svn_SvnDirEntry_h_

#include <string>
#include "Config.h"
#include "SvnEntry.h"

class SvnDirEntry : public SvnEntry
{
public:
	// -- Life-cycle ----------------------------------------------------------
	SvnDirEntry(const BPath& path);
		// Description : constructor
		
	~SvnDirEntry();
		// Description : destructor
		
	// -- Hook functions ------------------------------------------------------
	bool IsFile() const;
	
private:

};


#endif //__Svn_SvnDirEntry_h_
