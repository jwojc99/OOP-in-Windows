
// AnimView.cpp: implementation of the CAnimView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Anim.h"
#endif

#include "AnimDoc.h"
#include "AnimView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MIN 1
#define MAX 10
#define COLOR RGB(rand()%255, rand()%255,rand()%255) //do constructora losowy kolor


// CAnimView

IMPLEMENT_DYNCREATE(CAnimView, CView)

BEGIN_MESSAGE_MAP(CAnimView, CView)
	ON_COMMAND(ID_START_STOP, &CAnimView::OnStart)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_PLUS, &CAnimView::OnPlus)
	ON_UPDATE_COMMAND_UI(ID_PLUS, &CAnimView::OnUpdatePlus)
	ON_COMMAND(ID_MINUS, &CAnimView::OnMinus)
	ON_UPDATE_COMMAND_UI(ID_MINUS, &CAnimView::OnUpdateMinus)
	ON_WM_SIZE()
END_MESSAGE_MAP()

/////////////////////////////////////////
// CALLBACK Timer procedure
/////////////////////////////////////////
void CALLBACK ZfxTimerProc(
	HWND hWnd,			//handle of Cwnd that called SetTimer
	UINT nMsg,			//WM_TIMER
	UINT_PTR nIDEvent,	//timer identyfication
	DWORD dwTime		//system time
)
{
	::SendMessage(hWnd, WM_TIMER, 0, 0);
}
////////////////////////////////////////


//  CAnimView construction/destruction
CAnimView::CAnimView() noexcept
{
	//srand(time(NULL));
	m_nBalls = 0;
	m_bStart = FALSE;
	m_pRect = new CRect(0, 0, 0, 0);

	m_bPlus = TRUE;
	m_bMinus = FALSE;
	OnPlus();
	//OnMinus();
}

CAnimView::~CAnimView()
{
	//delete m_pBall;
	//delete m_pBallPen;
	//delete m_pBallBrush;
}

BOOL CAnimView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	return CView::PreCreateWindow(cs);
}

// CAnimView drawing
void CAnimView::OnDraw(CDC* pDC)
{
	CAnimDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
//	rysowanie po pamięciowym kontekście urządzenia, z którym będzie związana bitmapa,
//	na której będziemy realizować operacje czyszczenia tła

	CDC memDC;									//pamięciowy kontekst urządzenia
	BOOL b = memDC.CreateCompatibleDC(pDC);		//kreowanie jako kompatybilny do rzeczywistego
	ASSERT(b);

	CBitmap bmp;
	b = bmp.CreateCompatibleBitmap(pDC, m_pRect->Width(), m_pRect->Height());
	ASSERT(b);
	CBitmap* pOldBitmap = memDC.SelectObject(&bmp);
	memDC.FillSolidRect(m_pRect, RGB(230, 230, 200));
	
	//wybieramy  najpierw  do  kontekstu urządzenia  pióro  dla  kulki  a  potem  pędzel

//----------------zmiana
	CPen*    pOldPen = memDC.SelectObject(m_vBall[0]->GetPen());
	CBrush*  pOldBrush = memDC.SelectObject(m_vBall[0]->GetBrush());

//------------ zmiana ( memDC.Ellipse( m_pBall); )---------------
	for (int i = 0; i < m_nBalls; i++) 
	{
		pOldPen = memDC.SelectObject(m_vBall[i]->GetPen());
		pOldBrush = memDC.SelectObject(m_vBall[i]->GetBrush());
		m_vBall[i]->PaintBall(&memDC);
	}
//-----------------------
	//memDC.SelectObject(pOldPen);
	//memDC.SelectObject(pOldBrush);

	b = pDC->BitBlt(0, 0, m_pRect->Width(), m_pRect->Height(), &memDC, 0, 0, SRCCOPY);
	ASSERT(b);

	//sprzątanie
	memDC.SelectObject(pOldBitmap);
	bmp.DeleteObject();
	memDC.DeleteDC();
}


// CAnimView diagnostics

#ifdef _DEBUG
void CAnimView::AssertValid() const
{
	CView::AssertValid();
}

void CAnimView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAnimDoc* CAnimView::GetDocument() const  // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAnimDoc)));
	return (CAnimDoc*)m_pDocument;
}
#endif //_DEBUG


void CAnimView::OnStart()
{

	m_bStart = !m_bStart;
	CMainFrame* pFrame = (CMainFrame*)GetParentFrame();
	pFrame->ResetButton(m_bStart);
}


void CAnimView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	//m_nTimerId = SetTimer(WM_USER + 1, 20, NULL);

	m_nTimerId = SetTimer(WM_USER + 1, 20, ZfxTimerProc);
	//WM_USER - ostatnia wartość użyta w zasobach
	//20milisekund - interwał wysyłania komunikatu WM_TIMER
}

void CAnimView::OnDestroy()
{
	KillTimer(m_nTimerId);
	CView::OnDestroy();
}


void CAnimView::OnTimer(UINT_PTR nIDEvent)
{
	//należy  uzależnić  wykonanie przesuwania piłki i odrysowania od prawdy tej składowe
	if (m_bStart) 
	{
		for (int i = 0; i < m_nBalls; i++) {
			if (m_vBall[i]->top < m_pRect->top || m_vBall[i]->bottom >= m_pRect->bottom)
				m_vBall[i]->SetOffset(1, -1);
			if (m_vBall[i]->left < m_pRect->left || m_vBall[i]->right >= m_pRect->right)
				m_vBall[i]->SetOffset(-1, 1);

			m_vBall[i]->OffsetRect(m_vBall[i]->GetOffX(), m_vBall[i]->GetOffY());
		}

		Invalidate(); //odrysowanie
	}
	CView::OnTimer(nIDEvent);
}


BOOL CAnimView::OnEraseBkgnd(CDC* pDC)
{
	return 1;  //nie będzie czyszczenia tła okna widoku 
}


void CAnimView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{	// odczytanie rozmiaru obszaru klienta (realizowane przed każdym odrysowaniem 
	// więc zawsze będą aktualne rozmiary okna widoku) 
	GetClientRect(m_pRect);
	CView::OnPrepareDC(pDC, pInfo);
}


void CAnimView::OnPlus()
{
	if (m_nBalls >= 0 && m_nBalls < MAX) {
		int t_size = rand() % 100;
		CBall* pBall = new CBall(20, 20, 40+t_size, 40+t_size , COLOR, rand() % 30, rand() % 30, NULL);
		m_vBall.push_back(pBall);
		m_nBalls+=1;
		m_bPlus = TRUE;
	}
	else if (m_nBalls == MAX) {
		m_bPlus = FALSE;
	}
	
	if (m_nBalls > MIN) {
		m_bMinus = TRUE;
	}
	else if (m_nBalls == MIN) {
		m_bMinus = FALSE;
	}
}

void CAnimView::OnMinus()
{
	if (m_nBalls > MIN && m_nBalls <= MAX)
	{
		CBall* pBall = m_vBall.back();
		delete pBall;

		m_vBall.pop_back();
		m_nBalls -= 1;
		m_bMinus = TRUE;

	}
	else if (m_nBalls == MAX) {
		m_bPlus = FALSE;

	}
	else if (m_nBalls == MIN) {
		m_bMinus = FALSE;
		m_bPlus = TRUE;
	}
}

void CAnimView::OnUpdatePlus(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_bPlus);
}

void CAnimView::OnUpdateMinus(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_bMinus);
}

void CAnimView::OnSize(UINT nType, int cx, int cy)
{
	if (m_bStart) {

		for (int i = 0; i < m_nBalls; i++)
		{
			m_vBall[i]->SetBoundRect(m_pRect);
			m_vBall[i]->OffsetRect(m_vBall[i]->GetOffX(), m_vBall[i]->GetOffY());
		}
	}Invalidate();

		CView::OnSize(nType, cx, cy);
	
}
