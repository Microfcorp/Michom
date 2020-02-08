using michomeframework.Scenaries;
using michomeframework;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MichomeScriptEditor
{
    public partial class EditScenes : Form
    {
        uint SID = 0;
        Scenes SC;
        SceneNode ThisNode;
        string[] modules;

        List<GeneralParameters> ifs = new List<GeneralParameters>();
        List<GeneralParameters> bts = new List<GeneralParameters>();
        List<GeneralParameters> sns = new List<GeneralParameters>();

        List<GeneralParameters> bufer = new List<GeneralParameters>();

        public EditScenes(uint ScenesID, Scenes sc, Gateway gt, NameAndID[] nm)
        {
            InitializeComponent();
            CreateModules(nm);
            modules = nm.Select(tmp => tmp.IP).ToArray();
            SID = ScenesID;
            SC = sc;
            ThisNode = sc.GetScenes()[ScenesID];
            var pname = ThisNode.GetParametersCollectionName();

            numericUpDown1.Value = ThisNode.ID;
            textBox1.Text = pname.Text;
            comboBox1.Text = ThisNode.Modules;
            dateTimePicker1.Value = ThisNode.StartTime;
            dateTimePicker2.Value = ThisNode.EndTime;
            comboBox2.Text = ThisNode.GetParametersCollectionThen().Text;
            comboBox3.Text = ThisNode.GetParametersCollectionEnd().Text;
            numericUpDown2.Value = ThisNode.Timeout;

            checkBox1.Checked = pname.IsParameter(GeneralParameters.ParametersName.SDS);
            checkBox4.Checked = pname.IsParameter(GeneralParameters.ParametersName.SDE);
            checkBox2.Checked = pname.IsParameter(GeneralParameters.ParametersName.EDS);
            checkBox3.Checked = pname.IsParameter(GeneralParameters.ParametersName.EDE);

            ifs.AddRange(pname.GetParameters(GeneralParameters.ParametersName.IF));
            bts.AddRange(pname.GetParameters(GeneralParameters.ParametersName.BT));

            var pthen = ThisNode.GetParametersCollectionThen();
            sns.AddRange(pthen.GetParameters(GeneralParameters.ParametersName.SN));
            sns.ForEach(tmp => (tmp as ParametersSN).SendType = true);
            int c = sns.Count;
            var pend = ThisNode.GetParametersCollectionEnd();
            sns.AddRange(pend.GetParameters(GeneralParameters.ParametersName.SN));
            sns.GetRange(c, sns.Count-c).ForEach(tmp => (tmp as ParametersSN).SendType = false);

            Zap();
        }

        private void Zap()
        {
            comboBox4.Items.Clear();
            for (int i = 0; i < ifs.Count; i++)
                comboBox4.Items.Add(i);

            comboBox11.Items.Clear();
            for (int i = 0; i < bts.Count; i++)
                comboBox11.Items.Add(i);

            comboBox9.Items.Clear();
            for (int i = 0; i < sns.Count; i++)
                comboBox9.Items.Add(i);
        }

        private void CreateModules(NameAndID[] gtw)
        {
            comboBox1.Items.Clear();
            for (int i = 0; i < gtw.Length; i++)
                comboBox1.Items.Add(gtw[i].IP);
        }

        private void EditScenes_Load(object sender, EventArgs e)
        {

        }

        private void comboBox4_SelectedIndexChanged(object sender, EventArgs e)
        {
            var obj = ifs[comboBox4.SelectedIndex] as ParametersIF;

            comboBox5.Text = obj.GetStringChildren(obj.Viraz1);
            comboBox7.Text = obj.GetStringChildren(obj.Viraz2);
            comboBox6.Text = obj.OperatorToString();
        }

        private void comboBox11_SelectedIndexChanged(object sender, EventArgs e)
        {
            var obj = bts[comboBox11.SelectedIndex] as ParametersBT;

            comboBox10.Text = obj.Module;
            numericUpDown3.Value = Convert.ToInt32(obj.Pin);
            numericUpDown4.Value = Convert.ToInt32(obj.Count);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            ifs.Add(new ParametersIF("if_0==0;", new GeneralParameters[] { }));
            Zap();
            comboBox4.SelectedIndex = comboBox4.Items.Count - 1;
        }

        private void button8_Click(object sender, EventArgs e)
        {
            bts.Add(new ParametersBT("bt_192.168.1.34_5_2;", new GeneralParameters[]{ }));
            Zap();
            comboBox11.SelectedIndex = comboBox11.Items.Count - 1;
        }

        private void MasterAdd(Control ctr)
        {
            MasterViraz master = new MasterViraz(modules);
            if (master.ShowDialog() == DialogResult.OK)
            {
                ctr.Text = master.ReturnP.ToStringChildren;
                bufer.Add(master.ReturnP);
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            MasterAdd(comboBox5);
        }

        private void button5_Click(object sender, EventArgs e)
        {
            MasterAdd(comboBox7);
        }

        private void IFEdit(object sender, EventArgs e)
        {
            var ifg = ifs[comboBox4.SelectedIndex] as ParametersIF;
            ifg.Viraz1 = comboBox5.Text;
            ifg.StringToOperator(comboBox6.Text);
            ifg.Viraz2 = comboBox7.Text;
        }
        private void BTEdit(object sender, EventArgs e)
        {
            var ifg = bts[comboBox11.SelectedIndex] as ParametersBT;
            ifg.Module = comboBox10.Text;
            ifg.Pin = numericUpDown3.Value.ToString();
            ifg.Count = numericUpDown4.Value.ToString();
        }
        private void SNEdit(object sender, EventArgs e)
        {
            var ifg = sns[comboBox9.SelectedIndex] as ParametersSN;
            ifg.Group = IntToGroup(comboBox12.SelectedIndex);
            ifg.Message = richTextBox1.Text;
            ifg.SendType = radioButton1.Checked;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            var pname = ThisNode.GetParametersCollectionName();
            pname.ToString = textBox1.Text.Trim() + " ";

            if (checkBox1.Checked) pname.Add(new ParametersSDS(), true);
            else pname.Remove(GeneralParameters.ParametersName.SDS);
            if (checkBox2.Checked) pname.Add(new ParametersEDS(), true);
            else pname.Remove(GeneralParameters.ParametersName.EDS);
            if (checkBox3.Checked) pname.Add(new ParametersEDE(), true);
            else pname.Remove(GeneralParameters.ParametersName.EDE);
            if (checkBox4.Checked) pname.Add(new ParametersSDE(), true);
            else pname.Remove(GeneralParameters.ParametersName.SDE);

            pname.Add(ifs.ToArray(), true);
            pname.Add(bts.ToArray(), true);

            var pthen = ThisNode.GetParametersCollectionThen();
            pthen.ToString = comboBox2.Text;
            pthen.Add(sns.Where(tmp => (tmp as ParametersSN).SendType).ToArray(), true);

            var pend = ThisNode.GetParametersCollectionThen();
            pend.ToString = comboBox3.Text;
            pend.Add(sns.Where(tmp => !(tmp as ParametersSN).SendType).ToArray(), true);

            ThisNode.Name = pname.ToString;
            ThisNode.Modules = comboBox1.Text;
            ThisNode.StartTime = dateTimePicker1.Value;
            ThisNode.EndTime = dateTimePicker2.Value;
            ThisNode.SendThen = pthen.ToString;
            ThisNode.SendEnd = pend.ToString;
            ThisNode.Timeout = (int)numericUpDown2.Value;

            if (SC.SetScene(ThisNode, (int)numericUpDown1.Value)) MessageBox.Show("Успешно записано в шлюз");
            else MessageBox.Show("Ошибка записи в шлюз");

            if((int)numericUpDown1.Value != ThisNode.ID)
            {
                MessageBox.Show("Был изменен ID записи. Пожалуста откройте запись заново");
                Close();
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            SC.RemoveScene(ThisNode);
            MessageBox.Show("Сценарий успешно удален");
            Close();
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void tabPage5_Click(object sender, EventArgs e)
        {

        }

        private void button7_Click(object sender, EventArgs e)
        {
            MasterViraz master = new MasterViraz(modules);
            if (master.ShowDialog() == DialogResult.OK)
            {
                richTextBox1.Text += master.ReturnP.ToStringChildren;
            }
        }

        private int GroupToInt(string gr)
        {
            if (gr == "all") return 0;
            else return 1;
        }
        private string IntToGroup(int gr)
        {
            if (gr == 0) return "all";
            else return "general";
        }

        private void comboBox9_SelectedIndexChanged(object sender, EventArgs e)
        {
            var obj = (sns[comboBox9.SelectedIndex] as ParametersSN);

            radioButton1.Checked = obj.SendType;
            radioButton2.Checked = !obj.SendType;
            comboBox12.SelectedIndex = GroupToInt(obj.Group);
            richTextBox1.Text = obj.ReadOnlyMessage;
        }

        private void button6_Click(object sender, EventArgs e)
        {
            sns.Add(new ParametersSN("^sn_all_Привет;", new GeneralParameters[] { }));
            Zap();
            comboBox9.SelectedIndex = comboBox9.Items.Count - 1;
        }

        private void button12_Click(object sender, EventArgs e)
        {
            try
            {
                bts.RemoveAt(comboBox11.SelectedIndex);
                Zap();
                comboBox11.SelectedIndex = comboBox11.Items.Count - 1;
                comboBox10.Text = comboBox11.Text = "";
                numericUpDown3.Value = numericUpDown4.Value = 0;
            }
            catch { }
        }

        private void button13_Click(object sender, EventArgs e)
        {
            try
            {
                ifs.RemoveAt(comboBox4.SelectedIndex);
                Zap();
                comboBox4.SelectedIndex = comboBox4.Items.Count - 1;
                comboBox5.Text = comboBox6.Text = comboBox7.Text = comboBox4.Text = "";
            }
            catch { }
        }

        private void button14_Click(object sender, EventArgs e)
        {
            try
            {
                sns.RemoveAt(comboBox9.SelectedIndex);
                Zap();
                comboBox9.SelectedIndex = comboBox9.Items.Count - 1;
                radioButton1.Checked = radioButton2.Checked = false;
                comboBox12.Text = richTextBox1.Text = comboBox9.Text = "";
            }
            catch { }
        }
    }
}
