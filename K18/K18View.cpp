
// K18View.cpp : implementation of the CK18View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "K18.h"
#endif

#include "K18Doc.h"
#include "K18View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define _USE_MATH_DEFINES
#include <cmath>

float toRad(float angle) {
	return angle * M_PI / 180;
}

// CK18View

IMPLEMENT_DYNCREATE(CK18View, CView)

BEGIN_MESSAGE_MAP(CK18View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CK18View construction/destruction

CK18View::CK18View() noexcept
{
	// TODO: add construction code here
	bager = new DImage();
	arm1 = new DImage();
	arm2 = new DImage();
	pozadina = new DImage();
	bager->Load(_T("D:\\!Elfak\\Cetvrta Godina\\#Racunarska grafika\\lab-kolokvijum\\kolokvijumi\\2018\\bager.png"));
	arm1->Load(_T("D:\\!Elfak\\Cetvrta Godina\\#Racunarska grafika\\lab-kolokvijum\\kolokvijumi\\2018\\arm1.png"));
	arm2->Load(_T("D:\\!Elfak\\Cetvrta Godina\\#Racunarska grafika\\lab-kolokvijum\\kolokvijumi\\2018\\arm2.png"));
	pozadina->Load(_T("D:\\!Elfak\\Cetvrta Godina\\#Racunarska grafika\\lab-kolokvijum\\kolokvijumi\\2018\\pozadina.png"));
	viljuska = GetEnhMetaFileW(_T("D:\\!Elfak\\Cetvrta Godina\\#Racunarska grafika\\lab-kolokvijum\\kolokvijumi\\2018\\viljuska.emf"));
	ENHMETAHEADER header;
	GetEnhMetaFileHeader(viljuska, sizeof(ENHMETAHEADER), &header);
	viljuskaHeader.width = header.rclBounds.right - header.rclBounds.left;
	viljuskaHeader.height = header.rclBounds.bottom - header.rclBounds.top;
}

CK18View::~CK18View()
{
	delete bager;
	delete arm1;
	delete arm2;
	delete pozadina;
	DeleteEnhMetaFile(viljuska);
}

BOOL CK18View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CK18View drawing

void CK18View::Translate(CDC* pDC, float x, float y, bool rightMultiply) {
	XFORM xForm{
		1, 0,
		0, 1,
		x, y
	};

	pDC->ModifyWorldTransform(&xForm, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

void CK18View::Rotate(CDC* pDC, float angle, bool rightMultiply) {
	float angleRad = toRad(angle);
	XFORM xForm{
		cos(angleRad), sin(angleRad),
		-sin(angleRad), cos(angleRad),
		0, 0
	};

	pDC->ModifyWorldTransform(&xForm, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

void CK18View::Scale(CDC* pDC, float x, float y, bool rightMultiply)
{
	XFORM matrix =
	{
		x, 0,
		0, y
	};

	pDC->ModifyWorldTransform(&matrix, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}


void CK18View::OnDraw(CDC* pDC)
{
	CK18Doc* pDoc = GetDocument();
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

	int oldMode = memDC->SetGraphicsMode(GM_ADVANCED);

	DrawExcavator(memDC);

	memDC->SetGraphicsMode(oldMode);

	pDC->BitBlt(0, 0, clientRect.Width(), clientRect.Height(), memDC, 0, 0, SRCCOPY);

	memDC->DeleteDC();
}

void CK18View::DrawArm1(CDC* pDC)
{
	CRect clientRect;
	GetClientRect(&clientRect);
	Translate(pDC, clientRect.Width() * 0.75, clientRect.Height() * 0.75);
	Translate(pDC, 58, 61);
	Rotate(pDC, -90 - arm1Angle);
	Translate(pDC, -58, -61);
	DrawImgTransparent(pDC, arm1);
}

void CK18View::DrawArm2(CDC* pDC)
{
	Translate(pDC, 309, 61);
	Rotate(pDC, 270 + arm2Angle);
	Translate(pDC, -36, -40);
	DrawImgTransparent(pDC, arm2);
}

void CK18View::DrawFork(CDC* pDC)
{
	Translate(pDC, 272, 40);
	Rotate(pDC, -90 - viljuskaAngle);
	Scale(pDC, 2.5, 2.5);
	Translate(pDC, -14, -20);
	PlayEnhMetaFile(pDC->m_hDC, viljuska, CRect(0, 0, viljuskaHeader.width, viljuskaHeader.height));
}

void CK18View::DrawBody(CDC* pDC)
{
	XFORM t;
	pDC->GetWorldTransform(&t);
	CRect clientRect;
	GetClientRect(&clientRect);
	Translate(pDC, clientRect.Width() * 0.75, clientRect.Height() * 0.55);
	DrawImgTransparent(pDC, bager);
	pDC->SetWorldTransform(&t);
}


void CK18View::DrawBackground(CDC* pDC)
{
	CRect clientRect;
	GetClientRect(&clientRect);

	pozadina->Draw(pDC, CRect(0, 0, pozadina->Width(), pozadina->Height()), CRect(0, 0, clientRect.Width(), clientRect.Height()));
}

void CK18View::DrawExcavator(CDC* pDC)
{
	XFORM oldTransform, t2;
	pDC->GetWorldTransform(&oldTransform);
	DrawBackground(pDC);
	Translate(pDC, -x_translate, 0);
	DrawBody(pDC);
	DrawArm1(pDC);
	DrawArm2(pDC);
	DrawFork(pDC);
	pDC->SetWorldTransform(&oldTransform);
}

void CK18View::DrawImgTransparent(CDC* pDC, DImage* pImage)
{
	unsigned char* pix = pImage->GetDIBBits(); 
	//int bpp = pImage->BPP(); 
	int width = pImage->Width(); 
	int height = pImage->Height(); 

	//int bytesPerRow = ((width * bpp + 3) / 4) * 4
	//int bytesPerRow = width * bpp;
	//unsigned char* firstPixel = pix + (height - 1) * bytesPerRow;

	BYTE blue = pix[0];
	BYTE green = pix[1]; 
	BYTE red = pix[2]; 
	COLORREF bgColor = RGB(red, green, blue);

	pImage->DrawTransparent(pDC, CRect(0, 0, width, height), CRect(0, 0, width, height), bgColor);
}

// CK18View printing

BOOL CK18View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CK18View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CK18View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CK18View diagnostics

#ifdef _DEBUG
void CK18View::AssertValid() const
{
	CView::AssertValid();
}

void CK18View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CK18Doc* CK18View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CK18Doc)));
	return (CK18Doc*)m_pDocument;
}
#endif //_DEBUG


// CK18View message handlers


BOOL CK18View::OnEraseBkgnd(CDC* pDC)
{
	return true;
}


void CK18View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == '1') {
		arm1Angle += 10;
	}
	else if (nChar == '2') {
		arm1Angle -= 10;
	}
	else if (nChar == '3') {
		arm2Angle += 10;
	}
	else if (nChar == '4') {
		arm2Angle -= 10;
	}
	else if (nChar == '5') {
		viljuskaAngle += 10;
	}
	else if (nChar == '6') {
		viljuskaAngle -= 10;
	}
	else if (nChar == VK_LEFT) {
		x_translate += 10;
	}
	else if (nChar == VK_RIGHT) {
		x_translate -= 10;
	}

	Invalidate();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
