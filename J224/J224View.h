
// J224View.h : interface of the CJ224View class
//

#pragma once
#include "Item.h"

class CJ224View : public CView
{
public:
	float min = 1;
	float max = 25;
protected: // create from serialization only
	CJ224View() noexcept;
	DECLARE_DYNCREATE(CJ224View)

// Attributes
public:
	CJ224Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	void DrawItem(CDC* pDC, int w, int l, float min, float max, float v25, float v75, COLORREF fill, CString label);
	void DrawChart(CDC* pDC, Item* items, int n);
	void DrawScene(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	void Translate(CDC* pDC, float x, float y);
	void Rotate(CDC* pDC, float angle);
	void LoadIdentity(CDC* pDC);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CJ224View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in J224View.cpp
inline CJ224Doc* CJ224View::GetDocument() const
   { return reinterpret_cast<CJ224Doc*>(m_pDocument); }
#endif

