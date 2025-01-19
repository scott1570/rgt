
// DummyPosClinetDlg.h: 헤더 파일
//

#pragma once
#include <string>

// CDummyPosClinetDlg 대화 상자
class CDummyPosClinetDlg : public CDialogEx
{
// 생성입니다.
public:
	CDummyPosClinetDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	int generateInputJson(int max_table_number, char* dst);
	int SendJson(char* json);
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DUMMYPOSCLINET_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
