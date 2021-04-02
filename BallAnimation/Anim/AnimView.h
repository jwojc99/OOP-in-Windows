
// AnimView.h: interfejs klasy CAnimView
//

#pragma once
#include "MainFrm.h"
#include "CBall.h"
#include <vector>

class CAnimView : public CView
{
protected: // utwórz tylko na podstawie serializacji
	CAnimView() noexcept;
	DECLARE_DYNCREATE(CAnimView)

// Atrybuty
public:
	CAnimDoc* GetDocument() const;
private:
	UINT_PTR m_nTimerId;
	CRect* m_pBall;
	CPen* m_pBallPen;
	CBrush* m_pBallBrush;

	int m_nBallOffX;
	int m_nBallOffY;

	BOOL m_bStart;

// Operacje
public:

// Przesłania
public:
	virtual void OnDraw(CDC* pDC);  // zastąpiony, aby narysować ten widok
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementacja
public:
	virtual ~CAnimView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Wygenerowano funkcje mapy komunikatów
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStart();
	virtual void OnInitialUpdate();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);

	afx_msg void OnPlus();
	afx_msg void OnUpdatePlus(CCmdUI *pCmdUI);
	afx_msg void OnMinus();
	afx_msg void OnUpdateMinus(CCmdUI *pCmdUI);
	afx_msg void OnSize(UINT nType, int cx, int cy);

private:
	BOOL m_bStartStop;
	BOOL m_bCancel;
	BOOL m_bPlus;
	BOOL m_bMinus;

	CRect* m_pRect;
	int	m_nBalls;
	std::vector<CBall*> m_vBall;
	
};

#ifndef _DEBUG  // debuguj wersję w elemencie AnimView.cpp
inline CAnimDoc* CAnimView::GetDocument() const
   { return reinterpret_cast<CAnimDoc*>(m_pDocument); }
#endif

