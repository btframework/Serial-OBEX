object fmMain: TfmMain
  Left = 584
  Top = 341
  BorderStyle = bsSingle
  Caption = 'Serial OPP Server'
  ClientHeight = 459
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
  object btClear: TButton
    Left = 408
    Top = 64
    Width = 75
    Height = 25
    Caption = 'Clear'
    TabOrder = 4
    OnClick = btClearClick
  end
  object lbLog: TListBox
    Left = 8
    Top = 96
    Width = 473
    Height = 353
    ItemHeight = 13
    TabOrder = 5
  end
  object ProgressBar: TProgressBar
    Left = 8
    Top = 40
    Width = 473
    Height = 17
    Min = 0
    Max = 100
    TabOrder = 6
  end
  object wclSerialMonitor: TwclSerialMonitor
    OnInserted = wclSerialMonitorInserted
    OnRemoved = wclSerialMonitorRemoved
    Left = 104
    Top = 176
  end
  object wclSerialClient: TwclSerialClient
    DeviceName = 'COM1'
    WriteTimeout = 5000
    OnConnect = wclSerialClientConnect
    OnCreateProcessor = wclSerialClientCreateProcessor
    OnData = wclSerialClientData
    OnDisconnect = wclSerialClientDisconnect
    Left = 248
    Top = 216
  end
end
