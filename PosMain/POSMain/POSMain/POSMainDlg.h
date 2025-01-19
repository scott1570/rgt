
// POSMainDlg.h: 헤더 파일
//

#pragma once

#include "defines.h"
class Controller;

// CPOSMainDlg 대화 상자
class CPOSMainDlg : public CDialogEx
{
// 생성입니다.
public:
	CPOSMainDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_POSMAIN_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


	Controller* mpController;

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
	afx_msg void OnBnClickedButtonTable1();
	afx_msg void OnBnClickedButtonStatus();
	afx_msg void OnStnClickedStatus2();
	afx_msg void OnStnClickedStatus1();
	afx_msg void OnStnClickedStatus3();
	afx_msg void OnBnClickedButtonTable2();
	afx_msg void OnBnClickedButtonTable3();
};
