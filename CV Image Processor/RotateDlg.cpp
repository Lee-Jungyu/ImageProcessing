// RotateDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "CV Image Processor.h"
#include "RotateDlg.h"
#include "afxdialogex.h"


// RotateDlg 대화 상자

IMPLEMENT_DYNAMIC(RotateDlg, CDialogEx)

RotateDlg::RotateDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ROTATEDLG, pParent)
	, rotAngle(0)
{

}

RotateDlg::~RotateDlg()
{
}

void RotateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITROTANGLE, rotAngle);
}


BEGIN_MESSAGE_MAP(RotateDlg, CDialogEx)
END_MESSAGE_MAP()


// RotateDlg 메시지 처리기

BOOL RotateDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	rotAngle = 0;
	UpdateData(FALSE);
	return TRUE;
}
