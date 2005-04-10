///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : Utils
// File        : Exception.h
// Description : extends basic std exceptions
// Author      : cedric.bresson@artcoder.com
///////////////////////////////////////////////////////////////////////////////
#ifndef __Exception_h__
#define __Exception_h__

#include <string>
#include <stdexcept>

// Description : based class for all molesvn exceptions 
class MoleSvnException : public std::runtime_error
{
public:
	MoleSvnException(const std::string& strMessage)
	:std::runtime_error(strMessage){};
};

// Description : exception when a file doesn't exit
class FileNotFound : public MoleSvnException
{
public:
	FileNotFound(const std::string& strMsg):MoleSvnException(strMsg){};
};

#endif //__Exception_h__
