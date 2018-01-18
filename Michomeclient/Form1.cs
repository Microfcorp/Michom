using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Newtonsoft.Json.Linq;
using michomeframework;

namespace Michomeclient
{
    public partial class Form1 : Form
    {
        Gateway gtw = new Gateway();

        public Form1()
        {
            InitializeComponent();         
            gtw.Connect("192.168.1.42");
            int col = 0;
            comboBox2.Items.AddRange(gtw.Getdeviceip());

            string[] Getdeviceip = gtw.Getdeviceip();
            string[] Getdevicename = gtw.Getdevicename();
            string[] Getdevicetype = gtw.Getdevicetype();

            foreach (string tmp in Getdeviceip)
            {
                ToolStripMenuItem tr = new ToolStripMenuItem();
                tr.Text = tmp + " (" + Getdevicename[col] + ") (" + Getdevicetype[col] + ")";
                tr.Enabled = false;
                списокМодулейToolStripMenuItem.DropDownItems.Add(tr);
                col++;
            }
            pictureBox3.Image = gtw.Getimage("temp");
            pictureBox2.Image = gtw.Getimage("humm");
            pictureBox1.Image = gtw.Getimage("dawlen");

            JObject obj = JObject.Parse(gtw.Getdata("192.168.1.35", "temper"));
            JObject obj1 = JObject.Parse(gtw.Getdata("192.168.1.35", "humm"));
            JObject obj2 = JObject.Parse(gtw.Getdata("192.168.1.35", "dawlen"));

            col = 0;
            foreach (string tmp in Getdeviceip)
            {
                if (Getdevicetype[col] == "msinfoo")
                {
                    label13.Text += "\n" + tmp + " (" + Getdevicename[col] + ") (" + Getdevicetype[col] + ")";
                    col++;
                }
            }

            label9.Text = "Последний раз данные обновлялись " + obj1["date"][(Int32)obj["col"]].ToString();
            label10.Text = obj["data"][(Int32)obj["col"]].ToString();
            label11.Text = obj1["data"][(Int32)obj["col"]].ToString();
            label12.Text = obj2["data"][(Int32)obj["col"]].ToString();
            timer1.Start();
        }

        private void открытьКонсольToolStripMenuItem_Click(object sender, EventArgs e)
        {
            panel1.Visible = !panel1.Visible;
        }

        private void button1_Click(object sender, EventArgs e)
        {
           label4.Text = gtw.Setdata(comboBox2.Text, comboBox1.Text);
        }

        private void обновитьСписокМодулейToolStripMenuItem_Click(object sender, EventArgs e)
        {
            int col = 0;
            comboBox2.Items.AddRange(gtw.Getdeviceip());
            foreach (string tmp in gtw.Getdeviceip())
            {
                ToolStripMenuItem tr = new ToolStripMenuItem();
                tr.Text = tmp + " (" + gtw.Getdevicename()[col] + ")";
                tr.Enabled = false;
                списокМодулейToolStripMenuItem.DropDownItems.Add(tr);
                col++;
            }
        }

        private void сбораИнформацииToolStripMenuItem_Click(object sender, EventArgs e)
        {
            panel1.Visible = false;
            panel2.Visible = true;

            pictureBox3.Image = gtw.Getimage("temp");
            pictureBox2.Image = gtw.Getimage("humm");
            pictureBox1.Image = gtw.Getimage("dawlen");

            JObject obj = JObject.Parse(gtw.Getdata("192.168.1.35", "temper"));
            JObject obj1 = JObject.Parse(gtw.Getdata("192.168.1.35", "humm"));
            JObject obj2 = JObject.Parse(gtw.Getdata("192.168.1.35", "dawlen"));

            label9.Text = "Данные обновлялись в " + obj1["date"][(Int32)obj["col"]].ToString();
            label10.Text = obj["data"][(Int32)obj["col"]].ToString();
            label11.Text = obj1["data"][(Int32)obj["col"]].ToString();
            label12.Text = obj2["data"][(Int32)obj["col"]].ToString();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            timer1.Stop();
            string[] Getdeviceip = gtw.Getdeviceip();
            string[] Getdevicename = gtw.Getdevicename();
            string[] Getdevicetype = gtw.Getdevicetype();

            pictureBox3.Image = gtw.Getimage("temp");
            pictureBox2.Image = gtw.Getimage("humm");
            pictureBox1.Image = gtw.Getimage("dawlen");

            JObject obj = JObject.Parse(gtw.Getdata("192.168.1.35", "temper"));
            JObject obj1 = JObject.Parse(gtw.Getdata("192.168.1.35", "humm"));
            JObject obj2 = JObject.Parse(gtw.Getdata("192.168.1.35", "dawlen"));
            var col = 0;
            foreach (string tmp in Getdeviceip)
            {
                if (Getdevicetype[col] == "msinfoo")
                {
                    label13.Text += "\n" + tmp + " (" + Getdevicename[col] + ") (" + Getdevicetype[col] + ")";
                    col++;
                }
            }

            label9.Text = "Последний раз данные обновлялись " + obj1["date"][(Int32)obj["col"]].ToString();
            label10.Text = obj["data"][(Int32)obj["col"]].ToString();
            label11.Text = obj1["data"][(Int32)obj["col"]].ToString();
            label12.Text = obj2["data"][(Int32)obj["col"]].ToString();
            timer1.Start();
        }
    }
}
