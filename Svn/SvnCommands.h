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

class SvnCommand : public BHandler
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
		// Remarks     : svn commands must overide this function to launch the
		//               corresponding command

	// -- Hooks ---------------------------------------------------------------
	virtual void MessageReceived(BMessage *message);
		
	// -- Accessors -----------------------------------------------------------
	const std::string& GetName() const;
		// Description : returns the command name
	
	MessageCommand GetMessageCommand() const;
		// Description : returns the message command id
		
	BBitmap* GetMiniIcon() const;
		// Description : Returns the mini icon that represents the svn command
		
	BBitmap* GetLargeIcon() const;
		// Description : Returns the large icon that represents the svn command
	
	int ExecuteSvn(const std::string& strCommand);
		// Description : execute the svn command strCommand in a shell

	void SetTarget(BLooper* pTarget);
	
protected:
	std::string GetCommand() const;
		// Description : returns the command string
private:
	int RetrieveSvnOutput();
	
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
		
	int m_StdoutPipes[2];
		// Description : pipes for reading standard output

	int m_StderrPipes[2];
		// Description : pipes for reading error output
	
	std::string m_strCommand;
		// Description : string that represents the command line  
	
	pid_t m_pid; 
	
protected:	
	BLooper* m_pTarget;
	
	TRACE_CLASS (CC_APPLICATION);
};

#include "Update.h"
#include "Commit.h"
#include "Add.h"
#include "Checkout.h"
#include "Status.h"
#include "About.h"
#include "Delete.h"
#include "Blame.h"
#include "Cleanup.h"
#include "Resolved.h"
#include "Revert.h"
#include "Rename.h"


#endif //__SvnCommand_h__

