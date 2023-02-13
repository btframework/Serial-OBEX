unit main;

interface

uses
  Forms, StdCtrls, Controls, Classes, ComCtrls, wclSerialClients,
  wclSerialDevices, wclObex, wclConnections, Dialogs;

type
  TfmMain = class(TForm)
    laSelectComPort: TLabel;
    cbPorts: TComboBox;
    btRefresh: TButton;
    btConnect: TButton;
    btDisconnect: TButton;
    btClear: TButton;
    lbLog: TListBox;
    ProgressBar: TProgressBar;
    wclSerialMonitor: TwclSerialMonitor;
    wclSerialClient: TwclSerialClient;
    procedure FormCreate(Sender: TObject);
    procedure btRefreshClick(Sender: TObject);
    procedure btClearClick(Sender: TObject);
    procedure wclSerialMonitorInserted(Sender: TObject;
      const Device: TwclSerialDevice);
    procedure wclSerialMonitorRemoved(Sender: TObject;
      const Device: TwclSerialDevice);
    procedure FormDestroy(Sender: TObject);
    procedure btConnectClick(Sender: TObject);
    procedure btDisconnectClick(Sender: TObject);
    procedure wclSerialClientConnect(Sender: TObject;
      const Error: Integer);
    procedure wclSerialClientDisconnect(Sender: TObject;
      const Reason: Integer);
    procedure wclSerialClientCreateProcessor(Sender: TObject;
      const Connection: TwclClientDataConnection);
    procedure wclSerialClientData(Sender: TObject; const Data: Pointer;
      const Size: Cardinal);

  private
    FOppServer: TwclObexOppServer;

    procedure RefreshComPorts;
    procedure Trace(const Msg: string); overload;
    procedure Trace(const Msg: string; const Res: Integer); overload;

    procedure OppWrite(Sender: TObject; const Data: Pointer;
      const Size: Cardinal; out Written: Cardinal; out WriteResult: Integer);
    procedure OppConnect(Sender: TObject; const Description: string);
    procedure OppDisconnect(Sender: TObject; const Reason: Integer;
      const Description: string);
    procedure OppPutBegin(Sender: TObject; const Name: string;
      const Description: string; const Mime: string; const Length: Cardinal;
      out Accept: Boolean);
    procedure OppPutCompleted(Sender: TObject; const Error: Integer;
      const Stream: TStream; out Accept: Boolean);
    procedure OppPutProgress(Sender: TObject; const Position: Cardinal;
      const Length: Cardinal; out Continue: Boolean);
  end;

var
  fmMain: TfmMain;

implementation

uses
  wclErrors, SysUtils;

{$R *.dfm}

procedure TfmMain.FormCreate(Sender: TObject);
var
  Res: Integer;
begin
  FOppServer := nil;
  
  Res := wclSerialMonitor.Start;
  if Res <> WCL_E_SUCCESS then
    Trace('Start monitoring failed', Res);
  
  RefreshComPorts;
end;

procedure TfmMain.RefreshComPorts;
var
  Devices: TwclSerialDevices;
  Res: Integer;
  i: Integer;
begin
  Res := wclSerialMonitor.EnumDevices(Devices);
  if Res <> WCL_E_SUCCESS then
    ShowMessage('Error: 0x' + IntToHex(Res, 8))
  else begin
    cbPorts.Clear;
    if Length(Devices) > 0 then begin
      for i := 0 to Length(Devices) - 1 do
        cbPorts.Items.Add(Devices[i].DeviceName);
      cbPorts.ItemIndex := 0;
    end;
  end;
end;

procedure TfmMain.Trace(const Msg: string);
begin
  lbLog.Items.Add(Msg);
end;

procedure TfmMain.Trace(const Msg: string; const Res: Integer);
begin
  Trace(Msg + ': 0x' + IntToHex(Res, 8));
end;

procedure TfmMain.btRefreshClick(Sender: TObject);
begin
  RefreshComPorts;
end;

procedure TfmMain.btClearClick(Sender: TObject);
begin
  lbLog.Clear;
end;

procedure TfmMain.wclSerialMonitorInserted(Sender: TObject;
  const Device: TwclSerialDevice);
begin
  Trace('Device inserted: ' + Device.DeviceName);
end;

procedure TfmMain.wclSerialMonitorRemoved(Sender: TObject;
  const Device: TwclSerialDevice);
begin
  Trace('Device removed: ' + Device.DeviceName);
end;

procedure TfmMain.FormDestroy(Sender: TObject);
begin
  wclSerialClient.Disconnect;
  wclSerialMonitor.Stop;
end;

procedure TfmMain.btConnectClick(Sender: TObject);
var
  Res: Integer;
begin
  if cbPorts.Items.Count = 0 then
    ShowMessage('No COM ports found')

  else begin
    try
      wclSerialClient.DeviceName := cbPorts.Items[cbPorts.ItemIndex];
      Res := wclSerialClient.Connect;
      if Res <> WCL_E_SUCCESS then
        ShowMessage('Connect failed: 0x' + IntToHex(Res, 8));
        
    except
      on E: Exception do
        ShowMessage(E.Message);
    end;
  end;
end;

procedure TfmMain.btDisconnectClick(Sender: TObject);
var
  Res: Integer;
begin
  Res := wclSerialClient.Disconnect;
  if Res <> WCL_E_SUCCESS then
    ShowMessage('Disconnect failed: 0x' + IntToHex(Res, 8));
end;

procedure TfmMain.wclSerialClientConnect(Sender: TObject;
  const Error: Integer);
var
  Config: TwclSerialConfig;
begin
  if Error <> WCL_E_SUCCESS then
    Trace('Connect failed', Error)

  else begin
    Trace('Connected');
    
    if wclSerialClient.GetConfig(Config) = WCL_E_SUCCESS then begin
      Config.BaudRate := 115200;
      Config.ByteSize := 8;
      wclSerialClient.SetConfig(Config);
    end;
  end;
end;

procedure TfmMain.wclSerialClientDisconnect(Sender: TObject;
  const Reason: Integer);
begin
  if FOppServer <> nil then begin
    FOppServer.Free;
    FOppServer := nil;
  end;

  Trace('Disconnected with reason', Reason);
end;

procedure TfmMain.wclSerialClientCreateProcessor(Sender: TObject;
  const Connection: TwclClientDataConnection);
begin
  if FOppServer = nil then begin
    FOppServer := TwclObexOppServer.Create(nil, $00FF);
    FOppServer.OnWrite := OppWrite;
    FOppServer.OnConnect := OppConnect;
    FOppServer.OnDisconnected := OppDisconnect;
    FOppServer.OnPutProgress := OppPutProgress;
    FOppServer.OnPutBegin := OppPutBegin;
    FOppServer.OnPutCompleted := OppPutCompleted;
  end;
end;

procedure TfmMain.OppConnect(Sender: TObject; const Description: string);
begin
  Trace('OBEX client connected [' + Description + ']');
  FOppServer.Accept('Accept connection');
end;

procedure TfmMain.OppDisconnect(Sender: TObject; const Reason: Integer;
  const Description: string);
begin
  Trace('OBEX client disconnected with reason', Reason);
  Trace('  [' + Description + ']');
end;

procedure TfmMain.wclSerialClientData(Sender: TObject; const Data: Pointer;
  const Size: Cardinal);
begin
  if FOppServer <> nil then
    FOppServer.ProcessData(Data, Size);
end;

procedure TfmMain.OppWrite(Sender: TObject; const Data: Pointer;
  const Size: Cardinal; out Written: Cardinal; out WriteResult: Integer);
begin
  WriteResult := wclSerialClient.Write(Data, Size, Written);
end;

procedure TfmMain.OppPutBegin(Sender: TObject; const Name: string;
  const Description: string; const Mime: string; const Length: Cardinal;
  out Accept: Boolean);
begin
  Accept := True;
  Trace('Begin sending file: ' + Name);
end;

procedure TfmMain.OppPutCompleted(Sender: TObject; const Error: Integer;
  const Stream: TStream; out Accept: Boolean);
begin
  if Error <> WCL_E_SUCCESS then
    Trace('File receiving error', Error)

  else begin
    Accept := True;
    Trace('File received');
  end;
end;

procedure TfmMain.OppPutProgress(Sender: TObject; const Position: Cardinal;
  const Length: Cardinal; out Continue: Boolean);
begin
  ProgressBar.Max := Length;
  ProgressBar.Position := Position;
  Continue := True;
end;

end.
