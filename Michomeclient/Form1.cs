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

            UpdateModules();

            pictureBox4.Image = gtw.Getimage("tempul", gtw.TimeInsCurDay("192.168.1.11").Col, gtw.TimeInsCurDay("192.168.1.11").Min);
            pictureBox3.Image = gtw.Getimage("temp", gtw.TimeInsCurDay("192.168.1.10").Col, gtw.TimeInsCurDay("192.168.1.10").Min);
            pictureBox2.Image = gtw.Getimage("humm", gtw.TimeInsCurDay("192.168.1.10").Col, gtw.TimeInsCurDay("192.168.1.10").Min);
            pictureBox1.Image = gtw.Getimage("dawlen", gtw.TimeInsCurDay("192.168.1.10").Col, gtw.TimeInsCurDay("192.168.1.10").Min);

            JObject obj = JObject.Parse(gtw.Getdata("192.168.1.10", "temper"));
            JObject obj1 = JObject.Parse(gtw.Getdata("192.168.1.10", "humm"));
            JObject obj2 = JObject.Parse(gtw.Getdata("192.168.1.10", "dawlen"));
            JObject obj3 = JObject.Parse(gtw.Getdata("192.168.1.11", "tempertemp"));

            label9.Text = "Последний раз данные обновлялись " + obj1["date"][(Int32)obj1["col"]].ToString();
            label10.Text = obj["data"][(Int32)obj["col"]].ToString();
            label11.Text = obj1["data"][(Int32)obj1["col"]].ToString();
            label12.Text = obj2["data"][(Int32)obj2["col"]].ToString();
            label16.Text = obj3["data"][(Int32)obj3["col"]].ToString();
            timer1.Start();
        }

         private void UpdateModules()
         {
            NameAndID[] ids = gtw.GetDevice();
            foreach (var item in ids)
            {
                comboBox2.Items.Clear();
                comboBox2.Items.Add(item.IP);
                    ToolStripMenuItem tr = new ToolStripMenuItem();
                    tr.Text = item.IP + " (" + item.Name + ") (" + item.ID + ")";
                    tr.Enabled = false;
                    списокМодулейToolStripMenuItem.DropDownItems.Add(tr);

                if (item.ID == "msinfoo")
                {
                    label13.Text += "\n" + item.IP + " (" + item.Name + ") (" + item.ID + ")";
                }
                if (item.ID == "termometr")
                {
                    label17.Text += "\n" + item.IP + " (" + item.Name + ") (" + item.ID + ")";
                }
            }
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
            UpdateModules();
        }

        private void сбораИнформацииToolStripMenuItem_Click(object sender, EventArgs e)
        {
            panel1.Visible = false;
            panel3.Visible = false;
            panel2.Visible = true;
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            timer1.Stop();

            UpdateModules();

            pictureBox4.Image = gtw.Getimage("tempul", gtw.TimeInsCurDay("192.168.1.11").Col, gtw.TimeInsCurDay("192.168.1.11").Min);
            pictureBox3.Image = gtw.Getimage("temp", gtw.TimeInsCurDay("192.168.1.10").Col, gtw.TimeInsCurDay("192.168.1.10").Min);
            pictureBox2.Image = gtw.Getimage("humm", gtw.TimeInsCurDay("192.168.1.10").Col, gtw.TimeInsCurDay("192.168.1.10").Min);
            pictureBox1.Image = gtw.Getimage("dawlen", gtw.TimeInsCurDay("192.168.1.10").Col, gtw.TimeInsCurDay("192.168.1.10").Min);

            JObject obj = JObject.Parse(gtw.Getdata("192.168.1.10", "temper"));
            JObject obj1 = JObject.Parse(gtw.Getdata("192.168.1.10", "humm"));
            JObject obj2 = JObject.Parse(gtw.Getdata("192.168.1.10", "dawlen"));
            JObject obj3 = JObject.Parse(gtw.Getdata("192.168.1.11", "tempertemp"));

            label9.Text = "Последний раз данные обновлялись " + obj1["date"][(Int32)obj1["col"]].ToString();
            label10.Text = obj["data"][(Int32)obj["col"]].ToString();
            label11.Text = obj1["data"][(Int32)obj1["col"]].ToString();
            label12.Text = obj2["data"][(Int32)obj2["col"]].ToString();
            label16.Text = obj3["data"][(Int32)obj3["col"]].ToString();
            timer1.Start();
        }

        private void уличногоТермометраToolStripMenuItem_Click(object sender, EventArgs e)
        {
            panel1.Visible = false;
            panel3.Visible = true;
            panel2.Visible = false;
        }

        private void списокМодулейToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }
    }
}
