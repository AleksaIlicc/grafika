
// K15.h : main header file for the K15 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CK15App:
// See K15.cpp for the implementation of this class
//

class CK15App : public CWinApp
{
public:
	CK15App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CK15App theApp;
