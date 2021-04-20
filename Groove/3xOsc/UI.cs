using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _3xOsc
{
    public partial class UI : Form
    {
        _3xOsc o;
        public UI(_3xOsc p)
        {
            o = p;
            InitializeComponent();
            btn1Sine_Click(this, new EventArgs());
            btn2Sine_Click(this, new EventArgs());
            btn3Sine_Click(this, new EventArgs());
        }

        private void btn1Sine_Click(object sender, EventArgs e)
        {
            o.SetShape(0, _3xOsc.Shapes.Sine);
            btn1Sine.BackColor = Color.Lime;
            btn1Triangle.BackColor = SystemColors.Control;
            bnt1Noise.BackColor = SystemColors.Control;
            bnt1Square.BackColor = SystemColors.Control;
            bnt1Saw.BackColor = SystemColors.Control;
        }

        private void bnt1Square_Click(object sender, EventArgs e)
        {
            o.SetShape(0, _3xOsc.Shapes.Square);
            btn1Sine.BackColor = SystemColors.Control;
            btn1Triangle.BackColor = SystemColors.Control;
            bnt1Noise.BackColor = SystemColors.Control;
            bnt1Square.BackColor = Color.Lime;
            bnt1Saw.BackColor = SystemColors.Control;
        }

        private void bnt1Noise_Click(object sender, EventArgs e)
        {
            o.SetShape(0, _3xOsc.Shapes.Noise);
            btn1Sine.BackColor = SystemColors.Control;
            btn1Triangle.BackColor = SystemColors.Control;
            bnt1Noise.BackColor = Color.Lime;
            bnt1Square.BackColor = SystemColors.Control;
            bnt1Saw.BackColor = SystemColors.Control;
        }

        private void btn1Triangle_Click(object sender, EventArgs e)
        {
            o.SetShape(0, _3xOsc.Shapes.Triangle);
            btn1Sine.BackColor = SystemColors.Control;
            btn1Triangle.BackColor = Color.Lime;
            bnt1Noise.BackColor = SystemColors.Control;
            bnt1Square.BackColor = SystemColors.Control;
            bnt1Saw.BackColor = SystemColors.Control;
        }

        private void bnt1Saw_Click(object sender, EventArgs e)
        {
            o.SetShape(0, _3xOsc.Shapes.Saw);
            btn1Sine.BackColor = SystemColors.Control;
            btn1Triangle.BackColor = SystemColors.Control;
            bnt1Noise.BackColor = SystemColors.Control;
            bnt1Square.BackColor = SystemColors.Control;
            bnt1Saw.BackColor = Color.Lime;
        }

        private void btn2Sine_Click(object sender, EventArgs e)
        {
            o.SetShape(1, _3xOsc.Shapes.Sine);
            btn2Sine.BackColor = Color.Lime;
            btn2Triangle.BackColor = SystemColors.Control;
            btn2Noise.BackColor = SystemColors.Control;
            btn2Square.BackColor = SystemColors.Control;
            btn2Saw.BackColor = SystemColors.Control;
        }

        private void btn2Square_Click(object sender, EventArgs e)
        {
            o.SetShape(1, _3xOsc.Shapes.Square);
            btn2Square.BackColor = Color.Lime;
            btn2Triangle.BackColor = SystemColors.Control;
            btn2Noise.BackColor = SystemColors.Control;
            btn2Sine.BackColor = SystemColors.Control;
            btn2Saw.BackColor = SystemColors.Control;
        }

        private void btn2Noise_Click(object sender, EventArgs e)
        {
            o.SetShape(1, _3xOsc.Shapes.Noise);
            btn2Noise.BackColor = Color.Lime;
            btn2Triangle.BackColor = SystemColors.Control;
            btn2Sine.BackColor = SystemColors.Control;
            btn2Square.BackColor = SystemColors.Control;
            btn2Saw.BackColor = SystemColors.Control;
        }

        private void btn2Triangle_Click(object sender, EventArgs e)
        {
            o.SetShape(1, _3xOsc.Shapes.Triangle);
            btn2Triangle.BackColor = Color.Lime;
            btn2Sine.BackColor = SystemColors.Control;
            btn2Noise.BackColor = SystemColors.Control;
            btn2Square.BackColor = SystemColors.Control;
            btn2Saw.BackColor = SystemColors.Control;
        }

        private void btn2Saw_Click(object sender, EventArgs e)
        {
            o.SetShape(1, _3xOsc.Shapes.Sine);
            btn2Saw.BackColor = Color.Lime;
            btn2Triangle.BackColor = SystemColors.Control;
            btn2Noise.BackColor = SystemColors.Control;
            btn2Square.BackColor = SystemColors.Control;
            btn2Sine.BackColor = SystemColors.Control;
        }

        private void btn3Sine_Click(object sender, EventArgs e)
        {
            o.SetShape(2, _3xOsc.Shapes.Sine);
            btn3Sine.BackColor = Color.Lime;
            btn3Triangle.BackColor = SystemColors.Control;
            btn3Noise.BackColor = SystemColors.Control;
            btn3Square.BackColor = SystemColors.Control;
            bnt3Saw.BackColor = SystemColors.Control;
        }

        private void btn3Square_Click(object sender, EventArgs e)
        {
            o.SetShape(2, _3xOsc.Shapes.Square);
            btn3Square.BackColor = Color.Lime;
            btn3Triangle.BackColor = SystemColors.Control;
            btn3Noise.BackColor = SystemColors.Control;
            btn3Sine.BackColor = SystemColors.Control;
            bnt3Saw.BackColor = SystemColors.Control;
        }

        private void btn3Noise_Click(object sender, EventArgs e)
        {
            o.SetShape(2, _3xOsc.Shapes.Noise);
            btn3Noise.BackColor = Color.Lime;
            btn3Triangle.BackColor = SystemColors.Control;
            btn3Square.BackColor = SystemColors.Control;
            btn3Sine.BackColor = SystemColors.Control;
            bnt3Saw.BackColor = SystemColors.Control;
        }

        private void btn3Triangle_Click(object sender, EventArgs e)
        {
            o.SetShape(2, _3xOsc.Shapes.Triangle);
            btn3Triangle.BackColor = Color.Lime;
            btn3Square.BackColor = SystemColors.Control;
            btn3Noise.BackColor = SystemColors.Control;
            btn3Sine.BackColor = SystemColors.Control;
            bnt3Saw.BackColor = SystemColors.Control;
        }

        private void bnt3Saw_Click(object sender, EventArgs e)
        {
            o.SetShape(2, _3xOsc.Shapes.Saw);
            bnt3Saw.BackColor = Color.Lime;
            btn3Triangle.BackColor = SystemColors.Control;
            btn3Noise.BackColor = SystemColors.Control;
            btn3Sine.BackColor = SystemColors.Control;
            btn3Square.BackColor = SystemColors.Control;
        }

        private void AmOsc_CheckedChanged(object sender, EventArgs e)
        {
            o.SetAutomation("Am Osc", AmOsc.Checked ? 1 : 0, true);
        }

        private void UI_FormClosing(object sender, FormClosingEventArgs e)
        {
            this.Hide();
            e.Cancel = true;
        }

        internal void Send(string v1, double v2)
        {
            switch (v1)
            {
                case "Tuning 1": { tune1.Value = (int)(v2 * 48d); lbTune1.Text = tune1.Value.ToString(); break; }
                case "Tuning 2": { tune2.Value = (int)(v2 * 48d); lbTune2.Text = tune2.Value.ToString(); break; }
                case "Tuning 3": { tune3.Value = (int)(v2 * 48d); lbTune3.Text = tune3.Value.ToString(); break; }
                case "Pan 1": { pan1.Value = (int)(v2 * 10); lbPan1.Text = (pan1.Value / 10d).ToString(); break; }
                case "Pan 2": { pan2.Value = (int)(v2 * 10); lbPan2.Text = (pan2.Value / 10d).ToString(); break; }
                case "Pan 3": { pan3.Value = (int)(v2 * 10); lbPan3.Text = (pan3.Value / 10d).ToString(); break; }
                case "Level 1": { lev1.Value = (int)(v2 * 100); lbLev1.Text = lev1.Value.ToString(); break; }
                case "Level 2": { lev2.Value = (int)(v2 * 100); lbLev2.Text = lev2.Value.ToString(); break; }
                case "Level 3": { lev3.Value = (int)(v2 * 100); lbLev3.Text = lev3.Value.ToString(); break; }
                case "A": { Attack.Value = (int)(v2 *1000/ o.sr); lbA.Text = Attack.Value.ToString(); break; }
                case "D": { Decay.Value = (int)(v2 *1000/ o.sr); lbD.Text = Decay.Value.ToString(); break; }
                case "S": { Sustain.Value = (int)(v2 * 100d); lbS.Text = Sustain.Value.ToString(); break; }
                case "R": { Release.Value = (int)(v2 *1000/ o.sr); lbR.Text = Release.Value.ToString(); break; }
                case "Am Osc": { AmOsc.Checked = v2 == 1 ? true : false; break; }
            }
        }

        private void tune1_Scroll(object sender, EventArgs e)
        {
            o.SetAutomation("Tuning 1", (tune1.Value / 48d),true);
            lbTune1.Text = tune1.Value.ToString();
        }

        private void pan1_Scroll(object sender, EventArgs e)
        {
            o.SetAutomation("Pan 1", (pan1.Value / 10d), true);
            lbPan1.Text = (pan1.Value / 10d).ToString();
        }

        private void lev1_Scroll(object sender, EventArgs e)
        {
            o.SetAutomation("Level 1", (lev1.Value / 100d), true);
            lbLev1.Text = (lev1.Value).ToString();
        }

        private void tune2_Scroll(object sender, EventArgs e)
        {
            o.SetAutomation("Tuning 2", (tune2.Value / 48d), true);
            lbTune2.Text = tune2.Value.ToString();
        }

        private void pan2_Scroll(object sender, EventArgs e)
        {
            o.SetAutomation("Pan 2", (pan2.Value / 10d), true);
            lbPan2.Text = (pan2.Value / 10d).ToString();
        }

        private void lev2_Scroll(object sender, EventArgs e)
        {
            o.SetAutomation("Level 2", (lev2.Value / 100d), true);
            lbLev2.Text = (lev2.Value).ToString();
        }

        private void tune3_Scroll(object sender, EventArgs e)
        {
            o.SetAutomation("Tuning 3", (tune3.Value / 48d), true);
            lbTune3.Text = tune3.Value.ToString();
        }

        private void pan3_Scroll(object sender, EventArgs e)
        {
            o.SetAutomation("Pan 3", (pan3.Value / 10d), true);
            lbPan3.Text = (pan3.Value / 10d).ToString();
        }

        private void lev3_Scroll(object sender, EventArgs e)
        {
            o.SetAutomation("Level 3", (lev3.Value / 100d), true);
            lbLev3.Text = (lev3.Value).ToString();
        }

        private void Attack_Scroll(object sender, EventArgs e)
        {
            o.SetAutomation("A", Attack.Value*o.sr/1000d,true);
            lbA.Text = (Attack.Value).ToString();
        }

        private void Decay_Scroll(object sender, EventArgs e)
        {
            o.SetAutomation("D", Decay.Value * o.sr / 1000d, true);
            lbD.Text = (Decay.Value).ToString();
        }

        private void Sustain_Scroll(object sender, EventArgs e)
        {
            o.SetAutomation("D", Sustain.Value/ 100d, true);
            lbS.Text = (Sustain.Value).ToString();
        }

        private void Release_Scroll(object sender, EventArgs e)
        {
            o.SetAutomation("R", Release.Value * o.sr / 1000d, true);
            lbR.Text = (Release.Value).ToString();
        }
    }
}
