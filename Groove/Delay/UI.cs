using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Delay
{
    public partial class UI : Form
    {
        Delay d;

        public UI(Delay d)
        {
            this.d = d;
            InitializeComponent();
        }

        internal void Send(double v1, double v2, double v3)
        {
            trackBar1.Value = (int)(v1*100);
            trackBar2.Value = (int)(v2*100);
            trackBar3.Value = (int)(v3*100);
        }

        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            label2.Text = (3000f * trackBar1.Value / 100f).ToString();
            d.SetAutomation("Time", trackBar1.Value / 100d,true);
        }

        private void trackBar2_Scroll(object sender, EventArgs e)
        {
            label3.Text = trackBar2.Value.ToString();
            d.SetAutomation("FeedBack", trackBar2.Value / 100d,true);
        }

        private void trackBar3_Scroll(object sender, EventArgs e)
        {
            label5.Text = trackBar3.Value.ToString();
            d.SetAutomation("Dry/Wet", trackBar3.Value / 100d,true);
        }

        private void UI_FormClosing(object sender, FormClosingEventArgs e)
        {
            this.Hide();
            e.Cancel = true;
        }
    }
}
