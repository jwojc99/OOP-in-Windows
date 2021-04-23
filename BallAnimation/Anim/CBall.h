#include <afxwin.h>

#define BLACK RGB(0,0,0)

class CBall : public CRect
{
public:
	
	CBall(int xLT = 0, int yLT = 0, int xRB = 0, int yRB = 0, COLORREF col = BLACK,int offX = 0,int offY = 0, const CRect* rect = nullptr);
	CBall(const CRect& rect, COLORREF col = BLACK, int offX = 0, int offY = 0,	const  CRect* rect2 = nullptr);
	CBall(CPoint point, CSize size, COLORREF col = BLACK, int offX = 0, int offY = 0, const  CRect* rect = nullptr);
	~CBall(); 

	inline void SetBallColor(COLORREF); // ustaw kolor 
	inline void SetBallSize(const CRect& rect);  //ustaw rozmiar
	void PaintBall(CDC* pDC);		//narysuj kulkę
	void SetBall(const CRect& rect, COLORREF col, int nOffX, int nOffY);
	void SetOffset(int nOffX, int nOffY);	//ustawia wektory ruchu
	void SetBoundRect(const CRect& rect);	// ruch – obszar klienta, ustawia prostokąt ograniczający

	int GetOffX() const;
	int GetOffY() const;
	CPen* GetPen();
	CBrush* GetBrush();

private:

	CPen* m_pBallPen;
	CBrush* m_pBallBrush;
	CRect* m_BoundRect = nullptr;
	int m_nOffX;
	int m_nOffY;

private:
	inline void CreateObjects(COLORREF col);	// kolor pedzla i piora ten sam
												// CreatePen
												// CreateSolidBrush

	inline void DeleteObjects();				 // DeleteObject() dla piora i pędzla
	void InitObjects(COLORREF col);				 // przydziela pamiec i wykreować
	
};
