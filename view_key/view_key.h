
// view_key.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CviewkeyApp:
// See view_key.cpp for the implementation of this class
//

class CviewkeyApp : public CWinApp
{
public:
	CviewkeyApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CviewkeyApp theApp;
