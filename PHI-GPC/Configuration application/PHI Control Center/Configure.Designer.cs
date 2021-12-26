namespace PHI_Control_Center
{
    partial class Configure
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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Configure));
            this.TaskbarIcon = new System.Windows.Forms.NotifyIcon(this.components);
            this.TaskbarStrip = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.configureToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.StartStopRTPToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.EXITToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.DevicesLB = new System.Windows.Forms.ListBox();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.newProfileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openProfileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveProfileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.setAsActiveProfileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.addonsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.perisitentDataToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.pb = new System.Windows.Forms.PictureBox();
            this.RefreshL = new System.Windows.Forms.Button();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.TaskbarStrip.SuspendLayout();
            this.menuStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pb)).BeginInit();
            this.SuspendLayout();
            // 
            // TaskbarIcon
            // 
            this.TaskbarIcon.BalloonTipIcon = System.Windows.Forms.ToolTipIcon.Info;
            this.TaskbarIcon.BalloonTipTitle = "PHI Control Center";
            this.TaskbarIcon.ContextMenuStrip = this.TaskbarStrip;
            this.TaskbarIcon.Icon = ((System.Drawing.Icon)(resources.GetObject("TaskbarIcon.Icon")));
            this.TaskbarIcon.Text = "PHI Control Center";
            this.TaskbarIcon.Visible = true;
            // 
            // TaskbarStrip
            // 
            this.TaskbarStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.configureToolStripMenuItem,
            this.toolStripSeparator1,
            this.StartStopRTPToolStripMenuItem,
            this.toolStripSeparator2,
            this.EXITToolStripMenuItem});
            this.TaskbarStrip.Name = "TaskbarStrip";
            this.TaskbarStrip.Size = new System.Drawing.Size(151, 82);
            this.TaskbarStrip.Opened += new System.EventHandler(this.TaskbarStrip_Opened);
            // 
            // configureToolStripMenuItem
            // 
            this.configureToolStripMenuItem.Name = "configureToolStripMenuItem";
            this.configureToolStripMenuItem.Size = new System.Drawing.Size(150, 22);
            this.configureToolStripMenuItem.Text = "Configure";
            this.configureToolStripMenuItem.Click += new System.EventHandler(this.configureToolStripMenuItem_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(147, 6);
            // 
            // StartStopRTPToolStripMenuItem
            // 
            this.StartStopRTPToolStripMenuItem.Name = "StartStopRTPToolStripMenuItem";
            this.StartStopRTPToolStripMenuItem.Size = new System.Drawing.Size(150, 22);
            this.StartStopRTPToolStripMenuItem.Text = "Start/Stop RTP";
            this.StartStopRTPToolStripMenuItem.Click += new System.EventHandler(this.StartStopRTPToolStripMenuItem_Click);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(147, 6);
            // 
            // EXITToolStripMenuItem
            // 
            this.EXITToolStripMenuItem.Name = "EXITToolStripMenuItem";
            this.EXITToolStripMenuItem.Size = new System.Drawing.Size(150, 22);
            this.EXITToolStripMenuItem.Text = "EXIT";
            this.EXITToolStripMenuItem.Click += new System.EventHandler(this.EXITToolStripMenuItem_Click);
            // 
            // DevicesLB
            // 
            this.DevicesLB.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.DevicesLB.FormattingEnabled = true;
            this.DevicesLB.Location = new System.Drawing.Point(12, 27);
            this.DevicesLB.Name = "DevicesLB";
            this.DevicesLB.Size = new System.Drawing.Size(175, 615);
            this.DevicesLB.TabIndex = 1;
            this.DevicesLB.SelectedIndexChanged += new System.EventHandler(this.DevicesLB_SelectedIndexChanged);
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.addonsToolStripMenuItem,
            this.perisitentDataToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(1264, 24);
            this.menuStrip1.TabIndex = 2;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newProfileToolStripMenuItem,
            this.openProfileToolStripMenuItem,
            this.saveProfileToolStripMenuItem,
            this.setAsActiveProfileToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // newProfileToolStripMenuItem
            // 
            this.newProfileToolStripMenuItem.Name = "newProfileToolStripMenuItem";
            this.newProfileToolStripMenuItem.Size = new System.Drawing.Size(179, 22);
            this.newProfileToolStripMenuItem.Text = "New Profile";
            this.newProfileToolStripMenuItem.Click += new System.EventHandler(this.newProfileToolStripMenuItem_Click);
            // 
            // openProfileToolStripMenuItem
            // 
            this.openProfileToolStripMenuItem.Name = "openProfileToolStripMenuItem";
            this.openProfileToolStripMenuItem.Size = new System.Drawing.Size(179, 22);
            this.openProfileToolStripMenuItem.Text = "Open Profile";
            this.openProfileToolStripMenuItem.Click += new System.EventHandler(this.openProfileToolStripMenuItem_Click);
            // 
            // saveProfileToolStripMenuItem
            // 
            this.saveProfileToolStripMenuItem.Name = "saveProfileToolStripMenuItem";
            this.saveProfileToolStripMenuItem.Size = new System.Drawing.Size(179, 22);
            this.saveProfileToolStripMenuItem.Text = "Save Profile";
            this.saveProfileToolStripMenuItem.Click += new System.EventHandler(this.saveProfileToolStripMenuItem_Click);
            // 
            // setAsActiveProfileToolStripMenuItem
            // 
            this.setAsActiveProfileToolStripMenuItem.Name = "setAsActiveProfileToolStripMenuItem";
            this.setAsActiveProfileToolStripMenuItem.Size = new System.Drawing.Size(179, 22);
            this.setAsActiveProfileToolStripMenuItem.Text = "Set As Active Profile";
            this.setAsActiveProfileToolStripMenuItem.Click += new System.EventHandler(this.setAsActiveProfileToolStripMenuItem_Click);
            // 
            // addonsToolStripMenuItem
            // 
            this.addonsToolStripMenuItem.Name = "addonsToolStripMenuItem";
            this.addonsToolStripMenuItem.Size = new System.Drawing.Size(60, 20);
            this.addonsToolStripMenuItem.Text = "Addons";
            this.addonsToolStripMenuItem.Click += new System.EventHandler(this.addonsToolStripMenuItem_Click);
            // 
            // perisitentDataToolStripMenuItem
            // 
            this.perisitentDataToolStripMenuItem.Name = "perisitentDataToolStripMenuItem";
            this.perisitentDataToolStripMenuItem.Size = new System.Drawing.Size(95, 20);
            this.perisitentDataToolStripMenuItem.Text = "Perisitent Data";
            this.perisitentDataToolStripMenuItem.Click += new System.EventHandler(this.perisitentDataToolStripMenuItem_Click);
            // 
            // pb
            // 
            this.pb.Location = new System.Drawing.Point(193, 57);
            this.pb.Name = "pb";
            this.pb.Size = new System.Drawing.Size(870, 580);
            this.pb.TabIndex = 5;
            this.pb.TabStop = false;
            this.pb.MouseClick += new System.Windows.Forms.MouseEventHandler(this.pb_MouseClick);
            // 
            // RefreshL
            // 
            this.RefreshL.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.RefreshL.Location = new System.Drawing.Point(12, 648);
            this.RefreshL.Name = "RefreshL";
            this.RefreshL.Size = new System.Drawing.Size(175, 23);
            this.RefreshL.TabIndex = 6;
            this.RefreshL.Text = "Refresh";
            this.RefreshL.UseVisualStyleBackColor = true;
            this.RefreshL.Click += new System.EventHandler(this.Refresh_Click);
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.FileName = "openFileDialog1";
            this.openFileDialog1.Filter = "JSON|*.json";
            // 
            // saveFileDialog1
            // 
            this.saveFileDialog1.Filter = "JSON|*.json";
            // 
            // Configure
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1264, 681);
            this.Controls.Add(this.RefreshL);
            this.Controls.Add(this.pb);
            this.Controls.Add(this.DevicesLB);
            this.Controls.Add(this.menuStrip1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.KeyPreview = true;
            this.MainMenuStrip = this.menuStrip1;
            this.MinimumSize = new System.Drawing.Size(1280, 720);
            this.Name = "Configure";
            this.Text = "PHI Control Center";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Configure_FormClosing);
            this.Load += new System.EventHandler(this.Configure_Load);
            this.TaskbarStrip.ResumeLayout(false);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pb)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.NotifyIcon TaskbarIcon;
        private System.Windows.Forms.ContextMenuStrip TaskbarStrip;
        private System.Windows.Forms.ToolStripMenuItem configureToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem StartStopRTPToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripMenuItem EXITToolStripMenuItem;
        private System.Windows.Forms.ListBox DevicesLB;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.PictureBox pb;
        private System.Windows.Forms.Button RefreshL;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem newProfileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openProfileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveProfileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem setAsActiveProfileToolStripMenuItem;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.SaveFileDialog saveFileDialog1;
        private System.Windows.Forms.ToolStripMenuItem addonsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem perisitentDataToolStripMenuItem;
    }
}