using PluginBase;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PHI_Control_Center.Classes
{
    public class Device : IComparable<Device>
    {
        public String Name;
        public byte DeviceId;
        public bool IsAddon;
        public byte AddonAddress;
        public List<Bank> Banks;
        public List<PersistentVariable> PersistentVariables;
        public List<Addon> Addons;

        public Device()
        {
            Banks = new List<Bank>();
            PersistentVariables = new List<PersistentVariable>();
            Addons = new List<Addon>();
        }

        public int CompareTo(Device b)
        {
            int compinta = DeviceId + (IsAddon ? 1 + AddonAddress : 0);
            int compintb = b.DeviceId + (b.IsAddon ? 1 + b.AddonAddress : 0);
            return compinta.CompareTo(compintb);
        }

        public override string ToString()
        {
            if (IsAddon) { return "    " + Name; }
            return Name;
        }

    }

    public class Bank
    {
        public String Name;
        public List<Control> Controls;

        public Bank()
        {
            Controls = new List<Control>();
        }
    }

    public class Control
    {
        public CType Type;
        public byte Id;

        public byte Lin;
        public byte Char;
        public byte Idl;
        public byte IdA1;
        public byte IdA2;
        public byte IdS;

        public int X;
        public int Y;
        public int W;
        public int H;

    }

    public class PersistentVariable
    {
        public string Name;
        public byte Id;
    }

    public class Addon
    {
        public string Name;
        public byte AddonAddress;

        public override string ToString()
        {
            return Name;
        }
    }
}
