
// GDI2.h : main header file for the GDI2 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CGDI2App:
// See GDI2.cpp for the implementation of this class
//

class CGDI2App : public CWinApp
{
public:
	CGDI2App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGDI2App theApp;
