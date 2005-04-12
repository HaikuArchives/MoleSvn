///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : Utils
// File        : Utils.h
// Description : defines some utils global fonction
// Author      : cedric.bresson@artcoder.com
///////////////////////////////////////////////////////////////////////////////
#ifndef __Utils_h__
#define __Utils_h__

#include <stdio.h>
#include <stdarg.h>
#include <string>


void ShowAboutWindow();
	// Description : show an about window with different informations (version, ...)

std::string FormatString(const char* pBuffer, ...);
	// Description : like printf, but returns a string (usefull for debug string)

#endif //__Utils_h__
