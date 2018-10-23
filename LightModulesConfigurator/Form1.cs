using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using michomeframework;
using MicrofPlayer;

namespace LightModulesConfigurator
{
    public partial class Form1 : Form
    {
        public object[] paramss;
        public Sceene scenes = new Sceene();
        Gateway gtw = new Gateway("192.168.1.42");
        #if !MONO
            Player pl = new Player(new Point(389, 231));
        #endif

        public Form1()
        {
            InitializeComponent();
            paramss = new object[] { label3, label4, label5, label6, textBox1, trackBar1, trackBar2, trackBar3, label7, textBox2, checkBox1, label8, trackBar4 };
        }

        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            label4.Text = string.Format("Модуль освещения ({0})", trackBar1.Value);
        }

        private void trackBar2_Scroll(object sender, EventArgs e)
        {
            label5.Text = string.Format("Яркость ({0})", trackBar2.Value);
        }

        private void trackBar3_Scroll(object sender, EventArgs e)
        {
            label6.Text = string.Format("Время стробо (мс) ({0})", trackBar3.Value);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Steep tmp = new Steep();
            switch (namesc)
            {
                case "setlight":
                    Graphic.DrawBackgroung(panel1.CreateGraphics(), panel1);
                    Graphic.SetLight(panel1.CreateGraphics(), trackBar2.Value, trackBar1.Value);
                    break;
                case "strobo":
                    Graphic.DrawBackgroung(panel1.CreateGraphics(), panel1);
                    Graphic.Strobo(panel1.CreateGraphics(), Convert.ToSingle(trackBar3.Value), trackBar1.Value, trackBar4.Value, panel1);
                    break;
            }
            tmp.name = namesc;
            tmp.brightness = trackBar2.Value.ToString();
            tmp.col = trackBar4.Value.ToString();
            tmp.file = textBox2.Text;
            tmp.pin = trackBar1.Value.ToString();
            tmp.time = textBox1.Text;
            tmp.times = trackBar3.Value.ToString();
            tmp.waiting = checkBox1.Checked.ToString().ToLower();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Steep tmp = new Steep();
            tmp.name = namesc;
            tmp.brightness = trackBar2.Value.ToString();
            tmp.col = trackBar4.Value.ToString();
            tmp.file = textBox2.Text;
            tmp.pin = trackBar1.Value.ToString();
            tmp.time = textBox1.Text;
            tmp.times = trackBar3.Value.ToString();
            tmp.waiting = checkBox1.Checked.ToString().ToLower();
            scenes.Params.Add(tmp);
        }

        private void CloseOpen(object[] opens)
        {
            foreach (var item in paramss)
            {
                if (item is Label)
                    ((Label)item).Visible = false;
                else if (item is TextBox)
                    ((TextBox)item).Visible = false;
                else if (item is TrackBar)
                    ((TrackBar)item).Visible = false;
                else if (item is CheckBox)
                    ((CheckBox)item).Visible = false;
            }
            foreach (var open in opens)
            {
                if (open is Label)
                    ((Label)open).Visible = true;
                else if (open is TextBox)
                    ((TextBox)open).Visible = true;
                else if (open is TrackBar)
                    ((TrackBar)open).Visible = true;
                else if (open is CheckBox)
                    ((CheckBox)open).Visible = true;
            }
        }

        string namesc = "";

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if(comboBox1.SelectedIndex == 0)
            {
                CloseOpen(new object[] {label4, label5, trackBar1, trackBar2 });
                namesc = "setlight";
            }
            else if (comboBox1.SelectedIndex == 1)
            {
                namesc = "strobo";
                CloseOpen(new object[] { label4, label6, label8, trackBar1, trackBar3, trackBar4 , checkBox1 });
            }
            else if (comboBox1.SelectedIndex == 2)
            {
                namesc = "stroboall";
                CloseOpen(new object[] { label6, trackBar3, checkBox1, label8, trackBar4 });
            }
            else if (comboBox1.SelectedIndex == 3)
            {
                CloseOpen(new object[] { label3, textBox1 });
                namesc = "sleep";
            }
            else if (comboBox1.SelectedIndex == 4)
            {
                CloseOpen(new object[] { label7, textBox2 });
                namesc = "playmusic";
            }
            else
            {
                MessageBox.Show("Error");
            }
        }

        private void новыйСценарийToolStripMenuItem_Click(object sender, EventArgs e)
        {
            scenes = new Sceene();
            scenes.name = toolStripTextBox4.Text;
            scenes.Params = new List<Steep>();
        }

        private void trackBar4_Scroll(object sender, EventArgs e)
        {
            label8.Text = string.Format("Количество {1}стробо ({0})", trackBar4.Value, Environment.NewLine);
        }

        private void сохранитьСценарийToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog svf = new SaveFileDialog();
            svf.Filter = "JSON File|*.json";
            if (svf.ShowDialog() == DialogResult.OK)
            {
                string serialized = JsonConvert.SerializeObject(scenes);
                File.WriteAllText(svf.FileName, serialized);
            }
        }

        private void panel1_Paint(object sender, PaintEventArgs e)
        {
            Graphic.DrawBackgroung(e.Graphics, panel1);
        }

        private void panel1_MouseClick(object sender, MouseEventArgs e)
        {
            Console.WriteLine(e.Location);
        }

        private void включитьToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (!IsGateway())
                Gateway.Send("setlight?p=0&q=1023",toolStripTextBox2.Text);
            else
                gtw.Setdata("192.168.1.34", "setlight?p=0%26q=1023");
        }

        private void выключитьToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (!IsGateway())
                Gateway.Send("setlight?p=0&q=0", toolStripTextBox2.Text);
            else
            {              
                MessageBox.Show(gtw.Setdata("192.168.1.34", "setlight?p=0%26q=0"));
            }
                
        }

        private void включитьToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            if (!IsGateway())
                Gateway.Send("setlight?p=1&q=1023", toolStripTextBox2.Text);
            else
                gtw.Setdata("192.168.1.34", "setlight?p=1%26q=1023");
        }

        private void выключитьToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            if (!IsGateway())
                Gateway.Send("setlight?p=1&q=0", toolStripTextBox2.Text);
            else
                gtw.Setdata("192.168.1.34", "setlight?p=1%26q=0");
        }

        private void включитьToolStripMenuItem2_Click(object sender, EventArgs e)
        {
            if (!IsGateway())
                Gateway.Send("setlight?p=2&q=1023", toolStripTextBox2.Text);
            else
                gtw.Setdata("192.168.1.34", "setlight?p=2%26q=1023");
        }

        private void выключитьToolStripMenuItem2_Click(object sender, EventArgs e)
        {
            if (!IsGateway())
                Gateway.Send("setlight?p=2&q=0", toolStripTextBox2.Text);
            else
                gtw.Setdata("192.168.1.34", "setlight?p=2%26q=0");
        }

        private bool IsGateway()
        {
            return Gatewayq;
        }

        private void прямоеПодключениеToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            Gatewayq = false;
            прямоеПодключениеToolStripMenuItem1.Checked = true;
            шлюзToolStripMenuItem.Checked = false;
        }

        bool Gatewayq = false;

        private void шлюзToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            Gatewayq = true;
            прямоеПодключениеToolStripMenuItem1.Checked = false;
            шлюзToolStripMenuItem.Checked = true;
        }

        private void toolStripTextBox1_Click(object sender, EventArgs e)
        {
            gtw.Connect(toolStripTextBox1.Text);
        }

        private void полноеУправлениеToolStripMenuItem_Click(object sender, EventArgs e)
        {
            groupBox2.Visible = !groupBox2.Visible;
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (!IsGateway())
                Gateway.Send("strobo?p=" + numericUpDown1.Value.ToString() + "&q=" + trackBar6.Value.ToString()+"&d="+ trackBar6.Value.ToString(), toolStripTextBox2.Text);
            else
                gtw.Setdata("192.168.1.34", "strobo?p=" + numericUpDown1.Value.ToString() + "%26q=" + trackBar6.Value.ToString() + "%26d=" + trackBar6.Value.ToString());
        }

        private void trackBar5_Scroll(object sender, EventArgs e)
        {
            label9.Text = string.Format("Яркость ({0})", trackBar5.Value);

            if (!IsGateway())
                Gateway.Send("setlight?p="+numericUpDown1.Value.ToString()+"&q="+trackBar5.Value.ToString(), toolStripTextBox2.Text);
            else
                gtw.Setdata("192.168.1.34", "setlight?p=" + numericUpDown1.Value.ToString() + "%26q=" + trackBar5.Value.ToString());
        }

        private void trackBar6_Scroll(object sender, EventArgs e)
        {
            label11.Text = string.Format("Стробо ({0})", trackBar6.Value);
        }

        private void trackBar7_Scroll(object sender, EventArgs e)
        {
            label12.Text = string.Format("Время (мс) ({0})", trackBar7.Value);
        }

        private void Timing(object sender, MediaEventArgs e)
        {
            comboBox1.SelectedIndex = 3;
            points[0] = e.TimesMS;
            double p = points[0] - points[1];            
            textBox1.Text = p.ToString().Substring(0, p.ToString().IndexOf(',') + 2).Replace(',', '.');
            points[1] = e.TimesMS;
        }
        private void Play(object sender, MediaEventArgs e)
        {

        }
        private void Pause(object sender, MediaEventArgs e)
        {

        }

        double[] points = new double[] {0,0 }; //vsego, posl

        private void Form1_Load(object sender, EventArgs e)
        {
#if !MONO
            this.Controls.Add(pl);
            pl.ClickStrels += Timing;
            pl.MediaPlay += Play;
            pl.MediaPause += Pause;
#endif
        }
    }
}
