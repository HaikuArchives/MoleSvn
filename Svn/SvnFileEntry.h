///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : SVN
// File        : SvnFileEntry.h
// Description : defines the SvnFileEntry class, that represents stored informations
//               in entries file
// Author      : cedric.bresson@artcoder.com
///////////////////////////////////////////////////////////////////////////////
#ifndef __Svn_SvnFileEntry_h_
#define __Svn_SvnFileEntry_h_

#include <string>
#include "Config.h"
#include "SvnEntry.h"

class SvnFileEntry : public SvnEntry
{
public:
	// -- Nested classes ------------------------------------------------------
	enum Schedule
	{
		Add,
		Delete,
		None
	};

	// -- Life-cycle ----------------------------------------------------------
	SvnFileEntry(std::string strName);
		// Description : constructor
		
	~SvnFileEntry();
		// Description : destructor
		
	// -- Hook functions ------------------------------------------------------
	bool IsFile();

	// -- Accessors -----------------------------------------------------------
	unsigned int GetCommittedRevision() const;
		// Description : return the committed version of the file
		
	void SetCommittedRevision(const std::string& strRevision);
		// Description : set the committed version of the file
		
	const std::string& GetLastAuthor() const;
		// Description : return the last author who have committed the file
		
	void SetLastAuthor(const std::string& strLastAuthor);
		// Description : set the last author who have committed the file
		
	SvnFileEntry::Schedule GetSchedule() const;
		// Description : return the schedule type
	
	void SetSchedule(const std::string& strSchedule);
		// Description : set the scehdule type
	
private:
	unsigned int m_nCommittedRevision;
		// Description : last committed revision of the file
		// Init        : 0 by cons
		
	std::string m_strLastAuthor;
		// Description : last author who have committed the file
		// Init        : empty by cons
		
	SvnFileEntry::Schedule m_Schedule;
		// Descirption : schedule of the file for the next commit (add, delete, ...)
		// Init        : None
};


#endif //__Svn_SvnFileEntry_h_
