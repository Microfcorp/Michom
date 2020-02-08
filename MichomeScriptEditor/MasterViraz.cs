using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using michomeframework.Scenaries;

namespace MichomeScriptEditor
{
    public partial class MasterViraz : Form
    {
        public MasterViraz(string[] ips)
        {
            InitializeComponent();
            DialogResult = DialogResult.No;
            comboBox1.Items.AddRange(ips);
        }

        public string TypeToString()
        {
            if (comboBox2.SelectedIndex == 0) return "Temp";
            else if (comboBox2.SelectedIndex == 1) return "Humm";
            else if (comboBox2.SelectedIndex == 2) return "Dawlen";
            else if (comboBox2.SelectedIndex == 3) return "Visota";
            else if (comboBox2.SelectedIndex == 4) return "IP";
            else if (comboBox2.SelectedIndex == 5) return "ID";
            else if (comboBox2.SelectedIndex == 6) return "Data";
            else return "Date";
        }

        public ParametersRM RM
        {
            get
            {
                return new ParametersRM(comboBox1.Text, TypeToString());
            }
        }

        public GeneralParameters ReturnP
        {
            get;
            private set;
        }

        private void MasterViraz_Load(object sender, EventArgs e)
        {

        }

        private void button3_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.OK;
            ReturnP = RM;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.OK;
            ReturnP = new ParametersPBP();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.OK;
            ReturnP = new ParametersCBP();
        }
    }
}
