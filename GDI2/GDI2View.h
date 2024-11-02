
// GDI2View.h : interface of the CGDI2View class
//

#pragma once


class CGDI2View : public CView
{
private:
	bool showGrid = false;
	void ToggleGrid();
	int dim = 500;
	int gridItem = 25;
	int gridNumber = dim / gridItem;
private:
	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	void DrawPolygon(CDC* pDC, POINT points[], int numOfPoints, COLORREF penColor, COLORREF brushColor);
	void DrawCactusPot(CDC* pDC);
	void DrawBackground(CDC* pDC, COLORREF color);
	void DrawGrid(CDC* pDC);

protected: // create from serialization only
	CGDI2View() noexcept;
	DECLARE_DYNCREATE(CGDI2View)

// Attributes
public:
	CGDI2Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);
	// overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CGDI2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in GDI2View.cpp
inline CGDI2Doc* CGDI2View::GetDocument() const
   { return reinterpret_cast<CGDI2Doc*>(m_pDocument); }
#endif

