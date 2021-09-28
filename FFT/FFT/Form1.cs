using NAudio.Wave;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using michomeframework;
using michomeframework.Settings;
using michomeframework.Modules.StaticController;
using System.Threading;

namespace FFT
{
    public partial class Form1 : Form
    {
        enum LightType
        {
            Strobo,
            Light,
        }

        enum TypeAnalyze
        {
            User,
            Volume,
            Bass,
            Treble,
        }


        Gateway gtw = new Gateway();
        LightModule LightM = new LightModule("", Gateway.TypeConnect.Telnet);

        // Other inputs are also usable. Just look through the NAudio library.
        private IWaveIn waveIn;
        private const int fftLength = 1024; // NAudio fft wants powers of two!

        // There might be a sample aggregator in NAudio somewhere but I made a variation for my needs
        private SampleAggregator sampleAggregator = new SampleAggregator(fftLength);

        private int k = 1000000 * 2;
        private List<double> Ks = new List<double>();

        private TypeAnalyze typeAnalyze = TypeAnalyze.Volume;

        public Form1()
        {
            InitializeComponent();

            if (SettingManager.IsSetting())
                gtw.Connect(SettingManager.Load().GetData(Setting.GatewayIP));
            else
            {
                MessageBox.Show("Настройки шлюза не найдены. Пожалуйста, запустите конфигуратор сети Michome");
                Application.Exit();
            }

            sampleAggregator.FftCalculated += new EventHandler<FftEventArgs>(FftCalculated);
            sampleAggregator.PerformFFT = true;
            waveIn = new WasapiLoopbackCapture();
            waveIn.DataAvailable += OnDataAvailable;
            waveIn.StartRecording();
        }

        private void UpdateModules()
        {
            var allDevices = gtw.GetDevice();
            модульToolStripMenuItem.DropDownItems.Clear();
            foreach (var item in allDevices.Where(tmp => tmp.ID == LightModule.ModuleID))
            {
                ToolStripMenuItem tmp = new ToolStripMenuItem
                {
                    Name = item.IP,
                    Text = item.Name
                };
                tmp.Click += ChangeModule;
                модульToolStripMenuItem.DropDownItems.Add(tmp);
            }
        }

        private void ChangeModule(object sender, EventArgs e)
        {
            var tmp = sender as ToolStripMenuItem;
            LightM = new LightModule(tmp.Name, Gateway.TypeConnect.Telnet);
            LightM.InitTelnet();
            label1.Text = "Подключен модуль " + tmp.Name;
        }

        void OnDataAvailable(object sender, WaveInEventArgs e)
        {
            if (this.InvokeRequired)
            {
                this.BeginInvoke(new EventHandler<WaveInEventArgs>(OnDataAvailable), sender, e);
            }
            else
            {
                byte[] buffer = e.Buffer;
                int bytesRecorded = e.BytesRecorded;
                int bufferIncrement = waveIn.WaveFormat.BlockAlign;

                for (int index = 0; index < bytesRecorded; index += bufferIncrement)
                {
                    float sample32 = BitConverter.ToSingle(buffer, index);
                    sampleAggregator.Add(sample32);
                }
            }
        }
        private int autokerror = 0;
        void AutoTune()
        {
            if (Ks.Average() >= PorogStrobo)
                k /= 2;

            if (Ks.Average() <= 400)
                k *= 2;

            /*if (Ks.Average() > 800)
                k -= 200000;

            if (Ks.Average() < 450)
                k += 200000;*/
        }

        private void FftCalculated(object sender, FftEventArgs e)
        {
            double bas = 0;
            double mid = 0;
            double hig = 0;
            if (ColVse == "intel")
            {
                bas = Math.Min(1023, Math.Abs(Math.Round(GetAmplitede(e, 20, 89) * (k / 5))));
                mid = Math.Min(1023, Math.Abs(Math.Round(GetAmplitede(e, 150, 255) * (k * 4))));
                hig = Math.Min(1023, Math.Abs(Math.Round(GetAmplitede(e, 300, 512) * (k * 8))));
            }
            // Do something with e.result!            
            var amp = GetAmplitede(e, s, po);
            amp = Math.Abs(amp * k);           
            var data = Math.Min(1023, Math.Round(amp == double.PositiveInfinity ? 0 : amp));
            Console.WriteLine(data);

            Ks.Add(Math.Max(0, (int)data));

            if (Ks.Count > 128)
                Ks.RemoveAt(1);

            if (autok && data != 0)
                AutoTune();

            if (autok && autokerror > 20)
            {
                autok = false;
                label2.Text = "Автоподбор К выключен";
                autokerror = 0;
                MessageBox.Show("AutoK Off, then Error");
            }

            if (autok && data < 0)
                autokerror += 1;

            progressBar1.Value = Math.Max(0, (int)data);

            if (LightM.IsIP)
            {
                if (lt == LightType.Light)
                {
                    LightM.SetLightAll((short)Math.Max(0, (int)data));
                }
                else if (lt == LightType.Strobo)
                {
                    if (ColVse != "intel" && Math.Max(0, (int)data) >= PorogStrobo)
                    {
                        if (ColVse == "random")
                            LightM.Strobo(LightM.RandomChanel, 1, timestrob);
                        else if (ColVse == "vse")
                            LightM.StroboAll(1, timestrob);                      
                    }
                    if (ColVse == "intel")
                    {
                        if (Math.Max(0, (int)bas) >= PorogStrobo/6)
                        {
                            LightM.Strobo(2, 1, timestrob);
                        }
                        if (Math.Max(0, (int)mid) >= PorogStrobo/10)
                        {
                            LightM.Strobo(0, 1, timestrob);
                        }
                        if (Math.Max(0, (int)hig) >= PorogStrobo/10)
                        {
                            LightM.Strobo(1, 1, timestrob);
                        }
                    }
                }
                //System.Threading.Thread.Sleep(200);
            }

        }

        private double GetAmplitede(FftEventArgs e, int from, int to)
        {
            if (from < 0) from = 0;
            //if (to < from) to = from;

            if (to > e.Result.Length) to = e.Result.Length;

            double avg = 0;

            for (int i = from; i < to; i++)
            {              
                var v = Math.Sqrt(e.Result[i].X * e.Result[i].X + e.Result[i].Y * e.Result[i].Y);
                avg += v;
            }
            return avg / (to - from);
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            UpdateModules();
            autok = SettingManager.Load().GetData("FFT_AutoK") == bool.TrueString;

            k = Convert.ToInt32(SettingManager.Load().GetData("FFT_K", "2000000"));
            toolStripTextBox2.Text = k.ToString();

            PorogStrobo = Convert.ToInt32(SettingManager.Load().GetData("FFT_PS", "900"));
            progressBar2.Value = PorogStrobo;
            toolStripTextBox1.Text = PorogStrobo.ToString();

            typeAnalyze = (TypeAnalyze)Convert.ToInt32(SettingManager.Load().GetData("FFT_TA", ((int)TypeAnalyze.Volume).ToString()));
            ChangeLabel4();

            ColVse = SettingManager.Load().GetData("FFT_KA", "vse");
            if (ColVse == "vse")
                label5.Text = "Все каналы";
            else if (ColVse == "random")
                label5.Text = "Случайный канал";
            else
                label5.Text = "Интеллектуально канал";

            timestrob = Convert.ToInt16(SettingManager.Load().GetData("FFT_TS", "30"));
            toolStripTextBox5.Text = timestrob.ToString();

            if (SettingManager.Load().GetData("FFT_T") != Setting.NullData)
            {
                if (SettingManager.Load().GetData("FFT_T") == "Strobo")
                {
                    lt = LightType.Strobo;
                    label3.Text = "Работа стробо";
                }
                else if (SettingManager.Load().GetData("FFT_T") == "Light")
                {
                    lt = LightType.Light;
                    label3.Text = "Работа яркости";
                }
            }

            toolStripTextBox4.Text = SettingManager.Load().GetData("FFT_US", "0");
            toolStripTextBox3.Text = SettingManager.Load().GetData("FFT_UP", fftLength.ToString());
            ПрименитьToolStripMenuItem1_Click(null, null);


            if (autok)
                label2.Text = "Автоподбор К включен";
            else label2.Text = "Автоподбор К выключен";
        }

        private void ChangeLabel4()
        {
            if (typeAnalyze == TypeAnalyze.Bass)
                label4.Text = "Анализ басса";
            else if (typeAnalyze == TypeAnalyze.Treble)
                label4.Text = "Анализ высоких";
            else if (typeAnalyze == TypeAnalyze.User)
                label4.Text = "Анализ пользовательский";
            else if (typeAnalyze == TypeAnalyze.Volume)
                label4.Text = "Анализ громкости";
        }

        private void ЗапуститьToolStripMenuItem_Click(object sender, EventArgs e) => waveIn.StartRecording();
        private void ОстановитьToolStripMenuItem_Click(object sender, EventArgs e) => waveIn.StopRecording();
        private void Form1_FormClosing(object sender, FormClosingEventArgs e) => waveIn.StopRecording();

        private void ВключитьСветToolStripMenuItem_Click(object sender, EventArgs e)
        {
            LightM.SetLightAll(LightM.MaxDur);
            /*LightM.SetLight(0, 1023);
            LightM.SetLight(1, 1023);
            LightM.SetLight(2, 1023);*/
        }

        private void ВыключитьСветToolStripMenuItem_Click(object sender, EventArgs e)
        {
            LightM.SetLightAll(LightM.MinDur);
            /*LightM.SetLight(0, 0);
            LightM.SetLight(1, 0);
            LightM.SetLight(2, 0);*/
        }

        private int PorogStrobo = 900;
        private LightType lt = LightType.Strobo;

        private void ToolStripTextBox1_TextChanged(object sender, EventArgs e)
        {
            PorogStrobo = Convert.ToInt32(toolStripTextBox1.Text);
            progressBar2.Value = PorogStrobo;
            SettingManager.Load().SetData("FFT_PS", PorogStrobo.ToString());
        }

        private void ВставитьТекущееToolStripMenuItem_Click(object sender, EventArgs e)
        {
            PorogStrobo = (int)Ks[Ks.Count - 1];
            progressBar2.Value = PorogStrobo;
            SettingManager.Load().SetData("FFT_PS", PorogStrobo.ToString());
        }

        private void ВставитьСреднееToolStripMenuItem_Click(object sender, EventArgs e)
        {
            PorogStrobo = (int)Ks.Average();
            progressBar2.Value = PorogStrobo;
            SettingManager.Load().SetData("FFT_PS", PorogStrobo.ToString());
        }

        private void ПримениитьToolStripMenuItem_Click(object sender, EventArgs e)
        {
            lt = LightType.Strobo;
            SettingManager.Load().SetData("FFT_T", "Strobo");
            label3.Text = "Работа стробо";
        }

        private void ПрименитьToolStripMenuItem_Click(object sender, EventArgs e)
        {
            lt = LightType.Light;
            SettingManager.Load().SetData("FFT_T", "Light");
            label3.Text = "Работа яркости";
        }
        private bool autok = true;
        private void АвтоподборКToolStripMenuItem_Click(object sender, EventArgs e)
        {
            autok = !autok;
            SettingManager.Load().SetData("FFT_AutoK", autok.ToString());
            if (autok)
                label2.Text = "Автоподбор К включен";
            else label2.Text = "Автоподбор К выключен";
        }

        bool ChangePorog = false;

        private void Form1_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Escape)
                LightM.IP = "";
            if (e.KeyCode == Keys.End)
            {
                ChangePorog = !ChangePorog;
                if (ChangePorog)
                    progressBar2.Cursor = Cursors.IBeam;
                else
                    progressBar2.Cursor = Cursors.Default;
            }
        }

        private void ToolStripTextBox2_TextChanged(object sender, EventArgs e)
        {
            k = Convert.ToInt32(toolStripTextBox2.Text);
            SettingManager.Load().SetData("FFT_K", k.ToString());
            autok = false;
        }

        private void ПрименитьToolStripMenuItem4_Click(object sender, EventArgs e)
        {
            s = 0;
            po = fftLength;

            SettingManager.Load().SetData("FFT_US", s.ToString());
            SettingManager.Load().SetData("FFT_UP", po.ToString());

            typeAnalyze = TypeAnalyze.Volume;
            SettingManager.Load().SetData("FFT_TA", ((int)typeAnalyze).ToString());
            ChangeLabel4();
        }

        private void ПрименитьToolStripMenuItem3_Click(object sender, EventArgs e)
        {
            s = 20;
            po = 89;

            SettingManager.Load().SetData("FFT_US", s.ToString());
            SettingManager.Load().SetData("FFT_UP", po.ToString());

            typeAnalyze = TypeAnalyze.Bass;
            SettingManager.Load().SetData("FFT_TA", ((int)typeAnalyze).ToString());
            ChangeLabel4();
        }

        private void ПрименитьToolStripMenuItem2_Click(object sender, EventArgs e)
        {
            s = 300;
            po = 512;

            SettingManager.Load().SetData("FFT_US", s.ToString());
            SettingManager.Load().SetData("FFT_UP", po.ToString());

            typeAnalyze = TypeAnalyze.Treble;
            SettingManager.Load().SetData("FFT_TA", ((int)typeAnalyze).ToString());
            ChangeLabel4();
        }
        int s = 0;
        int po = fftLength;
        private void ПрименитьToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            typeAnalyze = TypeAnalyze.User;
            SettingManager.Load().SetData("FFT_TA", ((int)typeAnalyze).ToString());
            ChangeLabel4();

            s = Convert.ToInt32(toolStripTextBox4.Text);
            SettingManager.Load().SetData("FFT_US", s.ToString());
            po = Convert.ToInt32(toolStripTextBox3.Text);
            SettingManager.Load().SetData("FFT_UP", po.ToString());
        }

        private void ToolStripTextBox4_TextChanged(object sender, EventArgs e)
        {
            
        }

        private void ToolStripTextBox3_TextChanged(object sender, EventArgs e)
        {
            
        }

        private void ProgressBar2_MouseDown(object sender, MouseEventArgs e)
        {
            if (ChangePorog)
            {
                double X = e.Location.X;
                double OneDel = (double)Math.Max(progressBar2.Size.Width, progressBar2.Maximum) / (double)Math.Min(progressBar2.Size.Width, progressBar2.Maximum);
                int Result = (int)Math.Round(X * OneDel) + 2;

                PorogStrobo = Result;
                toolStripTextBox1.Text = PorogStrobo.ToString();
                progressBar2.Value = PorogStrobo;
                SettingManager.Load().SetData("FFT_PS", PorogStrobo.ToString());

                ChangePorog = false;
                progressBar2.Cursor = Cursors.Default;
            }
        }

        short timestrob = 30;

        private void ToolStripTextBox5_TextChanged(object sender, EventArgs e)
        {
            timestrob = Convert.ToInt16(toolStripTextBox5.Text);
            SettingManager.Load().SetData("FFT_TS", timestrob.ToString());
        }

        string ColVse = "random";

        private void ВсеToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ColVse = "vse";
            SettingManager.Load().SetData("FFT_KA", ColVse);
            label5.Text = "Все каналы";
        }

        private void СлучайноToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ColVse = "random";
            SettingManager.Load().SetData("FFT_KA", ColVse);
            label5.Text = "Случайный канал";
        }

        private void ИнтеллектуальноToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ColVse = "intel";
            SettingManager.Load().SetData("FFT_KA", ColVse);
            label5.Text = "Интеллектуально канал";
        }
    }
}
