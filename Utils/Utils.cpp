///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : 
// File        : Utils.cpp
// Description : defines some utils global fonction
// Author      : cedric.bresson@artcoder.com
///////////////////////////////////////////////////////////////////////////////

#include "Utils.h"
#include "../Config.h"

using namespace std;

void ShowAboutWindow() 
{
	char version[1024];
	sprintf(version, "MoleSVN -- Subversion Tracker add-on\n\nVersion %d.%d (%s)\n\nHomepage : http://molesvn.sourceforge.net\n\nCreated by :\n  - Kor (bresson.cedric@voila.fr)\n  - Chowette (lhumbertclaude@yahoo.fr)\n\nThanks to :\nRudolf, Ubix.org, Beosfrance.com", MOLESVN_MAJOR_VERSION, MOLESVN_MINOR_VERSION, __DATE__);
	(new BAlert(0, 
				version,
				"Okay",
				0,
				0,
				B_WIDTH_AS_USUAL,
				B_INFO_ALERT))->Go();
}

void ShowErrorWindow(const string& strMsg, const string& strTitle)
{
	(new BAlert(0, 
				(strTitle + string("\n\n") + strMsg).c_str(),
				"Okay",
				0,
				0,
				B_WIDTH_AS_USUAL,
				B_STOP_ALERT))->Go();

}


std::string FormatString(const char* pBuffer, ...)
{
    va_list argList;
    const int nMax = 1024;
    char caBuffer[nMax];
    va_start(argList, pBuffer);
    vsprintf(caBuffer, pBuffer, argList);
    va_end(argList);
    return std::string(caBuffer);
}
