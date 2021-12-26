using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using PluginBase;
using TobiasErichsen.teVirtualMIDI;

namespace MidiPlugin
{
    public class MidiPlugin : IPlugin
    {
        public const byte CONTROL_CHANGE = 0xB0;
        public const byte SET_LED = (byte)'L';

        public Dictionary<String, FunctionBox> Functions;
        TeVirtualMIDI MidiPort;
        bool init = false;
        dialogForm df;
        Dictionary<byte, bool>states;

        public Dictionary<string, FunctionBox> GetFunctions()
        {
            return Functions;
        }

        public MidiPlugin()
        {
            df = new dialogForm();
            Functions = new Dictionary<string, FunctionBox>
            {
                { "MidiCCAnalog", new FunctionBox(MidiCCAnalog, CType.Analog, df) },
                { "MidiCCMomentaryButton", new FunctionBox(MidiCCMomentaryButton, CType.Button, df) },
                { "MidiCCToggleButton", new FunctionBox(MidiCCToggleButton, CType.Button, df) }
            };
        }

        public void MidiCCAnalog(byte chan, int val, List<object> par)
        {
            if (init)
            {
                MidiPort.sendCommand(new byte[] { (byte)(CONTROL_CHANGE + Convert.ToByte(par[1])), Convert.ToByte(par[0]), (byte)(val / 8) });
            }
        }

        public void MidiCCMomentaryButton(byte chan, int val, List<object> par)
        {
            if (init)
            {
                MidiPort.sendCommand(new byte[] { (byte)(CONTROL_CHANGE + Convert.ToByte(par[1])), Convert.ToByte(par[0]), (byte)(val * 127) });
            }
        }

        public void MidiCCToggleButton(byte chan, int val, List<object> par)
        {
            if (val == 1)
            {
                if (!states.ContainsKey(chan)) { states.Add(chan, false); }
                states[chan] = !states[chan];
                if (init)
                {
                    MidiPort.sendCommand(new byte[] { (byte)(CONTROL_CHANGE + Convert.ToByte(par[1])), Convert.ToByte(par[0]), (byte)(states[chan] ? 127 : 0) });
                }
            }
            
        }

        public bool Selftest()
        {
            try
            {
                TeVirtualMIDI vm = new TeVirtualMIDI("PHI CC");
                vm.shutdown();
                return true;
            }
            catch
            {
                return false;
            }
        }

        public string GetPluginName()
        {
            return "MidiPlugin";
        }

        public void Init()
        {
            MidiPort = new TeVirtualMIDI("PHI CC");
            states = new Dictionary<byte, bool>();
            init = true;
        }

        public void Close()
        {
            MidiPort.shutdown();
        }
    }
}
