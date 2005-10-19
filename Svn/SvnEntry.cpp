///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : Svn
// File        : SvnEntry.cpp
// Description : implements the SvnEntry command class
// Author      : cedric.bresson@artcoder.com
///////////////////////////////////////////////////////////////////////////////

#include "SvnEntry.h"
#include "../MoleSvnAddon.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// -- Life-cycle
///////////////////////////////////////////////////////////////////////////////
SvnEntry::SvnEntry(const BPath& path)
:m_Path(path),
 m_Status(SvnEntry::Undefined)
{

}

SvnEntry::~SvnEntry()
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));
}

///////////////////////////////////////////////////////////////////////////////
// -- Accessors
///////////////////////////////////////////////////////////////////////////////
string SvnEntry::GetName() const
{
	return string(m_Path.Leaf());
}

string SvnEntry::GetRelativePath() const
{
	// Get the current path
	BPath parentPath(MoleSvnAddon::GetInstance()->GetCurrentDirectory());
	string strParentPath(parentPath.Path());
	
	string strPath(m_Path.Path());
	
	TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Parent Path = %s", strParentPath.c_str()));
	TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Entry Path = %s", strPath.c_str()));
	
	string strRelPath(strPath, 
					  (strParentPath.size() < strPath.size()) ? strParentPath.size() + 1 : 0,
					  strPath.size());
	
	TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Relative Path = %s", strRelPath.c_str()));	
	
	if(!IsFile())
		strRelPath += '/';
	
	return strRelPath;
}

	
string SvnEntry::GetPath() const
{
	string strRes(m_Path.Path());	
	
	if(!IsFile())
		strRes += '/';
	
	return strRes;
}


SvnEntry::Status SvnEntry::GetStatus() const
{
	return m_Status;
}

void SvnEntry::SetStatus(SvnEntry::Status status)
{
	m_Status = status;
}

rgb_color SvnEntry::GetStatusColor() const
{
	rgb_color col;
	switch(GetStatus())
	{
		case SvnEntry::Added:
			col.red = 0;
			col.green = 0;
			col.blue = 200;
			break;		
		case SvnEntry::NonVersioned:
			col.red = 0;
			col.green = 128;
			col.blue = 0;
		case SvnEntry::FileMissing:
			col.red = 200;
			col.green = 0;
			col.blue = 200;
			break;
		case SvnEntry::Deleted:
			col.red = 0;
			col.green = 128;
			col.blue = 128;
			break;
		case SvnEntry::Conflicted:
			col.red = 200;
			col.green = 0;
			col.blue = 0;
			break;
		default:
			col.red = 0;
			col.green = 0;
			col.blue = 0;			
			break;
	}
	return col;
}
	
string SvnEntry::GetStatusString() const
{
	string strStatus;
	switch(m_Status)
	{
	case SvnEntry::NonVersioned:
		strStatus = "Non-versioned";
		break;
	case SvnEntry::FileMissing:
		strStatus = "File missing";
		break;
	case SvnEntry::Added:
		strStatus = "Added";
		break;
	case SvnEntry::Modified:
		strStatus = "Modified";
		break;
	case SvnEntry::Deleted:
		strStatus = "Deleted";
		break;
	case SvnEntry::Conflicted:
		strStatus = "Conflicted";
		break;
	case SvnEntry::Unmodified:
		strStatus = "Unmodified";
		break;	
	default:
		strStatus = "Undefined";
		break;
	}
	
	return strStatus;
}
