///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : 
// File        : SvnCommand.cpp
// Description : defines the SvnCommand class, the commands send to svn
// Author      : cedric.bresson@artcoder.com
#include "SvnCommands.h"
#include <stdlib.h>
#include <string.h> 
#include <fstream.h> 
#include <unistd.h>
#include <io.h> 

using namespace std;

#define HF_STDIN 0
#define HF_STDOUT 1
#define HF_STDERR 2

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
 void SvnCommand::MessageReceived(BMessage *message)
 {
 	
 }

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
// -- Protected
///////////////////////////////////////////////////////////////////////////////
int SvnCommand::ExecuteSvn(const string& strCommand)
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));
	
	m_strCommand = strCommand;

	// Create new pipes
    pipe(m_Pipes); 
    
	pid_t pid; 
    pid = fork();
    if(pid == -1)
    {
		TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Fork failed"));
		return -1;
    }
    else if(pid == 0)
	{
		// Close reading pipe
		close(m_Pipes[0]);
		
		// Duplicate STDOUT to our pipe
		dup2(m_Pipes[1], HF_STDOUT);
		
		// close our writing pipe, because we must have only one pipe open
		// and STDOUT is already open
		close(m_Pipes[1]);

		// Execute command
		string strCmd = m_strCommand + string(" ") + MoleSvnAddon::GetInstance()->GetEntryNameList();
		TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Execute = %s", strCmd.c_str()));
		//int err = execl(strCmd.c_str(), NULL);
		int m_SvnError = system(strCmd.c_str());

		close(HF_STDOUT);
				
		TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Svn returns : %d", m_SvnError));
		exit(m_SvnError);
	}

	// Create a new thread
//	m_SvnThreadId = spawn_thread(SpawnThread, "MoleSvnCommandThread", B_NORMAL_PRIORITY, this);

//	resume_thread(m_SvnThreadId);

	RetrieveSvnOutput();	

/*	
	int32 exitValue = 0;
	if(m_SvnThreadId)
	{
		TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Wait for svn command thread = %d", m_SvnThreadId));
		wait_for_thread(m_SvnThreadId, &exitValue);	
	}
*/
	
//	return exitValue;
	return 0;
}

void SvnCommand::SetTarget(BLooper* pTarget)
{
	m_pTarget = pTarget;	
}

string SvnCommand::GetCommand() const
{
	return m_strCommand;
}


///////////////////////////////////////////////////////////////////////////////
// -- Private
///////////////////////////////////////////////////////////////////////////////
int32 SvnCommand::SpawnThread(void* arg) 
{ 
	int nError = ((SvnCommand*) arg)->SvnCommandThread();
	((SvnCommand*) arg)->m_SvnThreadId = 0;	
	return nError;
}

int32 SvnCommand::SvnCommandThread()
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));
	return 0;	
}

void SvnCommand::RetrieveSvnOutput()
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));
	
	// We don't need writing, so we close
	close(m_Pipes[1]);

	// Read the pipe 0
    char Line[128]; 
    ifstream R(m_Pipes[0]); 
    bool bHasMessage = false;
    
    string strTmp;
	TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Reading pipe..."));
	do
    { 
		R.getline(Line,sizeof(Line)); 
		
		strTmp = string(Line);
		// check if the line is not empty
		if(strTmp.size() > 0)
		{	
			// Create a message
			BMessage msg(MSG_SVN_STDOUT);
		
			// Add text to message
			msg.AddString("text", strTmp.c_str());
				
			// Send message
			m_pTarget->PostMessage(&msg);
			
			bHasMessage = true;
    	}
    } while (!R.eof());

	TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "End of reading pipe..."));

	// Close stream    
    R.close();

	// Close pipe
    close(m_Pipes[0]);
    
    if(!bHasMessage && !m_SvnError)
    {
		// Create a message
		BMessage msg(MSG_SVN_STDOUT);
		
		// Add text to message
		msg.AddString("text", "operation finished...");
				
		// Send message
		m_pTarget->PostMessage(&msg);
    }
    
    
	// Create a message
	BMessage msg(MSG_CMD_FINISHED);
	// Send message
	m_pTarget->PostMessage(&msg);
/*
    if(m_SvnError)
    {
		// Create a message
		BMessage msg('MERR');
		
		// Add text to message
		msg.AddString("text", "operation finished...");
				
		// Send message
		m_pTarget->PostMessage(&msg);
    }
*/    
}
