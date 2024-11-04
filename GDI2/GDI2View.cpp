
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

#define M_PI 3.14159265358979323846

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

CGDI2View::CGDI2View() noexcept
{
	CString pathOfCactusPartMF("D:\\!Elfak\\Cetvrta Godina\\#Racunarska grafika\\lab\\lab 2\\cactus_part.emf");
	CString pathOfCactusPartLightMF("D:\\!Elfak\\Cetvrta Godina\\#Racunarska grafika\\lab\\lab 2\\cactus_part_light.emf");

	this->cactusPartMF = GetEnhMetaFile(pathOfCactusPartMF);
	this->cactusPartLightMF = GetEnhMetaFile(pathOfCactusPartLightMF);
}

CGDI2View::~CGDI2View()
{
	DeleteEnhMetaFile(this->cactusPartMF);
	DeleteEnhMetaFile(this->cactusPartLightMF);
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

	int prevGM = SetGraphicsMode(pDC->m_hDC, GM_ADVANCED);

	COLORREF lightBlue = RGB(150, 200, 250);

	DrawBackground(pDC, lightBlue);
	
	DrawCactus(pDC);

	DrawCactusPot(pDC);
	
	if (showGrid) {
		DrawGrid(pDC);
	}

	SetGraphicsMode(pDC->m_hDC, prevGM);
}

void CGDI2View::DrawCactus(CDC* pDC) {

	COLORREF darkGreenColor = RGB(0, 204, 0);
	COLORREF blackColor = RGB(0, 0, 0);
	
	XFORM oldTransform;
	GetWorldTransform(pDC->m_hDC, &oldTransform);

	RotateAroundPoint(pDC, { 10 * gridItem, 17 * gridItem }, this->wholeCactusRotAngle);

	// ceo kaktus

	XFORM wholeCactusTransform;
	GetWorldTransform(pDC->m_hDC, &wholeCactusTransform);
	
	// ceo kaktus / prvi iznad

	Translate(pDC, 10 * gridItem, 17 * gridItem);
	Scale(pDC, 2.5, 3);

	pDC->PlayMetaFile(this->cactusPartLightMF, CRect(POINT{ - gridItem / 2, - gridItem }, SIZE{ gridItem, gridItem }));

	SetWorldTransform(pDC->m_hDC, &wholeCactusTransform);

	// ceo kaktus / tri spojena

	Translate(pDC, 10 * gridItem, 17 * gridItem);
	Scale(pDC, 0.8, 1);

	pDC->PlayMetaFile(this->cactusPartMF, CRect(POINT{ - gridItem / 2, - 6 * gridItem }, SIZE{ gridItem, 3 * gridItem }));

 	SetWorldTransform(pDC->m_hDC, &wholeCactusTransform);

	Translate(pDC, 10 * gridItem, 14 * gridItem);
	Rotate(pDC, M_PI / 4);
	Scale(pDC, 0.8, 1);

	pDC->PlayMetaFile(this->cactusPartMF, CRect(POINT{ - gridItem / 2, - 3 * gridItem }, SIZE{ gridItem, 3 * gridItem }));

	SetWorldTransform(pDC->m_hDC, &wholeCactusTransform);

	Translate(pDC, 10 * gridItem, 14 * gridItem);
	Rotate(pDC, - M_PI / 4);
 	Scale(pDC, 0.8, 1);

	pDC->PlayMetaFile(this->cactusPartMF, CRect(POINT{ - gridItem / 2, - 3 * gridItem }, SIZE{ gridItem, 3 * gridItem }));

	SetWorldTransform(pDC->m_hDC, &wholeCactusTransform);

	// ceo kaktus / levo / gore

	Translate(pDC, 7.9 * gridItem, 11.8 * gridItem);
	Scale(pDC, 1.6, 2.8);

	pDC->PlayMetaFile(this->cactusPartMF, CRect(POINT{ - gridItem / 2, - gridItem }, SIZE{ gridItem, gridItem }));

	SetWorldTransform(pDC->m_hDC, &wholeCactusTransform);

	// ceo kaktus / levo / gore / gore

	Translate(pDC, 7.9 * gridItem, 8.8 * gridItem);
	Scale(pDC, 2.4, 2.75);

	pDC->PlayMetaFile(this->cactusPartMF, CRect(POINT{ - gridItem / 2, - gridItem }, SIZE{ gridItem, gridItem }));

	SetWorldTransform(pDC->m_hDC, &wholeCactusTransform);

	// ceo kaktus / levo / levo

	Translate(pDC, 7.9 * gridItem, 11.8 * gridItem);
	Rotate(pDC, - M_PI / 2);
	Scale(pDC, 1.55, 1);

	pDC->PlayMetaFile(this->cactusPartMF, CRect(POINT{ -gridItem / 2, - 3 * gridItem }, SIZE{ gridItem, 3 * gridItem }));

	SetWorldTransform(pDC->m_hDC, &wholeCactusTransform);

	// mali kaktus

	RotateAroundPoint(pDC, { (int)(12.1 * gridItem), (int)(11.9 * gridItem) }, this->smallCactusRotAngle);

	Translate(pDC, 12 * gridItem, 11.9 * gridItem);
	Scale(pDC, 1.55, 2.85);

	pDC->PlayMetaFile(this->cactusPartLightMF, CRect(POINT{ - gridItem / 2, - gridItem }, SIZE{ gridItem, gridItem }));

	SetWorldTransform(pDC->m_hDC, &wholeCactusTransform);

	DrawCircle(pDC, { 10 * gridItem, 14 * gridItem }, gridItem / 2, blackColor, darkGreenColor);
	DrawCircle(pDC, { (int)(7.9 * gridItem), (int)(8.9 * gridItem) }, gridItem / 2, blackColor, darkGreenColor);
	DrawCircle(pDC, { (int)(7.9 * gridItem), (int)(11.9 * gridItem) }, gridItem / 2, blackColor, darkGreenColor);
	DrawCircle(pDC, { (int)(12 * gridItem), (int)(11.9 * gridItem) }, gridItem / 2, blackColor, darkGreenColor);
	DrawCircle(pDC, { (int)(15.1 * gridItem), (int)(11.9 * gridItem) }, gridItem / 2, blackColor, darkGreenColor);
	
	SetWorldTransform(pDC->m_hDC, &oldTransform);

	DrawCircle(pDC, { 10 * gridItem, 17 * gridItem }, gridItem / 2, blackColor, darkGreenColor);
}

void CGDI2View::Scale(CDC* pDC, float x, float y) {
	XFORM xForm{
		x, 0,
		0, y,
		0, 0
	};

	pDC->ModifyWorldTransform(&xForm, MWT_LEFTMULTIPLY);
}

void CGDI2View::Translate(CDC *pDC, float x, float y){
	XFORM xForm{
		1, 0,
		0, 1,
		x, y
	};

	pDC->ModifyWorldTransform(&xForm, MWT_LEFTMULTIPLY);
}

void CGDI2View::Rotate(CDC* pDC, float angle) {
	XFORM xForm{
		cos(angle), sin(angle),
		-sin(angle), cos(angle),
		0, 0
	};

	pDC->ModifyWorldTransform(&xForm, MWT_LEFTMULTIPLY);
}

void CGDI2View::RotateAroundPoint(CDC* pDC, POINT point, float angle)
{
	Translate(pDC, point.x, point.y);
	Rotate(pDC, angle);
	Translate(pDC, -point.x, -point.y);
}


void CGDI2View::DrawCactusPot(CDC* pDC) {
	COLORREF brownColor = RGB(200, 79, 19);
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

void CGDI2View::DrawCircle(CDC* pDC, POINT center, int r, COLORREF penColor, COLORREF brushColor) {
	CPen pen(PS_SOLID, 1, penColor);
	CBrush brush(brushColor);

	CPen* prevPen = pDC->SelectObject(&pen);
	CBrush* prevBrush = pDC->SelectObject(&brush);

	pDC->Ellipse(center.x - r, center.y - r, center.x + r, center.y + r);

	pDC->SelectObject(prevBrush);
	pDC->SelectObject(prevPen);
}

void CGDI2View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	switch (nChar)
	{
	case 'G':
	case 'g':
		this->showGrid = !this->showGrid;
		break;
	case VK_LEFT:
		this->smallCactusRotAngle -= M_PI / 6;
		break;
	case VK_RIGHT:
		this->smallCactusRotAngle += M_PI / 6;
		break;
	case 'A':
	case 'a':
		this->wholeCactusRotAngle -= M_PI / 6;
		break;
	case 'D':
	case 'd':
		this->wholeCactusRotAngle += M_PI / 6;
		break;
	default:
		break;
	}
	Invalidate();

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
