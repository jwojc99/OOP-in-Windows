
// AnimView.cpp: implementacja klasy CAnimView
//

#include "pch.h"
#include "framework.h"
// Element SHARED_HANDLERS można zdefiniować w projekcie ATL z implementacją podglądu, miniaturze
// procedury obsługi serializacji i filtrów wyszukiwania oraz umożliwia udostępnianie kodu dokumentu w tym projekcie.
#ifndef SHARED_HANDLERS
#include "Anim.h"
#endif

#include "AnimDoc.h"
#include "AnimView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//#define BALLSIZE 60
#define BLUE RGB(0,0,255)
#define MAX_BALL 10
#define MIN_BALL 1

#define COLOR RGB(rand()%255, rand()%255,rand()%255)
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

void CALLBACK ZfxTimerProc(
	HWND hWnd,
	UINT nMsg,
	UINT_PTR nIDEvent,
	DWORD dwTime
)
{
	::SendMessage(hWnd, WM_TIMER, 0, 0);
}

// Tworzenie/niszczenie obiektu CAnimView

CAnimView::CAnimView() noexcept
{
	srand(time(NULL));
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
	return CView::PreCreateWindow(cs);
}

void CAnimView::OnDraw(CDC* pDC)
{
	CAnimDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	CDC memDC;
	BOOL b = memDC.CreateCompatibleDC(pDC);
	ASSERT(b);

	CBitmap bmp;
	b = bmp.CreateCompatibleBitmap(pDC, m_pRect->Width(), m_pRect->Height());
	ASSERT(b);
	CBitmap* pOldBitmap = memDC.SelectObject(&bmp);
	memDC.FillSolidRect(m_pRect, RGB(230, 230, 200));
	
	CPen* pOldPen = memDC.SelectObject(m_vBall[0]->GetPen());
	CBrush* pOldBrush = memDC.SelectObject(m_vBall[0]->GetBrush());

	for (int i = 0; i < m_nBalls; i++) {
		pOldPen = memDC.SelectObject(m_vBall[i]->GetPen());
		pOldBrush = memDC.SelectObject(m_vBall[i]->GetBrush());
		m_vBall[i]->PaintBall(&memDC);
	}

	memDC.SelectObject(pOldPen);
	memDC.SelectObject(pOldBrush);

	b = pDC->BitBlt(0, 0, m_pRect->Width(), m_pRect->Height(), &memDC, 0, 0, SRCCOPY);
	ASSERT(b);

	memDC.SelectObject(pOldBitmap);
	bmp.DeleteObject();
	memDC.DeleteDC();
}


// Diagnostyka klasy CAnimView

#ifdef _DEBUG
void CAnimView::AssertValid() const
{
	CView::AssertValid();
}

void CAnimView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAnimDoc* CAnimView::GetDocument() const // wbudowana jest wersja bez debugowania
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAnimDoc)));
	return (CAnimDoc*)m_pDocument;
}
#endif //_DEBUG


// Procedury obsługi komunikatów CAnimView

void CAnimView::OnStart()
{
	m_bStart = !m_bStart;
	CMainFrame* pFrame = (CMainFrame*)GetParentFrame();
	pFrame->ResetButton(m_bStart);
}


void CAnimView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	m_nTimerId = SetTimer(WM_USER + 1, 20, ZfxTimerProc);
}


void CAnimView::OnDestroy()
{
	KillTimer(m_nTimerId);
	CView::OnDestroy();
}


void CAnimView::OnTimer(UINT_PTR nIDEvent)
{
	if (m_bStart) 
	{
		for (int i = 0; i < m_nBalls; i++) {
			if (m_vBall[i]->top < m_pRect->top || m_vBall[i]->bottom >= m_pRect->bottom)
				m_vBall[i]->SetOffset(1, -1);
			if (m_vBall[i]->left < m_pRect->left || m_vBall[i]->right >= m_pRect->right)
				m_vBall[i]->SetOffset(-1, 1);

			m_vBall[i]->OffsetRect(m_vBall[i]->GetOffX(), m_vBall[i]->GetOffY());
		}

		Invalidate();
	}
	CView::OnTimer(nIDEvent);
}


BOOL CAnimView::OnEraseBkgnd(CDC* pDC)
{
	return 1;
}


void CAnimView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	GetClientRect(m_pRect);
	CView::OnPrepareDC(pDC, pInfo);
}


void CAnimView::OnPlus()
{
	if (m_nBalls >= 0 && m_nBalls < MAX_BALL) {
		int t_size = rand() % 100;
		CBall* pBall = new CBall(10, 10, 30 + t_size, 30 + t_size, COLOR, rand() % 30, rand() % 30, NULL);
		m_vBall.push_back(pBall);
		m_nBalls+=1;
		m_bPlus = TRUE;
	}
	else if (m_nBalls == MAX_BALL) {
		m_bPlus = FALSE;
	}
	
	if (m_nBalls > MIN_BALL) {
		m_bMinus = TRUE;
	}
	else if (m_nBalls == MIN_BALL) {
		m_bMinus = FALSE;
	}
}

void CAnimView::OnMinus()
{
	if (m_nBalls > MIN_BALL && m_nBalls <= MAX_BALL)
	{
		CBall* pBall = m_vBall.back();
		delete pBall;

		m_vBall.pop_back();
		m_nBalls -= 1;
		m_bMinus = TRUE;

	}
	else if (m_nBalls == MAX_BALL) {
		m_bPlus = FALSE;

	}
	else if (m_nBalls == MIN_BALL) {
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
	for (int i = 0; i < m_nBalls; i++)
	{
		m_vBall[i]->SetBoundRect(m_pRect);
		m_vBall[i]->OffsetRect(m_vBall[i]->GetOffX(), m_vBall[i]->GetOffY());
	}
	CView::OnSize(nType, cx, cy);
}
