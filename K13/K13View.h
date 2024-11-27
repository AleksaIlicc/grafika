
// K13View.h : interface of the CK13View class
//

#pragma once
#include "DImage.h"

class CK13View : public CView
{
public:
	int x_translate = 100;
	int y_translate = 200;
	int angle = 0;
	bool collided = false;
	DImage sky, bark;
protected: // create from serialization only
	CK13View() noexcept;
	DECLARE_DYNCREATE(CK13View)

// Attributes
public:
	CK13Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	void CheckCollision(int maxX, int diameter);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	void DrawBlade(CDC* pDC, int size);
	void DrawStar(CDC* pDC, int size);
	void Translate(CDC* pDC, float x, float y);
	void Rotate(CDC* pDC, float angle);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CK13View();
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
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // debug version in K13View.cpp
inline CK13Doc* CK13View::GetDocument() const
   { return reinterpret_cast<CK13Doc*>(m_pDocument); }
#endif

