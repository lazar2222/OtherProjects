using PHI_Control_Center.Classes;
using PHI_Control_Center.RTP;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Newtonsoft.Json;
using System.IO;
using PHI_Control_Center.Dialogs;
using System.Reflection;
using PluginBase;

namespace PHI_Control_Center
{
    public partial class Configure : Form
    {
        public Configure()
        {
            InitializeComponent();
            TaskbarIcon.Visible = true;
        }

        bool exitclose = false;
        bool shown = false;
        Profile current;
        List<Device> Devices;
        public static Dictionary<string, IPlugin> plugins;

        private void EXITToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (RTPthread.running)
            {
                RTPthread.Stop(false);
            }
            exitclose = true;
            Application.Exit();
        }

        private void configureToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (RTPthread.running)
            {
                if (DialogResult.Yes == MessageBox.Show("RTP is running, do you want to stop it", "RTP", MessageBoxButtons.YesNo))
                {
                    RTPthread.Stop(false);
                    shown = true;
                    Show();
                }
            }
            else
            {
                shown = true;
                Show();
            }

        }

        private void Configure_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (!exitclose)
            {
                shown = false;
                Hide();
                e.Cancel = true;
            }
        }

        private void Configure_Load(object sender, EventArgs e)
        {
            LoadDevices();
            LoadPlugins();
            Directory.CreateDirectory("Profiles");
            if (File.Exists(@"Profiles\default.json"))
            {
                using (StreamReader sr = new StreamReader(@"Profiles\default.json"))
                {
                    current = JsonConvert.DeserializeObject<Profile>(sr.ReadToEnd());
                    Text = "PHI Control Center - default.json";
                }
            }
            else { InitializeProfile(); }
            
        }

        private void InitializeProfile()
        {
            Text = "PHI Control Center - Untitled.json";
            current = new Profile();
            foreach (Device d in Devices)
            {
                ConnectedDevice c;
                if (current.ConnectedDevices.ContainsKey(d.DeviceId))
                {
                    c = current.ConnectedDevices[d.DeviceId];
                }
                else
                {
                    c = new ConnectedDevice();
                    c.DeviceId = d.DeviceId;
                    current.ConnectedDevices.Add(c.DeviceId, c);
                }
                
                foreach (Bank b in d.Banks)
                {
                    c.ActivePage.Add(b.Name, b.Name + "1");
                    foreach (Classes.Control cnt in b.Controls)
                    {
                        if (cnt.Type == CType.RGBButton)
                        {
                            if (!c.Controlls.ContainsKey(CType.Button))
                            {
                                c.Controlls.Add(CType.Button, new Dictionary<int, ProfileControl>());
                            }
                            if (!c.Controlls.ContainsKey(CType.RGBLED))
                            {
                                c.Controlls.Add(CType.RGBLED, new Dictionary<int, ProfileControl>());
                            }
                            ProfileControl pc = new ProfileControl();
                            pc.BankName = b.Name;
                            c.Controlls[CType.Button].Add(cnt.Id, pc);
                            pc = new ProfileControl();
                            pc.BankName = b.Name;
                            c.Controlls[CType.RGBLED].Add(cnt.Idl, pc);
                        }
                        else if (cnt.Type == CType.JoyStick)
                        {
                            if (!c.Controlls.ContainsKey(CType.Analog))
                            {
                                c.Controlls.Add(CType.Analog, new Dictionary<int, ProfileControl>());
                            }
                            if (!c.Controlls.ContainsKey(CType.Button))
                            {
                                c.Controlls.Add(CType.Button, new Dictionary<int, ProfileControl>());
                            }
                            ProfileControl pc = new ProfileControl();
                            pc.BankName = b.Name;
                            c.Controlls[CType.Analog].Add(cnt.IdA1, pc);
                            pc = new ProfileControl();
                            pc.BankName = b.Name;
                            c.Controlls[CType.Analog].Add(cnt.IdA2, pc);
                            pc = new ProfileControl();
                            pc.BankName = b.Name;
                            c.Controlls[CType.Button].Add(cnt.IdS, pc);
                        }
                        else
                        {
                            if (!c.Controlls.ContainsKey(cnt.Type))
                            {
                                c.Controlls.Add(cnt.Type, new Dictionary<int, ProfileControl>());
                            }
                            ProfileControl pc = new ProfileControl();
                            pc.BankName = b.Name;
                            c.Controlls[cnt.Type].Add(cnt.Id, pc);
                        }
                    }
                }

            }
        }

        private void DevicesLB_SelectedIndexChanged(object sender, EventArgs e)
        {
            Device d = (Device)DevicesLB.SelectedItem;
            if (d.IsAddon == false)
            {
                pb.Image = new Bitmap(@"Devices/" + d.DeviceId + ".png");
                addonsToolStripMenuItem.Enabled = true;
            }
            else
            {
                pb.Image = new Bitmap(@"Devices/A" + (d.DeviceId + d.AddonAddress) + ".png");
                addonsToolStripMenuItem.Enabled = false;
            }
            perisitentDataToolStripMenuItem.Enabled = true;
        }

        private void pb_MouseClick(object sender, MouseEventArgs e)
        {
            try
            {
                foreach (Bank b in ((Device)DevicesLB.SelectedItem).Banks)
                {
                    foreach (Classes.Control c in b.Controls)
                    {
                        if (e.X >= c.X && e.X <= c.X + c.W && e.Y >= c.Y && e.Y <= c.Y + c.H)
                        {
                            new ControlDialog(c, plugins, current.ConnectedDevices[((Device)DevicesLB.SelectedItem).DeviceId]).ShowDialog();
                        }
                    }
                }
            }
            catch { }
        }

        private void SetText()
        {
            StartStopRTPToolStripMenuItem.Text = RTPthread.running ? "Stop RTP" : "Start RTP";
        }

        private void StartStopRTPToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (shown)
            {
                MessageBox.Show("Cant start RTP while configurator is open");
            }
            else
            {
                if (RTPthread.running)
                {
                    RTPthread.Stop(false);
                }
                else
                {
                    RTPthread.Start();
                }
            }
        }

        private void TaskbarStrip_Opened(object sender, EventArgs e)
        {
            SetText();
        }

        private void newProfileToolStripMenuItem_Click(object sender, EventArgs e)
        {
            InitializeProfile();
        }

        private void openProfileToolStripMenuItem_Click(object sender, EventArgs e)
        {
            openFileDialog1.ShowDialog();
            if (openFileDialog1.FileName != "")
            {
                using (StreamReader sw = new StreamReader(openFileDialog1.OpenFile()))
                {
                    current = JsonConvert.DeserializeObject<Profile>(sw.ReadToEnd());
                }
                Text = "PHI Control Center - " + openFileDialog1.FileName;
            }
        }

        private void saveProfileToolStripMenuItem_Click(object sender, EventArgs e)
        {
            saveFileDialog1.ShowDialog();
            if (saveFileDialog1.FileName != "")
            {
                using (StreamWriter sw = new StreamWriter(saveFileDialog1.OpenFile()))
                {
                    sw.Write(JsonConvert.SerializeObject(current));
                }
                Text = "PHI Control Center - " + saveFileDialog1.FileName;
            }
        }

        private void setAsActiveProfileToolStripMenuItem_Click(object sender, EventArgs e)
        {
            using (StreamWriter sw = new StreamWriter(@"Profiles\default.json"))
            {
                sw.Write(JsonConvert.SerializeObject(current));
            }
        }

        private void LoadDevices()
        {
            Devices = new List<Device>();
            foreach (string file in Directory.GetFiles("Devices"))
            {
                if (file.EndsWith(".json"))
                {
                    using (StreamReader sr = new StreamReader(file))
                    {
                        Device d = JsonConvert.DeserializeObject<Device>(sr.ReadToEnd());
                        if (!d.IsAddon)
                        {
                            if (GHP.DevicePort(d.DeviceId) != "")
                            {
                                Devices.Add(d);
                            }
                        }
                        else
                        {
                            if (GHP.AddonEnabled(d.DeviceId, d.AddonAddress))
                            {
                                Devices.Add(d);
                            }
                        }
                    }
                }
            }
            Devices.Sort();
            pb.Image = null;
            addonsToolStripMenuItem.Enabled = false;
            perisitentDataToolStripMenuItem.Enabled = false;
            DevicesLB.DataSource = Devices;
        }

        private static void LoadPlugins()
        {
            plugins = new Dictionary<string, IPlugin>();
            Directory.CreateDirectory("Plugins");
            string s = AppDomain.CurrentDomain.BaseDirectory + @"\Plugins";
            foreach (var item in Directory.EnumerateFiles(s))
            {
                if (item.EndsWith(".dll"))
                {
                    try
                    {
                        var DLL = Assembly.LoadFile(item);

                        foreach (Type type in DLL.GetExportedTypes())
                        {
                            try
                            {
                                dynamic c = Activator.CreateInstance(type);
                                if (c.Selftest())
                                {
                                    plugins.Add(c.GetPluginName(), c);
                                }
                            }
                            catch { Console.WriteLine(type + " Is not a plugn"); }
                        }

                    }
                    catch { Console.WriteLine(item + " Errored"); }
                }
            }
        }

        private void Refresh_Click(object sender, EventArgs e)
        {
            LoadDevices();
        }

        private void addonsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            new AddonDialog((Device)DevicesLB.SelectedItem).ShowDialog();
            LoadDevices();
        }

        private void perisitentDataToolStripMenuItem_Click(object sender, EventArgs e)
        {
            new PersistentDialog((Device)DevicesLB.SelectedItem).ShowDialog();
        }
    }
}
