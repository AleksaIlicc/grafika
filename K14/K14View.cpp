
// K14View.cpp : implementation of the CK14View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "K14.h"
#endif

#include "K14Doc.h"
#include "K14View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define _USE_MATH_DEFINES
#include <cmath>

float toRad(float angle) {
	return angle * M_PI / 180;
}

// CK14View

IMPLEMENT_DYNCREATE(CK14View, CView)

BEGIN_MESSAGE_MAP(CK14View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CK14View construction/destruction

CK14View::CK14View() noexcept
{
	// TODO: add construction code here
	wheel = new DImage();
	wheel->Load(_T("D:\\!Elfak\\Cetvrta Godina\\#Racunarska grafika\\lab-kolokvijum\\kolokvijumi\\2014\\Materijali\\Wheel.png"));
	clio = GetEnhMetaFileW(_T("D:\\!Elfak\\Cetvrta Godina\\#Racunarska grafika\\lab-kolokvijum\\kolokvijumi\\2014\\Materijali\\clio.emf"));
}

CK14View::~CK14View()
{
	delete wheel;
	DeleteEnhMetaFile(clio);
}

BOOL CK14View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CK14View drawing

void CK14View::OnDraw(CDC* pDC)
{
	CK14Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect clientRect;
	GetClientRect(&clientRect);
	
	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(pDC);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, clientRect.Width(), clientRect.Height());

	memDC->SelectObject(&bmp);

	DrawGround(memDC, angle);

	int oldGM = memDC->SetGraphicsMode(GM_ADVANCED);
	
	memDC->SetGraphicsMode(oldGM);

	pDC->BitBlt(0, 0, clientRect.Width(), clientRect.Height(), memDC, 0, 0, SRCCOPY);

	memDC->DeleteDC();
}

void CK14View::DrawGround(CDC* pDC, float angle) 
{
	CRect clientRect;
	GetClientRect(&clientRect);
	pDC->FillSolidRect(clientRect, RGB(200, 220, 255));

	CPen brownPen(PS_SOLID, 3, RGB(100, 45, 37));
	CPen* oldPen = pDC->SelectObject(&brownPen);
	CBrush greenBrush(HS_FDIAGONAL, RGB(145,164,109));

	float calculatedHeight = clientRect.Width() * tan(toRad(angle));
	POINT points[3] = {
		{0, clientRect.Height()},
		{clientRect.Width(), clientRect.Height()},
		{clientRect.Width(), clientRect.Height() - calculatedHeight}
	};
	CBrush lightGreenBrush(RGB(227, 246, 191));
	CBrush* oldBrush = pDC->SelectObject(&lightGreenBrush);
	pDC->Polygon(points, 3);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SelectObject(&greenBrush);
	pDC->Polygon(points, 3);

	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);
}

void CK14View::Translate(CDC* pDC, float x, float y, bool rightMultiply) {
	XFORM xForm{
		1, 0,
		0, 1,
		x, y
	};

	pDC->ModifyWorldTransform(&xForm, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

void CK14View::Rotate(CDC* pDC, float angle, bool rightMultiply) {
	float angleRad = toRad(angle);
	XFORM xForm{
		cos(angleRad), sin(angleRad),
		-sin(angleRad), cos(angleRad),
		0, 0
	};

	pDC->ModifyWorldTransform(&xForm, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

void CK14View::Scale(CDC* pDC, float x, float y, bool rightMultiply)
{
	XFORM matrix =
	{
		x, 0,
		0, y
	};

	pDC->ModifyWorldTransform(&matrix, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

// CK14View printing

BOOL CK14View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CK14View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CK14View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CK14View diagnostics

#ifdef _DEBUG
void CK14View::AssertValid() const
{
	CView::AssertValid();
}

void CK14View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CK14Doc* CK14View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CK14Doc)));
	return (CK14Doc*)m_pDocument;
}
#endif //_DEBUG


// CK14View message handlers


BOOL CK14View::OnEraseBkgnd(CDC* pDC)
{
	return true;
}


void CK14View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_UP) {
		if(angle < 80)
			angle += 10;
	} else if (nChar == VK_DOWN) {
		if (angle > -10)
			angle -= 10;
	}
	Invalidate();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
