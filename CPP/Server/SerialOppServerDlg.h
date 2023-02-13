
// SerialOppServerDlg.h : header file
//

#pragma once
#include "afxwin.h"

#include "..\Lib\Serial\wclSerialDevices.h"
#include "..\Lib\Serial\wclSerialClients.h"
#include "..\Lib\Communication\wclObex.h"
#include "afxcmn.h"

using namespace wclSerial;
using namespace wclCommon;
using namespace wclCommunication;


// CSerialOppServerDlg dialog
class CSerialOppServerDlg : public CDialogEx
{
// Construction
public:
	CSerialOppServerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SERIALOPPSERVER_DIALOG };
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
	CListBox lbLog;
	CProgressCtrl ProgressBar;

	CwclObexOppServer* FOppServer;
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
	void SerialClientData(void* Sender, const void* Data, const unsigned long Size);

	void OppConnect(void* Sender, const tstring& Description);
	void OppDisconnect(void* Sender, const int Reason, const tstring& Description);
	void OppWrite(void* Sender, const void* Data, const unsigned long Size,
		unsigned long& Written, int& WriteResult);
	void OppPutBegin(void* Sender, const tstring& Name, const tstring& Description,
		const tstring& Mime, const unsigned long Length, bool& Accept);
	void OppPutCompleted(void* Sender, const int Error, CwclStream* Stream, bool& Accept);
	void OppPutProgress(void* Sender, const unsigned long Position, const unsigned long Length,
		bool& Continue);

public:
	afx_msg void OnBnClickedButtonRefresh();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonDisconnect();
};
