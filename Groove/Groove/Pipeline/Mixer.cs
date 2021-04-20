using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using DipBase;
using NAudio.Wave.SampleProviders;
using Groove.Controls;

namespace Groove.Pipeline
{
    public class Mixer
    {
        public List<Channel> Channels;
        public List<Bus> Buses;
        public Master MasterC;
        public List<HardOut> HOuts;
        public List<HardInp> HInps;
        public Mixer()
        {
            Channels = new List<Channel>();
            Buses = new List<Bus>();
            HOuts = new List<HardOut>();
            HInps = new List<HardInp>();
            MasterC = new Master(512);

        }

        public void Mix(float[][] inp, float[][] ou, int bufsize, int channelcount)
        {
            for (int i = 0; i < Channels.Count; i++)
            {
                Channels[i].Process(inp, ou);
            }
            for (int i = 0; i < Buses.Count; i++)
            {
                Buses[i].Process(ou);
            }
            MasterC.Process(ou);
        }

        public void PopHOuts(Player p)
        {
            for (int i = 0; i < p.ASIO.DriverOutputChannelCount; i += 2)
            {
                HOuts.Add(new HardOut(p.ASIO.AsioOutputChannelName(i), i, i + 1));
            }
        }

        public void PopHInps(Player p)
        {
            for (int i = 0; i < p.ASIO.DriverInputChannelCount; i += 2)
            {
                HInps.Add(new HardInp(p.ASIO.AsioInputChannelName(i), i, i + 1));
            }
        }

        public abstract class BaseChannel
        {
            public String name;
            public float level;
            public bool mute;
            public bool preE;
            public bool preS;
            public Output Output;
            public AudioEffect[] Plugins;
            public bool[] plugine;
            public Track track;
            public float[] peaklvl;
        }

        public class Channel : BaseChannel
        {
            public float Pan;
            public Tuple<Bus, float>[] Sends;
            public Input Input;
            float[][] Stereo;
            float[][] Stereo2;

            public Channel(int bufsize, string name)
            {
                Sends = new Tuple<Bus, float>[10];
                Plugins = new AudioEffect[10];
                plugine = new bool[10];
                peaklvl = new float[2];
                Stereo = new float[2][];
                Stereo2 = new float[2][];
                for (int i = 0; i < 2; i++)
                {
                    Stereo[i] = new float[bufsize];
                    Stereo2[i] = new float[bufsize];
                }
                this.name = name;
                level = 1;
                mute = false;
                preE = true;
                preS = true;
                Pan = 0;
            }

            internal void Process(float[][] inp, float[][] ou)
            {
                if (Input != null) { Input.Get(inp, Stereo); }
                peaklvl[0] = -2;
                peaklvl[1] = -2;
                if (preE)
                {
                    for (int i = 0; i < 10; i++)
                    {
                        if (Plugins[i] != null && plugine[i] == true)
                        { Plugins[i].Get(Stereo); }
                    }
                }
                if (preS)
                {
                    for (int n = 0; n < 10; n++)
                    {
                        if (Sends[n] != null)
                        {
                            for (int i = 0; i < 2; i++)
                            {
                                for (int j = 0; j < Stereo[0].Length; j++)
                                {
                                    Stereo2[i][j] = Stereo[i][j] * Sends[n].Item2;
                                }
                            }
                            Sends[n].Item1.Set(Stereo2, ou);
                        }
                    }
                }
                for (int j = 0; j < Stereo[0].Length; j++)
                {
                    Stereo[0][j] *= level;
                    Stereo[1][j] *= level;
                    Stereo[0][j] *= 1 + Math.Min(-1 * Pan, 0);
                    Stereo[1][j] *= 1 + Math.Min(Pan, 0);
                }
                if (!preE)
                {
                    for (int i = 0; i < 10; i++)
                    {
                        if (Plugins[i] != null && plugine[i] == true)
                        { Plugins[i].Get(Stereo); }
                    }
                }
                if (!preS)
                {
                    for (int n = 0; n < 10; n++)
                    {
                        if (Sends[n] != null)
                        {
                            for (int i = 0; i < 2; i++)
                            {
                                for (int j = 0; j < Stereo[0].Length; j++)
                                {
                                    Stereo2[i][j] = Stereo[i][j] * Sends[n].Item2;
                                }
                            }
                            Sends[n].Item1.Set(Stereo2, ou);
                        }
                    }
                }
                if (mute)
                {
                    for (int i = 0; i < 2; i++)
                    {
                        for (int j = 0; j < Stereo[0].Length; j++)
                        {
                            Stereo[i][j] = 0;
                        }
                    }
                }
                for (int i = 0; i < Stereo[0].Length; i++)
                {
                    if (Math.Abs(Stereo[0][i]) > peaklvl[0]) { peaklvl[0] = Math.Abs(Stereo[0][i]); }
                    if (Math.Abs(Stereo[1][i]) > peaklvl[1]) { peaklvl[1] = Math.Abs(Stereo[1][i]); }
                }
                if (Output != null) { Output.Set(Stereo, ou); }

            }
        }

        public class Bus : BaseChannel, Output
        {
            public float Pan;
            public Tuple<Bus, float>[] Sends;
            float[][] Stereo;
            float[][] Stereo2;

            public Bus(int bufsize, string name)
            {
                Sends = new Tuple<Bus, float>[10];
                Plugins = new AudioEffect[10];
                plugine = new bool[10];
                Stereo = new float[2][];
                Stereo2 = new float[2][];
                peaklvl = new float[2];
                for (int i = 0; i < 2; i++)
                {
                    Stereo[i] = new float[bufsize];
                    Stereo2[i] = new float[bufsize];
                }
                this.name = name;
                level = 1;
                mute = false;
                preE = true;
                preS = true;
                Pan = 0;
            }

            public void Set(float[][] stereo, float[][] ou)
            {
                for (int i = 0; i < 2; i++)
                {
                    for (int j = 0; j < Stereo[0].Length; j++)
                    {
                        Stereo[i][j] += stereo[i][j];
                    }
                }
            }

            internal void Process(float[][] ou)
            {
                peaklvl[0] = -2;
                peaklvl[1] = -2;
                if (preE)
                {
                    for (int i = 0; i < 10; i++)
                    {
                        if (Plugins[i] != null && plugine[i] == true)
                        { Plugins[i].Get(Stereo); }
                    }
                }
                if (preS)
                {
                    for (int n = 0; n < 10; n++)
                    {
                        if (Sends[n] != null)
                        {
                            for (int i = 0; i < 2; i++)
                            {
                                for (int j = 0; j < Stereo[0].Length; j++)
                                {
                                    Stereo2[i][j] = Stereo[i][j] * Sends[n].Item2;
                                }
                            }
                            Sends[n].Item1.Set(Stereo2, ou);
                        }
                    }
                }
                for (int j = 0; j < Stereo[0].Length; j++)
                {
                    Stereo[0][j] *= level;
                    Stereo[1][j] *= level;
                    Stereo[0][j] *= 1 + Math.Min(-1 * Pan, 0);
                    Stereo[1][j] *= 1 + Math.Min(Pan, 0);
                }
                if (!preE)
                {
                    for (int i = 0; i < 10; i++)
                    {
                        if (Plugins[i] != null && plugine[i] == true)
                        { Plugins[i].Get(Stereo); }
                    }
                }
                if (!preS)
                {
                    for (int n = 0; n < 10; n++)
                    {
                        if (Sends[n] != null)
                        {
                            for (int i = 0; i < 2; i++)
                            {
                                for (int j = 0; j < Stereo[0].Length; j++)
                                {
                                    Stereo2[i][j] = Stereo[i][j] * Sends[n].Item2;
                                }
                            }
                            Sends[n].Item1.Set(Stereo2, ou);
                        }
                    }
                }
                if (mute)
                {
                    for (int i = 0; i < 2; i++)
                    {
                        for (int j = 0; j < Stereo[0].Length; j++)
                        {
                            Stereo[i][j] = 0;
                        }
                    }
                }
                for (int i = 0; i < Stereo[0].Length; i++)
                {
                    if (Math.Abs(Stereo[0][i]) > peaklvl[0]) { peaklvl[0] = Math.Abs(Stereo[0][i]); }
                    if (Math.Abs(Stereo[1][i]) > peaklvl[1]) { peaklvl[1] = Math.Abs(Stereo[1][i]); }
                }
                if (Output != null) { Output.Set(Stereo, ou); }
                for (int i = 0; i < 2; i++)
                {
                    for (int j = 0; j < Stereo[0].Length; j++)
                    {
                        Stereo[i][j] = 0;
                    }
                }
            }
        }

        public class Master : BaseChannel, Output
        {
            public float[][] Stereo;

            public bool ALIAS = true;

            public Master(int bufsize)
            {
                name = "Master";
                mute = false;
                level = 1;
                preE = true;
                preS = true;
                Plugins = new AudioEffect[10];
                plugine = new bool[10];
                Stereo = new float[2][];
                peaklvl = new float[2];
                for (int i = 0; i < 2; i++)
                {
                    Stereo[i] = new float[bufsize];
                }
            }

            public void Setup(Mixer m)
            {
                Output = m.HOuts[0];
            }

            public void Set(float[][] stereo, float[][] ou)
            {
                for (int i = 0; i < 2; i++)
                {
                    for (int j = 0; j < Stereo[0].Length; j++)
                    {
                        Stereo[i][j] += stereo[i][j];
                    }
                }
            }

            internal void Process(float[][] ou)
            {
                peaklvl[0] = -2;
                peaklvl[1] = -2;
                if (preE)
                {
                    for (int i = 0; i < 10; i++)
                    {
                        if (Plugins[i] != null && plugine[i] == true)
                        { Plugins[i].Get(Stereo); }
                    }
                }
                for (int i = 0; i < 2; i++)
                {
                    for (int j = 0; j < Stereo[0].Length; j++)
                    {
                        Stereo[i][j] *= level;
                    }
                }
                if (!preE)
                {
                    for (int i = 0; i < 10; i++)
                    {
                        if (Plugins[i] != null && plugine[i] == true)
                        { Plugins[i].Get(Stereo); }
                    }
                }
                if (mute)
                {
                    for (int i = 0; i < 2; i++)
                    {
                        for (int j = 0; j < Stereo[0].Length; j++)
                        {
                            Stereo[i][j] = 0;
                        }
                    }
                }
                for (int i = 0; i < Stereo[0].Length; i++)
                {
                    if (Math.Abs(Stereo[0][i]) > peaklvl[0]) { peaklvl[0] = Math.Abs(Stereo[0][i]); }
                    if (Math.Abs(Stereo[1][i]) > peaklvl[1]) { peaklvl[1] = Math.Abs(Stereo[1][i]); }
                }
                if (ALIAS)
                {
                    for (int i = 0; i < 2; i++)
                    {
                        for (int j = 1; j < Stereo[0].Length - 1; j++)
                        {
                            Stereo[i][j] = (Stereo[i][j - 1] + Stereo[i][j] + Stereo[i][j + 1]) / 3;
                        }

                        Stereo[i][0] = (Stereo[i][0] + Stereo[i][0] + Stereo[i][1]) / 3;
                        Stereo[i][Stereo[0].Length - 1] = (Stereo[i][Stereo[0].Length - 2] + Stereo[i][Stereo[0].Length - 1] + Stereo[i][Stereo[0].Length - 1]) / 3;
                    }
                }
                if (Output != null) { Output.Set(Stereo, ou); }
                for (int i = 0; i < 2; i++)
                {
                    for (int j = 0; j < Stereo[0].Length; j++)
                    {
                        Stereo[i][j] = 0;
                    }
                }
            }
        }

        public class HardOut : Output
        {
            public HardOut(String Name, int LI, int RI)
            {
                this.Name = Name;
                LeftIndex = LI;
                RightIndex = RI;
            }

            public String Name;
            public int LeftIndex;
            public int RightIndex;

            public void Set(float[][] stereo, float[][] ou)
            {
                for (int j = 0; j < stereo[0].Length; j++)
                {
                    ou[LeftIndex][j] = stereo[0][j];
                    ou[RightIndex][j] = stereo[1][j];
                }
            }
        }

        public class HardInp : Input
        {
            public HardInp(String Name, int LI, int RI)
            {
                this.Name = Name;
                LeftIndex = LI;
                RightIndex = RI;
            }
            public String Name;
            public int LeftIndex;
            public int RightIndex;

            public void Get(float[][] inp, float[][] stereo)
            {

                for (int j = 0; j < stereo[0].Length; j++)
                {
                    stereo[0][j] = inp[LeftIndex][j];
                    stereo[1][j] = inp[LeftIndex][j];
                }
            }

        }

    }

}
