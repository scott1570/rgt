
// DummyPosClinetDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "DummyPosClinet.h"
#include "DummyPosClinetDlg.h"
#include "afxdialogex.h"
#include "winsock2.h"
#include "json/json.h"
#include <WS2tcpip.h>
#pragma warning(disable:4996)
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(lib, "ws2_32.lib")

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

std::string base64_encode(const std::string& in) {

	typedef unsigned char uchar;
	std::string out;

	int val = 0, valb = -6;
	for (uchar c : in) {
		val = (val << 8) + c;
		valb += 8;
		while (valb >= 0) {
			out.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[(val >> valb) & 0x3F]);
			valb -= 6;
		}
	}
	if (valb > -6) out.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[((val << 8) >> (valb + 8)) & 0x3F]);
	while (out.size() % 4) out.push_back('=');
	return out;
}

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CDummyPosClinetDlg 대화 상자



CDummyPosClinetDlg::CDummyPosClinetDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DUMMYPOSCLINET_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	WSADATA data;
	WSAStartup(MAKEWORD(2, 2), &data);

}

void CDummyPosClinetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDummyPosClinetDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, &CDummyPosClinetDlg::OnBnClickedButtonStart)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CDummyPosClinetDlg 메시지 처리기
int CDummyPosClinetDlg::SendJson(char *szjson) {


	std::string json(szjson);
	OutputDebugString(json.c_str());
	//json = base64_encode(json);
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET) {
		return -1;
	}
	const char* serverIpAddr = "127.0.0.1";
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(5678);
	int convResult = inet_pton(AF_INET, serverIpAddr, &hint.sin_addr);


	if (connect(sock, reinterpret_cast<sockaddr*>(&hint), sizeof(hint)) == SOCKET_ERROR)
	{
		int err = WSAGetLastError();
		return -2;
	}
	char szBody[1024 * 8] = { 0 };
	std::string url = "127.0.0.1:5678";
	std::string request_string = "POST ";
	//request_string += path;
	request_string += " HTTP/1.1\r\n"; // or HTTP/1.0
	request_string += ("Host: " + url + "\r\n");
	request_string += "Accept: */*\r\n";
	request_string += "Content-Type: application/json\r\n";
	request_string += ("Content-Length: " + std::to_string(json.length()) + "\r\n");
	request_string += "Connection: close\r\n"; // omit this if using HTTP/1.0
	request_string += "\r\n";
	request_string += json;

	char szSend[1024] = { 0 };
	memcpy(szSend, json.c_str(), json.length());

	int sent = send(sock, szSend, request_string.length(), 0);

	
	TCHAR szdebug[100];
	wsprintf(szdebug, _T("sent %d"), sent);
	OutputDebugString(szdebug);

	closesocket(sock);




	return 0;
}


int CDummyPosClinetDlg::generateInputJson(int max_table_number, char* dst) {

	int range = 10 - 1 + 1;
	const int nMenu = 5;
	const int nstatus = 3;
	std::string strMenus[5] = { "pizza", "spagetti", "chicken", "cocktail", "wine" };
	std::string strStatus[3] = { "Accepted", "Processing", "Done"};


	Json::Value root;

	int menu_index;
	int numDish;
	int table;
	int status_index;

	
	menu_index = rand() % 5;
	numDish = rand() % range + 1;
	table = rand() % max_table_number+1;
	status_index = rand() % 3;
	


	Json::Value menus;
	Json::Value menu1;
	Json::Value menu2;
	menu1["menu"] = strMenus[menu_index].c_str();
	CString strAmount; strAmount.Format(_T("%d"), numDish);
	menu1["amount"] = strAmount.GetString();
	
	
	int prev_menu_index = menu_index;
	while (true) {
		menu_index = rand() % 5;
		if (menu_index != prev_menu_index)
			break;
	}
	menu2["menu"] = strMenus[menu_index].c_str();

	numDish = rand() % range + 1;

	strAmount.Format(_T("%d"), numDish);
	menu2["amount"] = strAmount.GetString();
	
	menus.append(menu1);
	menus.append(menu2);

	root["order"] = menus;

	

	CString strTable; strTable.Format(_T("%d"), table);
	root["status"] = strStatus[status_index].c_str();
	root["table"] = strTable.GetString();

	Json::StyledWriter writer;
	std::string strJson = writer.write(root);
	OutputDebugString(strJson.c_str());
	strcpy(dst, strJson.c_str());
	return 0;
}

BOOL CDummyPosClinetDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	srand(time(NULL));

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CDummyPosClinetDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CDummyPosClinetDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CDummyPosClinetDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDummyPosClinetDlg::OnBnClickedButtonStart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SetTimer(0, 1000 * 3, NULL);
}


void CDummyPosClinetDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nIDEvent == 0) {

		char szDst[512] = { 0 };
		int ret = generateInputJson(3, szDst);
		SendJson(szDst);
		int range = 15 - 3 + 1;
		int num = rand() % range + 3;
		

		KillTimer(0);
		SetTimer(0, 1000 * num, NULL);

	}
	CDialogEx::OnTimer(nIDEvent);
}


void CAboutDlg::OnDestroy()
{
	WSACleanup();
	CDialogEx::OnDestroy();
	
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}
