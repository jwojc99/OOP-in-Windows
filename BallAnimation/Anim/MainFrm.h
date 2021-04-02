
// MainFrm.h: interfejs klasy CMainFrame
//

#pragma once

class CMainFrame : public CFrameWnd
{
	
protected: // utwórz tylko na podstawie serializacji
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)

// Atrybuty
public:

// Operacje
public:
	void  ResetButton(BOOL b);
// Przesłania
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementacja
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // osadzone elementy członkowskie paska sterowania
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;
	static UINT m_buttonsIDs[];
// Wygenerowano funkcje mapy komunikatów
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

public:
	
};


