#include "DImage.h"

class CGDI3View : public CView
{
public:
	bool showGrid = true;
	int dim = 500;
	int gridItem = 25;
	int gridCount = 20;
	DImage pieces[3][3];
public:
	void DrawGrid(CDC* pDC);
	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	void Translate(CDC* pDC, float x, float y, bool rightMultiply = false);
	void Scale(CDC* pDC, float x, float y, bool rightMultiply = false);
	void Rotate(CDC* pDC, float angle, bool rightMultiply = false);
	void Mirror(CDC* pDC, bool x, bool y, bool rightMultiply = false);

protected: // create from serialization only
	CGDI3View() noexcept;
	DECLARE_DYNCREATE(CGDI3View)

// Attributes
public:
	CGDI3Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CGDI3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in GDI3View.cpp
inline CGDI3Doc* CGDI3View::GetDocument() const
   { return reinterpret_cast<CGDI3Doc*>(m_pDocument); }
#endif
