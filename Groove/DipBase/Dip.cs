using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DipBase
{
    public class Note
    {
        public Note(double f, int v, int a, double p)
        {
            freq = f;
            velocity = v;
            aftertouch = a;
            pitchbend = p;
        }

        public double freq;
        public int velocity;
        public int aftertouch;
        public double pitchbend;
    }


    public class PluginInfo
    {
        public PluginInfo(PluginType t, string n, string v)
        {
            type = t;
            name = n;
            version = v;
        }

        public PluginType type;
        public string name;
        public string version;

    }

    public enum PluginType
    {
        Instrument,
        AudioEffect
    }

    public interface Instrument : Input
    {
        PluginInfo GetPluginInfo();
        string[] GerAutomationParams();
        double GetAutomation(string name);
        void SetAutomation(string name, double value);
        void SetNote(Note note);
        void SetParams(Note note);
        void ShowUI();
    }

    public interface AudioEffect
    {
        PluginInfo GetPluginInfo();
        string[] GerAutomationParams();
        double GetAutomation(string name);
        void SetAutomation(string name, double value);
        void Get(float[][] output);
        void ShowUI();
    }

    public interface Input
    {
        void Get(float[][] inp, float[][] stereo);
    }
    public interface Output
    {
        void Set(float[][] stereo, float[][] ou);
    }
}
