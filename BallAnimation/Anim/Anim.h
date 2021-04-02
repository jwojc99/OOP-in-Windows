
// Anim.h: główny plik nagłówkowy aplikacji Anim
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // główne symbole


// CAnimApp:
// Aby uzyskać implementację klasy, zobacz Anim.cpp
//

class CAnimApp : public CWinApp
{
public:
	CAnimApp() noexcept;


// Przesłania
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementacja
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CAnimApp theApp;
