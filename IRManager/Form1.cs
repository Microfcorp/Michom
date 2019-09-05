using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using michomeframework.Settings;
using michomeframework;
using IRManager.IR;

namespace IRManager
{
    public partial class Form1 : Form
    {
        private Setting set = SettingManager.Load();
        private IIR iR;
        Gateway gtw = new Gateway();
        public Form1()
        {
            InitializeComponent();
            toolStripTextBox1.Text = set.GetData(Setting.GatewayIP);

            if(set.GetData(Setting.AutoConnect) != Setting.NullData)
                if (Convert.ToBoolean(set.GetData(Setting.AutoConnect)))
                {
                    gtw.Connect(toolStripTextBox1.Text);
                    даToolStripMenuItem.Checked = true;
                    нетToolStripMenuItem.Checked = false;
                }
                else
                {
                    даToolStripMenuItem.Checked = false;
                    нетToolStripMenuItem.Checked = true;
                }

            СабвуферToolStripMenuItem_Click(null,null);
            
        }

        private void ToolStripTextBox1_TextChanged(object sender, EventArgs e)
        {
            set.SetData(Setting.GatewayIP, toolStripTextBox1.Text);
        }

        private void SendIR(object sender, EventArgs e)
        {
            gtw.SendIRCode(iR.ModuleIP, (sender as MenuItem).Name);
        }

        private void Open(object sender, EventArgs e)
        {
            this.Show();
            this.WindowState = FormWindowState.Normal;
            this.Activate();
        }

        private void Clos(object sender, EventArgs e)
        {
            Application.Exit();
        }

        void Init()
        {
            iR.Init();
            pictureBox1.Image = iR.Image;
            notifyIcon1.Text = "IRControl " + iR.Name;

            /*MenuItem[] tlt = new MenuItem[iR.KeyName.Length+2];

            for (int i = 0; i < iR.KeyName.Length; i++)
            {
                tlt[i] = new MenuItem()
                {
                    Text = iR.KeyName[i],
                    Name = iR.KeyKode[i]
                };
                tlt[i].Click += SendIR;
            }

            tlt[iR.KeyName.Length] = new MenuItem()
            {
                Text = "Развернуть"
            };
            tlt[iR.KeyName.Length].Click += Open;

            tlt[iR.KeyName.Length + 1] = new MenuItem()
            {
                Text = "Выход",               
            };
            tlt[iR.KeyName.Length + 1].Click += Clos;

            notifyIcon1.ContextMenu = new ContextMenu();
            notifyIcon1.ContextMenu.MenuItems.AddRange(tlt);*/
        }

        private void СабвуферToolStripMenuItem_Click(object sender, EventArgs e)
        {
            iR = new IR.RC58();
            Init();
        }
        
        private void PictureBox1_MouseDown(object sender, MouseEventArgs e)
        {
            gtw.SendIRCode(iR.ModuleIP, iR.PressCode(e.Location));
        }

        private void ПереподключитьсяToolStripMenuItem_Click(object sender, EventArgs e)
        {
            gtw.Connect(toolStripTextBox1.Text);
        }

        private void ДаToolStripMenuItem_Click(object sender, EventArgs e)
        {
            даToolStripMenuItem.Checked = true;
            нетToolStripMenuItem.Checked = false;
            set.SetData(Setting.AutoConnect, bool.TrueString);
        }

        private void НетToolStripMenuItem_Click(object sender, EventArgs e)
        {
            даToolStripMenuItem.Checked = false;
            нетToolStripMenuItem.Checked = true;
            set.SetData(Setting.AutoConnect, bool.FalseString);
        }

        private void Form1_Resize(object sender, EventArgs e)
        {
            if(this.WindowState == FormWindowState.Minimized)
                this.Hide();
        }

        private void NotifyIcon1_DoubleClick(object sender, EventArgs e)
        {
            Open(null, null);
        }

        private void ToolStripMenuItem2_Click(object sender, EventArgs e)
        {
            gtw.SendIRCode(iR.ModuleIP, "1119703215");
        }

        private void ВходToolStripMenuItem_Click(object sender, EventArgs e)
        {
            gtw.SendIRCode(iR.ModuleIP, "1119684855");
        }

        private void РежимToolStripMenuItem_Click(object sender, EventArgs e)
        {
            gtw.SendIRCode(iR.ModuleIP, "1119701175");
        }

        private void ГромчеToolStripMenuItem_Click(object sender, EventArgs e)
        {
            gtw.SendIRCode(iR.ModuleIP, "1119739935");
        }

        private void ТишеToolStripMenuItem_Click(object sender, EventArgs e)
        {
            gtw.SendIRCode(iR.ModuleIP, "1119709335");
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            this.WindowState = FormWindowState.Minimized;
            this.Hide();
        }
    }
}
