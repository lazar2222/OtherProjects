using DipBase;
using Groove.Pipeline;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Groove
{
    public partial class PianoRoll : Form
    {
        public class PianoNote : DipBase.Note
        {
            public PianoNote(double f, int v, int a, double p, int s, int e,string n,int ri) : base(f, v, a, p)
            {
                end = e;
                start = s;
                this.n = n;
                r = ri;
            }

            public int end;
            public int start;
            public string n;
            public int r;
        }

        int cells;
        int bars;
        int row;
        int sc;
        int ec;
        Main m;
        List<PianoNote> temp;

        public Mixer.Channel target;
        public int BPM;
        public int php = 0;
        public bool loop;

        public Dictionary<Mixer.Channel, List<PianoNote>> Notes;


        public PianoRoll(int bars,Main m)
        {
            this.bars = bars;
            this.m = m;
            cells = bars * 4 * 16;
            BPM = 120;
            Notes = new Dictionary<Mixer.Channel, List<PianoNote>>();
            InitializeComponent();
            UpdateBPM();
        }

        internal void loadTrack()
        {
            dataGridView1.Rows.Clear();
            dataGridView2.Rows.Clear();
            dataGridView1.Columns.Clear();
            dataGridView2.Columns.Clear();
            if (!Notes.ContainsKey(target)) { Notes.Add(target, new List<PianoNote>()); }
            DataGridViewColumn c;
            for (int i = 0; i < cells; i++)
            {
                c = new DataGridViewTextBoxColumn();
                c.Width = 20;
                c.HeaderText = (Math.Truncate(i / 16d) + 1).ToString();
                dataGridView1.Columns.Add(c);
                c = new DataGridViewTextBoxColumn();
                c.Width = 20;
                dataGridView2.Columns.Add(c);
            }
            dataGridView2.Rows.Add();
            DataGridViewRow r;
            for (int i = 0; i < 108; i++)
            {
                r = new DataGridViewRow();
                r.HeaderCell.Value = NoteLib.NoteLib.LUT.ElementAt(i).Key.ToString();
                dataGridView1.Rows.Add(r);
            }
            trackBar1.Maximum = cells-1;
            for (int i = 0; i < Notes[target].Count; i++)
            {
                dataGridView1.Rows[Notes[target][i].r].Cells[Notes[target][i].start].Value = Notes[target][i].n + "*";
                for (int j = Notes[target][i].start+1; j <= Notes[target][i].end; j++)
                {
                    dataGridView1.Rows[Notes[target][i].r].Cells[j].Value = "*";
                }
            }
        }

        private void PianoRoll_Load(object sender, EventArgs e)
        {
            if (target == null) { new TrackF(m); }
        }

        private void dataGridView1_CellMouseUp(object sender, DataGridViewCellMouseEventArgs e)
        {
            ec = e.ColumnIndex;
            if (row >= 0 && sc >= 0 && ec >= sc)
            {
                if (dataGridView1.Rows[row].Cells[e.ColumnIndex].Value == null || dataGridView1.Rows[row].Cells[e.ColumnIndex].Value.ToString() == "")
                {
                    
                    Notes[target].Add(new PianoNote(NoteLib.NoteLib.LUT[dataGridView1.Rows[row].HeaderCell.Value.ToString()], 64, 0, 0, sc, ec, dataGridView1.Rows[row].HeaderCell.Value.ToString(), row));

                    dataGridView1.Rows[row].Cells[sc].Value = dataGridView1.Rows[row].HeaderCell.Value + "*";
                    for (int i = sc + 1; i <= ec; i++)
                    {
                        dataGridView1.Rows[row].Cells[i].Value = "*";
                    }

                }
                else
                {
                    PianoNote n = Notes[target].Find(x => x.freq == NoteLib.NoteLib.LUT[dataGridView1.Rows[row].HeaderCell.Value.ToString()] && x.start <= e.ColumnIndex && x.end >= e.ColumnIndex);
                    for (int i = n.start; i <= n.end; i++)
                    {
                        dataGridView1.Rows[row].Cells[i].Value = "";
                    }
                    Notes[target].Remove(n);
                }
            }

        }

        private void dataGridView1_CellMouseDown(object sender, DataGridViewCellMouseEventArgs e)
        {
            row = e.RowIndex;
            sc = e.ColumnIndex;
        }

        private void dataGridView2_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {

        }

        public void Clean()
        {
            foreach (var item in Notes)
            {
                int x = m.m.Channels.IndexOf(item.Key);
                temp = item.Value.FindAll(xyz => xyz.end >= php && xyz.start <= php);
                for (int i = 0; i < temp.Count; i++)
                {
                    try { ((Instrument)m.m.Channels[x].Input).SetParams(new Note(temp[i].freq, 0, temp[i].aftertouch, temp[i].pitchbend)); } catch { }
                }
                

            }
        }

        public void UpdateBPM()
        {
            BPMtoolStripMenuItem.Text = "BPM:" + BPM;
            timer1.Interval = (60000 / BPM) / 16;
        }

        public void trackToolStripMenuItem_Click(object sender, EventArgs e)
        {
            new TrackF(m);
        }

        private void PianoRoll_FormClosing(object sender, FormClosingEventArgs e)
        {
            Hide();
            e.Cancel = true;
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            foreach (var item in Notes)
            {
                int x = m.m.Channels.IndexOf(item.Key);
                temp = item.Value.FindAll(xyz => xyz.start == php);
                for (int i = 0; i < temp.Count; i++)
                {
                    try { ((Instrument)m.m.Channels[x].Input).SetNote(new Note(temp[i].freq, temp[i].velocity, temp[i].aftertouch, temp[i].pitchbend)); }catch{ }
                }
                temp = item.Value.FindAll(xyz => xyz.end == php);
                for (int i = 0; i < temp.Count; i++)
                {
                    try { ((Instrument)m.m.Channels[x].Input).SetParams(new Note(temp[i].freq,0, temp[i].aftertouch, temp[i].pitchbend)); } catch { }
                }
            }
            trackBar1.Value = php;
            php++;
            if (php == cells)
            {
                if (loop)
                {
                    php = 0;
                    trackBar1.Value = php;
                }
                else
                {
                    php = 0;
                    trackBar1.Value = php;
                    timer1.Stop();
                }
            }
        }

        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            php = trackBar1.Value;
        }
    }
}