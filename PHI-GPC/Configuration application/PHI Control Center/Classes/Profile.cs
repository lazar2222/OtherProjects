using PluginBase;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static PHI_Control_Center.Classes.Control;

namespace PHI_Control_Center.Classes
{
    public class Profile
    {
        public Dictionary<int,ConnectedDevice> ConnectedDevices;
        public Dictionary<string, object> PluginStates;

        public Profile()
        {
            ConnectedDevices = new Dictionary<int, ConnectedDevice>();
            PluginStates = new Dictionary<string, object>();
        }
    }

    public class ConnectedDevice
    {
        public string COMPort;
        public byte DeviceId;
        public Dictionary<CType,Dictionary<int,ProfileControl>> Controlls;
        public Dictionary<string, string> ActivePage;

        public ConnectedDevice()
        {
            COMPort = null;
            Controlls = new Dictionary<CType, Dictionary<int,ProfileControl>>();
            ActivePage = new Dictionary<string, string>();
        }
    }
    public class ProfileControl
    {
        public string BankName;
        public Dictionary<string, Mapping> Mappings;

        public ProfileControl()
        {
            Mappings = new Dictionary<string, Mapping>();
        }
    }

    public class Mapping
    {
        public string PluginName;
        public string FunctionName;
        public List<object> args;

        public Mapping()
        {
            args = new List<object>();
        }

        public Mapping(string plug,string fun,List<object> ar)
        {
            args = ar;
            PluginName = plug;
            FunctionName = fun;
        }
    }
}
