
// SerialOppClientDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#include "..\Lib\Serial\wclSerialDevices.h"
#include "..\Lib\Serial\wclSerialClients.h"
#include "..\Lib\Communication\wclObex.h"

using namespace wclSerial;
using namespace wclCommon;
using namespace wclCommunication;


// CSerialOppClientDlg dialog
class CSerialOppClientDlg : public CDialogEx
{
// Construction
public:
	CSerialOppClientDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SerialOppClient_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	CComboBox cbPorts;
	CEdit edFilePath;
	CProgressCtrl ProgressBar;
	CListBox lbLog;

	CwclSerialMonitor wclSerialMonitor;
	CwclSerialClient wclSerialClient;

	void RefreshComPorts();
	void Trace(const CString& Msg);
	void Trace(const CString& Msg, const int Res);

	void SerialMonitorInserted(void* Sender, const wclSerialDevice& Device);
	void SerialMonitorRemoved(void* Sender, const wclSerialDevice& Device);

	void SerialClientConnect(void* Sender, const int Error);
	void SerialClientDisconnect(void* Sender, const int Reason);
	void SerialClientCreateProcessor(void* Sender, CwclClientDataConnection* const Connection);
	void SerialClientDestroyProcessor(void* Sender, CwclClientDataConnection* const Connection);

	void OppConnect(void* Sender, const int Error, const tstring& Description);
	void OppDisconnect(void* Sender, const int Error, const tstring& Description);
	void OppProgress(void* Sender, const unsigned long Length, const unsigned long Position);
	void OppPutComplete(void* Sender, const int Error, const tstring& Description,
		CwclStream* const Stream);

public:
	afx_msg void OnBnClickedButtonRefresh();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonDisconnect();
	afx_msg void OnBnClickedButtonObexConnect();
	afx_msg void OnBnClickedButtonObexDisconnect();
	afx_msg void OnBnClickedButtonSendFile();
	afx_msg void OnBnClickedButtonSelectFile();
};
