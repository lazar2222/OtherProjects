namespace UILib
{
    partial class Track
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
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle1 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle2 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle3 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle4 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle5 = new System.Windows.Forms.DataGridViewCellStyle();
            this.Input = new System.Windows.Forms.ComboBox();
            this.Output = new System.Windows.Forms.ComboBox();
            this.EnableE = new System.Windows.Forms.Button();
            this.PPE = new System.Windows.Forms.Button();
            this.lbLevel = new System.Windows.Forms.Label();
            this.TrackName = new System.Windows.Forms.Label();
            this.Effects = new System.Windows.Forms.DataGridView();
            this.Enabled = new System.Windows.Forms.DataGridViewButtonColumn();
            this.Effect = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.Sends = new System.Windows.Forms.DataGridView();
            this.E = new System.Windows.Forms.DataGridViewButtonColumn();
            this.Send = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.Slevel = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Pan = new System.Windows.Forms.TrackBar();
            this.BG = new System.Windows.Forms.PictureBox();
            this.Mute = new System.Windows.Forms.Button();
            this.Solo = new System.Windows.Forms.Button();
            this.PPS = new System.Windows.Forms.Button();
            this.lbPan = new System.Windows.Forms.Label();
            this.Level = new System.Windows.Forms.TrackBar();
            this.WaveForm = new System.Windows.Forms.Button();
            this.Spectrogram = new System.Windows.Forms.Button();
            this.lbPeak = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.Effects)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Sends)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Pan)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.BG)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Level)).BeginInit();
            this.SuspendLayout();
            // 
            // Input
            // 
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
            // 
            // EnableE
            // 
            this.EnableE.Location = new System.Drawing.Point(3, 57);
            this.EnableE.Name = "EnableE";
            this.EnableE.Size = new System.Drawing.Size(25, 25);
            this.EnableE.TabIndex = 2;
            this.EnableE.Text = "E";
            this.EnableE.UseVisualStyleBackColor = true;
            // 
            // PPE
            // 
            this.PPE.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.PPE.Location = new System.Drawing.Point(34, 57);
            this.PPE.Name = "PPE";
            this.PPE.Size = new System.Drawing.Size(40, 25);
            this.PPE.TabIndex = 3;
            this.PPE.Text = "P/P E";
            this.PPE.UseVisualStyleBackColor = true;
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
            this.Effects.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.Enabled,
            this.Effect});
            this.Effects.EditMode = System.Windows.Forms.DataGridViewEditMode.EditProgrammatically;
            this.Effects.Location = new System.Drawing.Point(3, 88);
            this.Effects.MultiSelect = false;
            this.Effects.Name = "Effects";
            this.Effects.ReadOnly = true;
            this.Effects.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.Effects.RowHeadersBorderStyle = System.Windows.Forms.DataGridViewHeaderBorderStyle.None;
            this.Effects.RowHeadersVisible = false;
            this.Effects.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.CellSelect;
            this.Effects.Size = new System.Drawing.Size(121, 60);
            this.Effects.TabIndex = 6;
            // 
            // Enabled
            // 
            this.Enabled.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.None;
            dataGridViewCellStyle1.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
            dataGridViewCellStyle1.BackColor = System.Drawing.Color.White;
            dataGridViewCellStyle1.ForeColor = System.Drawing.Color.Black;
            dataGridViewCellStyle1.SelectionBackColor = System.Drawing.Color.White;
            dataGridViewCellStyle1.SelectionForeColor = System.Drawing.Color.Black;
            this.Enabled.DefaultCellStyle = dataGridViewCellStyle1;
            this.Enabled.HeaderText = "";
            this.Enabled.MinimumWidth = 30;
            this.Enabled.Name = "Enabled";
            this.Enabled.ReadOnly = true;
            this.Enabled.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.Enabled.Width = 30;
            // 
            // Effect
            // 
            dataGridViewCellStyle2.BackColor = System.Drawing.Color.White;
            dataGridViewCellStyle2.ForeColor = System.Drawing.Color.Black;
            dataGridViewCellStyle2.SelectionBackColor = System.Drawing.Color.White;
            dataGridViewCellStyle2.SelectionForeColor = System.Drawing.Color.Black;
            this.Effect.DefaultCellStyle = dataGridViewCellStyle2;
            this.Effect.HeaderText = "";
            this.Effect.MinimumWidth = 90;
            this.Effect.Name = "Effect";
            this.Effect.ReadOnly = true;
            this.Effect.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.Effect.Width = 90;
            // 
            // Sends
            // 
            this.Sends.AllowUserToAddRows = false;
            this.Sends.AllowUserToDeleteRows = false;
            this.Sends.AllowUserToResizeColumns = false;
            this.Sends.AllowUserToResizeRows = false;
            this.Sends.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.Sends.CellBorderStyle = System.Windows.Forms.DataGridViewCellBorderStyle.None;
            this.Sends.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.Sends.ColumnHeadersVisible = false;
            this.Sends.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.E,
            this.Send,
            this.Slevel});
            this.Sends.EditMode = System.Windows.Forms.DataGridViewEditMode.EditProgrammatically;
            this.Sends.Location = new System.Drawing.Point(3, 154);
            this.Sends.Name = "Sends";
            this.Sends.ReadOnly = true;
            this.Sends.RowHeadersBorderStyle = System.Windows.Forms.DataGridViewHeaderBorderStyle.None;
            this.Sends.RowHeadersVisible = false;
            this.Sends.RowHeadersWidthSizeMode = System.Windows.Forms.DataGridViewRowHeadersWidthSizeMode.DisableResizing;
            this.Sends.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.CellSelect;
            this.Sends.Size = new System.Drawing.Size(121, 60);
            this.Sends.TabIndex = 7;
            // 
            // E
            // 
            dataGridViewCellStyle3.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
            dataGridViewCellStyle3.BackColor = System.Drawing.Color.White;
            dataGridViewCellStyle3.ForeColor = System.Drawing.Color.Black;
            dataGridViewCellStyle3.SelectionBackColor = System.Drawing.Color.White;
            dataGridViewCellStyle3.SelectionForeColor = System.Drawing.Color.Black;
            this.E.DefaultCellStyle = dataGridViewCellStyle3;
            this.E.HeaderText = "";
            this.E.MinimumWidth = 30;
            this.E.Name = "E";
            this.E.ReadOnly = true;
            this.E.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.E.Width = 30;
            // 
            // Send
            // 
            dataGridViewCellStyle4.BackColor = System.Drawing.Color.White;
            dataGridViewCellStyle4.ForeColor = System.Drawing.Color.Black;
            dataGridViewCellStyle4.SelectionBackColor = System.Drawing.Color.White;
            dataGridViewCellStyle4.SelectionForeColor = System.Drawing.Color.Black;
            this.Send.DefaultCellStyle = dataGridViewCellStyle4;
            this.Send.HeaderText = "";
            this.Send.MinimumWidth = 90;
            this.Send.Name = "Send";
            this.Send.ReadOnly = true;
            this.Send.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.Send.Width = 90;
            // 
            // Slevel
            // 
            dataGridViewCellStyle5.BackColor = System.Drawing.Color.White;
            dataGridViewCellStyle5.ForeColor = System.Drawing.Color.Black;
            dataGridViewCellStyle5.SelectionBackColor = System.Drawing.Color.White;
            dataGridViewCellStyle5.SelectionForeColor = System.Drawing.Color.Black;
            this.Slevel.DefaultCellStyle = dataGridViewCellStyle5;
            this.Slevel.HeaderText = "";
            this.Slevel.MinimumWidth = 50;
            this.Slevel.Name = "Slevel";
            this.Slevel.ReadOnly = true;
            this.Slevel.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.Slevel.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            this.Slevel.Width = 50;
            // 
            // Pan
            // 
            this.Pan.Location = new System.Drawing.Point(3, 220);
            this.Pan.Minimum = -10;
            this.Pan.Name = "Pan";
            this.Pan.Size = new System.Drawing.Size(121, 45);
            this.Pan.TabIndex = 8;
            this.Pan.TickFrequency = 2;
            // 
            // BG
            // 
            this.BG.BackColor = System.Drawing.Color.White;
            this.BG.Image = global::UILib.Properties.Resources.Capture2;
            this.BG.Location = new System.Drawing.Point(34, 302);
            this.BG.Name = "BG";
            this.BG.Size = new System.Drawing.Size(95, 326);
            this.BG.TabIndex = 9;
            this.BG.TabStop = false;
            // 
            // Mute
            // 
            this.Mute.Location = new System.Drawing.Point(3, 271);
            this.Mute.Name = "Mute";
            this.Mute.Size = new System.Drawing.Size(25, 25);
            this.Mute.TabIndex = 10;
            this.Mute.Text = "M";
            this.Mute.UseVisualStyleBackColor = true;
            // 
            // Solo
            // 
            this.Solo.Location = new System.Drawing.Point(34, 271);
            this.Solo.Name = "Solo";
            this.Solo.Size = new System.Drawing.Size(25, 25);
            this.Solo.TabIndex = 11;
            this.Solo.Text = "S";
            this.Solo.UseVisualStyleBackColor = true;
            // 
            // PPS
            // 
            this.PPS.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.PPS.Location = new System.Drawing.Point(80, 57);
            this.PPS.Name = "PPS";
            this.PPS.Size = new System.Drawing.Size(40, 25);
            this.PPS.TabIndex = 12;
            this.PPS.Text = "P/P S";
            this.PPS.UseVisualStyleBackColor = true;
            // 
            // lbPan
            // 
            this.lbPan.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.lbPan.Location = new System.Drawing.Point(3, 245);
            this.lbPan.Name = "lbPan";
            this.lbPan.Size = new System.Drawing.Size(121, 20);
            this.lbPan.TabIndex = 13;
            this.lbPan.Text = "0";
            this.lbPan.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // Level
            // 
            this.Level.Location = new System.Drawing.Point(3, 313);
            this.Level.Maximum = 215;
            this.Level.Name = "Level";
            this.Level.Orientation = System.Windows.Forms.Orientation.Vertical;
            this.Level.Size = new System.Drawing.Size(45, 312);
            this.Level.TabIndex = 15;
            this.Level.TickFrequency = 0;
            this.Level.TickStyle = System.Windows.Forms.TickStyle.Both;
            this.Level.Value = 160;
            // 
            // WaveForm
            // 
            this.WaveForm.Location = new System.Drawing.Point(65, 271);
            this.WaveForm.Name = "WaveForm";
            this.WaveForm.Size = new System.Drawing.Size(25, 25);
            this.WaveForm.TabIndex = 16;
            this.WaveForm.Text = "W";
            this.WaveForm.UseVisualStyleBackColor = true;
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
            // Track
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(35)))), ((int)(((byte)(35)))), ((int)(((byte)(35)))));
            this.Controls.Add(this.lbPeak);
            this.Controls.Add(this.Spectrogram);
            this.Controls.Add(this.WaveForm);
            this.Controls.Add(this.Level);
            this.Controls.Add(this.lbPan);
            this.Controls.Add(this.PPS);
            this.Controls.Add(this.Solo);
            this.Controls.Add(this.Mute);
            this.Controls.Add(this.Pan);
            this.Controls.Add(this.Sends);
            this.Controls.Add(this.Effects);
            this.Controls.Add(this.TrackName);
            this.Controls.Add(this.lbLevel);
            this.Controls.Add(this.PPE);
            this.Controls.Add(this.EnableE);
            this.Controls.Add(this.Output);
            this.Controls.Add(this.Input);
            this.Controls.Add(this.BG);
            this.Name = "Track";
            this.Size = new System.Drawing.Size(127, 680);
            this.Paint += new System.Windows.Forms.PaintEventHandler(this.Track_Paint);
            ((System.ComponentModel.ISupportInitialize)(this.Effects)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Sends)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Pan)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.BG)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Level)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox Input;
        private System.Windows.Forms.ComboBox Output;
        private System.Windows.Forms.Button EnableE;
        private System.Windows.Forms.Button PPE;
        private System.Windows.Forms.Label lbLevel;
        private System.Windows.Forms.Label TrackName;
        private System.Windows.Forms.DataGridView Effects;
        private System.Windows.Forms.DataGridView Sends;
        private System.Windows.Forms.TrackBar Pan;
        private System.Windows.Forms.PictureBox BG;
        private System.Windows.Forms.Button Mute;
        private System.Windows.Forms.Button Solo;
        private System.Windows.Forms.Button PPS;
        private System.Windows.Forms.Label lbPan;
        private System.Windows.Forms.TrackBar Level;
        private System.Windows.Forms.Button WaveForm;
        private System.Windows.Forms.Button Spectrogram;
        private System.Windows.Forms.Label lbPeak;
        private System.Windows.Forms.DataGridViewButtonColumn Enabled;
        private System.Windows.Forms.DataGridViewComboBoxColumn Effect;
        private System.Windows.Forms.DataGridViewButtonColumn E;
        private System.Windows.Forms.DataGridViewComboBoxColumn Send;
        private System.Windows.Forms.DataGridViewTextBoxColumn Slevel;
    }
}
