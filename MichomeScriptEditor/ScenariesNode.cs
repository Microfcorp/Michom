using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using michomeframework.Scenaries;
using michomeframework;

namespace MichomeScriptEditor
{
    public partial class ScenariesNode : UserControl
    {
        public ScenariesNode(SceneNode sn, Scenes sc, Gateway g, NameAndID[] nm)
        {
            InitializeComponent();
            var col = sn.GetParametersCollectionName();

            label3.Text = sn.ID.ToString();

            label5.Text = sn.StartDateParse.TimeOfDay.ToString();
            label7.Text = sn.EndDateParse.TimeOfDay.ToString();

            label9.Text = sn.CSE.TimeOfDay.ToString();
            label2.Text = col.Text;
            checkBox4.Checked = sn.Enable;            
            checkBox1.Checked = col.IsParameter(GeneralParameters.ParametersName.IF);
            checkBox2.Checked = sn.GetParametersCollection().IsParameter(GeneralParameters.ParametersName.SN);
            checkBox3.Checked = col.IsParameter(GeneralParameters.ParametersName.BT);
            checkBox5.Checked = col.IsParameter(GeneralParameters.ParametersName.NOS);

            button1.Click += (o,e) => { EditScenes ed = new EditScenes(sn.ID-1, sc, g, nm); ed.ShowDialog(); };

            checkBox4.CheckedChanged += (o, e) => { sn.Enable = checkBox4.Checked; sc.SetScene(sn); };
        }


        private void ScenariesNode_Load(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {

        }
    }
}
