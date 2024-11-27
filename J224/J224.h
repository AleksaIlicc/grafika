
// J224.h : main header file for the J224 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CJ224App:
// See J224.cpp for the implementation of this class
//

class CJ224App : public CWinApp
{
public:
	CJ224App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CJ224App theApp;
