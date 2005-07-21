///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : Utils
// File        : Exception.h
// Description : extends basic std exceptions
// Author      : cedric.bresson@artcoder.com
///////////////////////////////////////////////////////////////////////////////
#ifndef __Exception_h__
#define __Exception_h__

#include "Utils.h"
#include "../UI/MoleSvnIcons.h"

#include <string>
#include <stdexcept>

// Description : based class for all molesvn exceptions 
class MoleSvnException : public std::runtime_error
{
public:
	MoleSvnException(const std::string& strMessage)
	:std::runtime_error(strMessage){};
};

///////////////////////////////////////////////////////////////////////////////
// -- Resource
///////////////////////////////////////////////////////////////////////////////
// Description : exception when a resource doesn't exit
class ResourceNotFoundException : public MoleSvnException
{
public:
	ResourceNotFoundException(MoleSvnIcons iconId):MoleSvnException(FormatString("resource id (%d) doesn't identify an existing image", iconId)){};
};

///////////////////////////////////////////////////////////////////////////////
// -- Memory
///////////////////////////////////////////////////////////////////////////////

// Description : exception when a file doesn't exit
class ImageException : public MoleSvnException
{
public:
	ImageException(image_id id):MoleSvnException(FormatString("%d doesn't identify an existing image", id)){};
};


///////////////////////////////////////////////////////////////////////////////
// -- File
///////////////////////////////////////////////////////////////////////////////

// Description : exception when a file doesn't exit
class FileNotFound : public MoleSvnException
{
public:
	FileNotFound(const std::string& strMsg):MoleSvnException(std::string("file not found : ") + strMsg){};
};

#endif //__Exception_h__
