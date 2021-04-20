using Groove.Controls;
using Groove.Pipeline;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Groove
{
    public partial class Prompt : Form
    {
        bool track;
        Main m;

        public Prompt(Main m, bool track)
        {
            this.track = track;
            this.m = m;
            InitializeComponent();
            ShowDialog();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (track)
            {
                Mixer.Channel c = new Mixer.Channel(512, textBox1.Text);
                m.m.Channels.Add(c);
                Track t = new Track(m, c);
                m.TC.Add(t);
            }
            else
            {
                Mixer.Bus b = new Mixer.Bus(512, "Bus A");
                m.m.Buses.Add(b);
                Trackb tb = new Trackb(m, b);
                m.TB.Add(tb);
                for (int i = 0; i < m.TC.Count; i++)
                {
                    m.TC[i].popOuts();
                }
                for (int i = 0; i < m.TB.Count; i++)
                {
                    m.TB[i].popOuts();
                }
            }
            Close();
        }
    }
}
