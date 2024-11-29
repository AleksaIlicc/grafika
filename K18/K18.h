
// K18.h : main header file for the K18 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CK18App:
// See K18.cpp for the implementation of this class
//

class CK18App : public CWinApp
{
public:
	CK18App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CK18App theApp;
