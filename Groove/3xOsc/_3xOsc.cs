using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using DipBase;
using NoteLib;

namespace _3xOsc
{
    public class _3xOsc : Instrument
    {
        Dictionary<string, double> d = new Dictionary<string, double>();
        List<MyNote> Notes = new List<MyNote>();
        UI ui;
        Shapes[] Shape = new Shapes[3];
        long count = 0;
        public int sr;
        double val = 0;
        private bool neg;
        Random r;

        internal class MyNote : Note
        {
            public MyNote(double f, int v, int a, double p, long t) : base(f, v, a, p)
            {
                ts = t;
            }
            public bool on = true;
            public long ts = 0;
            public long tsr = 0;
            public float ev = 0;
        }

        public enum Shapes
        {
            Sine,
            Square,
            Triangle,
            Saw,
            Noise
        }

        public _3xOsc(int SR)
        {
            sr = SR;
            ui = new UI(this);
            r = new Random();
            d.Add("Tuning 1", 0.5);
            d.Add("Tuning 2", 0.25);
            d.Add("Tuning 3", 0);
            d.Add("Pan 1", 0);
            d.Add("Pan 2", 0);
            d.Add("Pan 3", 0);
            d.Add("Level 1", 1);
            d.Add("Level 2", 0.5);
            d.Add("Level 3", 0.25);
            d.Add("A", 48);
            d.Add("D", 48);
            d.Add("S", 0.5);
            d.Add("R", 48);
            d.Add("Am Osc", 0);
            Shape[0] = Shapes.Sine;
            Shape[1] = Shapes.Sine;
            Shape[2] = Shapes.Sine;
        }

        public string[] GerAutomationParams()
        {
            return new string[] { "Tuning 1", "Pan 1", "Level 1", "Tuning 2", "Pan 2", "Level 2 ", "Tuning 3", "Pan 3", "Level 3", "Am Osc", "A", "D", "S", "R" };
        }

        public void Get(float[][] inp, float[][] stereo)
        {
            for (int i = 0; i < stereo[0].Length; i++)
            {
                stereo[0][i] = 0;
                stereo[1][i] = 0;
                for (int j = 0; j < Notes.Count; j++)
                {
                    float L=0, R=0;
                    //osc 1
                    switch (Shape[0])
                    {
                        case Shapes.Sine:
                            {
                                L += (float)(Math.Sin((2 * Math.PI * NoteLib.NoteLib.Shift(Notes[j].freq, ((d["Tuning 1"] * 48d) - 24d) + Notes[j].pitchbend) / sr) * count) * (1 + Math.Min(-1 * d["Pan 1"], 0)) * Notes[j].velocity / 128d * d["Level 1"]);
                                R += (float)(Math.Sin((2 * Math.PI * NoteLib.NoteLib.Shift(Notes[j].freq, ((d["Tuning 1"] * 48d) - 24d) + Notes[j].pitchbend) / sr) * count) * (1 + Math.Min(d["Pan 1"], 0)) * Notes[j].velocity / 128d * d["Level 1"]);
                                break;
                            }
                        case Shapes.Square:
                            {
                                L += (float)((Math.Sin((2 * Math.PI * NoteLib.NoteLib.Shift(Notes[j].freq, ((d["Tuning 1"] * 48d) - 24d) + Notes[j].pitchbend) / sr) * count) > 0d ? 1d : -1d) * (1 + Math.Min(-1 * d["Pan 1"], 0)) * Notes[j].velocity / 128d * d["Level 1"]);
                                R += (float)((Math.Sin((2 * Math.PI * NoteLib.NoteLib.Shift(Notes[j].freq, ((d["Tuning 1"] * 48d) - 24d) + Notes[j].pitchbend) / sr) * count) > 0d ? 1d : -1d) * (1 + Math.Min(d["Pan 1"], 0)) * Notes[j].velocity / 128d * d["Level 1"]);
                                break;
                            }
                        case Shapes.Saw:
                            {
                                double x = (NoteLib.NoteLib.Shift(Notes[j].freq, ((d["Tuning 1"] * 48d) - 24d) + Notes[j].pitchbend) / sr) * count;
                                L += (float)(((x - Math.Truncate(x)) * 2 - 1f) * (1 + Math.Min(-1 * d["Pan 1"], 0)) * Notes[j].velocity / 128d * d["Level 1"]);
                                R += (float)(((x - Math.Truncate(x)) * 2 - 1f) * (1 + Math.Min(d["Pan 1"], 0)) * Notes[j].velocity / 128d * d["Level 1"]);
                                break;
                            }
                        case Shapes.Triangle:
                            {
                                double x = (4 * NoteLib.NoteLib.Shift(Notes[j].freq, ((d["Tuning 1"] * 48d) - 24d) + Notes[j].pitchbend) / sr);
                                if (val >= 1) { neg = true; }
                                else if (val <= -1) { neg = false; }
                                if (neg) { x = -x; }
                                L += (float)(val * (1 + Math.Min(-1 * d["Pan 1"], 0)) * Notes[j].velocity / 128d * d["Level 1"]);
                                R += (float)(val * (1 + Math.Min(d["Pan 1"], 0)) * Notes[j].velocity / 128d * d["Level 1"]);
                                val += x;
                                break;
                            }
                        case Shapes.Noise:
                            {
                                L += (float)((r.NextDouble() * 2 - 1) * (1 + Math.Min(-1 * d["Pan 1"], 0)) * Notes[j].velocity / 128d * d["Level 1"]);
                                R += (float)((r.NextDouble() * 2 - 1) * (1 + Math.Min(d["Pan 1"], 0)) * Notes[j].velocity / 128d * d["Level 1"]);
                                break;
                            }
                    }
                    //osc 2
                    switch (Shape[1])
                    {
                        case Shapes.Sine:
                            {
                                L += (float)(Math.Sin((2 * Math.PI * NoteLib.NoteLib.Shift(Notes[j].freq, ((d["Tuning 2"] * 48d) - 24d) + Notes[j].pitchbend) / sr) * count) * (1 + Math.Min(-1 * d["Pan 2"], 0)) * Notes[j].velocity / 128d * d["Level 2"]);
                                R += (float)(Math.Sin((2 * Math.PI * NoteLib.NoteLib.Shift(Notes[j].freq, ((d["Tuning 2"] * 48d) - 24d) + Notes[j].pitchbend) / sr) * count) * (1 + Math.Min(d["Pan 2"], 0)) * Notes[j].velocity / 128d * d["Level 2"]);
                                break;
                            }
                        case Shapes.Square:
                            {
                                L += (float)((Math.Sin((2 * Math.PI * NoteLib.NoteLib.Shift(Notes[j].freq, ((d["Tuning 2"] * 48d) - 24d) + Notes[j].pitchbend) / sr) * count) > 0d ? 1d : -1d) * (1 + Math.Min(-1 * d["Pan 2"], 0)) * Notes[j].velocity / 128d * d["Level 2"]);
                                R += (float)((Math.Sin((2 * Math.PI * NoteLib.NoteLib.Shift(Notes[j].freq, ((d["Tuning 2"] * 48d) - 24d) + Notes[j].pitchbend) / sr) * count) > 0d ? 1d : -1d) * (1 + Math.Min(d["Pan 2"], 0)) * Notes[j].velocity / 128d * d["Level 2"]);
                                break;
                            }
                        case Shapes.Saw:
                            {
                                double x = (NoteLib.NoteLib.Shift(Notes[j].freq, ((d["Tuning 2"] * 48d) - 24d) + Notes[j].pitchbend) / sr) * count;
                                L += (float)(((x - Math.Truncate(x)) * 2 - 1f) * (1 + Math.Min(-1 * d["Pan 2"], 0)) * Notes[j].velocity / 128d * d["Level 2"]);
                                R += (float)(((x - Math.Truncate(x)) * 2 - 1f) * (1 + Math.Min(d["Pan 2"], 0)) * Notes[j].velocity / 128d * d["Level 2"]);
                                break;
                            }
                        case Shapes.Triangle:
                            {
                                double x = (4 * NoteLib.NoteLib.Shift(Notes[j].freq, ((d["Tuning 2"] * 48d) - 24d) + Notes[j].pitchbend) / sr);
                                if (val >= 1) { neg = true; }
                                else if (val <= -1) { neg = false; }
                                if (neg) { x = -x; }
                                L += (float)(val * (1 + Math.Min(-1 * d["Pan 2"], 0)) * Notes[j].velocity / 128d * d["Level 2"]);
                                R += (float)(val * (1 + Math.Min(d["Pan 2"], 0)) * Notes[j].velocity / 128d * d["Level 2"]);
                                val += x;
                                break;
                            }
                        case Shapes.Noise:
                            {
                                L += (float)((r.NextDouble() * 2 - 1) * (1 + Math.Min(-1 * d["Pan 2"], 0)) * Notes[j].velocity / 128d * d["Level 2"]);
                                R += (float)((r.NextDouble() * 2 - 1) * (1 + Math.Min(d["Pan 2"], 0)) * Notes[j].velocity / 128d * d["Level 2"]);
                                break;
                            }
                    }
                    //osc 3
                    if (d["Am Osc"] == 1)
                    {
                        switch (Shape[2])
                        {
                            case Shapes.Sine:
                                {
                                    L *= (float)(Math.Sin((2 * Math.PI * NoteLib.NoteLib.Shift(Notes[j].freq, ((d["Tuning 3"] * 48d) - 24d) + Notes[j].pitchbend) / sr) * count) * (1 + Math.Min(-1 * d["Pan 3"], 0)) * Notes[j].velocity / 128d * d["Level 3"]);
                                    R *= (float)(Math.Sin((2 * Math.PI * NoteLib.NoteLib.Shift(Notes[j].freq, ((d["Tuning 3"] * 48d) - 24d) + Notes[j].pitchbend) / sr) * count) * (1 + Math.Min(d["Pan 3"], 0)) * Notes[j].velocity / 128d * d["Level 3"]);
                                    break;
                                }
                            case Shapes.Square:
                                {
                                    L *= (float)((Math.Sin((2 * Math.PI * NoteLib.NoteLib.Shift(Notes[j].freq, ((d["Tuning 3"] * 48d) - 24d) + Notes[j].pitchbend) / sr) * count) > 0d ? 1d : -1d) * (1 + Math.Min(-1 * d["Pan 3"], 0)) * Notes[j].velocity / 128d * d["Level 3"]);
                                    R *= (float)((Math.Sin((2 * Math.PI * NoteLib.NoteLib.Shift(Notes[j].freq, ((d["Tuning 3"] * 48d) - 24d) + Notes[j].pitchbend) / sr) * count) > 0d ? 1d : -1d) * (1 + Math.Min(d["Pan 3"], 0)) * Notes[j].velocity / 128d * d["Level 3"]);
                                    break;
                                }
                            case Shapes.Saw:
                                {
                                    double x = (NoteLib.NoteLib.Shift(Notes[j].freq, ((d["Tuning 3"] * 48d) - 24d) + Notes[j].pitchbend) / sr) * count;
                                    L *= (float)(((x - Math.Truncate(x)) * 2 - 1f) * (1 + Math.Min(-1 * d["Pan 3"], 0)) * Notes[j].velocity / 128d * d["Level 3"]);
                                    R *= (float)(((x - Math.Truncate(x)) * 2 - 1f) * (1 + Math.Min(d["Pan 3"], 0)) * Notes[j].velocity / 128d * d["Level 3"]);
                                    break;
                                }
                            case Shapes.Triangle:
                                {
                                    double x = (4 * NoteLib.NoteLib.Shift(Notes[j].freq, ((d["Tuning 3"] * 48d) - 24d) + Notes[j].pitchbend) / sr);
                                    if (val >= 1) { neg = true; }
                                    else if (val <= -1) { neg = false; }
                                    if (neg) { x = -x; }
                                    L *= (float)(val * (1 + Math.Min(-1 * d["Pan 3"], 0)) * Notes[j].velocity / 128d * d["Level 3"]);
                                    R *= (float)(val * (1 + Math.Min(d["Pan 3"], 0)) * Notes[j].velocity / 128d * d["Level 3"]);
                                    val += x;
                                    break;
                                }
                            case Shapes.Noise:
                                {
                                    L *= (float)((r.NextDouble() * 2 - 1) * (1 + Math.Min(-1 * d["Pan 3"], 0)) * Notes[j].velocity / 128d * d["Level 3"]);
                                    R *= (float)((r.NextDouble() * 2 - 1) * (1 + Math.Min(d["Pan 3"], 0)) * Notes[j].velocity / 128d * d["Level 3"]);
                                    break;
                                }
                        }
                    }
                    else
                    {
                        switch (Shape[2])
                        {
                            case Shapes.Sine:
                                {
                                    L += (float)(Math.Sin((2 * Math.PI * NoteLib.NoteLib.Shift(Notes[j].freq, ((d["Tuning 3"] * 48d) - 24d) + Notes[j].pitchbend) / sr) * count) * (1 + Math.Min(-1 * d["Pan 3"], 0)) * Notes[j].velocity / 128d * d["Level 3"]);
                                    R += (float)(Math.Sin((2 * Math.PI * NoteLib.NoteLib.Shift(Notes[j].freq, ((d["Tuning 3"] * 48d) - 24d) + Notes[j].pitchbend) / sr) * count) * (1 + Math.Min(d["Pan 3"], 0)) * Notes[j].velocity / 128d * d["Level 3"]);
                                    break;
                                }
                            case Shapes.Square:
                                {
                                    L += (float)((Math.Sin((2 * Math.PI * NoteLib.NoteLib.Shift(Notes[j].freq, ((d["Tuning 3"] * 48d) - 24d) + Notes[j].pitchbend) / sr) * count) > 0d ? 1d : -1d) * (1 + Math.Min(-1 * d["Pan 3"], 0)) * Notes[j].velocity / 128d * d["Level 3"]);
                                    R += (float)((Math.Sin((2 * Math.PI * NoteLib.NoteLib.Shift(Notes[j].freq, ((d["Tuning 3"] * 48d) - 24d) + Notes[j].pitchbend) / sr) * count) > 0d ? 1d : -1d) * (1 + Math.Min(d["Pan 3"], 0)) * Notes[j].velocity / 128d * d["Level 3"]);
                                    break;
                                }
                            case Shapes.Saw:
                                {
                                    double x = (NoteLib.NoteLib.Shift(Notes[j].freq, ((d["Tuning 3"] * 48d) - 24d) + Notes[j].pitchbend) / sr) * count;
                                    L += (float)(((x - Math.Truncate(x)) * 2 - 1f) * (1 + Math.Min(-1 * d["Pan 3"], 0)) * Notes[j].velocity / 128d * d["Level 3"]);
                                    R += (float)(((x - Math.Truncate(x)) * 2 - 1f) * (1 + Math.Min(d["Pan 3"], 0)) * Notes[j].velocity / 128d * d["Level 3"]);
                                    break;
                                }
                            case Shapes.Triangle:
                                {
                                    double x = (4 * NoteLib.NoteLib.Shift(Notes[j].freq, ((d["Tuning 3"] * 48d) - 24d) + Notes[j].pitchbend) / sr);
                                    if (val >= 1) { neg = true; }
                                    else if (val <= -1) { neg = false; }
                                    if (neg) { x = -x; }
                                    L += (float)(val * (1 + Math.Min(-1 * d["Pan 3"], 0)) * Notes[j].velocity / 128d * d["Level 3"]);
                                    R += (float)(val * (1 + Math.Min(d["Pan 3"], 0)) * Notes[j].velocity / 128d * d["Level 3"]);
                                    val += x;
                                    break;
                                }
                            case Shapes.Noise:
                                {
                                    L += (float)((r.NextDouble() * 2 - 1) * (1 + Math.Min(-1 * d["Pan 3"], 0)) * Notes[j].velocity / 128d * d["Level 3"]);
                                    R += (float)((r.NextDouble() * 2 - 1) * (1 + Math.Min(d["Pan 3"], 0)) * Notes[j].velocity / 128d * d["Level 3"]);
                                    break;
                                }
                        }
                    }
                    //adsr
                    L *= (float)(
                        Notes[j].on == true ?
                        (count - Notes[j].ts) < d["A"] ?
                        (1d / d["A"]) * (count - Notes[j].ts) :
                        (count - Notes[j].ts) < d["A"] + d["D"] ?
                        1 - ((1 - d["S"]) / d["D"]) * (count - d["A"] - Notes[j].ts) :
                        d["S"] :
                        Notes[j].ev - (Notes[j].ev / d["R"]) * (count - Notes[j].tsr));
                    R *= (float)(
                        Notes[j].on == true ?
                        (count - Notes[j].ts) < d["A"] ?
                        (1d / d["A"]) * (count - Notes[j].ts) :
                        (count - Notes[j].ts) < d["A"] + d["D"] ?
                        1 - ((1 - d["S"]) / d["D"]) * (count - d["A"] - Notes[j].ts) :
                        d["S"] :
                        Notes[j].ev - (Notes[j].ev / d["R"]) * (count - Notes[j].tsr));

                    stereo[0][i] += L;
                    stereo[1][i] += R;
                    if (count - Notes[j].tsr > d["R"] && !Notes[j].on)
                    {
                        Notes.Remove(Notes[j]);
                    }
                }
                count++;
            }
        }

        public double GetAutomation(string name)
        {
            return d[name];
        }

        public PluginInfo GetPluginInfo()
        {
            return new PluginInfo(PluginType.Instrument, "3x Osc", "1.0");
        }

        public void SetAutomation(string name, double value)
        {
            d[name] = value;
            SendAll();
        }

        public void SetAutomation(string name, double value, bool v3)
        {
            d[name] = value;
        }

        public void SetShape(int i, Shapes s)
        {
            Shape[i] = s;
        }

        public void SetNote(Note note)
        {
            Notes.Add(new MyNote(note.freq, note.velocity, note.aftertouch, note.pitchbend, count));
        }

        public void SetParams(Note note)
        {
            MyNote n = Notes.Find(x => x.freq == note.freq && x.velocity != 0);
            n.aftertouch = note.aftertouch;
            n.pitchbend = note.pitchbend;
            if (note.velocity == 0) { n.tsr = count; n.on = false;
                n.ev = (float)((count - n.ts) < d["A"] ?
                (1d / d["A"]) * (count - n.ts) :
                (count - n.ts) < d["A"] + d["D"] ?
                1 - ((1 - d["S"]) / d["D"]) * (count - d["A"] - n.ts) :
                d["S"]);
            }
            else { n.velocity = note.velocity; }
        }

        public void ShowUI()
        {
            SendAll();
            ui.Show();
        }

        private void SendAll()
        {
            ui.Send("Tuning 1", d["Tuning 1"]);
            ui.Send("Tuning 2", d["Tuning 2"]);
            ui.Send("Tuning 3", d["Tuning 3"]);
            ui.Send("Pan 1", d["Pan 1"]);
            ui.Send("Pan 2", d["Pan 2"]);
            ui.Send("Pan 3", d["Pan 3"]);
            ui.Send("Level 1", d["Level 1"]);
            ui.Send("Level 2", d["Level 2"]);
            ui.Send("Level 3", d["Level 3"]);
            ui.Send("A", d["A"]);
            ui.Send("D", d["D"]);
            ui.Send("S", d["S"]);
            ui.Send("R", d["R"]);
            ui.Send("Am Osc", d["Am Osc"]);
        }
    }
}
