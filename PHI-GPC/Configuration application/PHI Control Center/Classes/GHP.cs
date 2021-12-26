using PHI_Control_Center.RTP;
using PluginBase;
using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace PHI_Control_Center.Classes
{
    public class GHP
    {
        public const byte ANALOG_CHANGE = (byte)'A';
        public const byte BUTTON_PRESS = (byte)'B';
        public const byte BUTTON_RELEASE = (byte)'R';
        public const byte ENCODER_INCREMENT = (byte)'I';
        public const byte ENCODER_DECREMENT = (byte)'D';
        public const byte RESPONCE_PERSISTENT = (byte)'r';
        public const byte RESPONCE_DISOVER = (byte)'w';
        public const byte SYSTEM = (byte)'S';
        public const byte SYSTEM_DISCOVER = (byte)'W';
        public const byte SYSTEM_RESET = (byte)'R';
        public const byte SET_LED = (byte)'L';
        public const byte SET_LCD = (byte)'l';
        public const byte SET_PERISTENT = (byte)'P';
        public const byte GET_PERISTENT = (byte)'p';

        public SerialPort port;
        public ConnectedDevice device;
        public Dictionary<string, IPlugin> plugins;
        public byte[] MsgBuffer;

        public static byte DeviceConnectedToPort(string com)
        {
            SerialPort tmp = new SerialPort();
            tmp.BaudRate = 115200;
            tmp.PortName = com;
            tmp.ReadTimeout = 500;
            tmp.Open();
            tmp.DiscardInBuffer();
            tmp.Write(new byte[] { SYSTEM, SYSTEM_DISCOVER }, 0, 2);
            try
            {
                int Bc = 0;
                while (tmp.ReadByte() != RESPONCE_DISOVER && Bc<75) { Bc++; }
                if (Bc == 75)
                {
                    tmp.Close();
                    return 0;
                }
                byte res = (byte)tmp.ReadByte();
                tmp.Close();
                return res;
            }
            catch
            {
                tmp.Close();
                return 0;
            }
        }

        public static string DevicePort(byte ID)
        {
            foreach (string com in SerialPort.GetPortNames())
            {
                if (DeviceConnectedToPort(com) == ID) { return com; }
            }
            return "";
        }

        public static bool AddonEnabled(byte ID, byte AddonAddres)
        {
            string port = DevicePort(ID);
            if (port == "") { return false; }
            return GetPeristent(port, AddonAddres) == 1;
        }

        public static byte GetPeristent(string port, byte addres)
        {
            SerialPort tmp = new SerialPort();
            tmp.BaudRate = 115200;
            tmp.PortName = port;
            tmp.Open();
            tmp.DiscardInBuffer();
            tmp.Write(new byte[] { GET_PERISTENT, addres }, 0, 2);
            try
            {
                int Bc = 0;
                while (tmp.ReadByte() != RESPONCE_PERSISTENT && Bc < 75) { Bc++; }
                if (Bc == 75)
                {
                    tmp.Close();
                    return 0;
                }
                tmp.ReadByte();
                byte res = (byte)tmp.ReadByte();
                tmp.Close();
                return res;
            }
            catch
            {
                tmp.Close();
                return 0;
            }
        }

        public static void SetPeristent(string port, byte addres,byte value)
        {
            SerialPort tmp = new SerialPort();
            tmp.BaudRate = 115200;
            tmp.PortName = port;
            tmp.Open();
            tmp.DiscardInBuffer();
            tmp.Write(new byte[] { SET_PERISTENT, addres,value }, 0, 3);
            tmp.Close();
        }

        public GHP(string com,ConnectedDevice d,Dictionary<string,IPlugin> pl)
        {
            device = d;
            plugins = pl;
            port = new SerialPort();
            port.BaudRate = 115200;
            port.PortName = com;
            port.Open();
            MsgBuffer = new byte[25];
        }

        public void SendMessage(params byte[] bytes)
        {
            port.Write(bytes, 0, bytes.Length);
        }

        public void read()
        {
            if (port.BytesToRead > 0)
            {
                MsgBuffer[0] = blockingRead();
                switch (MsgBuffer[0])
                {
                    case ANALOG_CHANGE: { ParseA(); break; }
                    case BUTTON_PRESS: { ParseB(); break; }
                    case BUTTON_RELEASE: { ParseR(); break; }
                    case ENCODER_INCREMENT: { ParseI(); break; }
                    case ENCODER_DECREMENT: { ParseD(); break; }
                    case SYSTEM: { ParseS(); break; }
                    default: { break; }
                }
            }
        }

        public void ParseS()
        {
            blockingRead(MsgBuffer, 1, 1);
            switch (MsgBuffer[1])
            {
                case SYSTEM_RESET: { RTPthread.Stop(true); break; }
                default: { break; }
            }
        }

        public void ParseD()
        {
            blockingRead(MsgBuffer, 1, 1);
            ExecuteMapping(GetMapping(CType.Encoder, MsgBuffer[1]), MsgBuffer[1], 0);
        }

        public void ParseI()
        {
            blockingRead(MsgBuffer, 1, 1);
            ExecuteMapping(GetMapping(CType.Encoder, MsgBuffer[1]), MsgBuffer[1], 1);
        }

        private void ParseR()
        {
            blockingRead(MsgBuffer, 1, 1);
            ExecuteMapping(GetMapping(CType.Button, MsgBuffer[1]), MsgBuffer[1], 0);
        }

        public void ParseB()
        {
            blockingRead(MsgBuffer, 1, 1);
            ExecuteMapping(GetMapping(CType.Button, MsgBuffer[1]), MsgBuffer[1], 1);
        }

        public void ParseA()
        {
            blockingRead(MsgBuffer, 1, 3);
            int val = MsgBuffer[2] + (MsgBuffer[3]<<8);
            ExecuteMapping(GetMapping(CType.Analog, MsgBuffer[1]),MsgBuffer[1],val);
        }

        public byte blockingRead()
        {
            while (port.BytesToRead < 1) { }
            return (byte)port.ReadByte();

        }

        public void blockingRead(byte[] A, byte start, byte cnt)
        {
            for (byte i = start; i < cnt + start; i++)
            {
                A[i] = blockingRead();
            }

        }

        public Mapping GetMapping(CType type,byte id)
        {
            string bankname = device.Controlls[type][id].BankName;
            bankname = device.ActivePage[bankname];
            if (device.Controlls[type][id].Mappings.ContainsKey(bankname))
            {
                return device.Controlls[type][id].Mappings[bankname];
            }
            else
            {
                return null;
            }
        }

        private void ExecuteMapping(Mapping mapping,byte chan, int val)
        {
            if (mapping != null)
            {
                try
                {
                    plugins[mapping.PluginName].GetFunctions()[mapping.FunctionName].function(chan, val, mapping.args);
                }
                catch(Exception e)
                {
                    Console.WriteLine(e);
                }
            }
        }

        public void Close()
        {
            port.Close();
        }
    }
}
