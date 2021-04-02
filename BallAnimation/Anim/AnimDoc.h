
// AnimDoc.h: interfejs klasy CAnimDoc
//


#pragma once


class CAnimDoc : public CDocument
{
protected: // utwórz tylko na podstawie serializacji
	CAnimDoc() noexcept;
	DECLARE_DYNCREATE(CAnimDoc)

// Atrybuty
public:

// Operacje
public:

// Przesłania
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementacja
public:
	virtual ~CAnimDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Wygenerowano funkcje mapy komunikatów
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Funkcja pomocnicza, która ustawia zawartość wyszukiwania dla procedury obsługi wyszukiwania
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
