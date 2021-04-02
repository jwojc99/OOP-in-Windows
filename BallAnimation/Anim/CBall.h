#include <afxwin.h>

class CBall : public CRect
{
public:
	CBall(int xLT, int yLT, int xRB, int yRB, COLORREF col, int x, int y,const CRect& rect);
	CBall(const CRect& rect, COLORREF col, int offX, int offY, const  CRect& rect2);
	CBall(CPoint point, CSize size, COLORREF col, int offX, int offY, const  CRect& rect);
	~CBall();

	inline COLORREF GetColor(COLORREF col);
	//inline SetBallColor(COLORREF); // ustaw kolor (Delete() + Create()),  nie usuwaæ tu pamiêci,  ustaw rozmiar
	inline void SetBallSize(const CRect& rect);     //ustaw rozmiar
	void PaintBall(CDC* pDC);						//narysuj kulkê
	void SetBall(const CRect& rect, COLORREF col, int nOffX, int nOffY);
	void SetOffset(int nOffX, int nOffY);			//ustawia wektory ruchu
	void SetBoundRect(const CRect& rect);			// ruch – obszar klienta, ustawia prostok¹t ograniczaj¹cy

	
	int GetOffX();
	int GetOffY();
	void SetPen(CPen* pPen);
	void SetBrush(CBrush* pBrush);

	CPen* GetPen();
	CBrush* GetBrush();
private:
	inline void CreateObjects(COLORREF col);	// kolor pedzla i piora ten sam
												// CreatePen
												// CreateSolidBrush

	inline void DeleteObjects();				 // DeleteObject() dla piora i pêdzla
	void InitObjects(COLORREF col);				 // przydziela pamiec i wykreowaæ
	
private:
	CPen* m_pBallPen;
	CBrush* m_pBallBrush;
	int m_nOffX;
	int m_nOffY;

	CRect* m_BoundRect;

	//Offsety ruchu
		// wszystkie wsk lokowane w konstruktorze i maja wartoœci z parametrów, a w
		//przypadku prostok¹ta ograniczaj¹cego gdy parametr konstr jest NULL to
		//tworzymy prostok¹t o wspó³rzêdnych zerowych

};
