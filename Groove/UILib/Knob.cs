using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace UILib
{
    public partial class Knob : UserControl
    {
        public Knob()
        {
            InitializeComponent();
            stringFormat.Alignment = StringAlignment.Center;
            stringFormat.LineAlignment = StringAlignment.Center;
        }
        public double min;
        public double max;
        public double val;
        public double inc;
        public double def;
        public bool lab;
        public string label;


        public event EventHandler ValChange;

        bool down;
        int x, y;
        double preval;

        StringFormat stringFormat = new StringFormat();

        private void Knob_MouseDown(object sender, MouseEventArgs e)
        {
            down = true;
            x = e.X;
            y = e.Y;
            preval = val;
        }

        private void Knob_MouseUp(object sender, MouseEventArgs e)
        {
            down = false;
        }

        private void Knob_MouseMove(object sender, MouseEventArgs e)
        {
            if (down)
            {
                val = preval + (((e.Y - y) / pix()) * inc);
                //val += e.Delta * inc*10;
                if (val > max) { val = max; }
                if (val < min) { val = min; }
                try
                {
                    ValChange(this, e);
                }
                catch { }
                Invalidate();

            }

        }

        private int step()
        {
            return (int)((max - min) / inc);
        }

        private void Knob_Paint(object sender, PaintEventArgs e)
        {
            if (lab)
            {
                e.Graphics.DrawString(val.ToString(), DefaultFont, Brushes.Black, new Point(Width / 2, Height - 20), stringFormat);
            }
            e.Graphics.DrawString(label, DefaultFont, Brushes.Black, new Point(Width / 2, Height - 10), stringFormat);
            e.Graphics.DrawArc(new Pen(Color.Black, 2), 5, 5, 65, 65, 120, 300);
            e.Graphics.DrawArc(new Pen(Color.Orange, 3), 5, 5, 65, 65, 120 + ((float)(ndef() / nmax()) * 300), 300 * (float)((nval() - ndef()) / nmax()));
            e.Graphics.DrawLine(new Pen(Color.Black, 2), 75 / 2, 75 / 2,
                75 / 2 - (30 * (float)Math.Cos((60-(300 * ((nval() - ndef()) / nmax()))) * Math.PI / 180)),
                75 / 2 + (30 * (float)Math.Sin((60-(300 * ((nval() - ndef()) / nmax()))) * Math.PI / 180))
                );


        }

        private int pix()
        {
            return Math.Max(200 / step(), 1);
        }

        private double nmin() { return 0; }
        private double nmax() { return max - min; }
        private double nval() { return val - min; }

        private void Knob_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            val = def;
            Invalidate();
        }

        private double ndef() { return def - min; }
    }
}
