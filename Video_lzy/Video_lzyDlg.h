
// Video_lzyDlg.h: 头文件
//

#pragma once


// CVideolzyDlg 对话框
class CVideolzyDlg : public CDialogEx
{
// 构造
public:
	CVideolzyDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VIDEO_LZY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CStatic picView;
	afx_msg void OnStnClickedPic();
	afx_msg void OnBnClickedCamera();
	static bool closeFlag;//关闭监控
	static bool takePhotoFlag;//拍照
	static bool recordFlag;//录像
	void playAVI(CString cfileName);//播放avi视频
	afx_msg void OnBnClickedCloseCamera();
	afx_msg void OnBnClickedPhoto();
	afx_msg void OnBnClickedPhotoPath();
	afx_msg void OnBnClickedRecord();
	afx_msg void OnBnClickedCloseRecord();
	afx_msg void OnBnClickedPlayvideo();
};
