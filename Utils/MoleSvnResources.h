///////////////////////////////////////////////////////////////////////////////
// Application : MoleSVN
// Package     : Utils
// File        : MoleSvnResources.h
// Description : defines BResources wrapper
// Author      : cedric.bresson@artcoder.com
///////////////////////////////////////////////////////////////////////////////
#ifndef __MoleSvnResources_h__
#define __MoleSvnResources_h__

#include "../Config.h"
#include "../UI/MoleSvnIcons.h"

class MoleSvnResources
{
public:
	// -- Life-cycle ----------------------------------------------------------
	MoleSvnResources(BFile* pFile);
		// Description : constructor
		
	~MoleSvnResources();
		// Description : destructor

	// -- Services ------------------------------------------------------------
	void LoadIcon(type_code type, MoleSvnIcons iconId, BBitmap** pDest);
		// Description : load an icon resource
		// Arguments   : - type : 'ICON' or 'MICN'
		//               - iconId : icon id 
		//               - pDest : bitmap destination
		// Remarks     : don't forget to delete pDest after user !!!
		
private:
	BResources* m_pResources;
		// Description : resources
};

#endif //__MoleSvnResources_h__
