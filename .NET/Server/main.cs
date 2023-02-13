using System;
using System.Windows.Forms;

using wclCommon;
using wclCommunication;
using wclSerial;

namespace SerialOppServer
{
    public partial class fmMain : Form
    {
        private wclSerialMonitor FMonitor;
        private wclSerialClient FClient;
        private wclObexOppServer FOppServer;

        public fmMain()
        {
            InitializeComponent();
        }

        private void fmMain_Load(object sender, EventArgs e)
        {
            FOppServer = null;

            FMonitor = new wclSerialMonitor();
            FMonitor.OnInserted += MonitorInserted;
            FMonitor.OnRemoved += MonitorRemoved;

            FClient = new wclSerialClient();
            FClient.OnConnect += ClientConnect;
            FClient.OnDisconnect += ClientDisconnect;
            FClient.OnCreateProcessor += ClientCreateProcessor;
            FClient.OnData += ClientData;

            Int32 Res = FMonitor.Start();
            if (Res != wclErrors.WCL_E_SUCCESS)
                Trace("Start monitoring failed", Res);

            RefreshComPorts();
        }

        private void ClientData(object Sender, byte[] Data)
        {
            if (FOppServer != null)
                FOppServer.ProcessData(Data);
        }

        private void ClientCreateProcessor(object Sender, wclClientDataConnection Connection)
        {
            if (FOppServer == null)
            {
                FOppServer = new wclObexOppServer(null, 0x00FF);
                FOppServer.OnWrite += OppWrite;
                FOppServer.OnConnect += OppConnect;
                FOppServer.OnDisconnected += OppDisconnected;
                FOppServer.OnPutProgress += OppPutProgress;
                FOppServer.OnPutBegin += OppPutBegin;
                FOppServer.OnPutCompleted += OppPutCompleted;
            }
        }

        private void OppPutProgress(object Sender, uint Position, uint Length, out bool Continue)
        {
            ProgressBar.Maximum = (Int32)Length;
            ProgressBar.Value = (Int32)Position;
            Continue = true;
        }

        private void OppPutCompleted(object Sender, int Error, System.IO.Stream Stream, out bool Accept)
        {
            if (Error != wclErrors.WCL_E_SUCCESS)
            {
                Trace("File receiving error", Error);
                Accept = false;
            }
            else
            {
                Accept = true;
                Trace("File received");
            }
        }

        private void OppPutBegin(object Sender, string Name, string Description, string Mime, uint Length, out bool Accept)
        {
            Accept = true;
            Trace("Begin sending file: " + Name);
        }

        private void OppWrite(object Sender, byte[] Data, out uint Written, out int WriteResult)
        {
            WriteResult = FClient.Write(Data, out Written);
        }

        private void OppDisconnected(object Sender, int Reason, string Description)
        {
            Trace("OBEX client disconnected with reason", Reason);
            Trace("  [" + Description + "]");
        }

        private void OppConnect(object Sender, string Description)
        {
            Trace("OBEX client connected [" + Description + "]");
            FOppServer.Accept("Accept connection");
        }

        private void ClientDisconnect(object Sender, int Reason)
        {
            if (FOppServer != null)
            {
                FOppServer.Dispose();
                FOppServer = null;
            }

            Trace("Disconnected with reason", Reason);
        }

        private void ClientConnect(object Sender, int Error)
        {
            if (Error != wclErrors.WCL_E_SUCCESS)
                Trace("Connect failed", Error);
            else
            {
                Trace("Connected");

                wclSerialConfig Config;
                if (FClient.GetConfig(out Config) == wclErrors.WCL_E_SUCCESS)
                {
                    Config.BaudRate = 115200;
                    Config.ByteSize = 8;
                    FClient.SetConfig(Config);
                }
            }
        }

        private void MonitorRemoved(object Sender, wclSerialDevice Device)
        {
            Trace("Device removed: " + Device.DeviceName);
        }

        private void MonitorInserted(object Sender, wclSerialDevice Device)
        {
            Trace("Device inserted: " + Device.DeviceName);
        }

        private void RefreshComPorts()
        {
            wclSerialDevice[] Devices;
            Int32 Res = FMonitor.EnumDevices(out Devices);
            if (Res != wclErrors.WCL_E_SUCCESS)
                MessageBox.Show("Error: 0x" + Res.ToString("X8"));
            else
            {
                cbPorts.Items.Clear();
                if (Devices != null && Devices.Length > 0)
                {
                    foreach (wclSerialDevice Device in Devices)
                        cbPorts.Items.Add(Device.DeviceName);
                    cbPorts.SelectedIndex = 0;
                }
            }
        }

        private void Trace(String Msg)
        {
            lbLog.Items.Add(Msg);
        }

        private void Trace(String Msg, Int32 Res)
        {
            Trace(Msg + ": 0x" + Res.ToString("X8"));
        }

        private void btRefresh_Click(object sender, EventArgs e)
        {
            RefreshComPorts();
        }

        private void btClear_Click(object sender, EventArgs e)
        {
            lbLog.Items.Clear();
        }

        private void fmMain_FormClosed(object sender, FormClosedEventArgs e)
        {
            FClient.Disconnect();
            FMonitor.Stop();
        }

        private void btConnect_Click(object sender, EventArgs e)
        {
            if (cbPorts.Items.Count == 0)
                MessageBox.Show("No COM ports found");
            else
            {
                try
                {
                    FClient.DeviceName = (String)cbPorts.Items[cbPorts.SelectedIndex];
                    Int32 Res = FClient.Connect();
                    if (Res != wclErrors.WCL_E_SUCCESS)
                        MessageBox.Show("Connect failed: 0x" + Res.ToString("X8"));
                }
                catch (Exception E)
                {
                    MessageBox.Show(E.Message);

                }
            }
        }

        private void btDisconnect_Click(object sender, EventArgs e)
        {
            Int32 Res = FClient.Disconnect();
            if (Res != wclErrors.WCL_E_SUCCESS)
                MessageBox.Show("Disconnect failed: 0x" + Res.ToString("X8"));
        }
    }
}
