using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using PHI_Control_Center.Classes;
using Newtonsoft.Json;

namespace PHI_Control_Center
{
    static class Program
    { 
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Configure configure = new Configure();
            Application.Run();
        }
    }
}
