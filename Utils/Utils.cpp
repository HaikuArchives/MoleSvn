///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : 
// File        : Utils.cpp
// Description : defines some utils global fonction
// Author      : cedric.bresson@artcoder.com
///////////////////////////////////////////////////////////////////////////////

#include "Utils.h"

#include <InterfaceKit.h>
#include <stdio.h>
#include "../Config.h"

void ShowAboutWindow() 
{
	char version[1024];
	sprintf(version, "MoleSVN -- SVN Tracker add-on\n\nVersion %d.%d (%s)\n\nHomepage : http://molesvn.sourceforge.net\n\nCreated by :\n  - Cedric Bresson (bresson.cedric@voila.fr)\n  - Laurent Humbertclaude (lhumbertclaude@yahoo.fr)", MOLESVN_MAJOR_VERSION, MOLESVN_MINOR_VERSION, __DATE__);
	(new BAlert(0, 
				version,
				"Okay",
				0,
				0,
				B_WIDTH_AS_USUAL,
				B_INFO_ALERT))->Go();
}
