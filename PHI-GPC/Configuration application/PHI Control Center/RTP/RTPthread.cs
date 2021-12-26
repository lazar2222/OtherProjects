using PHI_Control_Center.Classes;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using Newtonsoft.Json;
using System.IO;
using System.Windows.Forms;
using System.IO.Ports;
using PluginBase;
using System.Reflection;

namespace PHI_Control_Center.RTP
{
    public static class RTPthread
    {
        public static bool running = false;
        public static Profile profile;
        public static List<GHP> povezaniUredjaji;
        public static Dictionary<string, IPlugin> plugins;

        public static void ThreadFunc()
        {
            if (running)
            {
                LoadProfile();
            }
            if (running)
            {
                LoadPlugins();
            }
            if (running)
            {
                PoveziUredjaje();
            }
            while (running)
            {
                foreach (GHP item in povezaniUredjaji)
                {
                    item.read();
                }
                Thread.Sleep(1);
            }
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
            foreach (KeyValuePair<string, IPlugin> plug in plugins)
            {
                plug.Value.Init();
            }
        }

        private static void PoveziUredjaje()
        {
            povezaniUredjaji = new List<GHP>();
            foreach (string name in SerialPort.GetPortNames())
            {
                byte res = GHP.DeviceConnectedToPort(name);
                if (res != 0)
                {
                    povezaniUredjaji.Add(new GHP(name, profile.ConnectedDevices[res], plugins));
                }
            }
        }

        private static void LoadProfile()
        {
            Directory.CreateDirectory("Profiles");
            if (File.Exists(@"Profiles\default.json"))
            {
                using (StreamReader sr = new StreamReader(@"Profiles\default.json"))
                {
                    profile = JsonConvert.DeserializeObject<Profile>(sr.ReadToEnd());
                }
            }
            else { MessageBox.Show("Ne postoji konfiguracija"); running = false; }
        }

        public static void Start()
        {
            running = true;
            new Thread(ThreadFunc).Start();
        }

        public static void Stop(bool reset)
        {
            running = false;
            foreach (GHP item in povezaniUredjaji)
            {
                if (!reset) { item.SendMessage(GHP.SYSTEM, GHP.SYSTEM_RESET); }
                item.Close();
            }
            foreach (KeyValuePair<string, IPlugin> plug in plugins)
            {
                plug.Value.Close();
            }
        }
    }
}
