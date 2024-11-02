
// GDIView.cpp : implementation of the CGDIView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "GDI.h"
#endif

#include "GDIDoc.h"
#include "GDIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <corecrt_math_defines.h>
#define ID_VIEW_TOGGLEGRID 32771

double DegreeToRad(double angle) {
	return angle * M_PI / 180;
}

// CGDIView

IMPLEMENT_DYNCREATE(CGDIView, CView)

BEGIN_MESSAGE_MAP(CGDIView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN() 
	ON_COMMAND(ID_VIEW_TOGGLEGRID, &CGDIView::ToggleGrid) 
END_MESSAGE_MAP()
// CGDIView construction/destruction

CGDIView::CGDIView() noexcept
{
	// TODO: add construction code here

}

CGDIView::~CGDIView()
{
}

BOOL CGDIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CGDIView drawing

// functions 
void menjanjePozicijeKoordinatnogSistema(CDC* pDC, HWND handle) {
	CRect rect;
	GetClientRect(handle, &rect);
	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowExt(100, -100);
	pDC->SetViewportExt(rect.right, rect.bottom);
	pDC->SetWindowOrg(-50, 50);
	pDC->Rectangle(-20, 20, 20, -20);
}

void crtanjeSmajlija(CDC* pDC) {
	pDC->SetPixel(10, 10, RGB(255, 0, 0));
	pDC->SetPixel(20, 10, RGB(255, 0, 0));

	pDC->SetPixel(8, 14, RGB(255, 0, 0));
	pDC->SetPixel(22, 14, RGB(255, 0, 0));

	pDC->SetPixel(7, 13, RGB(255, 0, 0));
	pDC->SetPixel(23, 13, RGB(255, 0, 0));
	for (int i = 9; i <= 21; i++)
		pDC->SetPixel(i, 15, RGB(255, 0, 0));
}

void crtanjeTrouglova(CDC* pDC) {
	POINT* arr = new POINT[10];
	arr[0].x = 55;
	arr[0].y = 50;

	arr[1].x = 95;
	arr[1].y = 120;

	arr[2].x = 92;
	arr[2].y = 30;

	// prazan trougao
	pDC->Polygon(arr, 3);

	for (int i = 0; i < 3; i++)
		arr[i].x += 200;

	CBrush brush(RGB(0, 0, 0));
	CBrush* pOldBrush = pDC->SelectObject(&brush);

	// pun trougao
	pDC->Polygon(arr, 3);

	pDC->SelectObject(pOldBrush);

	delete[] arr;
}

void manuelnoCrtanjeLab1(CDC* pDC) {
	double X = 500.0;
	double Y = 500.0;

	CPen pen(PS_SOLID, 5, RGB(255, 0, 255));
	CBrush brush(RGB(255, 255, 0));

	CPen* pOldPen = pDC->SelectObject(&pen);
	CBrush* pOldBrush = pDC->SelectObject(&brush);

	CPoint points[3] = { CPoint(0,0), CPoint(X * 2 / 3, 0), CPoint(X * 1 / 3, Y * 1 / 2) };
	pDC->Polygon(points, 3);

	pDC->SelectObject(pOldBrush);

	points[0] = CPoint(X * 1 / 3, Y * 1 / 2);
	points[1] = CPoint(X * 2 / 3, Y);
	points[2] = CPoint(0, Y);
	pDC->Polygon(points, 3);
}

	/* funkcije koje rade, mogu se ubaciti u OnDraw metodu */
	//menjanjePozicijeKoordinatnogSistema(pDC, m_hWnd);
	//crtanjeSmajlija(pDC);
	//crtanjeTrouglova(pDC);
	//manuelnoCrtanjeLab1(pDC);

void CGDIView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (nChar == 'M' || nChar == 'm') { 
		ToggleGrid();  
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags); 
}

void CGDIView::ToggleGrid() {
	showGrid = !showGrid;  
	Invalidate(); 
}

void DrawGrid(CDC* pDC, const double dim, const int gridItem) {
	CBrush gridBrush(RGB(150, 150, 150));  

	for (int x = 0; x < dim; x += gridItem) {
		for (int y = 0; y < dim; y += gridItem) {
			pDC->FillRect(CRect(x, y, x+1, dim), &gridBrush);
			pDC->FillRect(CRect(0, y, dim, y + 1), &gridBrush);  
		}
	}
}

void CGDIView::OnDraw(CDC* pDC)
{
	CGDIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	const int gridItem = 25;
	const int gridNumber = this->dim / gridItem;

	POINT yellowTrianglePoints[] = {
		{ gridItem, 4 * gridItem},
		{ 13 * gridItem, 4 * gridItem},
		{ 7 * gridItem, 10 * gridItem }
	};

	COLORREF pinkColor = RGB(255, 0, 255);
	COLORREF yellowColor = RGB(255, 255, 0);

	DrawPolygon(pDC, yellowTrianglePoints, 3, pinkColor, yellowColor);
	DrawRegularPolygonInTriangle(pDC, yellowTrianglePoints[0], yellowTrianglePoints[1], yellowTrianglePoints[2], 6, pinkColor, yellowColor);

	COLORREF purpleColor = RGB(155, 0, 155);

	POINT purpleTrianglePoints[] = {
		{ 13 * gridItem, 4 * gridItem},
		{ 19 * gridItem, 4 * gridItem},
		{ 16 * gridItem, 7 * gridItem}
	};

	DrawPolygon(pDC, purpleTrianglePoints, 3, pinkColor, purpleColor);
	DrawRegularPolygonInTriangle(pDC, purpleTrianglePoints[0], purpleTrianglePoints[1], purpleTrianglePoints[2], 5, pinkColor, purpleColor);

	COLORREF greenColor = RGB(0, 255, 0);

	POINT greenTrianglePoints[] = {
		{ 10 * gridItem, 7 * gridItem},
		{ 10 * gridItem, 13 * gridItem},
		{ 16 * gridItem, 13 * gridItem}
	};

	DrawPolygon(pDC, greenTrianglePoints, 3, pinkColor, greenColor);
	DrawRegularPolygonInTriangle(pDC, greenTrianglePoints[0], greenTrianglePoints[1], greenTrianglePoints[2], 7, pinkColor, greenColor);

	COLORREF orangeColor = RGB(255, 165, 0);

	POINT orangeTrianglePoints[] = {
		{ 7 * gridItem, 10 * gridItem},
		{ 10 * gridItem, 13 * gridItem},
		{ 10 * gridItem, 7 * gridItem}
	};

	DrawPolygon(pDC, orangeTrianglePoints, 3, pinkColor, orangeColor);
	DrawRegularPolygonInTriangle(pDC, orangeTrianglePoints[0], orangeTrianglePoints[1], orangeTrianglePoints[2], 4, pinkColor, orangeColor);

	COLORREF blueColor = RGB(0, 0, 255);
	
	POINT blueTrianglePoints[] = {
		{ 7 * gridItem, 10 * gridItem},
		{ 1 * gridItem, 16 * gridItem},
		{ 13 * gridItem, 16 * gridItem}
	};

	DrawPolygon(pDC, blueTrianglePoints, 3, pinkColor, blueColor, HS_HORIZONTAL);
	DrawRegularPolygonInTriangle(pDC, blueTrianglePoints[0], blueTrianglePoints[1], blueTrianglePoints[2], 8, pinkColor);

	COLORREF lightPinkColor = RGB(255, 182, 193);
	POINT lightPinkSquarePoints[] = {
		{ 13 * gridItem, 4 * gridItem},
		{ 10 * gridItem, 7 * gridItem},
		{ 13 * gridItem, 10 * gridItem},
		{ 16 * gridItem, 7 * gridItem}
	};

	DrawPolygon(pDC, lightPinkSquarePoints, 4, pinkColor, lightPinkColor);

	COLORREF redColor = RGB(255, 0, 0);

	POINT redSquarePoints[] = {
		{ 10 * gridItem, 13 * gridItem},
		{ 16 * gridItem, 13 * gridItem},
		{ 19 * gridItem, 16 * gridItem},
		{ 13 * gridItem, 16 * gridItem}
	};

	DrawPolygon(pDC, redSquarePoints, 4, pinkColor, redColor);

	if (showGrid) {
		DrawGrid(pDC, this->dim, gridItem);
	}

}

void CGDIView::DrawPolygon(CDC* pDC, POINT points[], int numOfPoints, COLORREF penColor, COLORREF brushColor)
{
	CPen newPen(PS_SOLID, 5, penColor);
	CBrush newBrush(brushColor);

	CPen* prevPen = pDC->SelectObject(&newPen);
	CBrush* prevBrush = pDC->SelectObject(&newBrush);

	pDC->Polygon(points, numOfPoints);

	pDC->SelectObject(prevBrush);
	pDC->SelectObject(prevPen);

}

void CGDIView::DrawPolygon(CDC* pDC, POINT points[], int numOfPoints, COLORREF penColor, COLORREF brushColor, int brushStyle)
{
    CPen newPen(PS_SOLID, 5, penColor);
    CBrush brush(brushStyle, brushColor);

    CPen* prevPen = pDC->SelectObject(&newPen);
    CBrush* prevBrush = pDC->SelectObject(&brush);

    pDC->Polygon(points, numOfPoints);

    pDC->SelectObject(prevBrush);
    pDC->SelectObject(prevPen);
}

double CGDIView::GetDistance(POINT a, POINT b)
{
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

void CGDIView::DrawRegularPolygonInTriangle(CDC* pDC, POINT a, POINT b, POINT c, int n, COLORREF penColor, COLORREF brushColor) {
	double aLen = GetDistance(c, b);
	double bLen = GetDistance(c, a);
	double cLen = GetDistance(a, b);
	double sum = cLen + bLen + aLen;
	double s = sum / 2;
	double r = sqrt(s * (s - aLen) * (s - bLen) * (s - cLen)) / s;

	double cx = (cLen * c.x + bLen * b.x + aLen * a.x) / sum + 0.5;
	double cy = (cLen * c.y + bLen * b.y + aLen * a.y) / sum + 0.5;

	CPen pen(PS_SOLID, 3, penColor);
	CPen* prevPen = pDC->SelectObject(&pen);
	CBrush* prevBrush = NULL;
	if (brushColor != NULL) {
		CBrush brush(brushColor);
		CBrush* prevBrush = pDC->SelectObject(&brush);	
	}
	
	DrawRegularPolygon(pDC, cx, cy, r / 2, n, 0);

	pDC->SelectObject(prevPen);
	pDC->SelectObject(prevBrush);
}

void CGDIView::DrawRegularPolygon(CDC* pDC, int cx, int cy, int r, int n, float rotAngle)
{
	double rotAngleRad = DegreeToRad(rotAngle);
	double angleChangeRad = 2 * M_PI / n;

	POINT* points = new POINT[n];

	for (auto i = 0; i < n; i++) {
		points[i].x = cx + r * cos(rotAngleRad);
		points[i].y = cy + r * sin(rotAngleRad);
		rotAngleRad += angleChangeRad;
	}
	pDC->Polygon(points, n);

	delete[] points;
}

// CGDIView printing

BOOL CGDIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGDIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGDIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CGDIView diagnostics

#ifdef _DEBUG
void CGDIView::AssertValid() const
{
	CView::AssertValid();
}

void CGDIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGDIDoc* CGDIView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGDIDoc)));
	return (CGDIDoc*)m_pDocument;
}
#endif //_DEBUG


// CGDIView message handlers
