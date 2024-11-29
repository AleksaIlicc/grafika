
// K23.h : main header file for the K23 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CK23App:
// See K23.cpp for the implementation of this class
//

class CK23App : public CWinApp
{
public:
	CK23App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CK23App theApp;
