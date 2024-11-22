
// GDI3View.cpp : implementation of the CGDI3View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "GDI3.h"
#endif

#include "GDI3Doc.h"
#include "GDI3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "DImage.h"

#define M_PI 3.14159265358979323846
#define RAD(x) (x/180.0f * M_PI)
// CGDI3View

IMPLEMENT_DYNCREATE(CGDI3View, CView)

BEGIN_MESSAGE_MAP(CGDI3View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CGDI3View construction/destruction

CGDI3View::CGDI3View() noexcept
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			DImage image;
			CString path;
			path.Format(L"D:\\!Elfak\\Cetvrta Godina\\#Racunarska grafika\\lab\\lab 3\\%d.bmp", i * 3 + j + 1);
			image.Load(path);
			this->pieces[i][j].Load(path);
		}
	}
}

CGDI3View::~CGDI3View()
{
}

BOOL CGDI3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CGDI3View drawing

void CGDI3View::OnDraw(CDC* pDC)
{
	CGDI3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect rect;
	GetClientRect(&rect);

	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(pDC);
	CBitmap bm; 
	bm.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());

	memDC->SelectObject(&bm);
	CBrush brush(RGB(255, 255, 255));
	CRect gridRect(0, 0, this->dim, this->dim);
	memDC->FillRect(gridRect, &brush);

	if (showGrid) {
		DrawGrid(memDC);
	}

	int oldGM = memDC->SetGraphicsMode(GM_ADVANCED);

	
#pragma region Drawings
	this->pieces[0][0].Draw(memDC, CRect(0, 0, 256, 256), CRect(1*gridItem, 1 * gridItem, 19/3.0f * gridItem, 19 / 3.0f * gridItem));
	this->pieces[0][1].Draw(memDC, CRect(0, 0, 256, 256), CRect(19 / 3.0f * gridItem, 1 * gridItem, 2 * 19 / 3.0f * gridItem, 19 / 3.0f * gridItem));
	this->pieces[0][2].Draw(memDC, CRect(0, 0, 256, 256), CRect(2* 19 / 3.0f * gridItem, 1 * gridItem, 19 * gridItem, 19 / 3.0f * gridItem));
#pragma endregion

	memDC->SetGraphicsMode(oldGM);

	pDC->BitBlt(0, 0, gridRect.Width(), gridRect.Height(), memDC, 0, 0, SRCCOPY);

	memDC->DeleteDC(); 
}

void CGDI3View::DrawGrid(CDC* pDC) {
	CBrush gridBrush(RGB(225, 225, 225));

	for (int x = 0; x < this->dim; x += this->gridItem) {
		for (int y = 0; y < this->dim; y += this->gridItem) {
			pDC->FillRect(CRect(x, y, x + 1, this->dim), &gridBrush);
			pDC->FillRect(CRect(0, y, this->dim, y + 1), &gridBrush);
		}
	}
}

void CGDI3View::Translate(CDC* pDC, float x, float y, bool rightMultiply)
{
	XFORM matrix =
	{
		1, 0,
		0, 1,
		x, y
	};

	pDC->ModifyWorldTransform(&matrix, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

void CGDI3View::Scale(CDC* pDC, float x, float y, bool rightMultiply)
{
	XFORM matrix =
	{
		x, 0,
		0, y
	};

	pDC->ModifyWorldTransform(&matrix, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

void CGDI3View::Rotate(CDC* pDC, float angle, bool rightMultiply)
{
	XFORM matrix =
	{
		cos(RAD(angle)), sin((RAD(angle))),
		-sin(RAD(angle)), cos(RAD(angle))
	};

	pDC->ModifyWorldTransform(&matrix, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

void CGDI3View::Mirror(CDC* pDC, bool x, bool y, bool rightMultiply)
{
	XFORM matrix =
	{
		x ? -1 : 1, 0,
		0, y ? -1 : 1,
	};

	pDC->ModifyWorldTransform(&matrix, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

void CGDI3View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	switch (nChar)
	{
	case 'G':
	case 'g':
		this->showGrid = !this->showGrid;
		break;
	}
	Invalidate();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

// CGDI3View printing

BOOL CGDI3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGDI3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGDI3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CGDI3View diagnostics

#ifdef _DEBUG
void CGDI3View::AssertValid() const
{
	CView::AssertValid();
}

void CGDI3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGDI3Doc* CGDI3View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGDI3Doc)));
	return (CGDI3Doc*)m_pDocument;
}
#endif //_DEBUG


// CGDI3View message handlers
