
// K23View.cpp : implementation of the CK23View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "K23.h"
#endif

#include "K23Doc.h"
#include "K23View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define _USE_MATH_DEFINES
#include <cmath>

float toRad(float angle) {
	return angle * M_PI / 180;
}

// CK23View

IMPLEMENT_DYNCREATE(CK23View, CView)

BEGIN_MESSAGE_MAP(CK23View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CK23View construction/destruction

CK23View::CK23View() noexcept
{
	glava		= new DImage();
	nadkolenica = new DImage(); 
	nadlaktica	= new DImage();
	podkolenica	= new DImage();
	podlaktica	= new DImage();
	saka		= new DImage();
	stopalo		= new DImage();
	telo		= new DImage();
	pozadina	= new DImage();
	glava->Load(_T("D:\\!Elfak\\Cetvrta Godina\\#Racunarska grafika\\lab-kolokvijum\\kolokvijumi\\2023\\glava.png"));
	nadkolenica->Load(_T("D:\\!Elfak\\Cetvrta Godina\\#Racunarska grafika\\lab-kolokvijum\\kolokvijumi\\2023\\nadkolenica.png"));
	nadlaktica->Load(_T("D:\\!Elfak\\Cetvrta Godina\\#Racunarska grafika\\lab-kolokvijum\\kolokvijumi\\2023\\nadlaktica.png"));
	podkolenica->Load(_T("D:\\!Elfak\\Cetvrta Godina\\#Racunarska grafika\\lab-kolokvijum\\kolokvijumi\\2023\\podkolenica.png"));
	podlaktica->Load(_T("D:\\!Elfak\\Cetvrta Godina\\#Racunarska grafika\\lab-kolokvijum\\kolokvijumi\\2023\\podlaktica.png"));
	saka->Load(_T("D:\\!Elfak\\Cetvrta Godina\\#Racunarska grafika\\lab-kolokvijum\\kolokvijumi\\2023\\saka.png"));
	stopalo->Load(_T("D:\\!Elfak\\Cetvrta Godina\\#Racunarska grafika\\lab-kolokvijum\\kolokvijumi\\2023\\stopalo.png"));
	telo->Load(_T("D:\\!Elfak\\Cetvrta Godina\\#Racunarska grafika\\lab-kolokvijum\\kolokvijumi\\2023\\telo.png"));
	pozadina->Load(_T("D:\\!Elfak\\Cetvrta Godina\\#Racunarska grafika\\lab-kolokvijum\\kolokvijumi\\2023\\pozadina.jpg"));
}

CK23View::~CK23View()
{
	delete glava		;
	delete nadkolenica ;
	delete nadlaktica	;
	delete podkolenica ;
	delete podlaktica	;
	delete saka		;
	delete stopalo		;
	delete telo		;
	delete pozadina;
}

BOOL CK23View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CK23View drawing


void CK23View::Translate(CDC* pDC, float x, float y, bool rightMultiply) {
	XFORM xForm{
		1, 0,
		0, 1,
		x, y
	};

	pDC->ModifyWorldTransform(&xForm, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

void CK23View::Rotate(CDC* pDC, float angle, bool rightMultiply) {
	float angleRad = toRad(angle);
	XFORM xForm{
		cos(angleRad), sin(angleRad),
		-sin(angleRad), cos(angleRad),
		0, 0
	};

	pDC->ModifyWorldTransform(&xForm, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

void CK23View::Scale(CDC* pDC, float x, float y, bool rightMultiply)
{
	XFORM matrix =
	{
		x, 0,
		0, y
	};

	pDC->ModifyWorldTransform(&matrix, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

void CK23View::OnDraw(CDC* pDC)
{
	CK23Doc* pDoc = GetDocument();
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

	int oldGM = memDC->SetGraphicsMode(GM_ADVANCED);

	DrawBackground(memDC);

	XFORM oldT;
	memDC->GetWorldTransform(&oldT);

	Translate(memDC, clientRect.CenterPoint().x - 100, clientRect.CenterPoint().y - 200);
	Translate(memDC, 100, 200);
	Scale(memDC, robotScale, robotScale);
	Rotate(memDC, -robotRot);
	Translate(memDC, -100, -200);
	DrawRobot(memDC);
	memDC->SetWorldTransform(&oldT);

	memDC->SetGraphicsMode(oldGM);
	
	pDC->BitBlt(0, 0, clientRect.Width(), clientRect.Height(), memDC, 0, 0, SRCCOPY);

	memDC->DeleteDC();
}

void CK23View::DrawHalf(CDC* pDC)
{
	XFORM oldTransform;
	pDC->GetWorldTransform(&oldTransform);

	DrawImgTransparent(pDC, telo);

	Translate(pDC, 25 - 35, 65 - 35);
	Translate(pDC, 35, 35);
	Rotate(pDC, nadlakticaRot);
	Translate(pDC, -35, -35);
	DrawImgTransparent(pDC, nadlaktica); 
	
	Translate(pDC, 22 - 30, 167 - 33);
	Translate(pDC, 30, 33);
	Rotate(pDC, podlakticaRot);
	Translate(pDC, -30, -33);
	DrawImgTransparent(pDC, podlaktica);

	Translate(pDC, 30 - 25, 140 - 3);
	Translate(pDC, 25, 3);
	Rotate(pDC, sakaRot);
	Translate(pDC, -25, -3); 
	DrawImgTransparent(pDC, saka);

	pDC->SetWorldTransform(&oldTransform);

	Translate(pDC, 61 - 29, 262 - 20);
	DrawImgTransparent(pDC, nadkolenica);

	Translate(pDC, 30 - 25, 184 - 20);
	DrawImgTransparent(pDC, podkolenica);

	Translate(pDC, 25 - 20, 248 - 16);
	DrawImgTransparent(pDC, stopalo);

	pDC->SetWorldTransform(&oldTransform);
}

void CK23View::DrawHead(CDC* pDC) 
{
	Translate(pDC, 50, -100);
	DrawImgTransparent(pDC, glava);
	Translate(pDC, -50, 100);
}


void CK23View::DrawRobot(CDC* pDC) 
{
	DrawHead(pDC);
	XFORM oldTransform;
	pDC->GetWorldTransform(&oldTransform);
	DrawHalf(pDC);
	Translate(pDC, 200, 0);
	Scale(pDC, -1, 1);
	DrawHalf(pDC);
	pDC->SetWorldTransform(&oldTransform);
}

void CK23View::DrawBackground(CDC* pDC)
{
	CRect clientRect;
	GetClientRect(&clientRect);
	pozadina->Draw(pDC, CRect(0, 0, pozadina->Width(), pozadina->Height()), CRect(0, 0, clientRect.Width(), clientRect.Height()));
}


void CK23View::DrawImgTransparent(CDC* pDC, DImage* pImage)
{
	CBitmap bmpImage;
	CBitmap bmpMask;

	CDC srcDC, destDC;
	srcDC.CreateCompatibleDC(pDC);
	destDC.CreateCompatibleDC(pDC);

	bmpImage.CreateCompatibleBitmap(pDC, pImage->Width(), pImage->Height());
	bmpImage.SetBitmapBits(pImage->Width() * pImage->Height() * pImage->BPP(), pImage->GetDIBBits());

	bmpMask.CreateBitmap(pImage->Width(), pImage->Height(), 1, 1, NULL);

	CBitmap* oldSrcBmp = srcDC.SelectObject(&bmpImage);
	CBitmap* oldDestBmp = destDC.SelectObject(&bmpMask);

	CRect imageRect(0, 0, pImage->Width(), pImage->Height());
	pImage->Draw(&srcDC, imageRect, imageRect);

	COLORREF colorToRemove = srcDC.GetPixel(0, 0);
	COLORREF oldBackground = srcDC.SetBkColor(colorToRemove);

	destDC.BitBlt(0, 0, pImage->Width(), pImage->Height(), &srcDC, 0, 0, SRCCOPY);

	COLORREF oldForeground = srcDC.SetTextColor(RGB(255, 255, 255));
	srcDC.SetBkColor(RGB(0, 0, 0));

	srcDC.BitBlt(0, 0, pImage->Width(), pImage->Height(), &destDC, 0, 0, SRCAND);

	pDC->BitBlt(0, 0, pImage->Width(), pImage->Height(), &destDC, 0, 0, SRCAND);
	pDC->BitBlt(0, 0, pImage->Width(), pImage->Height(), &srcDC, 0, 0, SRCPAINT);

	destDC.SetTextColor(oldForeground);
	srcDC.SetBkColor(oldBackground);

	srcDC.SelectObject(oldSrcBmp);
	destDC.SelectObject(oldDestBmp);

	srcDC.DeleteDC();
	destDC.DeleteDC();
}

// CK23View printing

BOOL CK23View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CK23View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CK23View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CK23View diagnostics

#ifdef _DEBUG
void CK23View::AssertValid() const
{
	CView::AssertValid();
}

void CK23View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CK23Doc* CK23View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CK23Doc)));
	return (CK23Doc*)m_pDocument;
}
#endif //_DEBUG


// CK23View message handlers


BOOL CK23View::OnEraseBkgnd(CDC* pDC)
{
	return true;
}


void CK23View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == 'A') {
		if (sakaRot > -10)
			sakaRot -= 10;
	}
	else if (nChar == 'S') {
		if (sakaRot < 30)
			sakaRot += 10;
	}	
	else if (nChar == 'D') {
		if (podlakticaRot > -10)
			podlakticaRot -= 10;
	}
	else if (nChar == 'F') {
		if (podlakticaRot < 80)
			podlakticaRot += 10;
	}
	else if (nChar == 'G') {
		if (nadlakticaRot > -10)
			nadlakticaRot -= 10;
	}
	else if (nChar == 'H') {
		if (nadlakticaRot < 90)
			nadlakticaRot += 10;
	}
	else if (nChar == '1') {
		robotScale += 0.03;
		robotRot -= 10;
	}
	else if (nChar == '2') {
		robotScale -= 0.01;
		robotRot += 10;
	}
	Invalidate();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
