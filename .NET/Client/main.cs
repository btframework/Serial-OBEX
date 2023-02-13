using System;
using System.Windows.Forms;
using System.IO;

using wclCommon;
using wclCommunication;
using wclSerial;

namespace SerialOppClient
{
    public partial class fmMain : Form
    {
        private wclSerialMonitor FMonitor;
        private wclSerialClient FClient;

        public fmMain()
        {
            InitializeComponent();
        }

        private void fmMain_Load(object sender, EventArgs e)
        {
            FMonitor = new wclSerialMonitor();
            FMonitor.OnInserted += MonitorInserted;
            FMonitor.OnRemoved += MonitorRemoved;

            FClient = new wclSerialClient();
            FClient.OnConnect += ClientConnect;
            FClient.OnDisconnect += ClientDisconnect;
            FClient.OnCreateProcessor += ClientCreateProcessor;
            FClient.OnDestroyProcessor += ClientDestroyProcessor;

            Int32 Res = FMonitor.Start();
            if (Res != wclErrors.WCL_E_SUCCESS)
                Trace("Start monitoring failed", Res);

            RefreshComPorts();
        }

        private void ClientDestroyProcessor(object Sender, wclClientDataConnection Connection)
        {
            if (Connection.Processor != null)
                Connection.Processor.Dispose();
        }

        private void ClientCreateProcessor(object Sender, wclClientDataConnection Connection)
        {
            wclObexOppClient Proc = new wclObexOppClient(Connection);
            Proc.OnConnect += OppConnect;
            Proc.OnDisconnect += OppDisconnect;
            Proc.OnProgress += OppProgress;
            Proc.OnPutComplete += OppPutComplete;
        }

        private void OppPutComplete(object Sender, int Error, string Description, System.IO.Stream Stream)
        {
            Trace("Put completed", Error);
            Trace("  [" + Description + "]");
            Stream.Dispose();
        }

        private void OppProgress(object Sender, uint Length, uint Position)
        {
            ProgressBar.Maximum = (Int32)Length;
            ProgressBar.Value = (Int32)Position;
        }

        private void OppDisconnect(object Sender, int Error, string Description)
        {
            Trace("OBEX disconnect with reason", Error);
            Trace("  [" + Description + "]");
        }

        private void OppConnect(object Sender, int Error, string Description)
        {
            if (Error != wclErrors.WCL_E_SUCCESS)
            {
                Trace("OBEX connect failed", Error);
                Trace("  [" + Description + "]");
            }
            else
                Trace("OBEX connected");
        }

        private void ClientDisconnect(object Sender, int Reason)
        {
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

        private void btRefresh_Click(object sender, EventArgs e)
        {
            RefreshComPorts();
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

        private void btClear_Click(object sender, EventArgs e)
        {
            lbLog.Items.Clear();
        }

        private void Trace(String Msg)
        {
            lbLog.Items.Add(Msg);
        }

        private void Trace(String Msg, Int32 Res)
        {
            Trace(Msg + ": 0x" + Res.ToString("X8"));
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

        private void btObexConnect_Click(object sender, EventArgs e)
        {
            if (FClient.Processor == null)
                MessageBox.Show("Port not connected");
            else
            {
                Int32 Res = ((wclObexOppClient)FClient.Processor).Connect(0x00FF);
                if (Res != wclErrors.WCL_E_SUCCESS)
                    MessageBox.Show("OBEX connect failed: 0x" + Res.ToString("X8"));
            }
        }

        private void btObexDisconnect_Click(object sender, EventArgs e)
        {
            if (FClient.Processor == null)
                MessageBox.Show("OBEX not connected");
            else
            {
                Int32 Res = ((wclObexOppClient)FClient.Processor).Disconnect("Disconnect by user");
                if (Res != wclErrors.WCL_E_SUCCESS)
                    MessageBox.Show("OBEX disconnect failed: 0x" + Res.ToString("X8"));
            }
        }

        private void btSelectFile_Click(object sender, EventArgs e)
        {
            if (openFileDialog.ShowDialog() == DialogResult.OK)
                edFilePath.Text = openFileDialog.FileName;
        }

        private void btSendFile_Click(object sender, EventArgs e)
        {
            if (edFilePath.Text == "")
                MessageBox.Show("Select file");
            else
            {
                if (FClient.Processor == null)
                    MessageBox.Show("Not connected");
                else
                {
                    try
                    {
                        FileStream Stream = new FileStream(edFilePath.Text, FileMode.Open);
                        Int32 Res = ((wclObexOppClient)FClient.Processor).Put(Path.GetFileName(edFilePath.Text),
                            "Serial OPP", Stream);
                        if (Res != wclErrors.WCL_E_SUCCESS)
                        {
                            MessageBox.Show("Send failed: 0x" + Res.ToString("X8"));
                            Stream.Dispose();
                        }
                        else
                        {
                            ProgressBar.Value = 0;
                            ProgressBar.Maximum = 0;
                        }
                    }
                    catch (Exception E)
                    {
                        MessageBox.Show(E.Message);
                    }
                }
            }
        }
    }
}
