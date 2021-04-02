#include "pch.h"
#include "CBall.h"

#define BLACK RGB(0,0,0)

CBall::CBall(int xLT=0, int yLT=0, int xRB=0, int yRB=0, COLORREF col=BLACK, int x=0, int y=0,const CRect & rect = NULL):CRect(xLT,yLT,xRB,yRB),m_nOffX(x),m_nOffY(y)
{
	InitObjects(col);
}

CBall::CBall(const CRect & rect, COLORREF col, int offX, int offY, const  CRect & rect2):CRect(rect)
{
	InitObjects(col);
}

CBall::CBall(CPoint point, CSize size, COLORREF col, int offX, int offY, const  CRect & rect):CRect(point,size)
{
	InitObjects(col);
}

CBall::~CBall()
{
	DeleteObjects();
}

inline COLORREF CBall::GetColor(COLORREF col)
{
	return col;
}

inline void CBall::SetBallSize(const CRect & rect)
{
	CRect() = rect;
}

void CBall::PaintBall(CDC * pDC)
{
	pDC->Ellipse(this);
}

void CBall::SetBall(const CRect & rect, COLORREF col, int nOffX, int nOffY)
{
	CRect() = rect;
	m_nOffX = nOffX;
	m_nOffY = nOffY;
	InitObjects(col);
}

void CBall::SetOffset(int nOffX, int nOffY)
{
	m_nOffX *= nOffX;
	m_nOffY *= nOffY;
}

void CBall::SetBoundRect(const CRect & rect)
{
	int horizontal = right - left;
	int vertical = top - bottom;

	if (right > rect.right) {
		right = rect.right;
		left = right - horizontal;
		SetOffset(-1, 1);
	}

	if (top < rect.top) {
		top = rect.top;
		bottom = top + vertical;
		SetOffset(1, -1);
	}

	if (left < rect.left) {
		left = rect.left;
		right = left + horizontal;
		SetOffset(-1, 1);
	}

	if (bottom > rect.bottom) {
		bottom = rect.bottom;
		top = bottom - vertical;
		SetOffset(1, -1);
	}
}

int CBall::GetOffX()
{
	return m_nOffX;
}

int CBall::GetOffY()
{
	return m_nOffY;
}


CPen * CBall::GetPen()
{
	return m_pBallPen;
}

CBrush * CBall::GetBrush()
{
	return m_pBallBrush;
}

void CBall::SetPen(CPen * pPen)
{
	m_pBallPen = pPen;
}

void CBall::SetBrush(CBrush * pBrush)
{
	m_pBallBrush = pBrush;
}
inline void CBall::CreateObjects(COLORREF col = BLACK)
{
	m_pBallPen->CreatePen(PS_SOLID, 1, GetColor(col));
	m_pBallBrush->CreateSolidBrush(GetColor(col));
}

inline void CBall::DeleteObjects()
{
	delete m_pBallPen;
	delete m_pBallBrush;
}

void CBall::InitObjects(COLORREF col = BLACK)
{
	m_pBallPen = new CPen();
	m_pBallBrush = new CBrush();
	CreateObjects(col);
}
