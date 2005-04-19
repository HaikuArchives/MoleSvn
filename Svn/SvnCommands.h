///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : Svn
// File        : SvnCommand.h
// Description : defines the SvnCommand class, the commands send to svn
// Author      : cedric.bresson@artcoder.com
///////////////////////////////////////////////////////////////////////////////
#ifndef __SvnCommand_h__
#define __SvnCommand_h__

#include <string>
#include "Config.h"
#include "../MoleSvnAddon.h"
#include "../UI/MoleSvnIcons.h"
#include "../UI/MessageCommands.h"

class SvnCommand
{
public:
	// -- Life-cycle ----------------------------------------------------------
	SvnCommand(const std::string& strName, MessageCommand msgCmd, MoleSvnIcons iconId);
		// Description : constructor
		
	SvnCommand(const SvnCommand& rSvnCmd);
		// Description : copy constructor
	
	virtual ~SvnCommand(); 	
		// Description : Destructor
		
	// -- Services ------------------------------------------------------------
	virtual void Execute() = 0;
		// Description : executes the svn command
		// Remarks     : svn commands must overide this function and launch the
		//               corresponding command
		
	// -- Accessors -----------------------------------------------------------
	const std::string& GetName() const;
		// Description : returns the command name
	
	MessageCommand GetMessageCommand() const;
		// Description : returns the message command id
		
	BBitmap* GetMiniIcon() const;
		// Description : Returns the mini icon that represents the svn command
		
	BBitmap* GetLargeIcon() const;
		// Description : Returns the large icon that represents the svn command
	
private:
	std::string m_strName;
		// Description : name of the svn command (ex: Update, Commit, Add, ...)
		// Init        : By cons
		
	MessageCommand m_msgCmd;
		// Description : message command, usefull for BMessage
		// Init        : By cons
		
	BBitmap* m_pMiniIcon;
		// Description : Mini icon that represents the svn command
		// Init        : By cons

	BBitmap* m_pLargeIcon;
		// Description : Large icon that represents the svn command
		// Init        : By cons
		
	TRACE_CLASS (CC_APPLICATION);
};

#endif //__SvnCommand_h__

