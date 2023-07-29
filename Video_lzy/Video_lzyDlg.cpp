
// Video_lzyDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Video_lzy.h"
#include "afxdialogex.h"
#include "Video_lzyDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//关闭监控标志
bool CVideolzyDlg::closeFlag = false;
//拍照标志
bool CVideolzyDlg::takePhotoFlag = false;
//录像标志
bool CVideolzyDlg::recordFlag = false;
//图片、视频默认存储位置
CString folerPath = L"D:/opencv项目/Video_lzy/resourse/";


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CVideolzyDlg 对话框



CVideolzyDlg::CVideolzyDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_VIDEO_LZY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVideolzyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PIC, picView);
}

BEGIN_MESSAGE_MAP(CVideolzyDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CVideolzyDlg::OnBnClickedOk)
	ON_STN_CLICKED(IDC_PIC, &CVideolzyDlg::OnStnClickedPic)
	ON_BN_CLICKED(ID_CAMERA, &CVideolzyDlg::OnBnClickedCamera)
	ON_BN_CLICKED(IDC_CLOSE_CAMERA, &CVideolzyDlg::OnBnClickedCloseCamera)
	ON_BN_CLICKED(IDC_PHOTO, &CVideolzyDlg::OnBnClickedPhoto)
	ON_BN_CLICKED(IDC_PHOTO_PATH, &CVideolzyDlg::OnBnClickedPhotoPath)
	ON_BN_CLICKED(IDC_RECORD, &CVideolzyDlg::OnBnClickedRecord)
	ON_BN_CLICKED(IDC_CLOSE_RECORD, &CVideolzyDlg::OnBnClickedCloseRecord)
	ON_BN_CLICKED(IDC_PLAYVIDEO, &CVideolzyDlg::OnBnClickedPlayvideo)
END_MESSAGE_MAP()


// CVideolzyDlg 消息处理程序

BOOL CVideolzyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CVideolzyDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CVideolzyDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CVideolzyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CVideolzyDlg::playAVI(CString cfileName) {
	CTime m_time;
	m_time = CTime::GetCurrentTime();
	CString viewTime = m_time.Format("%Y%m%d%H%M%S");
	string viewNameString = CT2A(viewTime.GetBuffer());

	char* viewName = (char*)viewNameString.data();
	cv::namedWindow(viewName);
	HWND hWnd = (HWND)cvGetWindowHandle(viewName);
	HWND hParent = ::GetParent(hWnd);
	::SetParent(hWnd, GetDlgItem(IDC_PIC)->m_hWnd);
	::ShowWindow(hParent, SW_HIDE);

	string fileName = CT2A(cfileName.GetBuffer());
	VideoCapture capture(fileName);

	while (true) {
		Mat frame;
		capture >> frame;

		if (frame.empty()) break;
		try {
			cvtColor(frame, frame, COLOR_GRAY2BGR); 
		}
		catch (cv::Exception& e) {
			OutputDebugStringA(e.what()+ '\n');
		}
		imshow(viewName, frame);

		int key = waitKey(50);
		if (key == 27) break;
	}

	capture.release();
}

void CVideolzyDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	

	VideoCapture cap(0);
	if (!cap.isOpened()) {
		cout << "无法打开摄像头" << std::endl;
	}
	bool isPaused = false; // 是否暂停播放

	while (true) {
		Mat cam;
		cap >> cam;

		if (!isPaused) {
			imshow("picView", cam);
		}

		// 等待10毫秒，检测键盘输入
		int key = waitKey(10);

		// 如果按下回车键（ASCII码为13），则退出循环
		if (key == 27) { // 按下ESC键，切换暂停和继续播放状态
			isPaused = !isPaused;
		}
	}
	
}


void CVideolzyDlg::OnStnClickedPic()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CVideolzyDlg::OnBnClickedCamera()
{
	// TODO: 在此添加控件通知处理程序代码

	//获取时间
	CTime m_time;
	m_time = CTime::GetCurrentTime();
	CString viewTime = m_time.Format(_T("%Y%m%d%H%M%S"));
	string viewTitleString = CT2A(viewTime.GetBuffer());
	char* viewName = (char*)viewTitleString.data();

	CVideolzyDlg::closeFlag = false;
	//摄像头界面嵌套入对话框
	cv::namedWindow(viewName, cv::WINDOW_AUTOSIZE);//创建一个picview窗口
	HWND hWnd = (HWND)cvGetWindowHandle(viewName);//获取窗口句柄
	HWND hParent = ::GetParent(hWnd);//获取图像显示窗口的父窗口句柄
	::SetParent(hWnd, GetDlgItem(IDC_PIC)->m_hWnd);//替代父窗口句柄
	::ShowWindow(hParent, SW_HIDE);//隐藏原来的父窗口句柄

	//1.从摄像头读入视频
	VideoCapture cap(0);
	//2.循环显示每一帧
	while (1)
	{
		Mat cam;
		cap >> cam;//获取当前帧图像
		imshow(viewName, cam);//显示当前帧图像
		if (closeFlag) { 
		cap.release();//不用就把摄像头资源释放
		break; }
		waitKey(30);//延时30秒
	}
}


void CVideolzyDlg::OnBnClickedCloseCamera()
{
	// TODO: 在此添加控件通知处理程序代码
	CVideolzyDlg::closeFlag = true;
}


void CVideolzyDlg::OnBnClickedPhoto()
{
	// TODO: 在此添加控件通知处理程序代码
	takePhotoFlag = true;
	VideoCapture cap(0);

	if (takePhotoFlag) {


		//获取时间
		CTime m_time;
		m_time = CTime::GetCurrentTime();
		CString viewTime = m_time.Format(_T("%Y%m%d%H%M%S"));
		string viewTitleString = CT2A(viewTime.GetBuffer());
		char* viewName = (char*)viewTitleString.data();

		CVideolzyDlg::closeFlag = false;
		//摄像头界面嵌套入对话框
		cv::namedWindow(viewName, cv::WINDOW_AUTOSIZE);//创建一个picview窗口
		HWND hWnd = (HWND)cvGetWindowHandle(viewName);//获取窗口句柄
		HWND hParent = ::GetParent(hWnd);//获取图像显示窗口的父窗口句柄
		::SetParent(hWnd, GetDlgItem(IDC_PIC)->m_hWnd);//替代父窗口句柄
		::ShowWindow(hParent, SW_HIDE);//隐藏原来的父窗口句柄
		CString m_strDateTime = folerPath + m_time.Format(_T("%Y%m%d%H%M%S.jpg"));
		string name = CT2A(m_strDateTime.GetBuffer());

		Mat cam;
		cap >> cam;
		imshow(viewName, cam);
		takePhotoFlag = false;

		//写入文件
		bool res = imwrite(name, cam);
			
	}
}


void CVideolzyDlg::OnBnClickedPhotoPath()
{
	// TODO: 在此添加控件通知处理程序代码
	CreateDirectory(folerPath, NULL);
	ShellExecute(NULL, NULL, folerPath, NULL, NULL, SW_SHOW);
}


void CVideolzyDlg::OnBnClickedRecord()
{
	// TODO: 在此添加控件通知处理程序代码

	VideoCapture capture(0);
	//获取视频参数
	int width = capture.get(CAP_PROP_FRAME_WIDTH);
	int height = capture.get(CAP_PROP_FRAME_HEIGHT);
	int count = capture.get(CAP_PROP_FRAME_COUNT);
	double fps = capture.get(CAP_PROP_FPS);

	CTime m_time;
	m_time = CTime::GetCurrentTime();
	CString videoNameCString = folerPath + m_time.Format(_T("%Y%m%d%H%M%S.avi"));
	string videoName = CT2A(videoNameCString.GetBuffer());

	//将图像序列写入视频文件
	VideoWriter writer(videoName, VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, Size(width, height), true);

	//生成监控名
	Mat frame;
	CString viewNameCString = folerPath + m_time.Format(_T("%Y%m%d%H%M%S"));
	string viewNameString = CT2A(viewNameCString.GetBuffer());

	char* viewName = (char*)viewNameString.data();
	cv::namedWindow(viewName, cv::WINDOW_AUTOSIZE);
	HWND hWnd = (HWND)cvGetWindowHandle(viewName);
	HWND hParent = ::GetParent(hWnd);
	::SetParent(hWnd, GetDlgItem(IDC_PIC)->m_hWnd);
	::ShowWindow(hParent, SW_HIDE);

	while (true) {
		capture.read(frame);
		//flip(frame, frame, 1);
		if (frame.empty()) break;
		imshow(viewName, frame);
		writer.write(frame);
		waitKey(30);
		if (recordFlag) {
			capture.release();
			break;
		}
	}
	recordFlag = false;
	writer.release();
}


void CVideolzyDlg::OnBnClickedCloseRecord()
{
	// TODO: 在此添加控件通知处理程序代码
	recordFlag = true;
}


void CVideolzyDlg::OnBnClickedPlayvideo()
{
	// TODO: 在此添加控件通知处理程序代码

		// 公共对话框结构。   
	OPENFILENAME ofn;
	// 保存获取文件名称的缓冲区。
	TCHAR szFile[MAX_PATH];
	// 初始化选择文件对话框。   
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = L"All(*.*)\0*.*\0Text(*.txt)\0*.AVI\0\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	//ofn.lpTemplateName =  MAKEINTRESOURCE(ID_TEMP_DIALOG);  
	// 显示打开选择文件对话框。   

	if (GetOpenFileName(&ofn))
	{
		//显示选择的文件。   
		OutputDebugString(szFile);
		playAVI(szFile);
	}

}
