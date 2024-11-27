
// K13.h : main header file for the K13 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CK13App:
// See K13.cpp for the implementation of this class
//

class CK13App : public CWinApp
{
public:
	CK13App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CK13App theApp;
