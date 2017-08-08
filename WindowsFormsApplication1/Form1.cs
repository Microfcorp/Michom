using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        bool sleep = false;
        string lag;

        string call = "192.168.1.0";

        public Form1()
        {
            InitializeComponent();
            backgroundWorker1.RunWorkerAsync();
            comboBox1.Items.Add(call);
        }

        public void Setlog(string data, string url, bool priem)
        {
            string date = DateTime.Now.ToString();
            richTextBox1.Text += date + " ";
            richTextBox1.Text += data;
            if (priem)
            {
                richTextBox1.Text += " <- ";
            }
            else
            {
                richTextBox1.Text += " -> ";
            }
            richTextBox1.Text += url;
            richTextBox1.Text += Environment.NewLine;
        }

        public void CmdCont(string data, string url)
        {
            webBrowser1.Navigate(new Uri("http://" + url + "/" + data));
            Setlog(data, url, false);
        }

        public void Refresh(string url)
        {
            webBrowser1.Navigate(new Uri("http://" + url + "/refresh"));
            Setlog("Обновление", url, false);
            if (webBrowser1.DocumentText == "Call") {
                if (sleep) {
                    Setlog("Звонок в дверь", url, true);
                    notifyIcon1.ShowBalloonTip(2000, "Звонок в дверь", "Кто-то звонит в дверь", ToolTipIcon.None);
                }
            }
        }

        private void backgroundWorker1_DoWork(object sender, DoWorkEventArgs e)
        {
            //Label lab = new Label();
            //Form1 frm = new Form1();
            //lab.Text = "400000000000000000000000000000000000000000000000000000000000000000000000";
            //this.label1.Text = "84;";
            //while (true)
            //{
            //    Console.WriteLine("testtttttttttttttttttttttttttttttttttttttt");
            //}
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            Setlog("Starting","OK",false);
            //notifyIcon1.ShowBalloonTip(1000, "Привет", "Привет, ты запустил Michom", ToolTipIcon.None);
            timer1.Start();
        }

        private void webBrowser1_DocumentCompleted(object sender, WebBrowserDocumentCompletedEventArgs e)
        {
            Setlog(webBrowser1.DocumentText, " ", true);
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            timer1.Stop();
           // Refresh("");
            timer1.Start();
        }

        private void notifyIcon1_MouseClick(object sender, EventArgs e)
        {
            ShowBalloonTip();
            
        }
        private void ShowBalloonTip()
        {
            Container bpcomponents = new Container();
            ContextMenu contextMenu1 = new ContextMenu();

            MenuItem runMenu = new MenuItem();       
            runMenu.Index = 1;
            runMenu.Text = "Michom";
            runMenu.Click += new EventHandler(runMenu_Click);

            MenuItem breakMenu = new MenuItem();
            breakMenu.Index = 2;
            breakMenu.Text = "-------------";            

            MenuItem sleep = new MenuItem();                                 
            sleep.Index = 3;
            sleep.Text = "Не беспокоить";
            sleep.Click += new EventHandler(sleep_Click);

            MenuItem exitMenu = new MenuItem();
            exitMenu.Index = 4;
            exitMenu.Text = "E&xit";
            exitMenu.Click += new EventHandler(exitMenu_Click);
            /*
            MenuItem exitMenu = new MenuItem();
            exitMenu.Index = 5;
            exitMenu.Text = "E&xit";
            exitMenu.Click += new EventHandler(exitMenu_Click);

            MenuItem exitMenu = new MenuItem();
            exitMenu.Index = 6;
            exitMenu.Text = "E&xit";
            exitMenu.Click += new EventHandler(exitMenu_Click);
            */
            // Initialize contextMenu1
            contextMenu1.MenuItems.AddRange(
                        new System.Windows.Forms.MenuItem[] { runMenu, breakMenu, sleep, exitMenu });
            notifyIcon1.ContextMenu = contextMenu1;
            notifyIcon1.Visible = true;
        }

        void exitMenu_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        void runMenu_Click(object sender, EventArgs e)
        {
            this.Show();
        }
        void sleep_Click(object sender, EventArgs e)
        {
            if (sleep)
            {
                notifyIcon1.ShowBalloonTip(500, "Сон", "Уведомления поступают", ToolTipIcon.Info);
                sleep = false;
            }
            else
            {
                notifyIcon1.ShowBalloonTip(200, "Сон", "Уведомления не поступают", ToolTipIcon.Info);
                sleep = true;
            }
        }

        private void выходToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void неБеспокоитьToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (sleep)
            {
                notifyIcon1.ShowBalloonTip(500, "Сон", "Уведомления поступают", ToolTipIcon.Info);
                sleep = false;
            }
            else
            {
                notifyIcon1.ShowBalloonTip(50, "Сон", "Уведомления не поступают", ToolTipIcon.Info);
                sleep = true;
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string comand = textBox1.Text;
            string adress = comboBox1.Text;
            CmdCont(comand, adress);
        }

        private void richTextBox1_TextChanged(object sender, EventArgs e)
        {
            string line;
            if (File.Exists(Directory.GetCurrentDirectory() + "\\log.txt"))
            {            
            StreamReader sr = new StreamReader(Directory.GetCurrentDirectory() + "\\log.txt");
                line = sr.ReadLine();

                //Continue to read until you reach end of file
                while (line != null)
                {
                    //write the lie to console window
                    //Console.WriteLine(line);
                    lag += line + Environment.NewLine;
                    //Read the next line
                    line = sr.ReadLine();
                }
                sr.Close();
                StreamWriter sw = new StreamWriter(Directory.GetCurrentDirectory() + "\\log.txt");

                string[] words = richTextBox1.Text.Split(new char[] { '\n' });

                foreach (string s in words)
                {
                    sw.WriteLine(s);
                }
                

                // sw.WriteLine("From the StreamWriter class");
                //Close the file
                sw.Close();
            }
            else
            {
                StreamWriter sw = new StreamWriter(Directory.GetCurrentDirectory() + "\\log.txt");

                string[] words = richTextBox1.Text.Split(new char[] { '\n' });

                foreach (string s in words)
                {
                    sw.WriteLine(s);
                }

                // sw.WriteLine("From the StreamWriter class");
                //Close the file
                sw.Close();
            }
         }
    }
}
