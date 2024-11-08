
// GDI3.h : main header file for the GDI3 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CGDI3App:
// See GDI3.cpp for the implementation of this class
//

class CGDI3App : public CWinApp
{
public:
	CGDI3App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGDI3App theApp;
