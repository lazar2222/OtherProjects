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
    public partial class AddonDialog : Form
    {
        Device device;
        string port;

        public AddonDialog(Device d)
        {
            device = d;
            InitializeComponent();
        }

        private void AddonDialog_Load(object sender, EventArgs e)
        {
            port = GHP.DevicePort(device.DeviceId);
            foreach (Addon item in device.Addons)
            {
                checkedListBox1.Items.Add(item, GHP.AddonEnabled(device.DeviceId, item.AddonAddress));
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < checkedListBox1.Items.Count; i++)
            {
                GHP.SetPeristent(port, ((Addon)checkedListBox1.Items[i]).AddonAddress,(byte)(checkedListBox1.GetItemChecked(i)?1:0));
            }
            Close();
        }
    }
}
