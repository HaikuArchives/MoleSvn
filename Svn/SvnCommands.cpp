///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : 
// File        : SvnCommand.cpp
// Description : defines the SvnCommand class, the commands send to svn
// Author      : cedric.bresson@artcoder.com
///////////////////////////////////////////////////////////////////////////////
#include "SvnCommands.h"
#include <stdlib.h>
#include <string.h> 
#include <fstream.h> 
#include <unistd.h>
#include <sys/socket.h>

using namespace std;

#define HF_STDIN  0
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

//#include <unistd.h>
//#include <sys/wait.h>
//#include <signal.h>
//#include <iostream>

///////////////////////////////////////////////////////////////////////////////
// -- Protected
///////////////////////////////////////////////////////////////////////////////
int SvnCommand::ExecuteSvn(const string& strCommand)
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));
	
	m_strCommand = strCommand;

	//setvbuf(stdout,(char*)NULL,_IOLBF,0);
	
	// Create new pipes
    pipe(m_StdoutPipes); 
    pipe(m_StderrPipes); 

    m_pid = fork();
    if(m_pid == -1)
    {
		TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Fork failed"));
		return -1;
    }
    else if(m_pid == 0)
	{
		// Close reading pipe
		close(m_StdoutPipes[0]);
		close(m_StderrPipes[0]);
		
		// Duplicate STDOUT and STDERR to ours pipes
		dup2(m_StdoutPipes[1], HF_STDOUT);
		dup2(m_StderrPipes[1], HF_STDERR);

		// Execute command
		TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Execute = %s", strCommand.c_str()));
		//int err = execl(strCommand.c_str(), NULL);
		//int err = execvp(strCommand.c_str(), NULL);
		int err = system(m_strCommand.c_str());
/*
		int err = 0;
		printf("1\r\n");
		printf("2\r\n");
		printf("3\r\n");
		printf("4\r\n");
		printf("5\r\n");
		printf("6\r\n");
		printf("7\r\n");
*/
		// close our writing pipe, because we must have only one pipe open
		// and STDOUT is already open
		close(m_StdoutPipes[1]);
		close(m_StderrPipes[1]);

		close(HF_STDOUT);
		close(HF_STDERR);
		
		TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Svn returns : %d", err));

		exit(err);
	}

	return RetrieveSvnOutput();
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
int SvnCommand::RetrieveSvnOutput()
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));
	
	// We don't need writing, so we close
	close(m_StdoutPipes[1]);
	close(m_StderrPipes[1]);

	// Read the pipe 0
	const int Buffer_Max = 512;
    char Line[Buffer_Max]; 
#define MOLESVN_USE_IFSTREAM
#if defined(MOLESVN_USE_IFSTREAM)    
    ifstream R(m_StdoutPipes[0]); 
#else
	FILE* fstdout = fdopen(m_StdoutPipes[0], "r");
#endif //MOLESVN_USE_IFSTREAM
    
    bool bHasMessage = false;
    string strTmp;
    
	TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Reading pipe..."));
#if defined(MOLESVN_USE_IFSTREAM)
	do
    { 
		R.getline(Line, Buffer_Max);
		strTmp = string(Line);	

#else
	while (!feof(fstdout))
	{
		fgets(Line, Buffer_Max, fstdout);
		char *p;
		if((p=strrchr(Line,'\n')))
			*p=0;
		strTmp = string(Line);
		
#endif //MOLESVN_USE_IFSTREAM		
		
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
    	
#if defined(MOLESVN_USE_IFSTREAM)
    } while (!R.eof());
#else
	}
#endif    

	TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "End of reading pipe..."));

#if defined(MOLESVN_USE_IFSTREAM)
	// Close stream    
    R.close();
#else
    fclose(fstdout);
#endif    

	// Close pipe
    close(m_StdoutPipes[0]);

	int nSvnError = 0;
    waitpid(m_pid, &nSvnError, WUNTRACED);
    if(WIFEXITED(nSvnError))
    {
		nSvnError = WEXITSTATUS(nSvnError);
    }

	TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "SVN error : %d", nSvnError));
	if(nSvnError)
	{
#if defined(MOLESVN_USE_IFSTREAM)
		// Read stderr
    	ifstream ErrStream(m_StderrPipes[0]); 
#else
		FILE* fstderr = fdopen(m_StderrPipes[0], "r");
#endif
    
    	string strErr;
    	char tmp[128];
    	sprintf(tmp, "SVN returns error code : %d\n", nSvnError);
    	strErr += string(tmp);
    	
		TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Reading stderr pipe..."));

#if defined(MOLESVN_USE_IFSTREAM)
		do
	    { 
			ErrStream.getline(Line,sizeof(Line)); 
			strErr += string(Line);
    	} while (!ErrStream.eof());

		// Close stream    
    	ErrStream.close();
#else
		while(!feof(fstderr))
		{
			fgets(Line,sizeof(Line), fstderr); 
			strErr += string(Line);
		}
		
		fclose(fstderr);
#endif    
 
		TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "End of reading stderr pipe..."));
		
 		ShowErrorWindow(strErr);   	
	}
	
	// Send a finished message, in case where there is no output and no error,
	// just to inform the user that the operation is finished    
    if(!bHasMessage && !nSvnError)
    {
		// Create a message
		BMessage msg(MSG_SVN_STDOUT);
		
		// Add text to message
		msg.AddString("text", "Operation finished.");
				
		// Send message
		m_pTarget->PostMessage(&msg);
    }
	
	// Close pipe
    close(m_StderrPipes[0]);
    
	// Create a message
	BMessage msg(MSG_CMD_FINISHED);
	
	// Send message
	m_pTarget->PostMessage(&msg);
	
	return nSvnError;
}
