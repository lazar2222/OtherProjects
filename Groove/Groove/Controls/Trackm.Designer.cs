namespace Groove.Controls
{
    public partial class Trackm
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

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.Input = new System.Windows.Forms.ComboBox();
            this.Output = new System.Windows.Forms.ComboBox();
            this.PPE = new System.Windows.Forms.Button();
            this.lbLevel = new System.Windows.Forms.Label();
            this.TrackName = new System.Windows.Forms.Label();
            this.Effects = new System.Windows.Forms.DataGridView();
            this.BG = new System.Windows.Forms.PictureBox();
            this.Mute = new System.Windows.Forms.Button();
            this.PPS = new System.Windows.Forms.Button();
            this.Level = new System.Windows.Forms.TrackBar();
            this.WaveForm = new System.Windows.Forms.Button();
            this.Spectrogram = new System.Windows.Forms.Button();
            this.lbPeak = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.Effects)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.BG)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Level)).BeginInit();
            this.SuspendLayout();
            // 
            // Input
            // 
            this.Input.Enabled = false;
            this.Input.FormattingEnabled = true;
            this.Input.Location = new System.Drawing.Point(3, 3);
            this.Input.Name = "Input";
            this.Input.Size = new System.Drawing.Size(121, 21);
            this.Input.TabIndex = 0;
            // 
            // Output
            // 
            this.Output.FormattingEnabled = true;
            this.Output.Location = new System.Drawing.Point(3, 30);
            this.Output.Name = "Output";
            this.Output.Size = new System.Drawing.Size(121, 21);
            this.Output.TabIndex = 1;
            this.Output.SelectedIndexChanged += new System.EventHandler(this.Output_SelectedIndexChanged);
            // 
            // PPE
            // 
            this.PPE.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.PPE.Location = new System.Drawing.Point(3, 57);
            this.PPE.Name = "PPE";
            this.PPE.Size = new System.Drawing.Size(50, 25);
            this.PPE.TabIndex = 3;
            this.PPE.Text = "P/P E";
            this.PPE.UseVisualStyleBackColor = true;
            this.PPE.Click += new System.EventHandler(this.PPE_Click);
            // 
            // lbLevel
            // 
            this.lbLevel.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.lbLevel.Location = new System.Drawing.Point(3, 631);
            this.lbLevel.Name = "lbLevel";
            this.lbLevel.Size = new System.Drawing.Size(60, 20);
            this.lbLevel.TabIndex = 4;
            this.lbLevel.Text = "0 dB";
            this.lbLevel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // TrackName
            // 
            this.TrackName.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.TrackName.Location = new System.Drawing.Point(0, 651);
            this.TrackName.Name = "TrackName";
            this.TrackName.Size = new System.Drawing.Size(124, 29);
            this.TrackName.TabIndex = 5;
            this.TrackName.Text = "Track 1";
            this.TrackName.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // Effects
            // 
            this.Effects.AllowUserToAddRows = false;
            this.Effects.AllowUserToDeleteRows = false;
            this.Effects.AllowUserToResizeColumns = false;
            this.Effects.AllowUserToResizeRows = false;
            this.Effects.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.Effects.CellBorderStyle = System.Windows.Forms.DataGridViewCellBorderStyle.None;
            this.Effects.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.Effects.ColumnHeadersVisible = false;
            this.Effects.Location = new System.Drawing.Point(3, 88);
            this.Effects.MultiSelect = false;
            this.Effects.Name = "Effects";
            this.Effects.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.Effects.RowHeadersBorderStyle = System.Windows.Forms.DataGridViewHeaderBorderStyle.None;
            this.Effects.RowHeadersVisible = false;
            this.Effects.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.CellSelect;
            this.Effects.Size = new System.Drawing.Size(121, 126);
            this.Effects.TabIndex = 6;
            this.Effects.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.Effects_CellClick);
            this.Effects.CellValueChanged += new System.Windows.Forms.DataGridViewCellEventHandler(this.Effects_CellValueChanged);
            // 
            // BG
            // 
            this.BG.BackColor = System.Drawing.Color.White;
            this.BG.BackgroundImage = global::Groove.Properties.Resources.Capture2;
            this.BG.Location = new System.Drawing.Point(34, 302);
            this.BG.Name = "BG";
            this.BG.Size = new System.Drawing.Size(95, 326);
            this.BG.TabIndex = 9;
            this.BG.TabStop = false;
            this.BG.Click += new System.EventHandler(this.BG_Click);
            this.BG.Paint += new System.Windows.Forms.PaintEventHandler(this.BG_Paint);
            // 
            // Mute
            // 
            this.Mute.BackColor = System.Drawing.SystemColors.ControlLight;
            this.Mute.Location = new System.Drawing.Point(3, 271);
            this.Mute.Name = "Mute";
            this.Mute.Size = new System.Drawing.Size(25, 25);
            this.Mute.TabIndex = 10;
            this.Mute.Text = "M";
            this.Mute.UseVisualStyleBackColor = false;
            this.Mute.Click += new System.EventHandler(this.Mute_Click);
            // 
            // PPS
            // 
            this.PPS.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.PPS.Location = new System.Drawing.Point(59, 57);
            this.PPS.Name = "PPS";
            this.PPS.Size = new System.Drawing.Size(50, 25);
            this.PPS.TabIndex = 12;
            this.PPS.Text = "P/P S";
            this.PPS.UseVisualStyleBackColor = true;
            this.PPS.Visible = false;
            // 
            // Level
            // 
            this.Level.Location = new System.Drawing.Point(3, 313);
            this.Level.Maximum = 50;
            this.Level.Minimum = -135;
            this.Level.Name = "Level";
            this.Level.Orientation = System.Windows.Forms.Orientation.Vertical;
            this.Level.Size = new System.Drawing.Size(45, 312);
            this.Level.TabIndex = 15;
            this.Level.TickFrequency = 0;
            this.Level.TickStyle = System.Windows.Forms.TickStyle.Both;
            this.Level.Value = 3;
            this.Level.Scroll += new System.EventHandler(this.Level_Scroll);
            // 
            // WaveForm
            // 
            this.WaveForm.Location = new System.Drawing.Point(65, 271);
            this.WaveForm.Name = "WaveForm";
            this.WaveForm.Size = new System.Drawing.Size(25, 25);
            this.WaveForm.TabIndex = 16;
            this.WaveForm.Text = "W";
            this.WaveForm.UseVisualStyleBackColor = true;
            this.WaveForm.Click += new System.EventHandler(this.WaveForm_Click);
            // 
            // Spectrogram
            // 
            this.Spectrogram.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Spectrogram.Location = new System.Drawing.Point(96, 271);
            this.Spectrogram.Name = "Spectrogram";
            this.Spectrogram.Size = new System.Drawing.Size(25, 25);
            this.Spectrogram.TabIndex = 17;
            this.Spectrogram.Text = "SP";
            this.Spectrogram.UseVisualStyleBackColor = true;
            this.Spectrogram.Click += new System.EventHandler(this.Spectrogram_Click);
            // 
            // lbPeak
            // 
            this.lbPeak.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.lbPeak.Location = new System.Drawing.Point(64, 631);
            this.lbPeak.Name = "lbPeak";
            this.lbPeak.Size = new System.Drawing.Size(60, 20);
            this.lbPeak.TabIndex = 18;
            this.lbPeak.Text = "0 dB";
            this.lbPeak.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // Trackm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(35)))), ((int)(((byte)(35)))), ((int)(((byte)(35)))));
            this.Controls.Add(this.lbPeak);
            this.Controls.Add(this.Spectrogram);
            this.Controls.Add(this.WaveForm);
            this.Controls.Add(this.Level);
            this.Controls.Add(this.PPS);
            this.Controls.Add(this.Mute);
            this.Controls.Add(this.Effects);
            this.Controls.Add(this.TrackName);
            this.Controls.Add(this.lbLevel);
            this.Controls.Add(this.PPE);
            this.Controls.Add(this.Output);
            this.Controls.Add(this.Input);
            this.Controls.Add(this.BG);
            this.Name = "Trackm";
            this.Size = new System.Drawing.Size(127, 680);
            ((System.ComponentModel.ISupportInitialize)(this.Effects)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.BG)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Level)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox Input;
        private System.Windows.Forms.ComboBox Output;
        private System.Windows.Forms.Button PPE;
        private System.Windows.Forms.Label lbLevel;
        private System.Windows.Forms.Label TrackName;
        private System.Windows.Forms.DataGridView Effects;
        private System.Windows.Forms.PictureBox BG;
        private System.Windows.Forms.Button Mute;
        private System.Windows.Forms.Button PPS;
        private System.Windows.Forms.TrackBar Level;
        private System.Windows.Forms.Button WaveForm;
        private System.Windows.Forms.Button Spectrogram;
        private System.Windows.Forms.Label lbPeak;
    }
}
