
// K23View.h : interface of the CK23View class
//

#pragma once
#include "DImage.h"

class CK23View : public CView
{
private:
	DImage* glava, * nadkolenica, * nadlaktica, * podkolenica, * podlaktica, * saka, * stopalo, * telo, * pozadina;
	int nadlakticaRot = 0;
	int podlakticaRot = 0;
	int sakaRot = 0;
	int robotRot = 0;
	float robotScale = 0.8;
protected: // create from serialization only
	CK23View() noexcept;
	DECLARE_DYNCREATE(CK23View)

// Attributes
public:
	CK23Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	void Translate(CDC* pDC, float x, float y, bool rightMultiply = false);
	void Rotate(CDC* pDC, float angle, bool rightMultiply = false);
	void Scale(CDC* pDC, float x, float y, bool rightMultiply = false);
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	void DrawHalf(CDC* pDC);
	void DrawHead(CDC* pDC);
	void DrawRobot(CDC* pDC);
	void DrawBackground(CDC* pDC);
	void DrawImgTransparent(CDC* pDC, DImage* pImage);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CK23View();
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

#ifndef _DEBUG  // debug version in K23View.cpp
inline CK23Doc* CK23View::GetDocument() const
   { return reinterpret_cast<CK23Doc*>(m_pDocument); }
#endif

