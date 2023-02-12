
namespace SerialOppServer
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
            this.lbLog = new System.Windows.Forms.ListBox();
            this.ProgressBar = new System.Windows.Forms.ProgressBar();
            this.btDisconnect = new System.Windows.Forms.Button();
            this.btConnect = new System.Windows.Forms.Button();
            this.btRefresh = new System.Windows.Forms.Button();
            this.cbPorts = new System.Windows.Forms.ComboBox();
            this.laSelectComPort = new System.Windows.Forms.Label();
            this.btClear = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // lbLog
            // 
            this.lbLog.FormattingEnabled = true;
            this.lbLog.Location = new System.Drawing.Point(12, 97);
            this.lbLog.Name = "lbLog";
            this.lbLog.Size = new System.Drawing.Size(484, 290);
            this.lbLog.TabIndex = 21;
            // 
            // ProgressBar
            // 
            this.ProgressBar.Location = new System.Drawing.Point(12, 39);
            this.ProgressBar.Name = "ProgressBar";
            this.ProgressBar.Size = new System.Drawing.Size(484, 23);
            this.ProgressBar.TabIndex = 19;
            // 
            // btDisconnect
            // 
            this.btDisconnect.Location = new System.Drawing.Point(421, 9);
            this.btDisconnect.Name = "btDisconnect";
            this.btDisconnect.Size = new System.Drawing.Size(75, 23);
            this.btDisconnect.TabIndex = 18;
            this.btDisconnect.Text = "Disconnect";
            this.btDisconnect.UseVisualStyleBackColor = true;
            this.btDisconnect.Click += new System.EventHandler(this.btDisconnect_Click);
            // 
            // btConnect
            // 
            this.btConnect.Location = new System.Drawing.Point(340, 9);
            this.btConnect.Name = "btConnect";
            this.btConnect.Size = new System.Drawing.Size(75, 23);
            this.btConnect.TabIndex = 17;
            this.btConnect.Text = "Connect";
            this.btConnect.UseVisualStyleBackColor = true;
            this.btConnect.Click += new System.EventHandler(this.btConnect_Click);
            // 
            // btRefresh
            // 
            this.btRefresh.Location = new System.Drawing.Point(259, 9);
            this.btRefresh.Name = "btRefresh";
            this.btRefresh.Size = new System.Drawing.Size(75, 23);
            this.btRefresh.TabIndex = 16;
            this.btRefresh.Text = "Refresh";
            this.btRefresh.UseVisualStyleBackColor = true;
            this.btRefresh.Click += new System.EventHandler(this.btRefresh_Click);
            // 
            // cbPorts
            // 
            this.cbPorts.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbPorts.FormattingEnabled = true;
            this.cbPorts.Location = new System.Drawing.Point(101, 11);
            this.cbPorts.Name = "cbPorts";
            this.cbPorts.Size = new System.Drawing.Size(152, 21);
            this.cbPorts.TabIndex = 15;
            // 
            // laSelectComPort
            // 
            this.laSelectComPort.AutoSize = true;
            this.laSelectComPort.Location = new System.Drawing.Point(9, 14);
            this.laSelectComPort.Name = "laSelectComPort";
            this.laSelectComPort.Size = new System.Drawing.Size(86, 13);
            this.laSelectComPort.TabIndex = 14;
            this.laSelectComPort.Text = "Select COM Port";
            // 
            // btClear
            // 
            this.btClear.Location = new System.Drawing.Point(421, 68);
            this.btClear.Name = "btClear";
            this.btClear.Size = new System.Drawing.Size(75, 23);
            this.btClear.TabIndex = 22;
            this.btClear.Text = "Clear";
            this.btClear.UseVisualStyleBackColor = true;
            this.btClear.Click += new System.EventHandler(this.btClear_Click);
            // 
            // fmMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(504, 395);
            this.Controls.Add(this.btClear);
            this.Controls.Add(this.lbLog);
            this.Controls.Add(this.ProgressBar);
            this.Controls.Add(this.btDisconnect);
            this.Controls.Add(this.btConnect);
            this.Controls.Add(this.btRefresh);
            this.Controls.Add(this.cbPorts);
            this.Controls.Add(this.laSelectComPort);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Name = "fmMain";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Serial OPP Server";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.fmMain_FormClosed);
            this.Load += new System.EventHandler(this.fmMain_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ListBox lbLog;
        private System.Windows.Forms.ProgressBar ProgressBar;
        private System.Windows.Forms.Button btDisconnect;
        private System.Windows.Forms.Button btConnect;
        private System.Windows.Forms.Button btRefresh;
        private System.Windows.Forms.ComboBox cbPorts;
        private System.Windows.Forms.Label laSelectComPort;
        private System.Windows.Forms.Button btClear;
    }
}

