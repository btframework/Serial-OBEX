
namespace SerialOppClient
{
    partial class fmMain
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.laSelectComPort = new System.Windows.Forms.Label();
            this.cbPorts = new System.Windows.Forms.ComboBox();
            this.btRefresh = new System.Windows.Forms.Button();
            this.btConnect = new System.Windows.Forms.Button();
            this.btDisconnect = new System.Windows.Forms.Button();
            this.btObexDisconnect = new System.Windows.Forms.Button();
            this.btObexConnect = new System.Windows.Forms.Button();
            this.laFilePath = new System.Windows.Forms.Label();
            this.edFilePath = new System.Windows.Forms.TextBox();
            this.btSelectFile = new System.Windows.Forms.Button();
            this.btSendFile = new System.Windows.Forms.Button();
            this.ProgressBar = new System.Windows.Forms.ProgressBar();
            this.btClear = new System.Windows.Forms.Button();
            this.lbLog = new System.Windows.Forms.ListBox();
            this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.SuspendLayout();
            // 
            // laSelectComPort
            // 
            this.laSelectComPort.AutoSize = true;
            this.laSelectComPort.Location = new System.Drawing.Point(12, 15);
            this.laSelectComPort.Name = "laSelectComPort";
            this.laSelectComPort.Size = new System.Drawing.Size(86, 13);
            this.laSelectComPort.TabIndex = 0;
            this.laSelectComPort.Text = "Select COM Port";
            // 
            // cbPorts
            // 
            this.cbPorts.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbPorts.FormattingEnabled = true;
            this.cbPorts.Location = new System.Drawing.Point(104, 12);
            this.cbPorts.Name = "cbPorts";
            this.cbPorts.Size = new System.Drawing.Size(152, 21);
            this.cbPorts.TabIndex = 1;
            // 
            // btRefresh
            // 
            this.btRefresh.Location = new System.Drawing.Point(262, 10);
            this.btRefresh.Name = "btRefresh";
            this.btRefresh.Size = new System.Drawing.Size(75, 23);
            this.btRefresh.TabIndex = 2;
            this.btRefresh.Text = "Refresh";
            this.btRefresh.UseVisualStyleBackColor = true;
            this.btRefresh.Click += new System.EventHandler(this.btRefresh_Click);
            // 
            // btConnect
            // 
            this.btConnect.Location = new System.Drawing.Point(343, 10);
            this.btConnect.Name = "btConnect";
            this.btConnect.Size = new System.Drawing.Size(75, 23);
            this.btConnect.TabIndex = 3;
            this.btConnect.Text = "Connect";
            this.btConnect.UseVisualStyleBackColor = true;
            this.btConnect.Click += new System.EventHandler(this.btConnect_Click);
            // 
            // btDisconnect
            // 
            this.btDisconnect.Location = new System.Drawing.Point(424, 10);
            this.btDisconnect.Name = "btDisconnect";
            this.btDisconnect.Size = new System.Drawing.Size(75, 23);
            this.btDisconnect.TabIndex = 4;
            this.btDisconnect.Text = "Disconnect";
            this.btDisconnect.UseVisualStyleBackColor = true;
            this.btDisconnect.Click += new System.EventHandler(this.btDisconnect_Click);
            // 
            // btObexDisconnect
            // 
            this.btObexDisconnect.Location = new System.Drawing.Point(127, 39);
            this.btObexDisconnect.Name = "btObexDisconnect";
            this.btObexDisconnect.Size = new System.Drawing.Size(106, 23);
            this.btObexDisconnect.TabIndex = 5;
            this.btObexDisconnect.Text = "OBEX disconnect";
            this.btObexDisconnect.UseVisualStyleBackColor = true;
            this.btObexDisconnect.Click += new System.EventHandler(this.btObexDisconnect_Click);
            // 
            // btObexConnect
            // 
            this.btObexConnect.Location = new System.Drawing.Point(15, 39);
            this.btObexConnect.Name = "btObexConnect";
            this.btObexConnect.Size = new System.Drawing.Size(106, 23);
            this.btObexConnect.TabIndex = 6;
            this.btObexConnect.Text = "OBEX connect";
            this.btObexConnect.UseVisualStyleBackColor = true;
            this.btObexConnect.Click += new System.EventHandler(this.btObexConnect_Click);
            // 
            // laFilePath
            // 
            this.laFilePath.AutoSize = true;
            this.laFilePath.Location = new System.Drawing.Point(12, 71);
            this.laFilePath.Name = "laFilePath";
            this.laFilePath.Size = new System.Drawing.Size(47, 13);
            this.laFilePath.TabIndex = 7;
            this.laFilePath.Text = "File path";
            // 
            // edFilePath
            // 
            this.edFilePath.Location = new System.Drawing.Point(65, 68);
            this.edFilePath.Name = "edFilePath";
            this.edFilePath.Size = new System.Drawing.Size(272, 20);
            this.edFilePath.TabIndex = 8;
            // 
            // btSelectFile
            // 
            this.btSelectFile.Location = new System.Drawing.Point(343, 66);
            this.btSelectFile.Name = "btSelectFile";
            this.btSelectFile.Size = new System.Drawing.Size(75, 23);
            this.btSelectFile.TabIndex = 9;
            this.btSelectFile.Text = "Select file";
            this.btSelectFile.UseVisualStyleBackColor = true;
            this.btSelectFile.Click += new System.EventHandler(this.btSelectFile_Click);
            // 
            // btSendFile
            // 
            this.btSendFile.Location = new System.Drawing.Point(424, 66);
            this.btSendFile.Name = "btSendFile";
            this.btSendFile.Size = new System.Drawing.Size(75, 23);
            this.btSendFile.TabIndex = 10;
            this.btSendFile.Text = "Send file";
            this.btSendFile.UseVisualStyleBackColor = true;
            this.btSendFile.Click += new System.EventHandler(this.btSendFile_Click);
            // 
            // ProgressBar
            // 
            this.ProgressBar.Location = new System.Drawing.Point(15, 94);
            this.ProgressBar.Name = "ProgressBar";
            this.ProgressBar.Size = new System.Drawing.Size(484, 23);
            this.ProgressBar.TabIndex = 11;
            // 
            // btClear
            // 
            this.btClear.Location = new System.Drawing.Point(424, 123);
            this.btClear.Name = "btClear";
            this.btClear.Size = new System.Drawing.Size(75, 23);
            this.btClear.TabIndex = 12;
            this.btClear.Text = "Clear";
            this.btClear.UseVisualStyleBackColor = true;
            this.btClear.Click += new System.EventHandler(this.btClear_Click);
            // 
            // lbLog
            // 
            this.lbLog.FormattingEnabled = true;
            this.lbLog.Location = new System.Drawing.Point(15, 152);
            this.lbLog.Name = "lbLog";
            this.lbLog.Size = new System.Drawing.Size(484, 290);
            this.lbLog.TabIndex = 13;
            // 
            // fmMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(513, 450);
            this.Controls.Add(this.lbLog);
            this.Controls.Add(this.btClear);
            this.Controls.Add(this.ProgressBar);
            this.Controls.Add(this.btSendFile);
            this.Controls.Add(this.btSelectFile);
            this.Controls.Add(this.edFilePath);
            this.Controls.Add(this.laFilePath);
            this.Controls.Add(this.btObexConnect);
            this.Controls.Add(this.btObexDisconnect);
            this.Controls.Add(this.btDisconnect);
            this.Controls.Add(this.btConnect);
            this.Controls.Add(this.btRefresh);
            this.Controls.Add(this.cbPorts);
            this.Controls.Add(this.laSelectComPort);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Name = "fmMain";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Serial OPP Client";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.fmMain_FormClosed);
            this.Load += new System.EventHandler(this.fmMain_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label laSelectComPort;
        private System.Windows.Forms.ComboBox cbPorts;
        private System.Windows.Forms.Button btRefresh;
        private System.Windows.Forms.Button btConnect;
        private System.Windows.Forms.Button btDisconnect;
        private System.Windows.Forms.Button btObexDisconnect;
        private System.Windows.Forms.Button btObexConnect;
        private System.Windows.Forms.Label laFilePath;
        private System.Windows.Forms.TextBox edFilePath;
        private System.Windows.Forms.Button btSelectFile;
        private System.Windows.Forms.Button btSendFile;
        private System.Windows.Forms.ProgressBar ProgressBar;
        private System.Windows.Forms.Button btClear;
        private System.Windows.Forms.ListBox lbLog;
        private System.Windows.Forms.OpenFileDialog openFileDialog;
    }
}

