// ThresholdingDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "CV Image Processor.h"
#include "ThresholdingDlg.h"
#include "afxdialogex.h"


// ThresholdingDlg 대화 상자

IMPLEMENT_DYNAMIC(ThresholdingDlg, CDialogEx)

ThresholdingDlg::ThresholdingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_THRESHOLDINGDLG, pParent)
	, thrValue(0)
{

}

ThresholdingDlg::~ThresholdingDlg()
{
}

void ThresholdingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, thrValue);
}


BEGIN_MESSAGE_MAP(ThresholdingDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &ThresholdingDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// ThresholdingDlg 메시지 처리기


void ThresholdingDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}
