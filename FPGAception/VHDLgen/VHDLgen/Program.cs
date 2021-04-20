using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace VHDLgen
{
    class Program
    {
        static void Main(string[] args)
        {
            StreamWriter sw = new StreamWriter("../../../../Modules/FPGAprogram.vhd");
            StreamReader tA = new StreamReader("templateA.txt");
            StreamReader tB = new StreamReader("templateB.txt");
            StreamReader prog = new StreamReader("../../../../PROG.txt");

            sw.Write(tA.ReadToEnd());
            sw.Write('\n');
            int i = 0;
            while (!prog.EndOfStream) 
            {
                string line = prog.ReadLine();
                if (line != "0")
                {
                    string s = ("\tProg(" + i.ToString() + ")<=").PadRight(13)+"x\"" + line.PadLeft(2,'0') + "\";";
                    sw.WriteLine(s);
                }
                i++;
            }
            sw.Write(tB.ReadToEnd());

            prog.Close();
            tA.Close();
            tB.Close();
            sw.Close();
        }
    }
}
