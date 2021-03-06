
// CV Image ProcessorDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "CV Image Processor.h"
#include "CV Image ProcessorDlg.h"
#include "BitPlaneDlg.h"
#include "ThresholdingDlg.h"
#include "BlurringDlg.h"
#include "ExpandReduceDlg.h"
#include "RotateDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

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
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCVImageProcessorDlg 대화 상자


CCVImageProcessorDlg::CCVImageProcessorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CVIMAGEPROCESSOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//  m_NowImgPath = _T("");
}

BEGIN_MESSAGE_MAP(CCVImageProcessorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_1_1, &CCVImageProcessorDlg::OnFileOpen)
	ON_COMMAND(ID_1_4, &CCVImageProcessorDlg::OnQuitProgram)
	ON_COMMAND(ID_1_2, &CCVImageProcessorDlg::OnSave)
	ON_COMMAND(ID_1_3, &CCVImageProcessorDlg::OnSaveAs)
	ON_COMMAND(ID_2_1, &CCVImageProcessorDlg::OnUndo)
	ON_COMMAND(ID_3_1, &CCVImageProcessorDlg::OnRGB2GRAY)
	ON_COMMAND(ID_3_2, &CCVImageProcessorDlg::OnSwitchLeftRight)
	ON_COMMAND(ID_3_3, &CCVImageProcessorDlg::OnSwitchTopBottom)
	ON_COMMAND(ID_3_4, &CCVImageProcessorDlg::OnPrintBitPlane)
	ON_COMMAND(ID_4_1, &CCVImageProcessorDlg::OnHistogramStretching)
	ON_COMMAND(ID_4_2, &CCVImageProcessorDlg::OnHistogramEqualization)
	ON_COMMAND(ID_4_3, &CCVImageProcessorDlg::OnNegativeImage)
	ON_COMMAND(ID_4_4, &CCVImageProcessorDlg::OnThresholding)
	ON_COMMAND(ID_5_1, &CCVImageProcessorDlg::OnBlurring)
	ON_COMMAND(ID_5_2, &CCVImageProcessorDlg::OnSharpning)
	ON_COMMAND(ID_5_3, &CCVImageProcessorDlg::OnAverageFiltering)
	ON_COMMAND(ID_5_4, &CCVImageProcessorDlg::OnMedianFiltering)
	ON_COMMAND(ID_6_1, &CCVImageProcessorDlg::OnSobelMasking)
	ON_COMMAND(ID_6_2, &CCVImageProcessorDlg::OnLaplacianMasking)
	ON_COMMAND(ID_7_1, &CCVImageProcessorDlg::OnOpening)
	ON_COMMAND(ID_7_2, &CCVImageProcessorDlg::OnClosing)
	ON_COMMAND(ID_8_1, &CCVImageProcessorDlg::OnExpandReduce)
	ON_COMMAND(ID_8_3, &CCVImageProcessorDlg::OnRotate)
	ON_COMMAND(ID_32796, &CCVImageProcessorDlg::OnDithering)
END_MESSAGE_MAP()


// CCVImageProcessorDlg 메시지 처리기

BOOL CCVImageProcessorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CMenu menu;
	menu.LoadMenuW(IDR_MENU1);
	SetMenu(&menu);

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

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CCVImageProcessorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCVImageProcessorDlg::DoDataExchange(CDataExchange* pDX)
{

	DDX_Control(pDX, IDC_PIC, pictureControl);
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CCVImageProcessorDlg::OnPaint()
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
HCURSOR CCVImageProcessorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCVImageProcessorDlg::DisplayImage(int IDC_PICTURE_TARGET, Mat targetMat)
{
	IplImage* targetIplImage = new IplImage(targetMat);
	if (targetIplImage != nullptr) {
		CWnd* pWnd_ImageTraget = GetDlgItem(IDC_PICTURE_TARGET);
		CClientDC dcImageTraget(pWnd_ImageTraget);
		RECT rcImageTraget;
		pWnd_ImageTraget->GetClientRect(&rcImageTraget);
		
		BITMAPINFO bitmapInfo;
		memset(&bitmapInfo, 0, sizeof(bitmapInfo));
		bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bitmapInfo.bmiHeader.biPlanes = 1;
		bitmapInfo.bmiHeader.biCompression = BI_RGB;
		bitmapInfo.bmiHeader.biWidth = targetIplImage->width;
		bitmapInfo.bmiHeader.biHeight = -targetIplImage->height;

		IplImage *tempImage = nullptr;

		if (targetIplImage->nChannels == 1)
		{
			tempImage = cvCreateImage(cvSize(targetIplImage->width, targetIplImage->height), IPL_DEPTH_8U, 3);
			cvCvtColor(targetIplImage, tempImage, CV_GRAY2BGR);
		}
		else if (targetIplImage->nChannels == 3)
		{
			tempImage = cvCloneImage(targetIplImage);
		}

		bitmapInfo.bmiHeader.biBitCount = tempImage->depth * tempImage->nChannels;

		dcImageTraget.SetStretchBltMode(COLORONCOLOR);
		::StretchDIBits(dcImageTraget.GetSafeHdc(), rcImageTraget.left, rcImageTraget.top, rcImageTraget.right, rcImageTraget.bottom,
			0, 0, tempImage->width, tempImage->height, tempImage->imageData, &bitmapInfo, DIB_RGB_COLORS, SRCCOPY);

		cvReleaseImage(&tempImage);
	}
}

void CCVImageProcessorDlg::OnFileOpen()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CString szFilter = _T("Image (*.BMP, *.GIF, *.JPG, *.PNG) | *.BMP;*.GIF;*.JPG;*.PNG;*.bmp;*.gif;*.jpg;*.png | All Files(*.*)|*.*||");
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, AfxGetMainWnd());
	if (dlg.DoModal() == IDOK)
	{
		path = dlg.GetPathName();
		//AfxMessageBox(cstrImgPath);
		string str = CT2CA(path);
		Mat src = imread(str);
		image = src.clone();
		opened = true;
		DisplayImage(IDC_PIC, src);
	}
}

bool CCVImageProcessorDlg::openCheck() {
	if (!opened) {
		CString msg = _T("이미지를 먼저 불러오시오");
		AfxMessageBox(msg);
		return false;
	}
	return true;
}


void CCVImageProcessorDlg::OnQuitProgram()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	PostQuitMessage(0);
}


void CCVImageProcessorDlg::OnSave()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (openCheck()) {
		string str = CT2CA(path);
		imwrite(str, image);
		CString msg = _T("저장완료");
		AfxMessageBox(msg);
	}
	else {
		return;
	}
}


void CCVImageProcessorDlg::OnSaveAs()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (openCheck()) {
		CString szFilter= _T("JPEG Image (*.jpg)|*.jpg|PNG Image (*.png)|*.png|Bitmap Image (*.bmp)|*.bmp|");
		CFileDialog dlg(FALSE, _T("jpg"), _T("*.jpg"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR, szFilter, AfxGetMainWnd());
		if (dlg.DoModal() == IDOK) {
			CString savePath = dlg.GetPathName();
			string str = CT2CA(savePath);
			imwrite(str, image);
			CString msg = _T("저장완료");
			AfxMessageBox(msg);
		}
	}
	else {
		return;
	}
}


void CCVImageProcessorDlg::OnUndo()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (imgStack.empty()) {
		CString msg = _T("실행취소할 이미지가 없습니다.");
		AfxMessageBox(msg);
		return;
	}
	image = imgStack.top();
	imgStack.pop();
	DisplayImage(IDC_PIC, image);
}

void CCVImageProcessorDlg::OnRGB2GRAY()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (!openCheck()) {
		return;
	}
	if (image.channels() == 1) return;

	imgStack.push(image);
	Mat grayImg;
	cvtColor(image, grayImg, CV_BGR2GRAY);
	image = grayImg.clone();
	DisplayImage(IDC_PIC, image);
}


void CCVImageProcessorDlg::OnSwitchLeftRight()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (!openCheck()) {
		return;
	}
	
	imgStack.push(image);
	Mat switchImage;
	flip(image, switchImage, 1);
	image = switchImage.clone();
	DisplayImage(IDC_PIC, image);
}


void CCVImageProcessorDlg::OnSwitchTopBottom()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (!openCheck()) {
		return;
	}

	imgStack.push(image);
	Mat switchImage;
	flip(image, switchImage, 0);
	image = switchImage.clone();
	DisplayImage(IDC_PIC, image);
}

void getBitPlane(Mat &srcImg, Mat &dstImg, int n)//(원본이미지 , bitplane될 이미지,n칸 
{
	uchar mask = 0x01 << n; //쉬프트연산자를 이용하여 n칸 밀어버림니다. 나머지 밀어져 버린 부분은 0으로 숫자가 초기화 됨니다.


	Mat_<uchar> s = Mat_<uchar>(srcImg);
	Mat_<uchar> d = Mat_<uchar>(dstImg);

	for (int r = 0; r < srcImg.rows; r++)
	{
		uchar *p = srcImg.ptr<uchar>(r);//첫번째행의 값을 가져온다.
		uchar *dp = dstImg.ptr<uchar>(r);
		for (int c = 0; c < srcImg.cols; c++)
		{
			uchar pixelvalue = p[c];
			uchar one_zero = pixelvalue & mask;
			if (one_zero > 0)
				dp[c] = 255;
			else
				dp[c] = 0;
		}
	}
}

void CCVImageProcessorDlg::OnPrintBitPlane()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (!openCheck()) {
		return;
	}

	BitPlaneDlg dlg;
	if (dlg.DoModal() == IDOK) {
		imgStack.push(image);

		Mat bitPlaneImg = image.clone();

		getBitPlane(image, bitPlaneImg, dlg.m_nBit);
		image = bitPlaneImg.clone();
		DisplayImage(IDC_PIC, image);
	}
}

uint8_t saturated_add(uint8_t val1, int8_t val2)
{
	int16_t val1_int = val1;
	int16_t val2_int = val2;
	int16_t tmp = val1_int + val2_int;

	if (tmp > 255)
	{
		return 255;
	}
	else if (tmp < 0)
	{
		return 0;
	}
	else
	{
		return tmp;
	}
}

void CCVImageProcessorDlg::OnDithering()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (!openCheck()) {
		return;
	}

	imgStack.push(image);

	Mat rawImg;
	Mat dithImg;
	int imgWidth;
	int imgHeight;
	uint8_t** imgPtr;

	/* Load the image and convert to grayscale first */
	rawImg = image.clone();
	if (rawImg.channels() != 1)
		cvtColor(rawImg, dithImg, CV_BGR2GRAY);
	else
		dithImg = image.clone();

	/* Get the size info */
	imgWidth = rawImg.cols;
	imgHeight = rawImg.rows;

	/* Run the 'Floyd-Steinberg' dithering algorithm ... */
	int err;
	int8_t a, b, c, d;

	for (int i = 0; i < imgHeight; i++)
	{
		for (int j = 0; j < imgWidth; j++)
		{
			if (dithImg.at<uint8_t>(i, j) > 127)
			{
				err = dithImg.at<uint8_t>(i, j) - 255;
				dithImg.at<uint8_t>(i, j) = 255;
			}
			else
			{
				err = dithImg.at<uint8_t>(i, j) - 0;
				dithImg.at<uint8_t>(i, j) = 0;
			}

			a = (err * 7) / 16;
			b = (err * 1) / 16;
			c = (err * 5) / 16;
			d = (err * 3) / 16;

			if ((i != (imgHeight - 1)) && (j != 0) && (j != (imgWidth - 1)))
			{
				dithImg.at<uint8_t>(i + 0, j + 1) = saturated_add(dithImg.at<uint8_t>(i + 0, j + 1), a);
				dithImg.at<uint8_t>(i + 1, j + 1) = saturated_add(dithImg.at<uint8_t>(i + 1, j + 1), b);
				dithImg.at<uint8_t>(i + 1, j + 0) = saturated_add(dithImg.at<uint8_t>(i + 1, j + 0), c);
				dithImg.at<uint8_t>(i + 1, j - 1) = saturated_add(dithImg.at<uint8_t>(i + 1, j - 1), d);
			}
		}
	}

	/* Show results. */
	//imshow("Raw Image", rawImg);
	//imshow("Dithered Image", dithImg);
	//printf("> Press any key to exit ...\n");
	image = dithImg.clone();

	DisplayImage(IDC_PIC, image);

}


void histogramStretching(Mat img, Mat& out)
{
	int lowvalue = 255, highvalue = 0;
	int i, j;
	for (i = 0; i < img.rows; i++)
	{
		for (j = 0; j < img.cols; j++)
		{
			if (lowvalue > img.at<uchar>(i, j))
				lowvalue = img.at<uchar>(i, j);
			if (highvalue < img.at<uchar>(i, j))
				highvalue = img.at<uchar>(i, j);
		}
	}
	// histogram stretching 계산
	float mult = 255 / (float)(highvalue - lowvalue);
	for (i = 0; i < img.rows; i++)
	{
		for (j = 0; j < img.cols; j++)
			out.at<uchar>(i, j) = (uchar)(img.at<uchar>(i, j) - lowvalue) * mult;
	}
}

void CCVImageProcessorDlg::OnHistogramStretching()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (!openCheck()) {
		return;
	}

	imgStack.push(image);
	Mat temp = image.clone();
	histogramStretching(image, temp);
	image = temp.clone();
	DisplayImage(IDC_PIC, image);
}

void histogramEqualization(Mat img, Mat& out)
{
	int i, j;
	unsigned int hist[256] = { 0, };
	float cdf[256] = { 0, };
	int pixel, max;

	for (i = 0; i < img.rows; i++)
	{
		for (j = 0; j < img.cols; j++)
		{
			hist[img.at<uchar>(i, j)]++;
		}
	}

	cdf[0] = hist[0];

	for (i = 1; i < 256; i++)
		cdf[i] = cdf[i - 1] + hist[i];

	max = cdf[255];

	for (i = 0; i < img.rows; i++)
	{
		for (j = 0; j < img.cols; j++)
		{
			pixel = cdf[img.at<uchar>(i, j)] / max * 255;
			out.at<uchar>(i, j) = (pixel > 255) ? 255 : pixel;
		}
	}
}

void CCVImageProcessorDlg::OnHistogramEqualization()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (!openCheck()) {
		return;
	}

	imgStack.push(image);
	Mat temp = image.clone();
	histogramEqualization(image, temp);
	image = temp.clone();
	DisplayImage(IDC_PIC, image);
}

void CCVImageProcessorDlg::OnNegativeImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (!openCheck()) {
		return;
	}

	imgStack.push(image);
	
	Mat temp = image.clone();

	if (temp.channels() != 3) {
		for (int y = 0; y < temp.rows; y++)
		{
			uchar *imgPtr = temp.ptr<uchar>(y);
			for (int x = 0; x < temp.cols; x++)
			{
				uchar value = imgPtr[x];
				value = 255 - value;
				imgPtr[x] = value;
			}
		}
	}
	else {
		for (int y = 0; y < temp.rows; y++)
		{
			for (int x = 0; x < temp.cols; x++)
			{
				uchar b = temp.at<Vec3b>(y, x)[0];
				uchar g = temp.at<Vec3b>(y, x)[1];
				uchar r = temp.at<Vec3b>(y, x)[2];
				temp.at<Vec3b>(y, x)[0] = 255 - b;
				temp.at<Vec3b>(y, x)[1] = 255 - g;
				temp.at<Vec3b>(y, x)[2] = 255 - r;
			}
		}
	}

	image = temp.clone();
	DisplayImage(IDC_PIC, image);
}


void CCVImageProcessorDlg::OnThresholding()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (!openCheck()) {
		return;
	}


	ThresholdingDlg dlg;
	if (dlg.DoModal() == IDOK) {
		imgStack.push(image);

		Mat temp = image.clone();

		threshold(image, temp, dlg.thrValue, 255, THRESH_BINARY);

		image = temp.clone();
		DisplayImage(IDC_PIC, image);
	}
}


void CCVImageProcessorDlg::OnBlurring()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (!openCheck()) {
		return;
	}

	BlurringDlg dlg;
	if (dlg.DoModal() == IDOK) {

		imgStack.push(image);
		Mat temp = image.clone();

		GaussianBlur(image, temp, Size(dlg.gausian_size, dlg.gausian_size), 0);

		image = temp.clone();
		DisplayImage(IDC_PIC, image);
	}
}


void CCVImageProcessorDlg::OnSharpning()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (!openCheck()) {
		return;
	}

	imgStack.push(image);
	Mat temp = image.clone();

	GaussianBlur(image, temp, Size(3, 3), 0);
	addWeighted(image, 1.5, temp, -0.5, 0, image);

	image = temp.clone();
	DisplayImage(IDC_PIC, image);

}

void averageFilter(Mat& Input, Mat& Output)
{
	int row = Input.rows;
	int col = Input.cols;
	int size = 1;
	uchar count = 0;
	uchar sum = 0;

	for (int j = 1; j < (Input.rows - 1); ++j)
	{
		const uchar* previous = Input.ptr<uchar>(j - 1);
		const uchar* current = Input.ptr<uchar>(j);
		const uchar* next = Input.ptr<uchar>(j + 1);

		uchar* output = Output.ptr<uchar>(j);

		for (int i = 1; i < (Output.cols - 1); ++i)
		{
			double dResult = (current[i] + current[i - 1] + current[i + 1] +
				previous[i] + next[i] + previous[i - 1] + previous[i + 1] +
				next[i - 1] + next[i + 1]) / 9.0;
			*output++ = (unsigned char)dResult;
		}
	}
}

void CCVImageProcessorDlg::OnAverageFiltering()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (!openCheck()) {
		return;
	}

	imgStack.push(image);
	Mat temp = image.clone();

	averageFilter(image, temp);

	image = temp.clone();
	DisplayImage(IDC_PIC, image);
}


void CCVImageProcessorDlg::OnMedianFiltering()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (!openCheck()) {
		return;
	}

	imgStack.push(image);
	Mat temp = image.clone();
	
	medianBlur(image, temp, 3);

	image = temp.clone();
	DisplayImage(IDC_PIC, image);
}

void CCVImageProcessorDlg::OnSobelMasking()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (!openCheck()) {
		return;
	}

	imgStack.push(image);
	Mat temp = image.clone();
	
	Mat sobelX, sobelY, sobel;
	Sobel(image, sobelX, CV_16S, 1, 0);
	Sobel(image, sobelY, CV_16S, 0, 1);
	sobel = abs(sobelX) + abs(sobelY);    // L1 놈(norm) 계산

	double sobmin, sobmax;
	minMaxLoc(sobel, &sobmin, &sobmax); // sobel 최댓값 찾기

	sobel.convertTo(temp, CV_8U, -255. / sobmax, 255); // 8bit 영상으로 변환

	image = temp.clone();
	DisplayImage(IDC_PIC, image);
}

Mat filtroLaplace(cv::Mat src)
{
	cv::Mat output = src.clone();

	for (int y = 1; y < src.rows - 1; y++) {
		for (int x = 1; x < src.cols - 1; x++) {
			int sum = src.at<uchar>(y - 1, x)
				+ src.at<uchar>(y + 1, x)
				+ src.at<uchar>(y, x - 1)
				+ src.at<uchar>(y, x + 1)
				- 4 * src.at<uchar>(y, x);

			output.at<uchar>(y, x) = cv::saturate_cast<uchar>(sum);
		}
	}
	return output;
}

void CCVImageProcessorDlg::OnLaplacianMasking()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (!openCheck()) {
		return;
	}

	imgStack.push(image);
	Mat src, dst;
	int kernel_size = 3;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;
	src = image;
	Mat abs_dst;
	Laplacian(src, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(dst, abs_dst);
	image = abs_dst;
	DisplayImage(IDC_PIC, image);
}


void CCVImageProcessorDlg::OnOpening()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (!openCheck()) {
		return;
	}

	imgStack.push(image);

	Mat temp = image.clone();
	Mat element5(5, 5, CV_8U, cv::Scalar(1));
	morphologyEx(image, temp, MORPH_OPEN, element5);
	image = temp.clone();
	DisplayImage(IDC_PIC, image);
}


void CCVImageProcessorDlg::OnClosing()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (!openCheck()) {
		return;
	}

	imgStack.push(image);

	Mat temp = image.clone();
	Mat element5(5, 5, CV_8U, cv::Scalar(1));
	morphologyEx(image, temp, MORPH_CLOSE, element5);
	image = temp.clone();
	DisplayImage(IDC_PIC, image);
}


void CCVImageProcessorDlg::OnExpandReduce()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (!openCheck()) {
		return;
	}

	ExpandReduceDlg dlg;
	if (dlg.DoModal() == IDOK) {
		imgStack.push(image);
		Mat temp = image.clone();
		int width = (int)(image.cols * ((double)dlg.ratioValue / 100));
		int height = (int)(image.cols * ((double)dlg.ratioValue / 100));
		resize(image, temp, Size(width, height), dlg.num);
		dlg.num = -1;
		image = temp.clone();
		DisplayImage(IDC_PIC, image);
	}
}

void CCVImageProcessorDlg::OnRotate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (!openCheck()) {
		return;
	}

	RotateDlg dlg;
	if (dlg.DoModal() == IDOK) {
		imgStack.push(image);

		Mat temp = image.clone();

		double angle = dlg.rotAngle;

		Point2f center(image.cols / 2.0, image.rows / 2.0);
		Mat rot = cv::getRotationMatrix2D(center, angle, 1.0);

		Rect bbox = cv::RotatedRect(center, image.size(), angle).boundingRect();

		rot.at<double>(0, 2) += bbox.width / 2.0 - center.x;
		rot.at<double>(1, 2) += bbox.height / 2.0 - center.y;

		warpAffine(image, temp, rot, bbox.size());

		image = temp.clone();
		DisplayImage(IDC_PIC, image);
	}
}

