
// K15View.cpp : implementation of the CK15View class
//


#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "K15.h"
#endif

#include "K15Doc.h"
#include "K15View.h"
#define _USE_MATH_DEFINES
#include <cmath>

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

float toRad(float angle) {
	return angle * M_PI / 180;
}

// CK15View

IMPLEMENT_DYNCREATE(CK15View, CView)

BEGIN_MESSAGE_MAP(CK15View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CK15View construction/destruction

CK15View::CK15View() noexcept
{
	// TODO: add construction code here
	background.Load(CString("D:\\!Elfak\\Cetvrta Godina\\#Racunarska grafika\\lab-kolokvijum\\kolokvijumi\\2015\\blue.png"));
	//PlaySound(L"C:\\Users\\aleks\\Desktop\\PACMAN PHONK.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

CK15View::~CK15View()
{
}

BOOL CK15View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CK15View drawing

void CK15View::Translate(CDC* pDC, float x, float y) {
	XFORM xForm{
		1, 0,
		0, 1,
		x, y
	};

	pDC->ModifyWorldTransform(&xForm, MWT_LEFTMULTIPLY);
}

void CK15View::Rotate(CDC* pDC, float angle) {
	XFORM xForm{
		cos(angle), sin(angle),
		-sin(angle), cos(angle),
		0, 0
	};

	pDC->ModifyWorldTransform(&xForm, MWT_LEFTMULTIPLY);
}

void CK15View::OnDraw(CDC* pDC)
{
	CK15Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect ghostRect(100, 120, 196, 216);
	CRect pacmanRect(x_translate - 50, y_translate - 50, x_translate + 50, y_translate + 50);


	CRect clientRect;
	GetClientRect(&clientRect);

	CDC memDC;
	memDC.CreateCompatibleDC(pDC);

	CBitmap memBitmap;
	memBitmap.CreateCompatibleBitmap(pDC, clientRect.Width(), clientRect.Height());

	memDC.SelectObject(&memBitmap);

    background.Draw(&memDC, CRect(0, 0, background.Width(), background.Height()), clientRect); 

	CheckCollision(ghostRect, pacmanRect);

	int oldGM = memDC.SetGraphicsMode(GM_ADVANCED);

	XFORM oldTransform;
	memDC.GetWorldTransform(&oldTransform);
	
	Translate(&memDC, x_translate, y_translate);
	Rotate(&memDC, toRad(rotAngle));
	Translate(&memDC, -x_translate, -y_translate);

	DrawPacman(&memDC, pacmanRect, mouthAngle);

	memDC.SetWorldTransform(&oldTransform);

	DrawGhost(&memDC, ghostRect);

	memDC.SetGraphicsMode(oldGM);

	if (collided) {
		CFont font;
		font.CreateFont(72, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _T("Arial"));
		CFont* oldFont = memDC.SelectObject(&font);
		COLORREF oldTxtClr = memDC.SetTextColor(RGB(255, 255, 255));
		memDC.SetBkMode(TRANSPARENT);
		memDC.TextOutW(clientRect.CenterPoint().x - 140, clientRect.CenterPoint().y - 36, _T("The End!"));
		memDC.SetTextColor(oldTxtClr);
	}
	
	pDC->BitBlt(0, 0, clientRect.Width(), clientRect.Height(), &memDC, 0, 0, SRCCOPY);

	memDC.DeleteDC();
}

void CK15View::CheckCollision(CRect ghostRect, CRect pacmanRect) {
	int ghostR = ghostRect.Width() / 2;
	int pacmanR = pacmanRect.Width() / 2;

	CPoint ghostCenter = ghostRect.CenterPoint();
	CPoint pacmanCenter = pacmanRect.CenterPoint();

	float distance = sqrt(pow(ghostCenter.x - pacmanCenter.x, 2) + pow(ghostCenter.y - pacmanCenter.y, 2));
	if (distance < ghostR + pacmanR){
		collided = true;
		Invalidate();
	}
}

void CK15View::DrawGhost(CDC* pDC, CRect rect) {
	CPoint center = rect.CenterPoint();
	int rectWidth = rect.Width();
	int r = rectWidth / 2;
	int smallerR = r / 6;

	pDC->BeginPath();

	pDC->MoveTo(center.x - r, center.y + r); 
	pDC->LineTo(center.x - r, center.y);     

	POINT startPoint = { center.x - r, center.y };
	POINT endPoint = { center.x + r, center.y };  
	pDC->SetArcDirection(AD_CLOCKWISE);
	pDC->ArcTo(rect, startPoint, endPoint);

	pDC->LineTo(center.x + r, center.y + r);

	for (int i = 6; i >= 0; i--) {
		CRect rct(center.x - r - smallerR + i * 2 * smallerR, center.y + r - smallerR, center.x - r + smallerR + i * 2 * smallerR, center.y + r + smallerR);
		if (i == 6) {
			pDC->SetArcDirection(AD_CLOCKWISE); 
			POINT start = { rct.CenterPoint().x, rct.CenterPoint().y + smallerR };
			POINT end = { rct.CenterPoint().x - smallerR, rct.CenterPoint().y };
			pDC->ArcTo(rct, start, end);
		}
		else if (i == 0) {
			pDC->SetArcDirection(AD_CLOCKWISE); 
			POINT start = { rct.CenterPoint().x + smallerR, rct.CenterPoint().y };
			POINT end = { rct.CenterPoint().x , rct.CenterPoint().y + smallerR };
			pDC->ArcTo(rct, start, end);
		}
		else if (i % 2 == 0) {
			pDC->SetArcDirection(AD_CLOCKWISE);
			POINT start = { rct.CenterPoint().x + smallerR, rct.CenterPoint().y };
			POINT end = { rct.CenterPoint().x - smallerR, rct.CenterPoint().y };
			pDC->ArcTo(rct, start, end);
		}
		else {
			pDC->SetArcDirection(AD_COUNTERCLOCKWISE);
			POINT start = { rct.CenterPoint().x + smallerR, rct.CenterPoint().y };
			POINT end = { rct.CenterPoint().x - smallerR, rct.CenterPoint().y };
			pDC->ArcTo(rct, start, end);
		}
	}

	pDC->EndPath();

	CBrush redBrush(RGB(255, 0, 0));
	CBrush* oldBrush = pDC->SelectObject(&redBrush);

	pDC->StrokeAndFillPath();

	CRect whiteEyeRect(center.x - 12, center.y - 12, center.x + 12, center.y + 12);
	whiteEyeRect.OffsetRect(-5, 0);
	CBrush whiteBrush(RGB(255, 255, 255));
	pDC->SelectObject(&whiteBrush);
	whiteEyeRect.OffsetRect(4, 0);
	pDC->Ellipse(whiteEyeRect);
	whiteEyeRect.OffsetRect(30, 0);
	pDC->Ellipse(whiteEyeRect);

	CRect blueEyeRect(center.x - 6, center.y - 6, center.x + 6, center.y + 6);
	CBrush blueBrush(RGB(0, 0, 255));
	pDC->SelectObject(&blueBrush);

	blueEyeRect.OffsetRect(3, 0);
	pDC->Ellipse(blueEyeRect);
	blueEyeRect.OffsetRect(29, 0);
	pDC->Ellipse(blueEyeRect);

	pDC->SelectObject(oldBrush);
}


void CK15View::DrawPacman(CDC* pDC, CRect rect, float angle) {
	CPen blackPen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen* pOldPen = pDC->SelectObject(&blackPen);

	CBrush yellowBrush(RGB(255, 255, 0));
	CBrush* pOldBrush = pDC->SelectObject(&yellowBrush);
	int rectDim = rect.Height();
	int R = rectDim / 2;
	float angleInRad = toRad(angle);
	POINT start = {
		rect.CenterPoint().x + R * cos(-angleInRad),
		rect.CenterPoint().y + R * sin(-angleInRad)
	};
	POINT end = {
		rect.CenterPoint().x + R * cos(+angleInRad),
		rect.CenterPoint().y + R * sin(+angleInRad)
	};

	pDC->Pie(rect, start, end);

	CBrush blackBrush(RGB(0, 0, 0));
	pDC->SelectObject(&blackBrush);


	CRect eyeRect(rect.left + 2.0 / 3 * rectDim, rect.top + 1.0 / 5 * rectDim, 12 + rect.left + 2.0 / 3 * rectDim, 12 + rect.top + 1.0 / 5 * rectDim);
	pDC->Ellipse(eyeRect);
	
	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);
}


// CK15View printing

BOOL CK15View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CK15View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CK15View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CK15View diagnostics

#ifdef _DEBUG
void CK15View::AssertValid() const
{
	CView::AssertValid();
}

void CK15View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CK15Doc* CK15View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CK15Doc)));
	return (CK15Doc*)m_pDocument;
}
#endif //_DEBUG


// CK15View message handlers


void CK15View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!collided)
	{
		if (nChar==VK_LEFT || nChar==VK_RIGHT || nChar==VK_UP || nChar==VK_DOWN)
			mouthOpen = !mouthOpen;

		if (mouthOpen)
			mouthAngle = 15;
		else
			mouthAngle = 0;

		switch (nChar)
		{
		case VK_LEFT:
			x_translate -= 10;
			rotAngle = 180;
			break;
		case VK_RIGHT:
			x_translate += 10;
			rotAngle = 0;
			break;
		case VK_UP:
			y_translate -= 10;
			rotAngle = 270;
			break;
		case VK_DOWN:
			y_translate += 10;
			rotAngle = 90;
			break;
		default:
			break;
		}
	Invalidate();
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


BOOL CK15View::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return true;
}
