unit main;

interface

uses
  Forms, StdCtrls, Controls, Classes, wclSerialDevices, wclSerialClients,
  wclConnections, wclObex, Dialogs, ComCtrls;

type
  TfmMain = class(TForm)
    laSelectComPort: TLabel;
    cbPorts: TComboBox;
    btRefresh: TButton;
    btConnect: TButton;
    btDisconnect: TButton;
    wclSerialMonitor: TwclSerialMonitor;
    wclSerialClient: TwclSerialClient;
    lbLog: TListBox;
    btClear: TButton;
    btObexConnect: TButton;
    btObexDisconnect: TButton;
    laFilePath: TLabel;
    edFilePath: TEdit;
    btSelectFile: TButton;
    btSendFile: TButton;
    OpenDialog: TOpenDialog;
    ProgressBar: TProgressBar;
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
    procedure wclSerialClientDestroyProcessor(Sender: TObject;
      const Connection: TwclClientDataConnection);
    procedure btObexConnectClick(Sender: TObject);
    procedure btObexDisconnectClick(Sender: TObject);
    procedure btSelectFileClick(Sender: TObject);
    procedure btSendFileClick(Sender: TObject);

  private
    procedure RefreshComPorts;
    procedure Trace(const Msg: string); overload;
    procedure Trace(const Msg: string; const Res: Integer); overload;

    procedure OppConnect(Sender: TObject; const Error: Integer;
      const Description: string);
    procedure OppDisconnect(Sender: TObject; const Error: Integer;
      const Description: string);
    procedure OppProgress(Sender: TObject; const Length: Cardinal;
      const Position: Cardinal);
    procedure OppPutComplete(Sender: TObject; const Error: Integer;
      const Description: string; const Stream: TStream);
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
  Res := wclSerialMonitor.Start;
  if Res <> WCL_E_SUCCESS then
    Trace('Start monitoring failed', Res);
  
  RefreshComPorts;
end;

procedure TfmMain.btRefreshClick(Sender: TObject);
begin
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

procedure TfmMain.btClearClick(Sender: TObject);
begin
  lbLog.Clear;
end;

procedure TfmMain.wclSerialMonitorInserted(Sender: TObject;
  const Device: TwclSerialDevice);
begin
  Trace('Device inserted: ' + Device.DeviceName);
end;

procedure TfmMain.Trace(const Msg: string);
begin
  lbLog.Items.Add(Msg);
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

procedure TfmMain.Trace(const Msg: string; const Res: Integer);
begin
  Trace(Msg + ': 0x' + IntToHex(Res, 8));
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
begin
  if Error <> WCL_E_SUCCESS then
    Trace('Connect failed', Error)
  else
    Trace('Connected');
end;

procedure TfmMain.wclSerialClientDisconnect(Sender: TObject;
  const Reason: Integer);
begin
  Trace('Disconnected with reason', Reason);
end;

procedure TfmMain.wclSerialClientCreateProcessor(Sender: TObject;
  const Connection: TwclClientDataConnection);
var
  Proc: TwclObexOppClient;
begin
  Proc := TwclObexOppClient.Create(Connection);
  Proc.OnConnect := OppConnect;
  Proc.OnDisconnect := OppDisconnect;
  Proc.OnProgress := OppProgress;
  Proc.OnPutComplete := OppPutComplete;
end;

procedure TfmMain.wclSerialClientDestroyProcessor(Sender: TObject;
  const Connection: TwclClientDataConnection);
begin
  if Connection.Processor <> nil then
    Connection.Processor.Free;
end;

procedure TfmMain.OppConnect(Sender: TObject; const Error: Integer;
  const Description: string);
begin
  if Error <> WCL_E_SUCCESS then begin
    Trace('OBEX connect failed', Error);
    Trace('  [' + Description + ']');
  end else
    Trace('OBEX connected');
end;

procedure TfmMain.OppDisconnect(Sender: TObject; const Error: Integer;
  const Description: string);
begin
  Trace('OBEX disconnect with reason', Error);
  Trace('  [' + Description + ']');
end;

procedure TfmMain.btObexConnectClick(Sender: TObject);
var
  Res: Integer;
begin
  if wclSerialClient.Processor = nil then
    ShowMessage('Port not connected')

  else begin
    Res := TwclObexOppClient(wclSerialClient.Processor).Connect;
    if Res <> WCL_E_SUCCESS then
      ShowMessage('OBEX connect failed: 0x' + IntToHex(Res, 8));
  end;
end;

procedure TfmMain.btObexDisconnectClick(Sender: TObject);
var
  Res: Integer;
begin
  if wclSerialClient.Processor = nil then
    ShowMessage('OBEX not connected')

  else begin
    Res := TwclObexOppClient(wclSerialClient.Processor).Disconnect('Disconnect by user');
    if Res <> WCL_E_SUCCESS then
      ShowMessage('OBEX disconnect failed: 0x' + IntToHex(Res, 8));
  end;
end;

procedure TfmMain.btSelectFileClick(Sender: TObject);
begin
  if OpenDialog.Execute then
    edFilePath.Text := OpenDialog.FileName;
end;

procedure TfmMain.OppProgress(Sender: TObject; const Length: Cardinal;
  const Position: Cardinal);
begin
  ProgressBar.Max := Length;
  ProgressBar.Position := Position;
end;

procedure TfmMain.OppPutComplete(Sender: TObject; const Error: Integer;
  const Description: string; const Stream: TStream);
begin
  Trace('Put completed', Error);
  Trace('  [' + Description + ']');
  Stream.Free;
end;

procedure TfmMain.btSendFileClick(Sender: TObject);
var
  Stream: TFileStream;
  Res: Integer;
begin
  if edFilePath.Text = '' then
    ShowMessage('Select file')

  else begin
    if wclSerialClient.Processor = nil then
      ShowMessage('Not connected')

    else begin
      try
        Stream := TFileStream.Create(edFilePath.Text, fmOpenRead);
        Res := TwclObexOppClient(wclSerialClient.Processor).Put(
          ExtractFileName(edFilePath.Text), 'Serial OPP', Stream);
        if Res <> WCL_E_SUCCESS then begin
          ShowMessage('Send failed: 0x' + IntToHex(Res, 8));
          Stream.Free;

        end else begin
          ProgressBar.Position := 0;
          ProgressBar.Max := 0;
        end;

      except
        on E: Exception do
          ShowMessage(E.Message);
      end;
    end;
  end;
end;

end.
