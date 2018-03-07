///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : Svn
// File        : SvnFileEntry.cpp
// Description : implements the SvnFileEntry command class
// Author      : cedric.bresson@artcoder.com
///////////////////////////////////////////////////////////////////////////////

#include "SvnFileEntry.h"

//#define BOOST_NO_STRINGSTREAM
//#include <boost/lexical_cast.hpp>
#include <stdlib.h>	// atoi

using namespace std;
//using namespace boost;

///////////////////////////////////////////////////////////////////////////////
// -- Life-cycle
///////////////////////////////////////////////////////////////////////////////
SvnFileEntry::SvnFileEntry(const BPath& path)
:SvnEntry(path),
 m_nCommittedRevision(0),
 m_strLastAuthor(),
 m_Schedule(SvnFileEntry::None)
{

}

SvnFileEntry::~SvnFileEntry()
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));
}

///////////////////////////////////////////////////////////////////////////////
// -- Hook functions
///////////////////////////////////////////////////////////////////////////////
bool SvnFileEntry::IsFile() const
{
	return true;	
}

///////////////////////////////////////////////////////////////////////////////
// -- Accessors
///////////////////////////////////////////////////////////////////////////////
unsigned int SvnFileEntry::GetCommittedRevision() const
{
	return m_nCommittedRevision;
}
		
void SvnFileEntry::SetCommittedRevision(const std::string& strRevision)
{
	TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Revision = %s", strRevision.c_str()));

//	m_nCommittedRevision = lexical_cast<int>(strRevision);
	m_nCommittedRevision = atoi(strRevision.c_str());
	
	TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Revision = %d", m_nCommittedRevision));
}
		
const std::string& SvnFileEntry::GetLastAuthor() const
{
	return m_strLastAuthor;
}
		
void SvnFileEntry::SetLastAuthor(const std::string& strLastAuthor)
{
	m_strLastAuthor = strLastAuthor;
}

SvnFileEntry::Schedule SvnFileEntry::GetSchedule() const
{
	return m_Schedule;
}
	
void SvnFileEntry::SetSchedule(const std::string& strSchedule)
{
	if(strSchedule == "add")
		m_Schedule = SvnFileEntry::Add;
	else if(strSchedule == "delete")
		m_Schedule = SvnFileEntry::Delete;
	else
		m_Schedule = SvnFileEntry::None;
}



