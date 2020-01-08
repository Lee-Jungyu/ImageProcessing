#pragma once


// BitPlaneDlg 대화 상자

class BitPlaneDlg : public CDialogEx
{
	DECLARE_DYNAMIC(BitPlaneDlg)

public:
	BitPlaneDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~BitPlaneDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BITPLANEDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
//	CEdit editBit;
//	CSpinButtonCtrl spinBit;
	afx_msg void OnBnClickedOk();
	int m_spinval;
	UINT m_nBit;
	CSpinButtonCtrl m_spinBit;
	BOOL OnInitDialog();
//	afx_msg void OnNegativeImage();
};
