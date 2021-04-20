using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using DipBase;

namespace Delay
{
    public class Delay : AudioEffect
    {
        Dictionary<string, double> d = new Dictionary<string, double>();
        float[][] buf = new float[2][];
        int wc=0,MAX;
        float[] last=new float[2];
        UI ui;

        public Delay(int sr)
        {
            ui = new UI(this);
            d.Add("Time", 0);
            d.Add("Dry/Wet", 0);
            d.Add("FeedBack", 0);
            MAX = sr * 3;
            for (int i = 0; i < 2; i++)
            {
                buf[i] = new float[MAX];
                last[i] = 0;
            }
            
        }

        public string[] GerAutomationParams()
        {
            return new string[] { "Time", "Dry/Wet", "FeedBack" };
        }

        public void Get(float[][] output)
        {
            for (int j = 0; j < output[0].Length; j++)
            {
                for (int i = 0; i < 2; i++)
                {
                    float f = output[i][j]+(float)(last[i]*d["FeedBack"]);
                    output[i][j] = (float)((buf[i][wc]*d["Dry/Wet"])+(f*(1- d["Dry/Wet"])));
                    last[i] = output[i][j];
                    buf[i][wc] = f;
                    wc++;
                    if (wc >= MAX * d["Time"]) { wc = 0; }
                }
            }
        }

        internal void SetAutomation(string name, double value, bool v3)
        {
            d[name] = value;
        }

        public double GetAutomation(string name)
        {
            return d[name];
        }

        public PluginInfo GetPluginInfo()
        {
            return new PluginInfo(PluginType.AudioEffect, "Delay", "1.0");
        }

        public void SetAutomation(string name, double value)
        {
            d[name] = value;
            ui.Send(d["Time"], d["FeedBack"], d["Dry/Wet"]);
        }

        public void ShowUI()
        {
            ui.Send(d["Time"], d["FeedBack"], d["Dry/Wet"]);
            ui.Show();
        }
    }
}
