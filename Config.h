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

#define CLUE	// define it for debug session with clue tool
#include "Utils/Clue.h"

#include "Utils/Exception.h"
#include "Utils/Utils.h"

// Current MoleSVN version
#define MOLESVN_MAJOR_VERSION 0
#define MOLESVN_MINOR_VERSION 1


// UI constants
const float g_fButtonWidth = 80.0f;			// Width of buttons
const float g_fButtonHeight = 25.0f;		// Height of buttons
const float g_fControlSpace = 20.0f;        // Space between controls
const float g_fButtonsSpace = 20.0f;		// Space between buttons
const float g_fSpaceToWindowBorder = 20.0f;	// Space between control and window border 

#endif //__Config_h__
