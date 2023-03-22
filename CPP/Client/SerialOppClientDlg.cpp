
// SerialOppClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SerialOppClient.h"
#include "SerialOppClientDlg.h"
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

// CSerialOppClientDlg dialog



CSerialOppClientDlg::CSerialOppClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SerialOppClient_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSerialOppClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_PORTS, cbPorts);
	DDX_Control(pDX, IDC_EDIT_FILE_PATH, edFilePath);
	DDX_Control(pDX, IDC_PROGRESS, ProgressBar);
	DDX_Control(pDX, IDC_LIST_LOG, lbLog);
}

BEGIN_MESSAGE_MAP(CSerialOppClientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_REFRESH, &CSerialOppClientDlg::OnBnClickedButtonRefresh)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CSerialOppClientDlg::OnBnClickedButtonClear)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CSerialOppClientDlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT, &CSerialOppClientDlg::OnBnClickedButtonDisconnect)
	ON_BN_CLICKED(IDC_BUTTON_OBEX_CONNECT, &CSerialOppClientDlg::OnBnClickedButtonObexConnect)
	ON_BN_CLICKED(IDC_BUTTON_OBEX_DISCONNECT, &CSerialOppClientDlg::OnBnClickedButtonObexDisconnect)
	ON_BN_CLICKED(IDC_BUTTON_SEND_FILE, &CSerialOppClientDlg::OnBnClickedButtonSendFile)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_FILE, &CSerialOppClientDlg::OnBnClickedButtonSelectFile)
END_MESSAGE_MAP()


// CSerialOppClientDlg message handlers

BOOL CSerialOppClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	__hook(&CwclSerialMonitor::OnInserted, &wclSerialMonitor, &CSerialOppClientDlg::SerialMonitorInserted);
	__hook(&CwclSerialMonitor::OnRemoved, &wclSerialMonitor, &CSerialOppClientDlg::SerialMonitorRemoved);

	__hook(&CwclSerialClient::OnConnect, &wclSerialClient, &CSerialOppClientDlg::SerialClientConnect);
	__hook(&CwclSerialClient::OnDisconnect, &wclSerialClient, &CSerialOppClientDlg::SerialClientDisconnect);
	__hook(&CwclSerialClient::OnCreateProcessor, &wclSerialClient, &CSerialOppClientDlg::SerialClientCreateProcessor);
	__hook(&CwclSerialClient::OnDestroyProcessor, &wclSerialClient, &CSerialOppClientDlg::SerialClientDestroyProcessor);

	// TODO: Add extra initialization here
	int Res = wclSerialMonitor.Start();
	if (Res != WCL_E_SUCCESS)
		Trace(_T("Start monitoring failed"), Res);
	
	RefreshComPorts();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSerialOppClientDlg::OnPaint()
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
HCURSOR CSerialOppClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSerialOppClientDlg::OnBnClickedButtonRefresh()
{
	RefreshComPorts();
}

void CSerialOppClientDlg::RefreshComPorts()
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

void CSerialOppClientDlg::OnBnClickedButtonClear()
{
	lbLog.ResetContent();
}

void CSerialOppClientDlg::SerialMonitorInserted(void* Sender, const wclSerialDevice& Device)
{
	Trace(_T("Device inserted: ") + CString(Device.DeviceName.c_str()));
}

void CSerialOppClientDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	wclSerialClient.Disconnect();
	wclSerialMonitor.Stop();

	__unhook(&wclSerialMonitor);
	__unhook(&wclSerialClient);
}

void CSerialOppClientDlg::Trace(const CString& Msg)
{
	lbLog.AddString(Msg);
}

void CSerialOppClientDlg::Trace(const CString& Msg, const int Res)
{
	Trace(Msg + _T(": 0x") + IntToHex(Res));
}

void CSerialOppClientDlg::SerialMonitorRemoved(void* Sender, const wclSerialDevice& Device)
{
	Trace(_T("Device removed: ") + CString(Device.DeviceName.c_str()));
}

void CSerialOppClientDlg::OnBnClickedButtonConnect()
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

void CSerialOppClientDlg::OnBnClickedButtonDisconnect()
{
	int Res = wclSerialClient.Disconnect();
	if (Res != WCL_E_SUCCESS)
		AfxMessageBox(_T("Disconnect failed: 0x") + IntToHex(Res));
}

void CSerialOppClientDlg::SerialClientConnect(void* Sender, const int Error)
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

void CSerialOppClientDlg::SerialClientDisconnect(void* Sender, const int Reason)
{
	Trace(_T("Disconnected with reason"), Reason);
}

void CSerialOppClientDlg::SerialClientCreateProcessor(void* Sender,
	CwclClientDataConnection* const Connection)
{
	CwclObexOppClient* Proc = new CwclObexOppClient(Connection);
	__hook(&CwclObexOppClient::OnConnect, Proc, &CSerialOppClientDlg::OppConnect);
	__hook(&CwclObexOppClient::OnDisconnect, Proc, &CSerialOppClientDlg::OppDisconnect);
	__hook(&CwclObexOppClient::OnProgress, Proc, &CSerialOppClientDlg::OppProgress);
	__hook(&CwclObexOppClient::OnPutComplete, Proc, &CSerialOppClientDlg::OppPutComplete);
}

void CSerialOppClientDlg::SerialClientDestroyProcessor(void* Sender,
	CwclClientDataConnection* const Connection)
{
	CwclObexOppClient* Proc = (CwclObexOppClient*)Connection->Processor;
	if (Proc != NULL)
	{
		__unhook(Proc);
		delete Proc;
	}
}

void CSerialOppClientDlg::OppConnect(void* Sender, const int Error, const tstring& Description)
{
	if (Error != WCL_E_SUCCESS)
	{
		Trace(_T("OBEX connect failed"), Error);
		Trace(_T("  [") + CString(Description.c_str()) + _T("]"));
	}
	else
		Trace(_T("OBEX connected"));
}

void CSerialOppClientDlg::OppDisconnect(void* Sender, const int Error,
	const tstring& Description)
{
	Trace(_T("OBEX disconnect with reason"), Error);
	Trace(_T("  [") + CString(Description.c_str()) + _T("]"));
}

void CSerialOppClientDlg::OppProgress(void* Sender, const unsigned long Length,
	const unsigned long Position)
{
	ProgressBar.SetRange32(0, Length);
	ProgressBar.SetPos(Position);
}

void CSerialOppClientDlg::OppPutComplete(void* Sender, const int Error,
	const tstring& Description, CwclStream* const Stream)
{
	Trace(_T("Put completed"), Error);
	Trace(_T("  [") + CString(Description.c_str()) + _T("]"));
	delete Stream;
}

void CSerialOppClientDlg::OnBnClickedButtonObexConnect()
{
	if (wclSerialClient.Processor == NULL)
		AfxMessageBox(_T("Port not connected"));
	else
	{
		int Res = ((CwclObexOppClient*)wclSerialClient.Processor)->Connect(0x00FF);
		if (Res != WCL_E_SUCCESS)
			AfxMessageBox(_T("OBEX connect failed: 0x") + IntToHex(Res));
	}
}

void CSerialOppClientDlg::OnBnClickedButtonObexDisconnect()
{
	if (wclSerialClient.Processor == NULL)
		AfxMessageBox(_T("OBEX not connected"));
	else
	{
		int Res = ((CwclObexOppClient*)wclSerialClient.Processor)->Disconnect(_T("Disconnect by user"));
		if (Res != WCL_E_SUCCESS)
			AfxMessageBox(_T("OBEX disconnect failed: 0x") + IntToHex(Res));
	}
}

void CSerialOppClientDlg::OnBnClickedButtonSendFile()
{
	CString FilePath;
	edFilePath.GetWindowText(FilePath);
	if (FilePath == _T(""))
		AfxMessageBox(_T("Select file"));
	else
	{
		if (wclSerialClient.Processor == NULL)
			AfxMessageBox(_T("Not connected"));
		else
		{
			tstring FileName = tstring(FilePath.GetBuffer());
			CwclFileStream* Stream = new CwclFileStream(FileName, OPEN_EXISTING, GENERIC_READ,
				FILE_SHARE_READ);
			size_t last_slash_idx = FileName.find_last_of(_T("\\/"));
			if (tstring::npos != last_slash_idx)
				FileName.erase(0, last_slash_idx + 1);
			int Res = ((CwclObexOppClient*)wclSerialClient.Processor)->Put(FileName,
				_T("Serial OPP"), Stream);
			if (Res != WCL_E_SUCCESS)
			{
				AfxMessageBox(_T("Send failed: 0x") + IntToHex(Res));
				delete Stream;
			}
			else
			{
				ProgressBar.SetPos(0);
				ProgressBar.SetRange32(0, 0);
			}
		}
	}
}

void CSerialOppClientDlg::OnBnClickedButtonSelectFile()
{
	CFileDialog Dlg(TRUE);
	if (Dlg.DoModal() == IDOK)
		edFilePath.SetWindowText(Dlg.GetPathName());
}
