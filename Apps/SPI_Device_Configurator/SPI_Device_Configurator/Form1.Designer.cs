namespace SPI_Device_Configurator
{
    partial class Form1
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
			this.groupBox_Log = new System.Windows.Forms.GroupBox();
			this.button_CopyText = new System.Windows.Forms.Button();
			this.button_Clear_Log = new System.Windows.Forms.Button();
			this.richTextBox_Log = new System.Windows.Forms.RichTextBox();
			this.groupBox_Communications = new System.Windows.Forms.GroupBox();
			this.textBox_CommStatus = new System.Windows.Forms.TextBox();
			this.button_CloseBridge = new System.Windows.Forms.Button();
			this.button_Start_Bridge = new System.Windows.Forms.Button();
			this.label_Bridge = new System.Windows.Forms.Label();
			this.comboBox_BridgeChip = new System.Windows.Forms.ComboBox();
			this.groupBox_DataTRansfer = new System.Windows.Forms.GroupBox();
			this.groupBox_BridgeChip_Options = new System.Windows.Forms.GroupBox();
			this.groupBox_Log.SuspendLayout();
			this.groupBox_Communications.SuspendLayout();
			this.SuspendLayout();
			// 
			// groupBox_Log
			// 
			this.groupBox_Log.Controls.Add(this.button_CopyText);
			this.groupBox_Log.Controls.Add(this.button_Clear_Log);
			this.groupBox_Log.Controls.Add(this.richTextBox_Log);
			this.groupBox_Log.Location = new System.Drawing.Point(12, 278);
			this.groupBox_Log.Name = "groupBox_Log";
			this.groupBox_Log.Size = new System.Drawing.Size(603, 259);
			this.groupBox_Log.TabIndex = 2;
			this.groupBox_Log.TabStop = false;
			this.groupBox_Log.Text = "Log";
			// 
			// button_CopyText
			// 
			this.button_CopyText.Location = new System.Drawing.Point(98, 220);
			this.button_CopyText.Name = "button_CopyText";
			this.button_CopyText.Size = new System.Drawing.Size(136, 30);
			this.button_CopyText.TabIndex = 2;
			this.button_CopyText.Text = "Copy Log To Clipboard";
			this.button_CopyText.UseVisualStyleBackColor = true;
			this.button_CopyText.Click += new System.EventHandler(this.button_CopyText_Click);
			// 
			// button_Clear_Log
			// 
			this.button_Clear_Log.Location = new System.Drawing.Point(6, 220);
			this.button_Clear_Log.Name = "button_Clear_Log";
			this.button_Clear_Log.Size = new System.Drawing.Size(86, 30);
			this.button_Clear_Log.TabIndex = 1;
			this.button_Clear_Log.Text = "Clear Log";
			this.button_Clear_Log.UseVisualStyleBackColor = true;
			this.button_Clear_Log.Click += new System.EventHandler(this.button_Clear_Log_Click);
			// 
			// richTextBox_Log
			// 
			this.richTextBox_Log.Location = new System.Drawing.Point(6, 19);
			this.richTextBox_Log.Name = "richTextBox_Log";
			this.richTextBox_Log.ReadOnly = true;
			this.richTextBox_Log.ScrollBars = System.Windows.Forms.RichTextBoxScrollBars.Vertical;
			this.richTextBox_Log.Size = new System.Drawing.Size(591, 195);
			this.richTextBox_Log.TabIndex = 0;
			this.richTextBox_Log.Text = "";
			// 
			// groupBox_Communications
			// 
			this.groupBox_Communications.Controls.Add(this.textBox_CommStatus);
			this.groupBox_Communications.Controls.Add(this.button_CloseBridge);
			this.groupBox_Communications.Controls.Add(this.button_Start_Bridge);
			this.groupBox_Communications.Controls.Add(this.label_Bridge);
			this.groupBox_Communications.Controls.Add(this.comboBox_BridgeChip);
			this.groupBox_Communications.Location = new System.Drawing.Point(12, 13);
			this.groupBox_Communications.Name = "groupBox_Communications";
			this.groupBox_Communications.Size = new System.Drawing.Size(150, 165);
			this.groupBox_Communications.TabIndex = 3;
			this.groupBox_Communications.TabStop = false;
			this.groupBox_Communications.Text = "Serial Communication";
			// 
			// textBox_CommStatus
			// 
			this.textBox_CommStatus.Location = new System.Drawing.Point(6, 133);
			this.textBox_CommStatus.Name = "textBox_CommStatus";
			this.textBox_CommStatus.ReadOnly = true;
			this.textBox_CommStatus.ShortcutsEnabled = false;
			this.textBox_CommStatus.Size = new System.Drawing.Size(138, 20);
			this.textBox_CommStatus.TabIndex = 4;
			this.textBox_CommStatus.Text = "NOT CONNECTED";
			this.textBox_CommStatus.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
			// 
			// button_CloseBridge
			// 
			this.button_CloseBridge.Location = new System.Drawing.Point(6, 99);
			this.button_CloseBridge.Name = "button_CloseBridge";
			this.button_CloseBridge.Size = new System.Drawing.Size(138, 28);
			this.button_CloseBridge.TabIndex = 3;
			this.button_CloseBridge.Text = "Close Bridge";
			this.button_CloseBridge.UseVisualStyleBackColor = true;
			this.button_CloseBridge.Click += new System.EventHandler(this.button_CloseBridge_Click);
			// 
			// button_Start_Bridge
			// 
			this.button_Start_Bridge.AllowDrop = true;
			this.button_Start_Bridge.Location = new System.Drawing.Point(6, 65);
			this.button_Start_Bridge.Name = "button_Start_Bridge";
			this.button_Start_Bridge.Size = new System.Drawing.Size(138, 28);
			this.button_Start_Bridge.TabIndex = 2;
			this.button_Start_Bridge.Text = "Start Bridge";
			this.button_Start_Bridge.UseVisualStyleBackColor = true;
			this.button_Start_Bridge.Click += new System.EventHandler(this.button_Start_Bridge_Click);
			// 
			// label_Bridge
			// 
			this.label_Bridge.AutoSize = true;
			this.label_Bridge.Location = new System.Drawing.Point(6, 22);
			this.label_Bridge.Name = "label_Bridge";
			this.label_Bridge.Size = new System.Drawing.Size(108, 13);
			this.label_Bridge.TabIndex = 1;
			this.label_Bridge.Text = "Bridge Chip Selection";
			// 
			// comboBox_BridgeChip
			// 
			this.comboBox_BridgeChip.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.comboBox_BridgeChip.FormattingEnabled = true;
			this.comboBox_BridgeChip.Items.AddRange(new object[] {
            "CH341"});
			this.comboBox_BridgeChip.Location = new System.Drawing.Point(6, 38);
			this.comboBox_BridgeChip.Name = "comboBox_BridgeChip";
			this.comboBox_BridgeChip.Size = new System.Drawing.Size(138, 21);
			this.comboBox_BridgeChip.TabIndex = 0;
			// 
			// groupBox_DataTRansfer
			// 
			this.groupBox_DataTRansfer.Location = new System.Drawing.Point(12, 184);
			this.groupBox_DataTRansfer.Name = "groupBox_DataTRansfer";
			this.groupBox_DataTRansfer.Size = new System.Drawing.Size(603, 88);
			this.groupBox_DataTRansfer.TabIndex = 4;
			this.groupBox_DataTRansfer.TabStop = false;
			this.groupBox_DataTRansfer.Text = "Data Transfer";
			// 
			// groupBox_BridgeChip_Options
			// 
			this.groupBox_BridgeChip_Options.Location = new System.Drawing.Point(168, 13);
			this.groupBox_BridgeChip_Options.Name = "groupBox_BridgeChip_Options";
			this.groupBox_BridgeChip_Options.Size = new System.Drawing.Size(447, 165);
			this.groupBox_BridgeChip_Options.TabIndex = 5;
			this.groupBox_BridgeChip_Options.TabStop = false;
			this.groupBox_BridgeChip_Options.Text = "Bridge Chip Config Options";
			// 
			// Form1
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(626, 549);
			this.Controls.Add(this.groupBox_BridgeChip_Options);
			this.Controls.Add(this.groupBox_DataTRansfer);
			this.Controls.Add(this.groupBox_Communications);
			this.Controls.Add(this.groupBox_Log);
			this.Name = "Form1";
			this.Text = "Device Interface App";
			this.Load += new System.EventHandler(this.Form1_Load);
			this.groupBox_Log.ResumeLayout(false);
			this.groupBox_Communications.ResumeLayout(false);
			this.groupBox_Communications.PerformLayout();
			this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.GroupBox groupBox_Log;
        private System.Windows.Forms.Button button_CopyText;
        private System.Windows.Forms.Button button_Clear_Log;
        private System.Windows.Forms.RichTextBox richTextBox_Log;
        private System.Windows.Forms.GroupBox groupBox_Communications;
        private System.Windows.Forms.Label label_Bridge;
        private System.Windows.Forms.ComboBox comboBox_BridgeChip;
		private System.Windows.Forms.Button button_Start_Bridge;
		private System.Windows.Forms.Button button_CloseBridge;
		private System.Windows.Forms.GroupBox groupBox_DataTRansfer;
		private System.Windows.Forms.GroupBox groupBox_BridgeChip_Options;
		private System.Windows.Forms.TextBox textBox_CommStatus;
	}
}

