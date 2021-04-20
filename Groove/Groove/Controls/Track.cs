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
    public partial class Track : UserControl
    {
        Main m;
        Mixer.Channel mc;
        int ticks1 = 0, ticks2 = 0;
        float s1, s2;
        bool peak;
        DataGridViewComboBoxColumn sends;

        private void PPE_Click(object sender, EventArgs e)
        {
            mc.preE = !mc.preE;
            if (mc.preE) { PPE.BackColor = Color.Lime; }
            else { PPE.BackColor = Color.Red; }
        }

        private void PPS_Click(object sender, EventArgs e)
        {
            mc.preS = !mc.preS;
            if (mc.preS) { PPS.BackColor = Color.Lime; }
            else { PPS.BackColor = Color.Red; }
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

        private void WaveForm_Click(object sender, EventArgs e)
        {

        }

        private void Spectrogram_Click(object sender, EventArgs e)
        {

        }

        private void Pan_Scroll(object sender, EventArgs e)
        {
            mc.Pan = (Pan.Value * 0.1f);
            lbPan.Text = (Pan.Value * 0.1d).ToString();
        }

        private void Level_Scroll(object sender, EventArgs e)
        {
            double x = ((Level.Value * 0.3d) * (Math.Abs(Level.Value) / 54d));
            mc.level = (float)(x < -101 ? 0 : Math.Pow(10, x / 20d));
            lbLevel.Text = (Math.Round(x, 2) >= 101 ? "-Inf " : Math.Round(x, 2).ToString()) + "dB";
        }

        private void BG_Click(object sender, EventArgs e)
        {
            peak = false;
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
            if (x1 >= -0.0000001 || x1 >= -0.0000001) { peak = true; }
            if (peak) { e.Graphics.FillRectangle(Brushes.Red, 52, 10, 15, 8); }
            e.Graphics.FillRectangle(Brushes.Red, 52f, 316f - ((60f + (float)Math.Min(x1, 0)) * 4.95f), 7f, ((60f + (float)Math.Min(x1, -18)) * 5f));
            e.Graphics.FillRectangle(Brushes.Red, 60f, 316f - ((60f + (float)Math.Min(x2, 0)) * 4.95f), 7f, ((60f + (float)Math.Min(x2, -18)) * 5f));
            e.Graphics.FillRectangle(Brushes.Yellow, 52f, 316f - ((60f + (float)Math.Min(x1, -6)) * 4.95f), 7f, ((60f + (float)Math.Min(x1, -18)) * 5f));
            e.Graphics.FillRectangle(Brushes.Yellow, 60f, 316f - ((60f + (float)Math.Min(x2, -6)) * 4.95f), 7f, ((60f + (float)Math.Min(x2, -18)) * 5f));
            e.Graphics.FillRectangle(Brushes.Lime, 52f, 316f - ((60f + (float)Math.Min(x1, -18)) * 4.95f), 7f, ((60f + (float)Math.Min(x1, -18)) * 5f));
            e.Graphics.FillRectangle(Brushes.Lime, 60f, 316f - ((60f + (float)Math.Min(x2, -18)) * 4.95f), 7f, ((60f + (float)Math.Min(x2, -18)) * 5f));
            e.Graphics.DrawLine(Pens.Orange, 52f, 316f - ((60f + (float)Math.Min(sx1, 0)) * 4.95f), 59f, 316f - ((60f + (float)Math.Min(sx1, 0)) * 4.95f));
            e.Graphics.DrawLine(Pens.Orange, 60f, 316f - ((60f + (float)Math.Min(sx2, 0)) * 4.95f), 67f, 316f - ((60f + (float)Math.Min(sx2, 0)) * 4.95f));
            lbPeak.Text = Math.Round(Math.Max(x1, x2), 2).ToString() + " dB";
        }

        private void Input_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (Input.Items[Input.SelectedIndex].ToString() == "None") { mc.Input = null; }
            else if (Input.SelectedIndex < m.inst.Count + 1) { mc.Input = (Instrument)Activator.CreateInstance(m.inst.Find(x => x.GetPluginInfo().name == Input.Items[Input.SelectedIndex].ToString()).GetType(), 48000); }
            else { mc.Input = m.m.HInps.Find(x => x.Name == Input.Items[Input.SelectedIndex].ToString()); }
        }

        private void Output_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (Output.Items[Output.SelectedIndex].ToString() == "None") { mc.Output = null; }
            else if (Output.Items[Output.SelectedIndex].ToString() == "Master") { mc.Output = m.m.MasterC; }
            else if (Output.SelectedIndex < m.m.Buses.Count + 2) { mc.Output = m.m.Buses.Find(x => x.name == Output.Items[Output.SelectedIndex].ToString()); }
            else { mc.Output = m.m.HOuts.Find(x => x.Name == Output.Items[Output.SelectedIndex].ToString()); }
        }

        private void Sends_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            if (e.ColumnIndex == 1)
            {
                
                if (Sends.Rows[e.RowIndex].Cells[1].Value.ToString() == "None")
                {
                    mc.Sends[e.RowIndex] = null;
                }
                else
                {
                    mc.Sends[e.RowIndex]=new Tuple<Mixer.Bus, float>(m.m.Buses.Find(x => x.name == Sends.Rows[e.RowIndex].Cells[1].Value.ToString()), (float)Math.Pow(10, 0 / 20f));
                }
            }
            else
            {
                try { mc.Sends[e.RowIndex] = new Tuple<Mixer.Bus, float>(mc.Sends[e.RowIndex].Item1, (float)Math.Pow(10, Convert.ToSingle(Sends.Rows[e.RowIndex].Cells[0].Value.ToString()) / 20f)); } catch { }
            }
        }

        private void Sends_CellClick(object sender, DataGridViewCellEventArgs e)
        {
        }

        private void TrackName_DoubleClick(object sender, EventArgs e)
        {
            ((Instrument)mc.Input).ShowUI();
            m.selectedINST = m.m.Channels.IndexOf(mc);
        }

        private void Track_Load(object sender, EventArgs e)
        {

        }

        private void TrackName_MouseClick(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Right)
            {
                if (MessageBox.Show("Do you raly want to delete this track", "Confiramtion", MessageBoxButtons.YesNo) == DialogResult.Yes)
                {
                    m.m.Channels.Remove(mc);
                    if( m.piano.Notes.ContainsKey(mc)){ m.piano.Notes.Remove(mc); m.piano.trackToolStripMenuItem_Click(this, new EventArgs()); }
                    m.TC.Remove(this);
                    m.Reorder();
                    m.Controls.Remove(this);
                    this.Dispose();
                }
            }
        }

        public Track(Main m, Mixer.Channel mc)
        {
            this.m = m;
            this.mc = mc;
            InitializeComponent();
            TrackName.Text = mc.name;
            if (mc.preE) { PPE.BackColor = Color.Lime; }
            else { PPE.BackColor = Color.Red; }
            if (mc.preS) { PPS.BackColor = Color.Lime; }
            else { PPS.BackColor = Color.Red; }
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
            sends = new DataGridViewComboBoxColumn();
            sends.MaxDropDownItems = 4;
            sends.Width = 90;
            Sends.Columns.Add("e", "e");
            Sends.Columns[0].Width = 30;
            Sends.Columns.Add(sends);
            for (int i = 0; i < 10; i++)
            {
                Sends.Rows.Add("0");
            }
            Location = new Point(m.x, 27);
            m.x += 130;
            m.Controls.Add(this);
            popOuts();
        }

        public void popOuts()
        {
            Input.Items.Clear();
            Output.Items.Clear();
            sends.Items.Clear();
            Input.Items.Add("None");
            for (int i = 0; i < m.inst.Count; i++)
            {
                Input.Items.Add(m.inst[i].GetPluginInfo().name);
            }
            for (int i = 0; i < m.m.HInps.Count; i++)
            {
                Input.Items.Add(m.m.HInps[i].Name);
            }
            Output.Items.Add("None");
            Output.Items.Add("Master");
            for (int i = 0; i < m.m.Buses.Count; i++)
            {
                Output.Items.Add(m.m.Buses[i].name);
            }
            for (int i = 0; i < m.m.HOuts.Count; i++)
            {
                Output.Items.Add(m.m.HOuts[i].Name);
            }
            sends.Items.Add("None");
            for (int i = 0; i < m.m.Buses.Count; i++)
            {
                sends.Items.Add(m.m.Buses[i].name);
            }
        }
    }
}
