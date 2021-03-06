#pragma once


// ThresholdingDlg 대화 상자

class ThresholdingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ThresholdingDlg)

public:
	ThresholdingDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~ThresholdingDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_THRESHOLDINGDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	UINT thrValue;
	afx_msg void OnBnClickedOk();
};
