///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : Utils
// File        : MoleSvnResources.cpp
// Description : implements BResources wrapper
// Author      : cedric.bresson@artcoder.com
///////////////////////////////////////////////////////////////////////////////

#include "MoleSvnResources.h"
#include "Exception.h"
#include "../MoleSvnAddon.h"

using namespace std;

MoleSvnResources::MoleSvnResources(BFile* pFile)
:m_pResources(NULL)
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));
	m_pResources = new BResources();
	if( m_pResources->SetTo(pFile) != B_OK)
	{
		delete m_pResources;
		m_pResources = NULL;
		throw MoleSvnException(string("cannot initialize resources"));	
	}
}
		
MoleSvnResources::~MoleSvnResources()
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));
	if(m_pResources)
	{
		delete m_pResources;
	}
}

///////////////////////////////////////////////////////////////////////////
// -- Services
///////////////////////////////////////////////////////////////////////////
void MoleSvnResources::LoadIcon(type_code type, MoleSvnIcons iconId, BBitmap** pDest)
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));
	// Check if the resource exits
	if(!m_pResources->HasResource(type, iconId))
	//if(!m_pResources->HasResource('BBMP', iconId))
	{
//		throw ResourceNotFoundException(iconId);
	}

	// Load icons from ressource file
	size_t len;
	const void *data = m_pResources->LoadResource(type, iconId, &len);
	//const void *data = m_pResources->LoadResource('BBMP', iconId, &len);
	BRect dim(0,0,15,15);
	if(type == 'ICON')
	{
		dim.right = 31;
		dim.bottom = 31;	
	}
	
	*pDest = new BBitmap(dim, B_CMAP8);
	(*pDest)->SetBits(data, len, 0, B_CMAP8);
	//*pDest = new BBitmap(dim, B_RGB32);
	//(*pDest)->SetBits(data, len, 0, B_RGB32);
}


