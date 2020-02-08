using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using michomeframework.Settings;
using michomeframework;
using michomeframework.Scenaries;

namespace MichomeScriptEditor
{
    public partial class Form1 : Form
    {
        private Setting set = SettingManager.Load();
        Gateway gtw = new Gateway();
        Scenes sc;
        NameAndID[] nm;
        public Form1()
        {
            InitializeComponent();
            toolStripTextBox1.Text = set.GetData(Setting.GatewayIP);
            if (toolStripTextBox1.Text != "")
            {
                gtw.Connect(toolStripTextBox1.Text);
                sc = gtw.GetScenes();
                nm = gtw.GetDevice();
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void toolStripTextBox1_Click(object sender, EventArgs e)
        {
            set.SetData(Setting.GatewayIP, toolStripTextBox1.Text);
            try
            {
                gtw.Connect(toolStripTextBox1.Text);
                sc = gtw.GetScenes();
            }
            catch { return; }
        }

        private void загрузитьСценарииToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (sc == null) return;
            flowLayoutPanel1.Controls.Clear();
            var sn = sc.GetScenes();
            foreach (var item in sn)
            {
                var tmp = new ScenariesNode(item, sc, gtw, nm);
                flowLayoutPanel1.Controls.Add(tmp);
            }
        }

        private void мастерСозданияСценариевToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (sc == null) return;            
            var tmp = new ScenariesNode(sc.AddScene(), sc, gtw, nm);
            flowLayoutPanel1.Controls.Add(tmp);
        }
    }
}
