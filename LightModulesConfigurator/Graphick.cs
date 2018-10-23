using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace LightModulesConfigurator
{
    public struct Graphic
    {
        public static void DrawBackgroung(Graphics g, Panel panel1)
        {
            Image img = Properties.Resources.Безымянный;
            g.Clear(Color.Gray);
            g.DrawImage(img, new Rectangle(new Point(0, 0), panel1.Size));
        }
        public static void SetLight(Graphics g, int BR, int pin)
        {
            Image img = Properties.Resources.Light;
            if(pin == 0)
            {
                g.DrawImage(img, new RectangleF((float)(481), (float)(329), (float)(~BR*0.041055), (float)(~BR*0.034213)));
            }
            else if(pin == 1)
            {
                g.DrawImage(img, new RectangleF((float)(32), (float)(326), (float)(~BR * 0.041055), (float)(~BR * 0.034213)));
            }
            else
            {
                g.DrawImage(img, new RectangleF((float)(163), (float)(35), (float)(~BR * 0.041055), (float)(~BR * 0.034213)));
            }        
        }
        public static void Strobo(Graphics g, float delay, int pin, int col, Panel panel1)
        {
            Image img = Properties.Resources.Light;
            for (int i = 0; i < col; i++)
            {
                if (pin == 0)
                {
                    g.DrawImage(img, new RectangleF((float)(481), (float)(329), (float)(~1023 * 0.041055), (float)(~1023 * 0.034213)));

                }
                else if (pin == 1)
                {
                    g.DrawImage(img, new RectangleF((float)(32), (float)(326), (float)(~1023 * 0.041055), (float)(~1023 * 0.034213)));
                }
                else
                {
                    g.DrawImage(img, new RectangleF((float)(163), (float)(35), (float)(~1023 * 0.041055), (float)(~1023 * 0.034213)));                  
                }
                System.Threading.Thread.Sleep((int)(delay / 1000));
                DrawBackgroung(g, panel1);
                System.Threading.Thread.Sleep((int)(delay / 1000));
            }
        }
    }
}
