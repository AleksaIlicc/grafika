
// GDI2View.cpp : implementation of the CGDI2View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "GDI2.h"
#endif

#include "GDI2Doc.h"
#include "GDI2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define ID_VIEW_TOGGLEGRID 32771

// CGDI2View

IMPLEMENT_DYNCREATE(CGDI2View, CView)

BEGIN_MESSAGE_MAP(CGDI2View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CGDI2View construction/destruction

void CGDI2View::ToggleGrid()
{
	this->showGrid = !this->showGrid;
	Invalidate();
}

CGDI2View::CGDI2View() noexcept
{
	// TODO: add construction code here

}

CGDI2View::~CGDI2View()
{
}

BOOL CGDI2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CGDI2View drawing

void CGDI2View::DrawGrid(CDC* pDC) {
	CBrush gridBrush(RGB(225, 225, 225));

	for (int x = 0; x < this->dim; x += this->gridItem) {
		for (int y = 0; y < this->dim; y += this->gridItem) {
			pDC->FillRect(CRect(x, y, x + 1, this->dim), &gridBrush);
			pDC->FillRect(CRect(0, y, this->dim, y + 1), &gridBrush);
		}
	}
}

void CGDI2View::OnDraw(CDC* pDC)
{
	CGDI2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	COLORREF lightBlue = RGB(150, 200, 250);
	
	DrawBackground(pDC, lightBlue);

	DrawCactusPot(pDC);
	

	if (showGrid) {
		DrawGrid(pDC);
	}
}


void CGDI2View::DrawCactusPot(CDC* pDC) {
	COLORREF brownColor = RGB(220, 79, 19);
	COLORREF blackColor = RGB(0, 0, 0);

	POINT bottomPart[4] = {
		{ 8.4 * gridItem, 20 * gridItem},
		{ 11.6 * gridItem, 20 * gridItem},
		{ 12 * gridItem, 18 * gridItem },
		{ 8 * gridItem, 18 * gridItem }
	};

	DrawPolygon(pDC, bottomPart, 4, blackColor, brownColor);

	POINT topPart[4] = {
		{ 7.6 * gridItem, 17.3 * gridItem},
		{ 7.6 * gridItem, 18 * gridItem},
		{ 12.4 * gridItem, 18 * gridItem },
		{ 12.4 * gridItem, 17.3 * gridItem}
	};

	DrawPolygon(pDC, topPart, 4, blackColor, brownColor); // alternativa pDC->Rectangle(7.6 * gridItem, 17.3 * gridItem, 12.4 * gridItem, 18 * gridItem); 
}

void CGDI2View::DrawBackground(CDC* pDC, COLORREF color)
{
	POINT background[4] = {
		{0,0},
		{this->dim - 1,0},
		{this->dim - 1, this->dim - 1},
		{0, this->dim - 1}
	};

	DrawPolygon(pDC, background, 4, color, color);
}


void CGDI2View::DrawPolygon(CDC* pDC, POINT points[], int numOfPoints, COLORREF penColor, COLORREF brushColor)
{
	CPen newPen(PS_SOLID, 1, penColor);
	CBrush newBrush(brushColor);

	CPen* prevPen = pDC->SelectObject(&newPen);
	CBrush* prevBrush = pDC->SelectObject(&newBrush);

	pDC->Polygon(points, numOfPoints);

	pDC->SelectObject(prevBrush);
	pDC->SelectObject(prevPen);

}

void CGDI2View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (nChar == 'G' || nChar == 'g') {
		ToggleGrid();
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

// CGDI2View printing

BOOL CGDI2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGDI2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGDI2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CGDI2View diagnostics

#ifdef _DEBUG
void CGDI2View::AssertValid() const
{
	CView::AssertValid();
}

void CGDI2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGDI2Doc* CGDI2View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGDI2Doc)));
	return (CGDI2Doc*)m_pDocument;
}
#endif //_DEBUG


// CGDI2View message handlers
