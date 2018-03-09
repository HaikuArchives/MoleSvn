///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : 
// File        : Config.h
// Description : defines some global defines, like enable clue, ... 
// Author      : cedric.bresson@artcoder.com
///////////////////////////////////////////////////////////////////////////////
#ifndef __Config_h__
#define __Config_h__

#define _ZETA_USING_DEPRECATED_API_ 1

#include <AppKit.h>
#include <InterfaceKit.h>
#include <SupportKit.h>
#include <StorageKit.h>

#define _DEBUG_	1	// define it for debug compilation

#if defined(_DEBUG_)
//#define CLUE	// define it for debug session with clue tool
#include "Utils/Clue.h"
#endif //_DEBUG_

#include "Utils/Exception.h"
#include "Utils/Utils.h"


//#include "3rd/mmgr/mmgr.h"	// Enable mmgr

// Current MoleSVN version
#define MOLESVN_MAJOR_VERSION 0
#define MOLESVN_MINOR_VERSION 3


// UI constants
const float g_fButtonWidth = 80.0f;			// Width of buttons
const float g_fButtonHeight = 25.0f;		// Height of buttons
const float g_fStringViewHeight = 15.0f;	// Height of string views
const float g_fControlSpace = 15.0f;        // Space between controls
const float g_fButtonsSpace = 20.0f;		// Space between buttons
const float g_fSpaceToWindowBorder = 15.0f;	// Space between control and window border 

// Action colors
const rgb_color g_colDefaultAction = {0, 0, 0, 255};
const rgb_color g_colModifiedAction = {0, 255, 0, 255};

#endif //__Config_h__
