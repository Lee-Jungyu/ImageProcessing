// BitPlaneDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "CV Image Processor.h"
#include "BitPlaneDlg.h"
#include "afxdialogex.h"

// BitPlaneDlg 대화 상자

IMPLEMENT_DYNAMIC(BitPlaneDlg, CDialogEx)

BitPlaneDlg::BitPlaneDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BITPLANEDLG, pParent)
	, m_nBit(0)
{

	m_spinval = 0;
}

BitPlaneDlg::~BitPlaneDlg()
{
}

void BitPlaneDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_EDITBIT, editBit);
	//  DDX_Control(pDX, IDC_SPINBIT, spinBit);
	DDX_Text(pDX, IDC_EDITBIT, m_nBit);
	DDX_Control(pDX, IDC_SPINBIT, m_spinBit);
}


BEGIN_MESSAGE_MAP(BitPlaneDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &BitPlaneDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// BitPlaneDlg 메시지 처리기


void BitPlaneDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}


BOOL BitPlaneDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_spinBit.SetRange(0, 7);
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
