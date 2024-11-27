
// K13View.cpp : implementation of the CK13View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "K13.h"
#endif

#include "K13Doc.h"
#include "K13View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define _USE_MATH_DEFINES
#include <cmath>

float toRad(float angle) {
	return angle * M_PI / 180;
}

// CK13View

IMPLEMENT_DYNCREATE(CK13View, CView)

BEGIN_MESSAGE_MAP(CK13View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CK13View construction/destruction

CK13View::CK13View() noexcept
{
	// TODO: add construction code here
	sky.Load(_T("D:\\!Elfak\\Cetvrta Godina\\#Racunarska grafika\\lab-kolokvijum\\kolokvijumi\\2013\\sky.jpg"));
	bark.Load(_T("D:\\!Elfak\\Cetvrta Godina\\#Racunarska grafika\\lab-kolokvijum\\kolokvijumi\\2013\\bark.jpg"));
}

CK13View::~CK13View()
{
}

BOOL CK13View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CK13View drawing

void CK13View::OnDraw(CDC* pDC)
{
	CK13Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect clientRect;
	GetClientRect(&clientRect);

	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap memBitmap;
	memBitmap.CreateCompatibleBitmap(pDC, clientRect.Width(), clientRect.Height());

	memDC.SelectObject(&memBitmap);
	//memDC.FillSolidRect(&clientRect, RGB(255, 255, 255));
	
	sky.Draw(&memDC, CRect(0, 0, sky.Width(), sky.Height()/2), clientRect);

	int oldGM = memDC.SetGraphicsMode(GM_ADVANCED);
	int diameter = 320;
	DrawStar(&memDC, diameter);

	bark.Draw(&memDC, CRect(0, 0, bark.Width(), bark.Height()), CRect(clientRect.Width()*4/5, 0, clientRect.Width(),clientRect.Height()));

	CheckCollision(clientRect.Width() * 4 / 5, diameter/2);
	
	memDC.SetGraphicsMode(oldGM);

	pDC->BitBlt(0, 0, clientRect.Width(), clientRect.Height(), &memDC, 0, 0, SRCCOPY);
}

void CK13View::CheckCollision(int maxX, int radius){
	if (x_translate + 0.8 * radius >= maxX)
		collided = true;
}

void CK13View::DrawBlade(CDC* pDC, int size) {
	POINT points[3] = {
		{x_translate, y_translate},
		{x_translate + size, y_translate + size},
		{x_translate + 4 * size, y_translate}
	};
	POINT points2[3] = {
		{x_translate, y_translate},
		{x_translate + size, y_translate - size},
		{x_translate + 4 * size, y_translate}
	};

	CPen grayPen(PS_SOLID, 1, RGB(224, 224, 224));
	CBrush darkGrayBrush(RGB(192, 192, 192));
	CBrush lightGrayBrush(RGB(224, 224, 224));

	CPen* oldPen = pDC->SelectObject(&grayPen);
	CBrush* oldBrush = pDC->SelectObject(&darkGrayBrush);
	pDC->Polygon(points, 3);

	pDC->SelectObject(&lightGrayBrush);
	pDC->Polygon(points2, 3);

	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);

	CFont font;
	font.CreateFont(0.7 * size, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _T("Monotype Corsiva"));
	pDC->SelectObject(&font);
	pDC->SetTextColor(RGB(255, 255, 255));
	pDC->SetBkMode(TRANSPARENT);
	pDC->TextOutW(x_translate + size / 1.6 - 1, y_translate - size / 2.8 - 1, _T("Shuricane"));

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->TextOutW(x_translate + size / 1.6, y_translate - size / 2.8, _T("Shuricane"));
	pDC->SetBkMode(OPAQUE);
}


void CK13View::DrawStar(CDC* pDC, int size) {
	XFORM oldTransform;
	GetWorldTransform(pDC->m_hDC, &oldTransform);

	for (int i = 0; i < 4; i++) {
		Translate(pDC, x_translate, y_translate);
		Rotate(pDC, 90*i + angle);
		Translate(pDC, -x_translate, -y_translate);

		DrawBlade(pDC, size/8); 
		SetWorldTransform(pDC->m_hDC, &oldTransform);
	}
}


void CK13View::Translate(CDC* pDC, float x, float y) {
	XFORM xForm{
		1, 0,
		0, 1,
		x, y
	};

	pDC->ModifyWorldTransform(&xForm, MWT_LEFTMULTIPLY);
}

void CK13View::Rotate(CDC* pDC, float angle) {
	float angleRad = toRad(angle);
	XFORM xForm{
		cos(angleRad), sin(angleRad),
		-sin(angleRad), cos(angleRad),
		0, 0
	};

	pDC->ModifyWorldTransform(&xForm, MWT_LEFTMULTIPLY);
}

// CK13View printing

BOOL CK13View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CK13View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CK13View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CK13View diagnostics

#ifdef _DEBUG
void CK13View::AssertValid() const
{
	CView::AssertValid();
}

void CK13View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CK13Doc* CK13View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CK13Doc)));
	return (CK13Doc*)m_pDocument;
}
#endif //_DEBUG


// CK13View message handlers


void CK13View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if(!collided){
		if (nChar == 'W') {
			x_translate += 20;
			angle += 10;
		}

		Invalidate();
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


BOOL CK13View::OnEraseBkgnd(CDC* pDC)
{
	return true;
}
