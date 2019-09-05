using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace IRManager.IR
{
    class RC58 : IIR
    {
        const int SizeX = 30;
        const int SizeY = 30;

        const int PoprX = 6;
        const int PoprY = 8;

        public string Name
        {
            get
            {
                return "RC58";
            }
        }

        public string ModuleIP
        {
            get
            {
                return "192.168.1.34";
            }
        }

        public Rectangle[] Points
        {
            get;
            set;
        }

        public string[] KeyKode
        {
            get;
            set;
        }

        public string[] KeyName
        {
            get;
            set;
        }

        public Image Image
        {
            get
            {
                return Properties.Resources.rc58;
            }
        }

        public void Init()
        {
            Points = new Rectangle[] {
                new Rectangle(45-PoprX, 64-PoprY, SizeX, SizeY),
                new Rectangle(105-PoprX, 63-PoprY, SizeX, SizeY),
                new Rectangle(165-PoprX, 63-PoprY, SizeX, SizeY),
                new Rectangle(226-PoprX, 63-PoprY, SizeX, SizeY),
                new Rectangle(46-PoprX, 121-PoprY, SizeX, SizeY),
                new Rectangle(106-PoprX, 123-PoprY, SizeX, SizeY),
                new Rectangle(166-PoprX, 122-PoprY, SizeX, SizeY),
                new Rectangle(228-PoprX, 123-PoprY, SizeX, SizeY),
                new Rectangle(228-PoprX, 178-PoprY, SizeX, SizeY),
                new Rectangle(167-PoprX, 180-PoprY, SizeX, SizeY),
                new Rectangle(105-PoprX, 181-PoprY, SizeX, SizeY),
                new Rectangle(45-PoprX, 181-PoprY, SizeX, SizeY),
                new Rectangle(43-PoprX, 240-PoprY, SizeX, SizeY),
                new Rectangle(106-PoprX, 239-PoprY, SizeX, SizeY),
                new Rectangle(165-PoprX, 238-PoprY, SizeX, SizeY),
                new Rectangle(228-PoprX, 238-PoprY, SizeX, SizeY),
                new Rectangle(45-PoprX, 297-PoprY, SizeX, SizeY),
            };

            KeyKode = new string[] {
                "1119703215",
                "1119719535",
                "1119717495",
                "1119684855",
                "1119707295",
                "1119735855",
                "1119733815",
                "1119701175",
                "1119739935",
                "1119727695",
                "1119731775",
                "1119699135",
                "1119690975",
                "1119723615",
                "1119686895",
                "1119709335",
                "1119682815"
            };

            KeyName = new string[] {
                "Включение",
                "Бас увеличить",
                "Требл увеличить",
                "Вход",
                "Без звука",
                "Бас уменьшить",
                "Требл уменьшить",
                "Режим",
                "Громче",
                "Саб увеличить",
                "Центр увеличить",
                "Задние увеличить",
                "Задние уменьшить",
                "Центр уменьшить",
                "Саб уменьшить",
                "Тише",
                "Сброс"
            };
        }
        public int PressID(Point p)
        {
            for (int i = 0; i < Points.Length; i++)
            {
                if (Points[i].Contains(p))
                    return i;
            }
            return -1;
        }

        public string PressCode(Point p)
        {
            for (int i = 0; i < Points.Length; i++)
            {
                if (Points[i].Contains(p))
                    return KeyKode[i];
            }
            return "";
        }

        public void PrintRect(PictureBox pb)
        {
            Graphics gr = pb.CreateGraphics();

            foreach (var item in Points)
            {
                gr.DrawRectangle(new Pen(Color.Red, 3f), item);
            }
            gr.Save();
        }
    }
}
