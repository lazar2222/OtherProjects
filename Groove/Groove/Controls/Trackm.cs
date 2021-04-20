using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Groove.Pipeline;
using DipBase;

namespace Groove.Controls
{
    public partial class Trackm : UserControl
    {
        Main m;
        Mixer.Master mc;
        int ticks1 = 0, ticks2 = 0;
        float s1, s2;
        bool peak;

        public Trackm(Main m, Mixer.Master mc)
        {
            this.m = m;
            this.mc = mc;
            InitializeComponent();
            TrackName.Text = mc.name;
            for (int i = 0; i < m.m.HOuts.Count; i++)
            {
                Output.Items.Add(m.m.HOuts[i].Name);
            }
            if (mc.preE) { PPE.BackColor = Color.Lime; }
            else { PPE.BackColor = Color.Red; }
            DataGridViewComboBoxColumn Effect = new DataGridViewComboBoxColumn();
            Effect.MaxDropDownItems = 4;
            Effect.Width = 90;
            Effect.Items.Add("None");
            for (int i = 0; i < m.eff.Count; i++)
            {
                Effect.Items.Add(m.eff[i].GetPluginInfo().name);
            }
            Effects.Columns.Add("e", "e");
            Effects.Columns.Add("e", "e");
            Effects.Columns[0].Width = 15;
            Effects.Columns[0].ReadOnly = true;
            Effects.Columns[1].Width = 15;
            Effects.Columns[1].ReadOnly = true;
            Effects.Columns.Add(Effect);
            for (int i = 0; i < 10; i++)
            {
                Effects.Rows.Add("D", "O");
            }

            Location = new Point(m.x, 27);
            m.x += 130;
            m.Controls.Add(this);
        }

        private void Output_SelectedIndexChanged(object sender, EventArgs e)
        {
            mc.Output = m.m.HOuts[Output.SelectedIndex];
        }

        private void PPE_Click(object sender, EventArgs e)
        {
            mc.preE = !mc.preE;
            if (mc.preE) { PPE.BackColor = Color.Lime; }
            else { PPE.BackColor = Color.Red; }
        }

        private void Effects_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.ColumnIndex == 0)
            {
                mc.plugine[e.RowIndex] = !mc.plugine[e.RowIndex];
                if (mc.plugine[e.RowIndex]) { Effects.Rows[e.RowIndex].Cells[0].Value = "E"; }
                else { Effects.Rows[e.RowIndex].Cells[0].Value = "D"; }
            }
            else if (e.ColumnIndex == 1) { try { mc.Plugins[e.RowIndex].ShowUI(); } catch { } }

        }

        private void Effects_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            if (e.ColumnIndex == 2)
            {
                if (Effects.Rows[e.RowIndex].Cells[e.ColumnIndex].Value.ToString() == "None")
                {
                    mc.Plugins[e.RowIndex] = null;
                }
                else
                {
                    mc.Plugins[e.RowIndex] = m.eff.Find(x => x.GetPluginInfo().name == Effects.Rows[e.RowIndex].Cells[e.ColumnIndex].Value.ToString());
                }
            }
        }

        private void Mute_Click(object sender, EventArgs e)
        {
            mc.mute = !mc.mute;
            if (mc.mute) { Mute.BackColor = Color.Red; }
            else { Mute.BackColor = SystemColors.ControlLight; }
        }

        private void Level_Scroll(object sender, EventArgs e)
        {
            double x = ((Level.Value * 0.3d) * (Math.Abs(Level.Value) / 54d));
            mc.level = (float)(x < -101 ? 0 : Math.Pow(10, x / 20d));
            lbLevel.Text = (Math.Round(x,2) >= 101 ? "-Inf " : Math.Round(x, 2).ToString()) + "dB";
        }

        private void WaveForm_Click(object sender, EventArgs e)
        {

        }

        private void BG_Click(object sender, EventArgs e)
        {
            peak = false;
        }

        private void Spectrogram_Click(object sender, EventArgs e)
        {

        }

        private void BG_Paint(object sender, PaintEventArgs e)
        {
            e.Graphics.Clear(BackColor);
            e.Graphics.DrawImage(BG.BackgroundImage, 0, 0);
            if (mc.peaklvl[0] >= s1) { s1 = mc.peaklvl[0]; ticks1 = 0; } else { ticks1++; }
            if (mc.peaklvl[1] >= s2) { s2 = mc.peaklvl[1]; ticks2 = 0; } else { ticks2++; }
            if (ticks1 > 15) { s1 = 0; }
            if (ticks2 > 15) { s2 = 0; }
            double x1 = 20 * Math.Log10(mc.peaklvl[0] + 0.000001);
            double x2 = 20 * Math.Log10(mc.peaklvl[1] + 0.000001);
            double sx1 = 20 * Math.Log10(s1 + 0.000001);
            double sx2 = 20 * Math.Log10(s2 + 0.000001);
            if (x1 >= -0.0000001 || x1 >= -0.0000001) { peak=true; }
            if (peak){ e.Graphics.FillRectangle(Brushes.Red,52,10,15,8); }
            e.Graphics.FillRectangle(Brushes.Red, 52f, 316f - ((60f + (float)Math.Min(x1, 0)) * 4.95f), 7f, ((60f + (float)Math.Min(x1, -18)) * 5f));
            e.Graphics.FillRectangle(Brushes.Red, 60f, 316f - ((60f + (float)Math.Min(x2, 0)) * 4.95f), 7f, ((60f + (float)Math.Min(x2, -18)) * 5f));
            e.Graphics.FillRectangle(Brushes.Yellow, 52f, 316f - ((60f + (float)Math.Min(x1, -6)) * 4.95f), 7f, ((60f + (float)Math.Min(x1, -18)) * 5f));
            e.Graphics.FillRectangle(Brushes.Yellow, 60f, 316f - ((60f + (float)Math.Min(x2, -6)) * 4.95f), 7f, ((60f + (float)Math.Min(x2, -18)) * 5f));
            e.Graphics.FillRectangle(Brushes.Lime, 52f, 316f - ((60f + (float)Math.Min(x1, -18)) * 4.95f), 7f, ((60f + (float)Math.Min(x1, -18)) * 5f));
            e.Graphics.FillRectangle(Brushes.Lime, 60f, 316f - ((60f + (float)Math.Min(x2, -18)) * 4.95f), 7f, ((60f + (float)Math.Min(x2, -18)) * 5f));
            e.Graphics.DrawLine(Pens.Orange, 52f, 316f - ((60f + (float)Math.Min(sx1, 0)) * 4.95f), 59f, 316f - ((60f + (float)Math.Min(sx1, 0)) * 4.95f));
            e.Graphics.DrawLine(Pens.Orange, 60f, 316f - ((60f + (float)Math.Min(sx2, 0)) * 4.95f), 67f, 316f - ((60f + (float)Math.Min(sx2, 0)) * 4.95f));
            lbPeak.Text = Math.Round(Math.Max(x1, x2),2).ToString()+" dB";
        }
    }
}
