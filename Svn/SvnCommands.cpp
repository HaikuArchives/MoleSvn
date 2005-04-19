///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : 
// File        : SvnCommand.cpp
// Description : defines the SvnCommand class, the commands send to svn
// Author      : cedric.bresson@artcoder.com
#include "SvnCommands.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// -- Life-cycle
///////////////////////////////////////////////////////////////////////////////
SvnCommand::SvnCommand(const std::string& strName, MessageCommand msgCmd, 
					   MoleSvnIcons iconId)
:m_strName(strName), m_msgCmd(msgCmd), m_pMiniIcon(NULL), m_pLargeIcon(NULL)
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));
	
	MoleSvnAddon::GetInstance()->GetResources()->LoadIcon('MICN', iconId, &m_pMiniIcon);
	MoleSvnAddon::GetInstance()->GetResources()->LoadIcon('ICON', iconId, &m_pLargeIcon);
}
/*
SvnCommand::SvnCommand(const SvnCommand& rSvnCmd)
:m_strName(rSvnCmd.m_strName), m_msgCmd(rSvnCmd.msgCmd), m_pMiniIcon(NULL), m_pLargeIcon(NULL)
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));

	if(rSvnCmd.m_pMiniIcon)
	{
		m_pMiniIcon = new BBitmap(rSvnCmd.m_pMiniIcon->Bounds(), 
								  rSvnCmd.m_pMiniIcon->ColorSpace() );
								  
		m_pMiniIcon->SetBits(rSvnCmd.m_pMiniIcon->Bits(),
		                     rSvnCmd.m_pMiniIcon->BitsLength(),
		                     0,
		                     rSvnCmd.m_pMiniIcon->ColorSpace());
	}

	if(rSvnCmd.m_pLargeIcon)
	{
		m_pLargeIcon = new BBitmap(rSvnCmd.m_pLargeIcon->Bounds(), 
		                           rSvnCmd.m_pLargeIcon->ColorSpace() );
		                           
		m_pLargeIcon->SetBits(rSvnCmd.m_pLargeIcon->Bits(),
		                      rSvnCmd.m_pLargeIcon->BitsLength(),
		                      0,
		                      rSvnCmd.m_pLargeIcon->ColorSpace());
	}
}
*/
SvnCommand::~SvnCommand()
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));
	
	if(m_pMiniIcon)
	{
		delete m_pMiniIcon;
	}
	
	if(m_pLargeIcon)
	{
		delete m_pLargeIcon;
	}
}


///////////////////////////////////////////////////////////////////////////////
// -- Services
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// -- Accessors
///////////////////////////////////////////////////////////////////////////////
const string& SvnCommand::GetName() const
{
	return m_strName;
}

MessageCommand SvnCommand::GetMessageCommand() const
{
	return m_msgCmd;
}

BBitmap* SvnCommand::GetMiniIcon() const
{
	return m_pMiniIcon;
}
		
BBitmap* SvnCommand::GetLargeIcon() const
{
	return m_pLargeIcon;
}

///////////////////////////////////////////////////////////////////////////////
// -- Private
///////////////////////////////////////////////////////////////////////////////
