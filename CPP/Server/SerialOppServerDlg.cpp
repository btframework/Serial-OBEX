
// SerialOppServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SerialOppServer.h"
#include "SerialOppServerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CString IntToHex(int i)
{
	CString s;
	s.Format(_T("%.8X"), i);
	return s;
}

// CSerialOppServerDlg dialog



CSerialOppServerDlg::CSerialOppServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SERIALOPPSERVER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSerialOppServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_PORTS, cbPorts);
	DDX_Control(pDX, IDC_LIST_LOG, lbLog);
	DDX_Control(pDX, IDC_PROGRESS, ProgressBar);
}

BEGIN_MESSAGE_MAP(CSerialOppServerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_REFRESH, &CSerialOppServerDlg::OnBnClickedButtonRefresh)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CSerialOppServerDlg::OnBnClickedButtonClear)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CSerialOppServerDlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT, &CSerialOppServerDlg::OnBnClickedButtonDisconnect)
END_MESSAGE_MAP()


// CSerialOppServerDlg message handlers

BOOL CSerialOppServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	__hook(&CwclSerialMonitor::OnInserted, &wclSerialMonitor, &CSerialOppServerDlg::SerialMonitorInserted);
	__hook(&CwclSerialMonitor::OnRemoved, &wclSerialMonitor, &CSerialOppServerDlg::SerialMonitorRemoved);

	__hook(&CwclSerialClient::OnConnect, &wclSerialClient, &CSerialOppServerDlg::SerialClientConnect);
	__hook(&CwclSerialClient::OnDisconnect, &wclSerialClient, &CSerialOppServerDlg::SerialClientDisconnect);
	__hook(&CwclSerialClient::OnCreateProcessor, &wclSerialClient, &CSerialOppServerDlg::SerialClientCreateProcessor);
	__hook(&CwclSerialClient::OnData, &wclSerialClient, &CSerialOppServerDlg::SerialClientData);

	FOppServer = NULL;
	
	int Res = wclSerialMonitor.Start();
	if (Res != WCL_E_SUCCESS)
		Trace(_T("Start monitoring failed"), Res);
	
	RefreshComPorts();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSerialOppServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSerialOppServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSerialOppServerDlg::RefreshComPorts()
{
	wclSerialDevices Devices;
	int Res = wclSerialMonitor.EnumDevices(Devices);
	if (Res != WCL_E_SUCCESS)
		AfxMessageBox(_T("Error: 0x") + IntToHex(Res));
	else
	{
		cbPorts.ResetContent();
		if (Devices.size() > 0)
		{
			for (wclSerialDevices::iterator Device = Devices.begin(); Device != Devices.end(); Device++)
				cbPorts.AddString(((*Device).DeviceName).c_str());
			cbPorts.SetCurSel(0);
		}
	}
}

void CSerialOppServerDlg::Trace(const CString& Msg)
{
	lbLog.AddString(Msg);
}

void CSerialOppServerDlg::Trace(const CString& Msg, const int Res)
{
	Trace(Msg + _T(": 0x") + IntToHex(Res));
}

void CSerialOppServerDlg::OnBnClickedButtonRefresh()
{
	RefreshComPorts();
}

void CSerialOppServerDlg::OnBnClickedButtonClear()
{
	lbLog.ResetContent();
}

void CSerialOppServerDlg::SerialMonitorInserted(void* Sender, const wclSerialDevice& Device)
{
	Trace(_T("Device inserted: ") + CString(Device.DeviceName.c_str()));
}

void CSerialOppServerDlg::SerialMonitorRemoved(void* Sender, const wclSerialDevice& Device)
{
	Trace(_T("Device removed: ") + CString(Device.DeviceName.c_str()));
}

void CSerialOppServerDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	wclSerialClient.Disconnect();
	wclSerialMonitor.Stop();

	__unhook(&wclSerialMonitor);
	__unhook(&wclSerialClient);
}

void CSerialOppServerDlg::OnBnClickedButtonConnect()
{
	if (cbPorts.GetCount() == 0)
		AfxMessageBox(_T("No COM ports found"));
	else
	{
		CString Sel;
		cbPorts.GetLBText(cbPorts.GetCurSel(), Sel);
		wclSerialClient.DeviceName = Sel.GetBuffer();
		int Res = wclSerialClient.Connect();
		if (Res != WCL_E_SUCCESS)
			AfxMessageBox(_T("Connect failed: 0x") + IntToHex(Res));
	}
}

void CSerialOppServerDlg::OnBnClickedButtonDisconnect()
{
	int Res = wclSerialClient.Disconnect();
	if (Res != WCL_E_SUCCESS)
		AfxMessageBox(_T("Disconnect failed: 0x") + IntToHex(Res));
}

void CSerialOppServerDlg::SerialClientConnect(void* Sender, const int Error)
{
	if (Error != WCL_E_SUCCESS)
		Trace(_T("Connect failed"), Error);
	else
	{
		Trace(_T("Connected"));

		wclSerialConfig Config;
		if (wclSerialClient.GetConfig(Config) == WCL_E_SUCCESS)
		{
			Config.BaudRate = 115200;
			Config.ByteSize = 8;
			wclSerialClient.SetConfig(Config);
		}
	}
}

void CSerialOppServerDlg::SerialClientDisconnect(void* Sender, const int Reason)
{
	if (FOppServer != NULL)
	{
		__unhook(FOppServer);
		delete FOppServer;
		FOppServer = NULL;
	}

	Trace(_T("Disconnected with reason"), Reason);
}

void CSerialOppServerDlg::SerialClientCreateProcessor(void* Sender,
	CwclClientDataConnection* const Connection)
{
	if (FOppServer == NULL)
	{
		FOppServer = new CwclObexOppServer(NULL);
		__hook(&CwclObexOppServer::OnConnect, FOppServer, &CSerialOppServerDlg::OppConnect);
		__hook(&CwclObexOppServer::OnDisconnected, FOppServer, &CSerialOppServerDlg::OppDisconnect);
		__hook(&CwclObexOppServer::OnWrite, FOppServer, &CSerialOppServerDlg::OppWrite);
		__hook(&CwclObexOppServer::OnPutBegin, FOppServer, &CSerialOppServerDlg::OppPutBegin);
		__hook(&CwclObexOppServer::OnPutCompleted, FOppServer, &CSerialOppServerDlg::OppPutCompleted);
		__hook(&CwclObexOppServer::OnPutProgress, FOppServer, &CSerialOppServerDlg::OppPutProgress);
	}
}

void CSerialOppServerDlg::OppConnect(void* Sender, const tstring& Description)
{
	Trace(_T("OBEX client connected [") + CString(Description.c_str()) + _T("]"));
	FOppServer->Accept(_T("Accept connection"), 0x00FF);
}

void CSerialOppServerDlg::OppDisconnect(void* Sender, const int Reason, const tstring& Description)
{
	Trace(_T("OBEX client disconnected with reason"), Reason);
	Trace(_T("  [") + CString(Description.c_str()) + _T("]"));
}

void CSerialOppServerDlg::SerialClientData(void* Sender, const void* Data,
	const unsigned long Size)
{
	if (FOppServer != NULL)
		FOppServer->ProcessData(Data, Size);
}

void CSerialOppServerDlg::OppWrite(void* Sender, const void* Data,
	const unsigned long Size, unsigned long& Written, int& WriteResult)
{
	WriteResult = wclSerialClient.Write(Data, Size, Written);
}

void CSerialOppServerDlg::OppPutBegin(void* Sender, const tstring& Name,
	const tstring& Description, const tstring& Mime, const unsigned long Length,
	bool& Accept)
{
	Accept = true;
	Trace(_T("Begin sending file: ") + CString(Name.c_str()));
}

void CSerialOppServerDlg::OppPutCompleted(void* Sender, const int Error, CwclStream* Stream,
	bool& Accept)
{
	if (Error != WCL_E_SUCCESS)
		Trace(_T("File receiving error"), Error);
	else
	{
		Accept = true;
		Trace(_T("File received"));
	}
}

void CSerialOppServerDlg::OppPutProgress(void* Sender, const unsigned long Position,
	const unsigned long Length, bool& Continue)
{
	ProgressBar.SetRange32(0, Length);
	ProgressBar.SetPos(Position);
	Continue = true;
}