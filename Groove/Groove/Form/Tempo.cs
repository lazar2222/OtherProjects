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
    public partial class Tempo : Form
    {
        Main m;
        public Tempo(Main m)
        {
            this.m = m;
            InitializeComponent();
            numericUpDown1.Value = m.piano.BPM;
            ShowDialog();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            m.piano.BPM = Convert.ToInt32(numericUpDown1.Value);
            m.piano.UpdateBPM();
            this.Close();
        }
    }
}
