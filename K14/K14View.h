
// K14View.h : interface of the CK14View class
//

#pragma once
#include "DImage.h"

class CK14View : public CView
{
public:
	int angle = 0;
public:
	DImage* wheel;
	HENHMETAFILE clio;
protected: // create from serialization only
	CK14View() noexcept;
	DECLARE_DYNCREATE(CK14View)

// Attributes
public:
	CK14Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	void DrawGround(CDC* pDC, float angle);
	void Translate(CDC* pDC, float x, float y, bool rightMultiply = false);
	void Rotate(CDC* pDC, float angle, bool rightMultiply = false);
	void Scale(CDC* pDC, float x, float y, bool rightMultiply = false);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CK14View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // debug version in K14View.cpp
inline CK14Doc* CK14View::GetDocument() const
   { return reinterpret_cast<CK14Doc*>(m_pDocument); }
#endif

