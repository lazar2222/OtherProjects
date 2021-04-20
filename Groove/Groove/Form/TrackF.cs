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
    public partial class TrackF : Form
    {
        Main m;
        public TrackF(Main m)
        {
            this.m = m;
            InitializeComponent();
            for (int i = 0; i < m.m.Channels.Count; i++)
            {
                comboBox1.Items.Add(m.m.Channels[i].name);
            }
            ShowDialog();
        }

        private void button1_Click(object sender, EventArgs e)
        {

            m.piano.Text = comboBox1.Items[comboBox1.SelectedIndex].ToString();
            m.piano.target = m.m.Channels.Find(x => x.name == comboBox1.Items[comboBox1.SelectedIndex].ToString());
            m.piano.loadTrack();
            Close();
        }
    }
}
