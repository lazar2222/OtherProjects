using PHI_Control_Center.Classes;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace PHI_Control_Center.Dialogs
{
    public partial class PersistentDialog : Form
    {
        Device device;
        string port;
        public PersistentDialog(Device d)
        {
            device = d;
            InitializeComponent();
        }

        private void PersistentDialog_Load(object sender, EventArgs e)
        {
            port = GHP.DevicePort(device.DeviceId);
            if (port != "")
            {
                foreach (PersistentVariable var in device.PersistentVariables)
                {
                    dataGridView1.Rows.Add(var.Name, var.Id, GHP.GetPeristent(port, var.Id));
                }
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            foreach (DataGridViewRow item in dataGridView1.Rows)
            {
                GHP.SetPeristent(port,Convert.ToByte(item.Cells[1].Value), Convert.ToByte(item.Cells[2].Value));
            }
            Close();
        }
    }
}
