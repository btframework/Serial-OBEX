object fmMain: TfmMain
  Left = 515
  Top = 297
  BorderStyle = bsSingle
  Caption = 'Serial OPP Client'
  ClientHeight = 458
  ClientWidth = 494
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object laSelectComPort: TLabel
    Left = 8
    Top = 16
    Width = 79
    Height = 13
    Caption = 'Select COM Port'
  end
  object laFilePath: TLabel
    Left = 8
    Top = 80
    Width = 40
    Height = 13
    Caption = 'File path'
  end
  object cbPorts: TComboBox
    Left = 96
    Top = 8
    Width = 145
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 0
  end
  object btRefresh: TButton
    Left = 248
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Refresh'
    TabOrder = 1
    OnClick = btRefreshClick
  end
  object btConnect: TButton
    Left = 328
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Connect'
    TabOrder = 2
    OnClick = btConnectClick
  end
  object btDisconnect: TButton
    Left = 408
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Disconnect'
    TabOrder = 3
    OnClick = btDisconnectClick
  end
  object lbLog: TListBox
    Left = 8
    Top = 160
    Width = 473
    Height = 289
    ItemHeight = 13
    TabOrder = 4
  end
  object btClear: TButton
    Left = 408
    Top = 128
    Width = 75
    Height = 25
    Caption = 'Clear'
    TabOrder = 5
    OnClick = btClearClick
  end
  object btObexConnect: TButton
    Left = 8
    Top = 40
    Width = 105
    Height = 25
    Caption = 'OBEX Connect'
    TabOrder = 6
    OnClick = btObexConnectClick
  end
  object btObexDisconnect: TButton
    Left = 120
    Top = 40
    Width = 105
    Height = 25
    Caption = 'OBEX disconnect'
    TabOrder = 7
    OnClick = btObexDisconnectClick
  end
  object edFilePath: TEdit
    Left = 64
    Top = 72
    Width = 257
    Height = 21
    TabOrder = 8
  end
  object btSelectFile: TButton
    Left = 328
    Top = 72
    Width = 75
    Height = 25
    Caption = 'Select file'
    TabOrder = 9
    OnClick = btSelectFileClick
  end
  object btSendFile: TButton
    Left = 408
    Top = 72
    Width = 75
    Height = 25
    Caption = 'Send file'
    TabOrder = 10
    OnClick = btSendFileClick
  end
  object ProgressBar: TProgressBar
    Left = 8
    Top = 104
    Width = 473
    Height = 17
    Min = 0
    Max = 100
    TabOrder = 11
  end
  object wclSerialMonitor: TwclSerialMonitor
    OnInserted = wclSerialMonitorInserted
    OnRemoved = wclSerialMonitorRemoved
    Left = 160
    Top = 272
  end
  object wclSerialClient: TwclSerialClient
    DeviceName = 'COM1'
    WriteTimeout = 5000
    OnConnect = wclSerialClientConnect
    OnCreateProcessor = wclSerialClientCreateProcessor
    OnDestroyProcessor = wclSerialClientDestroyProcessor
    OnDisconnect = wclSerialClientDisconnect
    Left = 280
    Top = 272
  end
  object OpenDialog: TOpenDialog
    Options = [ofReadOnly, ofPathMustExist, ofFileMustExist, ofNoTestFileCreate, ofNoNetworkButton, ofEnableSizing]
    Title = 'Select file for sending'
    Left = 328
    Top = 32
  end
end
