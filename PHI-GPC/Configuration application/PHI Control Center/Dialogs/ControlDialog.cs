using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using PHI_Control_Center.Classes;
using PluginBase;

namespace PHI_Control_Center.Dialogs
{
    public partial class ControlDialog : Form
    {
        private Classes.Control c;
        private Dictionary<string, IPlugin> plugins;
        private ConnectedDevice current;
        private List<object> tmp1;
        private List<object> tmp2;
        private List<object> tmp3;

        public ControlDialog(Classes.Control c, Dictionary<string, IPlugin> plugins, ConnectedDevice current)
        {
            this.c = c;
            this.plugins = plugins;
            this.current = current;
            InitializeComponent();
        }

        private void setVis(bool a, bool b, bool c)
        {
            label1.Visible = a;
            comboBox1.Visible = a;
            button1.Visible = a;
            label2.Visible = b;
            comboBox2.Visible = b;
            button2.Visible = b;
            label3.Visible = c;
            comboBox3.Visible = c;
            button3.Visible = c;
        }

        private void Populate(ComboBox cb, CType tt)
        {
            foreach (KeyValuePair<string, IPlugin> plugin in plugins)
            {
                foreach (KeyValuePair<string, FunctionBox> fb in plugin.Value.GetFunctions())
                {
                    if (fb.Value.functionType == tt) { cb.Items.Add(fb.Key); }
                }
            }
        }

        private void ControlDialog_Load(object sender, EventArgs e)
        {
            Text = c.Type.ToString() + " " + c.Id;
            if (c.Type == CType.RGBButton)
            {
                setVis(true, true, false);
                label1.Text = CType.Button.ToString() + " " + c.Id;
                label2.Text = CType.RGBLED.ToString() + " " + c.Idl;
                Populate(comboBox1, CType.Button);
                Populate(comboBox2, CType.RGBLED);
                string page = current.ActivePage[current.Controlls[CType.Button][c.Id].BankName];
                if (current.Controlls[CType.Button][c.Id].Mappings.ContainsKey(page))
                {
                    comboBox1.SelectedItem = current.Controlls[CType.Button][c.Id].Mappings[page].FunctionName;
                    tmp1 = current.Controlls[CType.Button][c.Id].Mappings[page].args;
                }
                page = current.ActivePage[current.Controlls[CType.RGBLED][c.Idl].BankName];
                if (current.Controlls[CType.RGBLED][c.Idl].Mappings.ContainsKey(page))
                {
                    comboBox2.SelectedItem = current.Controlls[CType.RGBLED][c.Idl].Mappings[page].FunctionName;
                    tmp2 = current.Controlls[CType.RGBLED][c.Idl].Mappings[page].args;
                }
            }
            else if (c.Type == CType.JoyStick)
            {
                setVis(true, true, true);
                label1.Text = CType.Analog.ToString() + " " + c.IdA1;
                label2.Text = CType.Button.ToString() + " " + c.IdA2;
                label3.Text = CType.Button.ToString() + " " + c.IdS;
                Populate(comboBox1, CType.Analog);
                Populate(comboBox2, CType.Analog);
                Populate(comboBox3, CType.Button);

                string page = current.ActivePage[current.Controlls[CType.Analog][c.IdA1].BankName];
                if (current.Controlls[CType.Analog][c.IdA1].Mappings.ContainsKey(page))
                {
                    comboBox1.SelectedItem = current.Controlls[CType.Analog][c.IdA1].Mappings[page].FunctionName;
                    tmp1 = current.Controlls[CType.Analog][c.IdA1].Mappings[page].args;
                }
                page = current.ActivePage[current.Controlls[CType.Analog][c.IdA2].BankName];
                if (current.Controlls[CType.Analog][c.IdA2].Mappings.ContainsKey(page))
                {
                    comboBox2.SelectedItem = current.Controlls[CType.Analog][c.IdA2].Mappings[page].FunctionName;
                    tmp2 = current.Controlls[CType.Analog][c.IdA2].Mappings[page].args;
                }
                page = current.ActivePage[current.Controlls[CType.Button][c.IdS].BankName];
                if (current.Controlls[CType.Button][c.IdS].Mappings.ContainsKey(page))
                {
                    comboBox3.SelectedItem = current.Controlls[CType.Button][c.IdS].Mappings[page].FunctionName;
                    tmp3 = current.Controlls[CType.Button][c.IdS].Mappings[page].args;
                }
            }
            else
            {
                setVis(true, false, false);
                label1.Text = c.Type.ToString() + " " + c.Id;
                Populate(comboBox1, c.Type);

                string page = current.ActivePage[current.Controlls[c.Type][c.Id].BankName];
                if (current.Controlls[c.Type][c.Id].Mappings.ContainsKey(page))
                {
                    comboBox1.SelectedItem = current.Controlls[c.Type][c.Id].Mappings[page].FunctionName;
                    tmp1 = current.Controlls[c.Type][c.Id].Mappings[page].args;
                }
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            foreach (KeyValuePair<string, IPlugin> plugin in plugins)
            {
                if (plugin.Value.GetFunctions().ContainsKey(comboBox1.Text))
                {
                    tmp1 = plugin.Value.GetFunctions()[comboBox1.Text].dialogForm.go(tmp1);
                }
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            foreach (KeyValuePair<string, IPlugin> plugin in plugins)
            {
                if (plugin.Value.GetFunctions().ContainsKey(comboBox2.Text))
                {
                    tmp2 = plugin.Value.GetFunctions()[comboBox2.Text].dialogForm.go(tmp2);
                }
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            foreach (KeyValuePair<string, IPlugin> plugin in plugins)
            {
                if (plugin.Value.GetFunctions().ContainsKey(comboBox3.Text))
                {
                    tmp3 = plugin.Value.GetFunctions()[comboBox3.Text].dialogForm.go(tmp3);
                }
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            if (c.Type == CType.RGBButton)
            {
                string page = current.ActivePage[current.Controlls[CType.Button][c.Id].BankName];
                if (comboBox1.Text != "")
                {
                    if (!current.Controlls[CType.Button][c.Id].Mappings.ContainsKey(page))
                    {
                        current.Controlls[CType.Button][c.Id].Mappings.Add(page, new Mapping());
                    }
                    current.Controlls[CType.Button][c.Id].Mappings[page] = new Mapping(GetPluginName(comboBox1), comboBox1.Text, tmp1);
                }
                else
                {
                    current.Controlls[CType.Button][c.Id].Mappings.Remove(page);
                }

                page = current.ActivePage[current.Controlls[CType.RGBLED][c.Idl].BankName];
                if (comboBox2.Text != "")
                {
                    if (!current.Controlls[CType.RGBLED][c.Idl].Mappings.ContainsKey(page))
                    {
                        current.Controlls[CType.RGBLED][c.Idl].Mappings.Add(page, new Mapping());
                    }
                    current.Controlls[CType.RGBLED][c.Idl].Mappings[page] = new Mapping(GetPluginName(comboBox2), comboBox2.Text, tmp2);
                }
                else
                {
                    current.Controlls[CType.RGBLED][c.Idl].Mappings.Remove(page);
                }
            }
            else if (c.Type == CType.JoyStick)
            {
                string page = current.ActivePage[current.Controlls[CType.Analog][c.IdA1].BankName];
                if (comboBox1.Text != "")
                {
                    if (!current.Controlls[CType.Analog][c.IdA1].Mappings.ContainsKey(page))
                    {
                        current.Controlls[CType.Analog][c.IdA1].Mappings.Add(page, new Mapping());
                    }
                    current.Controlls[CType.Analog][c.IdA1].Mappings[page] = new Mapping(GetPluginName(comboBox1), comboBox1.Text, tmp1);
                }
                else
                {
                    current.Controlls[CType.Analog][c.IdA1].Mappings.Remove(page);
                }

                page = current.ActivePage[current.Controlls[CType.Analog][c.IdA2].BankName];
                if (comboBox2.Text != "")
                {
                    if (!current.Controlls[CType.Analog][c.IdA2].Mappings.ContainsKey(page))
                    {
                        current.Controlls[CType.Analog][c.IdA2].Mappings.Add(page, new Mapping());
                    }
                    current.Controlls[CType.Analog][c.IdA2].Mappings[page] = new Mapping(GetPluginName(comboBox2), comboBox2.Text, tmp2);
                }
                else
                {
                    current.Controlls[CType.Analog][c.IdA2].Mappings.Remove(page);
                }

                page = current.ActivePage[current.Controlls[CType.Button][c.IdS].BankName];
                if (comboBox3.Text != "")
                {
                    if (!current.Controlls[CType.Button][c.IdS].Mappings.ContainsKey(page))
                    {
                        current.Controlls[CType.Button][c.IdS].Mappings.Add(page, new Mapping());
                    }
                    current.Controlls[CType.Button][c.IdS].Mappings[page] = new Mapping(GetPluginName(comboBox3), comboBox3.Text, tmp3);
                }
                else
                {
                    current.Controlls[CType.Button][c.IdS].Mappings.Remove(page);
                }
            }
            else
            {
                string page = current.ActivePage[current.Controlls[c.Type][c.Id].BankName];
                if (comboBox1.Text != "")
                {
                    if (!current.Controlls[c.Type][c.Id].Mappings.ContainsKey(page))
                    {
                        current.Controlls[c.Type][c.Id].Mappings.Add(page, new Mapping());
                    }
                    current.Controlls[c.Type][c.Id].Mappings[page] = new Mapping(GetPluginName(comboBox1), comboBox1.Text, tmp1);
                }
                else
                {
                    current.Controlls[c.Type][c.Id].Mappings.Remove(page);
                }
            }
            Close();
        }

        private string GetPluginName(ComboBox cb)
        {
            foreach (KeyValuePair<string, IPlugin> plugin in plugins)
            {
                if (plugin.Value.GetFunctions().ContainsKey(cb.Text))
                {
                    return plugin.Key;
                }
            }
            return "";
        }
    }
}
