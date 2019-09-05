using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace IRManager.IR
{
    interface IIR
    {
        Rectangle[] Points
        {
            get;
            set;
        }

        string[] KeyKode
        {
            get;
            set;
        }

        string Name
        {
            get;
        }
        string[] KeyName
        {
            get;
            set;
        }

        string ModuleIP
        {
            get;
        }

        Image Image
        {
            get;
        }

        void Init();
        int PressID(Point p);
        void PrintRect(PictureBox pb);
        string PressCode(Point p);
    }
}
