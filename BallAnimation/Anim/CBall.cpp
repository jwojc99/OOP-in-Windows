#include "pch.h"
#include "CBall.h"


CBall::CBall(int xLT, int yLT, int xRB, int yRB, COLORREF col, int offX, int offY, const CRect * rect) :CRect(xLT, yLT, xRB, yRB), m_nOffX(offX), m_nOffY(offY)
{
	InitObjects(col);
}

CBall::CBall(const CRect & rect, COLORREF col, int offX, int offY, const  CRect * rect2):CRect(rect)
{
	InitObjects(col);
}

CBall::CBall(CPoint point, CSize size, COLORREF col, int offX, int offY, const  CRect * rect):CRect(point,size)
{
	InitObjects(col);
}

CBall::~CBall()
{
	DeleteObjects();
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

void CBall::SetOffset(int nOffX, int nOffY) //odbijanie się
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

int CBall::GetOffX() const
{
	return m_nOffX;
}

int CBall::GetOffY() const
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

inline void CBall::CreateObjects(COLORREF col = BLACK)
{
	m_pBallPen->CreatePen(PS_SOLID, 1, col);
	m_pBallBrush->CreateSolidBrush(col);
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
