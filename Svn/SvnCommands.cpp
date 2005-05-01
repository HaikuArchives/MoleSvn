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
// -- Protected
///////////////////////////////////////////////////////////////////////////////
int SvnCommand::ExecuteSvn(const string& strCommand)
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));
	
	m_strCommand = strCommand;

	// Create a new thread
	m_SvnThreadId = spawn_thread(SpawnThread, "MoleSvnCommandThread", B_NORMAL_PRIORITY, this);

	resume_thread(m_SvnThreadId); 
	
	int32 exitValue;
	wait_for_thread(m_SvnThreadId, &exitValue);	
	
	return exitValue;
/*
    int StdoutSave, StderrSave; 
    int Pipes[2]; 

	// Save the stdout and stderr handle
    StdoutSave = dup(HF_STDOUT);
    StderrSave = dup(HF_STDERR);
    //close(StdoutSave);

	// Create new pipes
    pipe(Pipes); 

	// Redirect stdout, stderr
    dup2(Pipes[1], HF_STDOUT);
    dup2(Pipes[1], HF_STDERR);
  
    // Execute svn command
	string strCmd(strCommand);
	TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Execute = %s", strCmd.c_str()));
	int nErrorCode = system(strCmd.c_str());
	//int nErrorCode = execl("svn", "--version");

    close(Pipes[1]); 

	// Read the pipe 0
    char Line[128]; 
    ifstream R(Pipes[0]); 
    //ofstream Log("log.txt"); 
    int nIndex = 0;
    
    while (!R.eof() && nIndex < 30) 
    { 
		R.getline(Line,sizeof(Line)); 
		TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "%d : %s", nIndex, Line));
        //Log << Line << flush; 
        ++nIndex;
    } 
    
    R.close();

	// Close pipe
    close(Pipes[0]);
  
    // Restore default stdout and stderr
    dup2(StdoutSave, HF_STDOUT);
    dup2(StderrSave, HF_STDERR); 

	// Return svn command error code
	return nErrorCode;
*/
}

///////////////////////////////////////////////////////////////////////////////
// -- Private
///////////////////////////////////////////////////////////////////////////////
int32 SvnCommand::SpawnThread(void* arg) 
{ 
	return ((SvnCommand*) arg)->SvnCommandThread();
}

int32 SvnCommand::SvnCommandThread()
{
	char fileName[B_PATH_NAME_LENGTH]; 
	const int32 nBufferSize = 512;
	char tempString[nBufferSize];
	
	// Create a temporary file, where to write stdout
	BPath tempFile;
	sprintf(fileName, "/boot/var/tmp/MoleSvn%ld", find_thread(NULL));
	tempFile.SetTo(fileName);
	
	// Create the command string
	string strCmd(m_strCommand + " > \"" + string(tempFile.Path()) + "\"");
	TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Execute = %s", strCmd.c_str()));
	
	// Launch the svn command
	int nErrorCode = system(strCmd.c_str());
	
	// Read each line of the file
	if ((nErrorCode == 0))
	{
		FILE* results = fopen(tempFile.Path(), "r");

		if (results != NULL)
		{
			while (fgets(tempString, nBufferSize, results) != 0)
			{
				// Create a message
				BMessage msg('SVNC');
				
				// Replace non printable caracter by space
				string strTmp(tempString);
				strTmp[strTmp.size() - 1] = 0;
				
				// Add text to message
				msg.AddString("text", strTmp.c_str());
				
				// Send message
				TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "%s", tempString));
				m_pTarget->PostMessage(&msg);
			}
			
			// Close the tempoerary file
			fclose(results);
		}
	}
/*
	// End message		
	BMessage msg;
	msg.AddString("text", tempString);
	TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "%s", tempString));
	m_pTarget->PostMessage(&msg);
*/				
	
	// Remove the temporary file
	remove(tempFile.Path());
	
	return nErrorCode;	
}
