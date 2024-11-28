
// K14.h : main header file for the K14 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CK14App:
// See K14.cpp for the implementation of this class
//

class CK14App : public CWinApp
{
public:
	CK14App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CK14App theApp;
