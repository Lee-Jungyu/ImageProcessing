#pragma once


// BlurringDlg 대화 상자

class BlurringDlg : public CDialogEx
{
	DECLARE_DYNAMIC(BlurringDlg)

public:
	BlurringDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~BlurringDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BLURDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedRadio2();
	int gausian_size;
	afx_msg void OnBnClickedRadio1();
};
