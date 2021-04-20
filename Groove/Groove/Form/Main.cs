using DipBase;
using Groove.Controls;
using Groove.Pipeline;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace Groove
{
    public partial class Main : Form
    {
        public Main()
        {
            InitializeComponent();
        }

        public PianoRoll piano;
        public Mixer m;
        public List<Instrument> inst;
        public List<AudioEffect> eff;
        public List<Trackb> TB;
        public List<Track> TC;
        public int x = 3;
        Player p;
        bool[] arr = new bool[16];
        public int selectedINST = 0;
        int vel = 60;
        int octave = 4;


        private void Main_Load(object sender, EventArgs e)
        {
            inst = new List<Instrument>();
            eff = new List<AudioEffect>();
            TB = new List<Trackb>();
            TC = new List<Track>();
            piano = new PianoRoll(1, this);
            string s = AppDomain.CurrentDomain.BaseDirectory + @"\Plugins";
            if (!Directory.Exists(s))
            {
                Directory.CreateDirectory(s);
            }
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
                                dynamic c = Activator.CreateInstance(type, 48000);
                                PluginInfo p = c.GetPluginInfo();
                                if (p.type == PluginType.AudioEffect) { eff.Add(c); }
                                else { inst.Add(c); }
                            }
                            catch { Console.WriteLine(type + " Is not a plugn"); }
                        }

                    }
                    catch { Console.WriteLine(item + " Errored"); }
                }
            }
            timer1.Start();
            //signal chain
            m = new Mixer();
            p = new Player(m);
            p.SetDevice(0);
            p.SetFormat(48000, 16, 2);
            p.Init();
            m.PopHInps(p);
            m.PopHOuts(p);
            m.MasterC.Setup(m);
            selectedINST = 0;
            Trackm t = new Trackm(this, m.MasterC);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            p.ASIO.Play();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            p.ASIO.Stop();
        }

        private void Main_KeyDown(object sender, KeyEventArgs e)
        {

            switch (e.KeyCode)
            {
                case Keys.Z: { if (arr[0] != true) { octave--; if (octave < 0) { octave = 0; } } arr[0] = true; break; }
                case Keys.X: { if (arr[1] != true) { octave++; if (octave > 8) { octave = 8; } } arr[1] = true; break; }
                case Keys.V: { if (arr[2] != true) { vel += 10; if (vel > 127) { vel = 127; } } arr[2] = true; break; }
                case Keys.C: { if (arr[3] != true) { vel -= 10; if (vel < 1) { vel = 1; } } arr[3] = true; break; }
                case Keys.A: { if (arr[4] != true) { try { ((Instrument)m.Channels[selectedINST].Input).SetNote(new Note(NoteLib.NoteLib.LUT["C" + octave.ToString()], vel, 0, 0)); } catch { } } arr[4] = true; break; }
                case Keys.W: { if (arr[5] != true) { try { ((Instrument)m.Channels[selectedINST].Input).SetNote(new Note(NoteLib.NoteLib.LUT["C#" + octave.ToString()], vel, 0, 0)); } catch { } } arr[5] = true; break; }
                case Keys.S: { if (arr[6] != true) { try { ((Instrument)m.Channels[selectedINST].Input).SetNote(new Note(NoteLib.NoteLib.LUT["D" + octave.ToString()], vel, 0, 0)); } catch { } } arr[6] = true; break; }
                case Keys.E: { if (arr[7] != true) { try { ((Instrument)m.Channels[selectedINST].Input).SetNote(new Note(NoteLib.NoteLib.LUT["D#" + octave.ToString()], vel, 0, 0)); } catch { } } arr[7] = true; break; }
                case Keys.D: { if (arr[8] != true) { try { ((Instrument)m.Channels[selectedINST].Input).SetNote(new Note(NoteLib.NoteLib.LUT["E" + octave.ToString()], vel, 0, 0)); } catch { } } arr[8] = true; break; }
                case Keys.F: { if (arr[9] != true) { try { ((Instrument)m.Channels[selectedINST].Input).SetNote(new Note(NoteLib.NoteLib.LUT["F" + octave.ToString()], vel, 0, 0)); } catch { } } arr[9] = true; break; }
                case Keys.T: { if (arr[10] != true) { try { ((Instrument)m.Channels[selectedINST].Input).SetNote(new Note(NoteLib.NoteLib.LUT["F#" + octave.ToString()], vel, 0, 0)); } catch { } } arr[10] = true; break; }
                case Keys.G: { if (arr[11] != true) { try { ((Instrument)m.Channels[selectedINST].Input).SetNote(new Note(NoteLib.NoteLib.LUT["G" + octave.ToString()], vel, 0, 0)); } catch { } } arr[11] = true; break; }
                case Keys.Y: { if (arr[12] != true) { try { ((Instrument)m.Channels[selectedINST].Input).SetNote(new Note(NoteLib.NoteLib.LUT["G#" + octave.ToString()], vel, 0, 0)); } catch { } } arr[12] = true; break; }
                case Keys.H: { if (arr[13] != true) { try { ((Instrument)m.Channels[selectedINST].Input).SetNote(new Note(NoteLib.NoteLib.LUT["A" + octave.ToString()], vel, 0, 0)); } catch { } } arr[13] = true; break; }
                case Keys.U: { if (arr[14] != true) { try { ((Instrument)m.Channels[selectedINST].Input).SetNote(new Note(NoteLib.NoteLib.LUT["A#" + octave.ToString()], vel, 0, 0)); } catch { } } arr[14] = true; break; }
                case Keys.J: { if (arr[15] != true) { try { ((Instrument)m.Channels[selectedINST].Input).SetNote(new Note(NoteLib.NoteLib.LUT["B" + octave.ToString()], vel, 0, 0)); } catch { } } arr[15] = true; break; }
            }
        }

        private void Main_KeyUp(object sender, KeyEventArgs e)
        {

            switch (e.KeyCode)
            {
                case Keys.Z: { if (arr[0] != false) { } arr[0] = false; break; }
                case Keys.X: { if (arr[1] != false) { } arr[1] = false; break; }
                case Keys.C: { if (arr[2] != false) { } arr[2] = false; break; }
                case Keys.V: { if (arr[3] != false) { } arr[3] = false; break; }
                case Keys.A: { if (arr[4] != false) { try { ((Instrument)m.Channels[selectedINST].Input).SetParams(new Note(NoteLib.NoteLib.LUT["C" + octave.ToString()], 0, 0, 0)); } catch { } } arr[4] = false; break; }
                case Keys.W: { if (arr[5] != false) { try { ((Instrument)m.Channels[selectedINST].Input).SetParams(new Note(NoteLib.NoteLib.LUT["C#" + octave.ToString()], 0, 0, 0)); } catch { } } arr[5] = false; break; }
                case Keys.S: { if (arr[6] != false) { try { ((Instrument)m.Channels[selectedINST].Input).SetParams(new Note(NoteLib.NoteLib.LUT["D" + octave.ToString()], 0, 0, 0)); } catch { } } arr[6] = false; break; }
                case Keys.E: { if (arr[7] != false) { try { ((Instrument)m.Channels[selectedINST].Input).SetParams(new Note(NoteLib.NoteLib.LUT["D#" + octave.ToString()], 0, 0, 0)); } catch { } } arr[7] = false; break; }
                case Keys.D: { if (arr[8] != false) { try { ((Instrument)m.Channels[selectedINST].Input).SetParams(new Note(NoteLib.NoteLib.LUT["E" + octave.ToString()], 0, 0, 0)); } catch { } } arr[8] = false; break; }
                case Keys.F: { if (arr[9] != false) { try { ((Instrument)m.Channels[selectedINST].Input).SetParams(new Note(NoteLib.NoteLib.LUT["F" + octave.ToString()], 0, 0, 0)); } catch { } } arr[9] = false; break; }
                case Keys.T: { if (arr[10] != false) { try { ((Instrument)m.Channels[selectedINST].Input).SetParams(new Note(NoteLib.NoteLib.LUT["F#" + octave.ToString()], 0, 0, 0)); } catch { } } arr[10] = false; break; }
                case Keys.G: { if (arr[11] != false) { try { ((Instrument)m.Channels[selectedINST].Input).SetParams(new Note(NoteLib.NoteLib.LUT["G" + octave.ToString()], 0, 0, 0)); } catch { } } arr[11] = false; break; }
                case Keys.Y: { if (arr[12] != false) { try { ((Instrument)m.Channels[selectedINST].Input).SetParams(new Note(NoteLib.NoteLib.LUT["G#" + octave.ToString()], 0, 0, 0)); } catch { } } arr[12] = false; break; }
                case Keys.H: { if (arr[13] != false) { try { ((Instrument)m.Channels[selectedINST].Input).SetParams(new Note(NoteLib.NoteLib.LUT["A" + octave.ToString()], 0, 0, 0)); } catch { } } arr[13] = false; break; }
                case Keys.U: { if (arr[14] != false) { try { ((Instrument)m.Channels[selectedINST].Input).SetParams(new Note(NoteLib.NoteLib.LUT["A#" + octave.ToString()], 0, 0, 0)); } catch { } } arr[14] = false; break; }
                case Keys.J: { if (arr[15] != false) { try { ((Instrument)m.Channels[selectedINST].Input).SetParams(new Note(NoteLib.NoteLib.LUT["B" + octave.ToString()], 0, 0, 0)); } catch { } } arr[15] = false; break; }
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            Refresh();
        }

        private void addTrackToolStripMenuItem_Click(object sender, EventArgs e)
        {
            new Prompt(this, true);
            Reorder();

        }

        private void addBusToolStripMenuItem_Click(object sender, EventArgs e)
        {
            new Prompt(this, false);
            Reorder();
        }

        public void Reorder()
        {
            x = 133;
            for (int i = 0; i < TC.Count; i++)
            {
                TC[i].Location = new Point(x, 27);
                x += 130;
            }
            for (int i = 0; i < TB.Count; i++)
            {
                TB[i].Location = new Point(x, 27);
                x += 130;
            }
        }

        private void pianoRollToolStripMenuItem_Click(object sender, EventArgs e)
        {
            piano.Show();
        }

        private void tempoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            new Tempo(this);
        }

        private void pauseToolStripMenuItem_Click(object sender, EventArgs e)
        {
            piano.timer1.Stop();
            piano.Clean();
        }

        private void playToolStripMenuItem_Click(object sender, EventArgs e)
        {
            piano.timer1.Start();
        }

        private void stopToolStripMenuItem_Click(object sender, EventArgs e)
        {
            piano.timer1.Stop();
            piano.Clean();
            piano.php = 0;
            piano.trackBar1.Value = piano.php;
        }

        private void beginingToolStripMenuItem_Click(object sender, EventArgs e)
        {
            piano.php = 0;
            piano.trackBar1.Value = piano.php;
        }

        private void loopToolStripMenuItem_Click(object sender, EventArgs e)
        {
            piano.loop = !piano.loop;
            if (piano.loop) { loopToolStripMenuItem.BackColor = Color.Lime; }
            else { loopToolStripMenuItem.BackColor = SystemColors.ControlLight; }
        }
    }
}
