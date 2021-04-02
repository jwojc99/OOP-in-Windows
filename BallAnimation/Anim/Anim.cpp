
// Anim.cpp: definiuje zachowania klasy dla aplikacji.
//

#include "pch.h"
#include "framework.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "Anim.h"
#include "MainFrm.h"

#include "AnimDoc.h"
#include "AnimView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAnimApp

BEGIN_MESSAGE_MAP(CAnimApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CAnimApp::OnAppAbout)
	// Standardowe polecenia dokumentu oparte na pliku
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()


// Konstrukcja klasy CAnimApp

CAnimApp::CAnimApp() noexcept
{
	// obsługa menedżera ponownego uruchamiania
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// Jeśli aplikacja została skompilowana z obsługą środowiska uruchomieniowego języka wspólnego (/clr):
	//     1) To dodatkowe ustawienie jest wymagane do poprawnego działania obsługi Menedżera ponownego uruchamiania.
	//     2) W projekcie musisz dodać odwołanie do elementu System.Windows.Forms, aby skompilować.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: Zastąp ciąg identyfikatora aplikacji poniżej za pomocą unikatowego ciągu identyfikatora; zalecane
	// format ciągu to CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("Anim.AppID.NoVersion"));

	// TODO: W tym miejscu dodaj kod konstruktora,
	// Umieść wszystkie znaczące inicjacje w InitInstance
}

// Jedyny obiekt CAnimApp

CAnimApp theApp;


// Inicjowanie klasy CAnimApp

BOOL CAnimApp::InitInstance()
{
	// Funkcja InitCommonControlsEx() jest wymagana w systemie Windows XP, jeśli aplikacja
	// manifest określa użycie pliku ComCtl32.dll w wersji 6 lub nowszej, który ma zostać użyty
	// style wizualne. W przeciwnym razie utworzenie jakiegokolwiek okna nie powiedzie się.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Ustaw ten element tak, aby uwzględniał wszystkie typowe klasy kontrolek, których chcesz użyć
	// w aplikacji.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	// Zainicjuj biblioteki OLE
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// Funkcja AfxInitRichEdit2() musi używać kontrolki RichEdit
	// AfxInitRichEdit2();

	// Inicjowanie standardowe
	// Jeśli nie używasz tych funkcji i chcesz zmniejszyć rozmiar
	// końcowego pliku wykonywalnego, usuń poniżej
	// określone procedury inicjowania, które nie są potrzebne
	// Zmień klucz rejestru, w którym są przechowywane ustawienia
	// TODO: zmodyfikuj ten ciąg, aby był poprawny
	// takie jak nazwa firmy lub organizacji
	SetRegistryKey(_T("Aplikacje lokalne wygenerowane przez kreatora aplikacji"));
	LoadStdProfileSettings(4);  // Ładuj opcje ze standardowego pliku INI (włącznie z listą ostatnio używanych)


	// Rejestruj szablony dokumentu aplikacji. Szablony dokumentu
	//  służą jako połączenie między dokumentami, oknami ramek i widokami
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CAnimDoc),
		RUNTIME_CLASS(CMainFrame),       // główne okno ramek SDI
		RUNTIME_CLASS(CAnimView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// Analizuj wiersz polecenia pod kątem standardowych poleceń powłoki, DDE i otwarcia pliku
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// Polecenia wysyłania określone w wierszu polecenia. Zwraca wartość FALSE, jeśli
	// aplikacja została uruchomiona z parametrem /RegServer, /Register, /Unregserver lub /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Jedyne okno zostało zainicjowane, więc wyświetl je i zaktualizuj
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

int CAnimApp::ExitInstance()
{
	//TODO: Obsłuż kolejne zasoby, które mogły zostać dodane
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}

// procedury obsługi komunikatów klasy CAnimApp


// Okno dialogowe CAboutDlg używane na potrzeby informacji o aplikacji

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() noexcept;

// Dane okna dialogowego
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // obsługa DDX/DDV

// Implementacja
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// Polecenie aplikacji uruchamiające okno dialogowe
void CAnimApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// procedury obsługi komunikatów klasy CAnimApp



