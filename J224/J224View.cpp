
// J224View.cpp : implementation of the CJ224View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "J224.h"
#endif

#include "J224Doc.h"
#include "J224View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define _USE_MATH_DEFINES
#include <cmath>

float toRad(float angle) {
	return angle * M_PI / 180;
}

// CJ224View

IMPLEMENT_DYNCREATE(CJ224View, CView)

BEGIN_MESSAGE_MAP(CJ224View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CJ224View construction/destruction

CJ224View::CJ224View() noexcept
{
	// TODO: add construction code here

}

CJ224View::~CJ224View()
{
}

BOOL CJ224View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CJ224View drawing

void CJ224View::Translate(CDC* pDC, float x, float y) {
	XFORM xForm{
		1, 0,
		0, 1,
		x, y
	};

	pDC->ModifyWorldTransform(&xForm, MWT_LEFTMULTIPLY);
}

void CJ224View::Rotate(CDC* pDC, float angle) {
	float angleRad = toRad(angle);
	XFORM xForm{
		cos(angleRad), sin(angleRad),
		-sin(angleRad), cos(angleRad),
		0, 0
	};

	pDC->ModifyWorldTransform(&xForm, MWT_LEFTMULTIPLY);
}

void CJ224View::LoadIdentity(CDC* pDC) {
	XFORM xForm = {
		1, 0,
		0, 1,
		0, 0
	};

	pDC->SetWorldTransform(&xForm);
}

void CJ224View::OnDraw(CDC* pDC)
{
	CJ224Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	int oldGM = pDC->SetGraphicsMode(GM_ADVANCED);
	
	DrawScene(pDC);
	if(save)
		SaveGraph(pDC);

	pDC->SetGraphicsMode(oldGM);
}
// w - visina, l - duzina
void CJ224View::DrawItem(CDC* pDC, int w, int l, float min, float max, float v25, float v75, COLORREF fill, CString label)
{
	//pDC->Rectangle(0, 0, l, w);
	CPen pen(PS_SOLID, 2, RGB(0, 0, 0));
	CPen* oldPen = pDC->SelectObject(&pen);

	pDC->MoveTo((min - this->min) / (this->max - this->min) * l, 0);
	pDC->LineTo((min - this->min) / (this->max - this->min) * l, w);
	pDC->MoveTo((max - this->min) / (this->max - this->min) * l , 0);
	pDC->LineTo((max - this->min) / (this->max - this->min) * l, w);

	pDC->MoveTo((min - this->min) / (this->max - this->min) * l, w / 2);
	pDC->LineTo((v25 - this->min) / (this->max - this->min) * l, w / 2);
				
	pDC->MoveTo((v75 - this->min) / (this->max - this->min) * l, w / 2);
	pDC->LineTo((max - this->min) / (this->max - this->min) * l, w / 2);
	
	CBrush brush(fill);
	CBrush* oldBrush = pDC->SelectObject(&brush);
	pDC->Rectangle((v25 - this->min) / (this->max - this->min) * l, 0, (v75 - this->min) / (this->max - this->min) * l, w);
	pDC->SelectObject(oldBrush); 
	pDC->SelectObject(oldPen);

	CFont font;
	font.CreateFont(20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _T("Times New Roman"));
	pDC->SelectObject(&font);
	pDC->SetTextAlign(TA_RIGHT);
	pDC->TextOutW(0 - w / 2, 0, label);
}

void CJ224View::DrawChart(CDC* pDC, Item* items, int n) {

	Translate(pDC, 100, 300);
	Rotate(pDC, -90);

	int height = 20;
	int width = 200;
	int rectHeight = 20 + n * height + n * (40 - height);
	XFORM transform;
	pDC->GetWorldTransform(&transform);

	Rotate(pDC, 90);
	CFont font;
	font.CreateFontW(20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _T("Times New Roman"));
	pDC->SelectObject(&font);
	pDC->SetTextAlign(TA_RIGHT);
	CString txt; 
	txt.Format(_T("%.1f"), this->min);
	pDC->TextOutW(-10, -10, txt);

	txt.Format(_T("%.1f"), this->max);
	pDC->TextOutW(-10, -width - 10, txt);

	pDC->SetWorldTransform(&transform);

	CFont boldFont;
	boldFont.CreateFontW(20, 0, 0, 0, 700, 0, 0, 0, 0, 0, 0, 0, 0, _T("Times New Roman"));
	pDC->SelectObject(&boldFont);
	pDC->SetTextAlign(TA_CENTER);
	pDC->TextOutW(width / 2, -20, _T("Y-vrednosti"));

	Rotate(pDC, 90);
	CFont boldBiggerFont;
	boldBiggerFont.CreateFontW(30, 0, 0, 0, 700, 0, 0, 0, 0, 0, 0, 0, 0, _T("Times New Roman"));
	pDC->SelectObject(&boldBiggerFont);
	pDC->SetTextAlign(TA_CENTER);
	pDC->TextOutW(rectHeight/2, -width-30, _T("JUN2 2024"));
	pDC->SetWorldTransform(&transform);


	pDC->Rectangle(0, 0, width, rectHeight);
	Translate(pDC, 0, 20);
	for (int i = 0; i < n; i++)
	{
		DrawItem(pDC, height, 200, items[i].min, items[i].max, items[i].v25, items[i].v75, RGB(255, 0, 0), items[i].label);
		Translate(pDC, 0, 40); 
	}
}

void CJ224View::DrawScene(CDC* pDC)
{
	Item* items = new Item[10];	
	items[0].set(2, 5, 8, 14, CString("Pera"));
	items[1].set(4, 15, 18, 25, CString("Mika"));
	items[2].set(1, 10, 12, 20, CString("Laza"));
	items[3].set(1, 4, 15, 25, CString("Boban"));

	DrawChart(pDC, items, 4);
}

void CJ224View::SaveGraph(CDC* pDC)
{
	int width = 800;   
	int height = 600;  

	CDC memDC;
	memDC.CreateCompatibleDC(pDC);

	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(pDC, width, height);
	memDC.SelectObject(&bitmap);

	memDC.FillSolidRect(0, 0, width, height, RGB(255, 255, 255));
	int oldGM = memDC.SetGraphicsMode(GM_ADVANCED);
	DrawScene(&memDC);
	memDC.SetGraphicsMode(oldGM);
	DImage img(bitmap);
	img.Save(_T("Graph.bmp")); 

	pDC->BitBlt(0, 0, width, height, &memDC, 0, 0, SRCCOPY);
}


// CJ224View printing

BOOL CJ224View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CJ224View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CJ224View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CJ224View diagnostics

#ifdef _DEBUG
void CJ224View::AssertValid() const
{
	CView::AssertValid();
}

void CJ224View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CJ224Doc* CJ224View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CJ224Doc)));
	return (CJ224Doc*)m_pDocument;
}
#endif //_DEBUG


// CJ224View message handlers


void CJ224View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == 'S') {
		save = true;
	}
	Invalidate();
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
