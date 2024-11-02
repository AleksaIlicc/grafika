
// GDIView.h : interface of the CGDIView class
//

#pragma once


class CGDIView : public CView
{
private:
	bool showGrid = false;
	int dim = 500;
public:
	afx_msg void ToggleGrid();
	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

protected: // create from serialization only
	CGDIView() noexcept;
	DECLARE_DYNCREATE(CGDIView)

// Attributes
public:
	CGDIDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	void DrawPolygon(CDC* pDC, POINT points[], int numOfPoints, COLORREF penColor, COLORREF brushColor);
	void DrawPolygon(CDC* pDC, POINT points[], int numOfPoints, COLORREF penColor, COLORREF brushColor, int brushStyle);
	double GetDistance(POINT a, POINT b);
	void DrawRegularPolygonInTriangle(CDC* pDC, POINT a, POINT b, POINT c, int n, COLORREF penColor, COLORREF brushColor = NULL);
	void DrawRegularPolygon(CDC* pDC, int cx, int cy, int r, int n, float rotAngle);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CGDIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in GDIView.cpp
inline CGDIDoc* CGDIView::GetDocument() const
   { return reinterpret_cast<CGDIDoc*>(m_pDocument); }
#endif

