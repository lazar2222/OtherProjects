using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace PluginBase
{
    public interface IPlugin
    {
        Dictionary<string, FunctionBox> GetFunctions();
        bool Selftest();
        string GetPluginName();
        void Init();
        void Close();
    }

    public class FunctionBox
    {
        public delegate void Function(byte chan, int val,List<object> par);
        public Function function;
        public CType functionType;
        public IDialogForm dialogForm;

        public FunctionBox(Function f, CType fType, IDialogForm df)
        {
            function = f;
            functionType = fType;
            dialogForm = df;
        }

        public List<object> aditionalArgs(List <object> start)
        {
            return dialogForm.go(start);
        }
    }

    public enum CType
    {
        Analog = 0,
        Button = 1,
        RGBButton = 2,
        Encoder = 3,
        LCD = 4,
        JoyStick = 5,
        RGBLED = 6
    }

    public interface IDialogForm
    {
        List<object> go(List<object> start);
    }
}
