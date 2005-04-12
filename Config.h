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


#endif //__Config_h__
