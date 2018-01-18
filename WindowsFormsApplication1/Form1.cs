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
using System.Net;
using System.Web;
using Newtonsoft.Json.Linq;
using LukeSkywalker.IPNetwork;

namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        //Settings
        string[] ips = new string[] { }; //iPs
        //Settings

        bool sleep = false;
        bool dock = false;
        string lag;
        string ip = "";
        string type = "";
        string data = "";
        string tip = "";

        string temp = "";
        string humm = "";

        HttpListener server;
        bool flag = true;
        IPNetwork ip_network = IPNetwork.Parse("192.168.1.1/24");

        public Form1()
        {
            InitializeComponent();
            backgroundWorker1.RunWorkerAsync();
            backgroundWorker2.RunWorkerAsync();
            comboBox1.Items.AddRange(ips);
        }

        private void StartServer(string prefix)
        {
            server = new HttpListener();
            // текущая ос не поддерживается
            if (!HttpListener.IsSupported) return;
            //добавление префикса (say/)
            //обязательно в конце должна быть косая черта
            if (string.IsNullOrEmpty(prefix))
                throw new ArgumentException("prefix");
            server.Prefixes.Add(prefix);
            //запускаем север
            server.Start();
            //this.Text = "Сервер запущен!";
            //сервер запущен? Тогда слушаем входящие соединения
            while (server.IsListening)
            {
                //ожидаем входящие запросы
                HttpListenerContext context = server.GetContext();
                //получаем входящий запрос
                HttpListenerRequest request = context.Request;
                //обрабатываем POST запрос
                //запрос получен методом POST (пришли данные формы)
                if (request.HttpMethod == "POST")
                {
                    //показать, что пришло от клиента
                    ShowRequestData(request);
                    //завершаем работу сервера
                    if (!flag) return;
                }
                //формируем ответ сервера:
                //динамически создаём страницу
                string responseString = @"<!DOCTYPE HTML>
<html><head></head><body>
<form method=""post"" action=""says"">
<p><b>Name: </b><br>
<input type=""text"" name=""myname"" size=""40""></p>
<p><input type=""submit"" value=""send""></p>
</form></body></html>";
                //отправка данных клиенту
                HttpListenerResponse response = context.Response;
                response.ContentType = "text/html; charset=UTF-8";
                byte[] buffer = Encoding.UTF8.GetBytes(responseString);
                response.ContentLength64 = buffer.Length;
                using (Stream output = response.OutputStream)
                {
                    output.Write(buffer, 0, buffer.Length);
                }
            }
        }
        private void ShowRequestData(HttpListenerRequest request)
        {
            //есть данные от клиента?
            if (!request.HasEntityBody) return;
            //смотрим, что пришло
            using (Stream body = request.InputStream)
            {
                using (StreamReader reader = new StreamReader(body))
                {
                    string text = reader.ReadToEnd();
                    //оставляем только имя
                    //text = text.Remove(0, 7);
                    //преобразуем %CC%E0%EA%F1 -> Макс
                    text = System.Web.HttpUtility.UrlDecode(text, Encoding.UTF8);
                    //выводим имя
                    //         MessageBox.Show(text);                   
                    JObject obj = JObject.Parse(text);
                    /*foreach (var item in obj["data"]["temper"])
                    {
                        MessageBox.Show(item + ";");
                    }*/
                    ip = obj["ip"].ToString();
                    type = obj["type"].ToString();
                    data = obj["data"].ToString();
                    if (type == "DHT") {
                        temp = (obj["data"]["temper"].ToString());
                        humm = (obj["data"]["humm"].ToString());
                        RichTextBox rch = new RichTextBox();
                        Invoke(new Action(() =>
                        {
                            Setlog(obj["data"].ToString(), ip, true);
                            label5.Text = obj["data"]["temper"].ToString() + "C";
                            label6.Text = obj["data"]["humm"].ToString() + "%";
                        }));

                    }
                    if (type == "Sobit")
                    {
                        tip = obj["data"].ToString();
                        Invoke(new Action(() =>
                        {
                            Setlog(tip, ip, true);
                            //label5.Text = obj["data"]["temper"].ToString() + "C";
                            //label6.Text = obj["data"]["humm"].ToString() + "%";
                        }));

                    }
                    //MessageBox.Show(text);
                    flag = true;
                    //останавливаем сервер
                }
            }
        }

        public String vibior(string plata)
        {
            string ip = "";
            switch (plata)
            {
                //Settings
                case "call": //The name of the device
                    ip = "192.168.1.0"; //IP device  
                    break;
                    /*
                    case "call":
                    ip = "192.168.1.0";
                    break;
                    ip = "192.168.1.0";
                    case "call":
                    ip = "192.168.1.0";
                    break;
                    */
                    //Settings
            }
            return ip;
        }

        public void Setlog(string data, string url, bool priem)
        {
            string date = DateTime.Now.ToString();
            this.richTextBox1.Text += date + " ";
            this.richTextBox1.Text += data;
            if (priem)
            {
                this.richTextBox1.Text += " <- ";
            }
            else
            {
                this.richTextBox1.Text += " -> ";
            }
            this.richTextBox1.Text += url;
            this.richTextBox1.Text += Environment.NewLine;
        }

        public void SetData(string data, string url)
        {
            timer1.Stop();
            if (url != "" && data != "") {
                webBrowser1.Navigate(new Uri("http://" + url + "/" + data));
                Setlog(data, url, false);
            }
            else { MessageBox.Show("Ошибка", "Не все параметры введены"); }

        }

        public void Refresh(string url)
        {
            webBrowser1.Navigate(new Uri("http://" + url + "/refresh"));
            System.Threading.Thread.Sleep(1000);
        }

        private void backgroundWorker1_DoWork(object sender, DoWorkEventArgs e)
        {
            string Host = System.Net.Dns.GetHostName();
            string IP = Dns.GetHostByName(Host).AddressList[0].ToString();
            string uri = "http://" + IP + ":8080/say/";
            StartServer(uri);
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            string line = "";
            string lagg = "";
            string it = "";
            if (File.Exists(Directory.GetCurrentDirectory() + "\\board.cfg"))
            {
                StreamReader sr = new StreamReader(Directory.GetCurrentDirectory() + "\\board.cfg");
                line = sr.ReadLine();

                //Continue to read until you reach end of file
                while (line != null)
                {
                    //write the lie to console window
                    //Console.WriteLine(line);
                    if (line != "") { comboBox1.Items.Add(line); }
                    //Read the next line
                    line = sr.ReadLine();
                }
                ///ips = new string[] { lagg };
                sr.Close();
                StreamReader srr = new StreamReader(Directory.GetCurrentDirectory() + "\\board.cfg");
                line = srr.ReadLine();

                //Continue to read until you reach end of file
                while (line != null)
                {
                    //write the lie to console window
                    //Console.WriteLine(line);
                    if (line != "") { lagg += line; }
                    //Read the next line
                    line = srr.ReadLine();
                }
                ///ips = new string[] { lagg };
                srr.Close();
                //
                //   
                foreach (string d in comboBox1.Items)
                {
                    it += "\"" + d + "\",";
                    удалитьToolStripMenuItem.DropDownItems.Add(d, image: null);

                }
                ips = new string[] { it };
                foreach (string a in ips) { Console.WriteLine(a); }
            }

            Setlog("Starting", "OK", false);

            //notifyIcon1.ShowBalloonTip(1000, "Привет", "Привет, ты запустил Michom", ToolTipIcon.None);
            timer1.Start();
        }

        private void webBrowser1_DocumentCompleted(object sender, WebBrowserDocumentCompletedEventArgs e)
        {
            Setlog(webBrowser1.DocumentText, webBrowser1.Url.ToString(), true);
            dock = true;
            timer1.Start();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            timer1.Stop();

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
            breakMenu.Text = "Показать погоду";
            breakMenu.Click += new EventHandler(setpog_Click);

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

        void setpog_Click(object sender, EventArgs e)
        {
            notifyIcon1.ShowBalloonTip(500, "Погода", "Температура " + label5.Text + "\n Влажность " + label6.Text, ToolTipIcon.None);
        }

        void runMenu_Click(object sender, EventArgs e)
        {
            this.Show();
            this.WindowState = FormWindowState.Normal;
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

            string comand = comboBox2.Text;
            string adress = comboBox1.Text;
            SetData(comand, adress);
        }

        private void richTextBox1_TextChanged(object sender, EventArgs e)
        {
            if (richTextBox1.TextLength >= 100000) richTextBox1.Text = "";
            string line;
            if (File.Exists(Directory.GetCurrentDirectory() + "\\log.log"))
            {
                StreamReader sr = new StreamReader(Directory.GetCurrentDirectory() + "\\log.log");
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
                StreamWriter sw = new StreamWriter(Directory.GetCurrentDirectory() + "\\log.log");

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
                StreamWriter sw = new StreamWriter(Directory.GetCurrentDirectory() + "\\log.log");

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

        private void отчистьтьКонсольToolStripMenuItem_Click(object sender, EventArgs e)
        {
            richTextBox1.Text = null;
            Setlog("Консоль отчищена", "ОК", false);
        }

        private void дзыыньToolStripMenuItem_Click(object sender, EventArgs e)
        {
            timer1.Stop();
            SetData("calling", vibior("call"));
            timer1.Start();
        }

        private void значнияПогодыToolStripMenuItem_Click(object sender, EventArgs e)
        {
            panel1.Visible = !panel1.Visible;
        }

        private void добавитьToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //ips.Concat(Enumerable.Range(toolStripTextBox2.Text, 1)).ToArray()
            comboBox1.Items.Add(toolStripTextBox2.Text);
            string itt = "";
            string it = "";
            string ita = "";
            foreach (string itm in ips) {
                itt += itm;
            }
            foreach (string d in comboBox1.Items)
            {
                it += d;
            }
            ita = itt + toolStripTextBox2.Text;
            ips = new string[] { ita };
            foreach (string a in ips)
            {
                Console.WriteLine(a);
            }

            string line = "";
            string lagg = "";
            if (File.Exists(Directory.GetCurrentDirectory() + "\\board.cfg"))
            {
                StreamReader sr = new StreamReader(Directory.GetCurrentDirectory() + "\\board.cfg");
                line = sr.ReadLine();

                //Continue to read until you reach end of file
                while (line != null)
                {
                    //write the lie to console window
                    //Console.WriteLine(line);
                    lagg += line + Environment.NewLine;
                    //Read the next line
                    line = sr.ReadLine();
                }
                ///ips = new string[] { lagg };
                sr.Close();

                StreamWriter sw = new StreamWriter(Directory.GetCurrentDirectory() + "\\board.cfg");
                lagg = lagg.Replace("", string.Empty);
                lagg += Environment.NewLine + toolStripTextBox2.Text;

                string[] words = lagg.Split(new char[] { '\n' });

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
                StreamWriter sw = new StreamWriter(Directory.GetCurrentDirectory() + "\\board.cfg");
                foreach (string a in ips)
                {
                    lagg += Environment.NewLine + a;
                }

                string[] words = lagg.Split(new char[] { '\n' });

                foreach (string s in words)
                {
                    sw.WriteLine(s);
                }


                // sw.WriteLine("From the StreamWriter class");
                //Close the file
                sw.Close();
            }
        }

        private void backgroundWorker2_DoWork(object sender, DoWorkEventArgs e)
        {
            System.Threading.Thread.Sleep(5000);
            while (true)
            {
                foreach (string ipr in comboBox1.Items)
                {
                    if (!dock)
                    {
                        Invoke(new Action(() =>
                        {
                            webBrowser1.Navigate(new Uri("http://" + ipr + "/refresh"));
                        }));

                    }
                    dock = false;
                    Console.WriteLine(ipr);
                    System.Threading.Thread.Sleep(20000);
                }
            }
        }

        private void автопоискToolStripMenuItem_Click(object sender, EventArgs e)
        {
            backgroundWorker4.RunWorkerAsync();
        }

        private void соединениеToolStripMenuItem_Click(object sender, EventArgs e)
        {
            backgroundWorker3.RunWorkerAsync();
            if (соединениеToolStripMenuItem.Text == "Соединение") соединениеToolStripMenuItem.Text = "Отключение";
            else serialPort1.Close(); соединениеToolStripMenuItem.Text = "Соединение";
        }

        private void backgroundWorker3_DoWork(object sender, DoWorkEventArgs e)
        {
            serialPort1 = new System.IO.Ports.SerialPort();
            if (toolStripTextBox1.Text != "") serialPort1.PortName = toolStripTextBox1.Text;
            if (toolStripTextBox3.Text != "") serialPort1.BaudRate = Convert.ToInt32(toolStripTextBox3.Text);
            serialPort1.Open();
            Invoke(new Action(() =>
            {
                Setlog(serialPort1.ReadLine(), serialPort1.PortName, true);
            }));
            serialPort1.Close();
        }
        private new void Closing(object sender, FormClosingEventArgs e)
        {
            this.WindowState = FormWindowState.Minimized;
            this.ShowInTaskbar = false;
            e.Cancel = true;
        }



        private void backgroundWorker4_DoWork(object sender, DoWorkEventArgs e)
        {
            WebBrowser wb1 = new WebBrowser();
            Console.WriteLine(ip_network.FirstUsable); // oпределяем первый IP адрес в подсети.
            Console.WriteLine(ip_network.LastUsable);
            IPAddressCollection ipss = IPNetwork.ListIPAddress(ip_network);
            foreach (var ip in ipss)
            {
                backgroundWorker2.CancelAsync();
                wb1.Navigate(new Uri(ip.ToString()));
            }

        }
        
    }
}
    
