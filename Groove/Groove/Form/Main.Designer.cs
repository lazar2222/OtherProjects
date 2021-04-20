namespace Groove
{
    partial class Main
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Main));
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.preferencesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.tracksToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.addTrackToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.addBusToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.pianoRollToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.playlistToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.playToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.pauseToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.stopToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.beginingToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.loopToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.tempoToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.recordToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.writeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.renderToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.startAudioEngineToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.stopAudioEngineToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.tracksToolStripMenuItem,
            this.pianoRollToolStripMenuItem,
            this.playlistToolStripMenuItem,
            this.playToolStripMenuItem,
            this.pauseToolStripMenuItem,
            this.stopToolStripMenuItem,
            this.beginingToolStripMenuItem,
            this.loopToolStripMenuItem,
            this.tempoToolStripMenuItem,
            this.recordToolStripMenuItem,
            this.writeToolStripMenuItem,
            this.renderToolStripMenuItem,
            this.startAudioEngineToolStripMenuItem,
            this.stopAudioEngineToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(1350, 24);
            this.menuStrip1.TabIndex = 26;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.openToolStripMenuItem,
            this.saveToolStripMenuItem,
            this.preferencesToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // openToolStripMenuItem
            // 
            this.openToolStripMenuItem.Name = "openToolStripMenuItem";
            this.openToolStripMenuItem.Size = new System.Drawing.Size(135, 22);
            this.openToolStripMenuItem.Text = "Open";
            // 
            // saveToolStripMenuItem
            // 
            this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
            this.saveToolStripMenuItem.Size = new System.Drawing.Size(135, 22);
            this.saveToolStripMenuItem.Text = "Save";
            // 
            // preferencesToolStripMenuItem
            // 
            this.preferencesToolStripMenuItem.Name = "preferencesToolStripMenuItem";
            this.preferencesToolStripMenuItem.Size = new System.Drawing.Size(135, 22);
            this.preferencesToolStripMenuItem.Text = "Preferences";
            // 
            // tracksToolStripMenuItem
            // 
            this.tracksToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.addTrackToolStripMenuItem,
            this.addBusToolStripMenuItem});
            this.tracksToolStripMenuItem.Name = "tracksToolStripMenuItem";
            this.tracksToolStripMenuItem.Size = new System.Drawing.Size(52, 20);
            this.tracksToolStripMenuItem.Text = "Tracks";
            // 
            // addTrackToolStripMenuItem
            // 
            this.addTrackToolStripMenuItem.Name = "addTrackToolStripMenuItem";
            this.addTrackToolStripMenuItem.Size = new System.Drawing.Size(127, 22);
            this.addTrackToolStripMenuItem.Text = "Add Track";
            this.addTrackToolStripMenuItem.Click += new System.EventHandler(this.addTrackToolStripMenuItem_Click);
            // 
            // addBusToolStripMenuItem
            // 
            this.addBusToolStripMenuItem.Name = "addBusToolStripMenuItem";
            this.addBusToolStripMenuItem.Size = new System.Drawing.Size(127, 22);
            this.addBusToolStripMenuItem.Text = "Add Bus";
            this.addBusToolStripMenuItem.Click += new System.EventHandler(this.addBusToolStripMenuItem_Click);
            // 
            // pianoRollToolStripMenuItem
            // 
            this.pianoRollToolStripMenuItem.Name = "pianoRollToolStripMenuItem";
            this.pianoRollToolStripMenuItem.Size = new System.Drawing.Size(72, 20);
            this.pianoRollToolStripMenuItem.Text = "Piano Roll";
            this.pianoRollToolStripMenuItem.Click += new System.EventHandler(this.pianoRollToolStripMenuItem_Click);
            // 
            // playlistToolStripMenuItem
            // 
            this.playlistToolStripMenuItem.Name = "playlistToolStripMenuItem";
            this.playlistToolStripMenuItem.Size = new System.Drawing.Size(56, 20);
            this.playlistToolStripMenuItem.Text = "Playlist";
            // 
            // playToolStripMenuItem
            // 
            this.playToolStripMenuItem.Name = "playToolStripMenuItem";
            this.playToolStripMenuItem.Size = new System.Drawing.Size(41, 20);
            this.playToolStripMenuItem.Text = "Play";
            this.playToolStripMenuItem.Click += new System.EventHandler(this.playToolStripMenuItem_Click);
            // 
            // pauseToolStripMenuItem
            // 
            this.pauseToolStripMenuItem.Name = "pauseToolStripMenuItem";
            this.pauseToolStripMenuItem.Size = new System.Drawing.Size(50, 20);
            this.pauseToolStripMenuItem.Text = "Pause";
            this.pauseToolStripMenuItem.Click += new System.EventHandler(this.pauseToolStripMenuItem_Click);
            // 
            // stopToolStripMenuItem
            // 
            this.stopToolStripMenuItem.Name = "stopToolStripMenuItem";
            this.stopToolStripMenuItem.Size = new System.Drawing.Size(43, 20);
            this.stopToolStripMenuItem.Text = "Stop";
            this.stopToolStripMenuItem.Click += new System.EventHandler(this.stopToolStripMenuItem_Click);
            // 
            // beginingToolStripMenuItem
            // 
            this.beginingToolStripMenuItem.Name = "beginingToolStripMenuItem";
            this.beginingToolStripMenuItem.Size = new System.Drawing.Size(66, 20);
            this.beginingToolStripMenuItem.Text = "Begining";
            this.beginingToolStripMenuItem.Click += new System.EventHandler(this.beginingToolStripMenuItem_Click);
            // 
            // loopToolStripMenuItem
            // 
            this.loopToolStripMenuItem.Name = "loopToolStripMenuItem";
            this.loopToolStripMenuItem.Size = new System.Drawing.Size(46, 20);
            this.loopToolStripMenuItem.Text = "Loop";
            this.loopToolStripMenuItem.Click += new System.EventHandler(this.loopToolStripMenuItem_Click);
            // 
            // tempoToolStripMenuItem
            // 
            this.tempoToolStripMenuItem.Name = "tempoToolStripMenuItem";
            this.tempoToolStripMenuItem.Size = new System.Drawing.Size(56, 20);
            this.tempoToolStripMenuItem.Text = "Tempo";
            this.tempoToolStripMenuItem.Click += new System.EventHandler(this.tempoToolStripMenuItem_Click);
            // 
            // recordToolStripMenuItem
            // 
            this.recordToolStripMenuItem.Name = "recordToolStripMenuItem";
            this.recordToolStripMenuItem.Size = new System.Drawing.Size(56, 20);
            this.recordToolStripMenuItem.Text = "Record";
            // 
            // writeToolStripMenuItem
            // 
            this.writeToolStripMenuItem.Name = "writeToolStripMenuItem";
            this.writeToolStripMenuItem.Size = new System.Drawing.Size(47, 20);
            this.writeToolStripMenuItem.Text = "Write";
            // 
            // renderToolStripMenuItem
            // 
            this.renderToolStripMenuItem.Name = "renderToolStripMenuItem";
            this.renderToolStripMenuItem.Size = new System.Drawing.Size(56, 20);
            this.renderToolStripMenuItem.Text = "Render";
            // 
            // startAudioEngineToolStripMenuItem
            // 
            this.startAudioEngineToolStripMenuItem.Name = "startAudioEngineToolStripMenuItem";
            this.startAudioEngineToolStripMenuItem.Size = new System.Drawing.Size(117, 20);
            this.startAudioEngineToolStripMenuItem.Text = "Start Audio Engine";
            this.startAudioEngineToolStripMenuItem.Click += new System.EventHandler(this.button1_Click);
            // 
            // stopAudioEngineToolStripMenuItem
            // 
            this.stopAudioEngineToolStripMenuItem.Name = "stopAudioEngineToolStripMenuItem";
            this.stopAudioEngineToolStripMenuItem.Size = new System.Drawing.Size(117, 20);
            this.stopAudioEngineToolStripMenuItem.Text = "Stop Audio Engine";
            this.stopAudioEngineToolStripMenuItem.Click += new System.EventHandler(this.button2_Click);
            // 
            // timer1
            // 
            this.timer1.Interval = 66;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // Main
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoScroll = true;
            this.BackColor = System.Drawing.SystemColors.ControlDark;
            this.ClientSize = new System.Drawing.Size(1350, 729);
            this.Controls.Add(this.menuStrip1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.KeyPreview = true;
            this.MainMenuStrip = this.menuStrip1;
            this.MinimumSize = new System.Drawing.Size(1280, 720);
            this.Name = "Main";
            this.Text = "GROOVE";
            this.Load += new System.EventHandler(this.Main_Load);
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.Main_KeyDown);
            this.KeyUp += new System.Windows.Forms.KeyEventHandler(this.Main_KeyUp);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem preferencesToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem tracksToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem addTrackToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem addBusToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem pianoRollToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem playlistToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem playToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem stopToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem recordToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem writeToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem renderToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem startAudioEngineToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem stopAudioEngineToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem pauseToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem beginingToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem loopToolStripMenuItem;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.ToolStripMenuItem tempoToolStripMenuItem;
    }
}

