
// K18View.h : interface of the CK18View class
//

#pragma once
#include "DImage.h"

class CK18View : public CView
{
private:
	DImage* bager;
	DImage* arm1;
	DImage* arm2;
	DImage* pozadina;
	HENHMETAFILE viljuska;
	struct {
		int width;
		int height;
	} viljuskaHeader;
	int viljuskaAngle = 0;
	int arm1Angle = 0;
	int arm2Angle = 0;
	int x_translate = 0;

protected: // create from serialization only
	CK18View() noexcept;
	DECLARE_DYNCREATE(CK18View)

// Attributes
public:
	CK18Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	void Translate(CDC* pDC, float x, float y, bool rightMultiply = false);
	void Rotate(CDC* pDC, float angle, bool rightMultiply = false);
	void Scale(CDC* pDC, float x, float y, bool rightMultiply = false);
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	void DrawArm1(CDC* pDC);
	void DrawArm2(CDC* pDC);
	void DrawFork(CDC* pDC);
	void DrawBody(CDC* pDC);
	void DrawImgTransparent(CDC* pDC, DImage* pImage);
	void DrawBackground(CDC* pDC);
	void DrawExcavator(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CK18View();
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

#ifndef _DEBUG  // debug version in K18View.cpp
inline CK18Doc* CK18View::GetDocument() const
   { return reinterpret_cast<CK18Doc*>(m_pDocument); }
#endif

