using PluginBase;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MidiPlugin
{
    public partial class dialogForm : Form, IDialogForm

    {
        public dialogForm()
        {
            InitializeComponent();
        }

        public List<object> go(List<object> start)
        {
            if (start == null)
            {
                start = new List<object>();
                start.Add(0);
                start.Add(0);
            }
            numericUpDown1.Value = Convert.ToInt32(start[1]);
            numericUpDown2.Value = Convert.ToInt32(start[0]);
            ShowDialog();
            start[0] = numericUpDown2.Value;
            start[1] = numericUpDown1.Value;
            return start;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Close();
        }
    }
}
