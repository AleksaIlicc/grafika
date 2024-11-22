
// K15View.h : interface of the CK15View class
//

#pragma once
#include "DImage.h"


class CK15View : public CView
{
protected: // create from serialization only
	CK15View() noexcept;
	DECLARE_DYNCREATE(CK15View)
	int x_translate=400;
	int y_translate=400;
	int rotAngle = 0;
	bool mouthOpen = true;
	int mouthAngle = 15;
	DImage background;
// Attributes
public:
	CK15Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	void Translate(CDC* pDC, float x, float y);
	void Rotate(CDC* pDC, float angle);
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	void DrawPacman(CDC* pDC, CRect rect, float angle);




	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CK15View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // debug version in K15View.cpp
inline CK15Doc* CK15View::GetDocument() const
   { return reinterpret_cast<CK15Doc*>(m_pDocument); }
#endif

