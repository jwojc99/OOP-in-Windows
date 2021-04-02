
// MainFrm.cpp: implementacja klasy CMainFrame
//

#include "pch.h"
#include "framework.h"
#include "Anim.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	//ON_COMMAND(ID_START_STOP, &CMainFrame::OnStartStop)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // wskaźnik stanu wiersza
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


UINT CMainFrame::m_buttonsIDs[]
{
	ID_START_STOP,
	ID_PLUS,
	ID_MINUS,
	ID_APP_ABOUT,
	
};
// Tworzenie/niszczenie obiektu CMainFrame

CMainFrame::CMainFrame() noexcept
{
	// TODO: dodaj tutaj kod inicjowania elementu członkowskiego
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	/*
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Nie można utworzyć paska narzędzi\n");
		return -1;      // nie można utworzyć
	}*/
	
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadBitmap(IDR_MAINFRAME) ||
		!m_wndToolBar.SetButtons(m_buttonsIDs, sizeof(m_buttonsIDs) / sizeof(UINT)))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	CToolBarCtrl& barCtrl = m_wndToolBar.GetToolBarCtrl();
	barCtrl.SetBitmapSize(CSize(45, 43));
	barCtrl.SetButtonSize(CSize(53, 50)); //+8 +7

	
//----------------------------
	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Nie można utworzyć paska stanu\n");
		return -1;      // nie można utworzyć
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: usuń te trzy wiersze, jeśli pasek narzędzi nie ma mieć możliwości dokowania
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	return 0;
}

void CMainFrame::ResetButton(BOOL b) {
	int buttonIx = sizeof(m_buttonsIDs) / sizeof(UINT); // index szachownicy
	if( b ) 
		m_wndToolBar.SetButtonInfo( 0, ID_START_STOP, TBBS_BUTTON, buttonIx );
	else
		m_wndToolBar.SetButtonInfo( 0, ID_START_STOP, TBBS_BUTTON, 0 );
	
	m_wndToolBar.Invalidate(); //odrysowanie toolbara
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: zmodyfikuj klasę Window lub style w tym miejscu, modyfikując
	//  styl kaskadowy CREATESTRUCT

	return TRUE;
}

// Diagnostyka klasy CMainFrame

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// Procedury obsługi komunikatów CMainFrame

