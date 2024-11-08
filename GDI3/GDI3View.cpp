
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


// CGDI3View

IMPLEMENT_DYNCREATE(CGDI3View, CView)

BEGIN_MESSAGE_MAP(CGDI3View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CGDI3View construction/destruction

CGDI3View::CGDI3View() noexcept
{
	// TODO: add construction code here

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

	CPen redPen(PS_SOLID, 1, RGB(255, 0, 0));
	CPen* oldPen = pDC->SelectObject(&redPen);

	CString path("D:\\!Elfak\\Cetvrta Godina\\#Racunarska grafika\\lab\\lab 3\\1.bmp");
	DImage img;
	img.Load(path);

	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	memDC.SelectObject(img.GetBitmap());

	COLORREF transparentColor = RGB(0, 255, 0);

	//CBitmap maskBitmap;
	//maskBitmap.CreateBitmap(img.Width(), img.Height(), 1, 1, NULL);

	//CDC maskDC;
	//maskDC.CreateCompatibleDC(pDC);
	//maskDC.SelectObject(&maskBitmap);

	//COLORREF oldBkColor = memDC.SetBkColor(transparentColor);

	//maskDC.BitBlt(0, 0, img.Width(), img.Height(), &memDC, 0, 0, SRCCOPY);

	//memDC.SetBkColor(oldBkColor);

	//pDC->BitBlt(0, 0, img.Width(), img.Height(), &memDC, 0, 0, SRCINVERT);
	//pDC->BitBlt(0, 0, img.Width(), img.Height(), &maskDC, 0, 0, SRCAND);
	//pDC->BitBlt(0, 0, img.Width(), img.Height(), &memDC, 0, 0, SRCINVERT);

	pDC->TransparentBlt(0, 0, img.Width(), img.Height(), &memDC, 0, 0, img.Width(), img.Height(), transparentColor);

	memDC.DeleteDC();
	//maskDC.DeleteDC();
}


//CString path("D:\\!Elfak\\Cetvrta Godina\\#Racunarska grafika\\lab\\lab 3\\1.bmp");
//DImage img;
//img.Load(path);
//
//CDC* memDC = new CDC();
//memDC->CreateCompatibleDC(pDC);
//memDC->SelectObject(img.GetBitmap());
//
//BitBlt(pDC->m_hDC, 0, 0, img.Width(), img.Height(), memDC->m_hDC, 0, 0, SRCCOPY);
//memDC->DeleteDC();

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
