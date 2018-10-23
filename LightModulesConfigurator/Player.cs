using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Media;

namespace MicrofPlayer
{
    public class Player : Panel
    {
        CheckBox checkBox2 = new CheckBox();
        Label Info = new Label();
        Button Leight = new Button();
        WMPLib.WindowsMediaPlayer wplayer = new WMPLib.WindowsMediaPlayer();

        public bool IsPaused
        {
            get;
            internal set;
        }

        private double PauseTime = 0;

        public double PauseTimeSeconds
        {
            get
            {
                return PauseTime;
            }
        }

        public String PauseTimeString
        {
            get
            {
                return (PauseTime / 1000).ToString();
            }
        }

        public String Path
        {
            get
            {
                return wplayer.URL;
            }
            set
            {
                wplayer.URL = value;
                Info.Text = wplayer.controls.currentItem.name;
                wplayer.controls.stop();
            }
        }

        public delegate void MediaEventHandler(object sender, MediaEventArgs e);
        public event MediaEventHandler ClickStrels;
        public event MediaEventHandler MediaPlay;
        public event MediaEventHandler MediaPause;

        public void SetPath(string URL)
        {
            string tmp = URL;
            if (tmp.Split('.')[tmp.Split('.').Length - 1] == "mp3")
            {               
                Path = tmp;
            }
            else
                throw new Exception("Error MP3 Files");
        }


        public Player(Point p)
        {
            this.Location = p;
            this.BackColor = Color.Gray;
            this.Size = new Size(220, 48);       
            checkBox2.Location = new Point(3,6);
            Info.Location = new Point(120, 6);
            Leight.Location = new Point(1, 25);
            Leight.Size = new Size(215, 20);
            Leight.Text = "Получить время";
            Leight.Click += Button1_Click;
            checkBox2.CheckedChanged += checkBox2_CheckedChanged;
            Info.Click += SelectTrack;
            checkBox2.Text = "Play";
            Info.Text = "Трек не выбран";
            this.Controls.Add(checkBox2);
            this.Controls.Add(Info);
            this.Controls.Add(Leight);
        }
        private void checkBox2_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox2.Checked)
            {
                checkBox2.Text = "Пауза";
                Play();
            }
            else
            {
                checkBox2.Text = "Play";
                Pause();
            }
        }
        public void Play()
        {
            IsPaused = false;
            wplayer.controls.play();
            MediaPlay(this, new MediaEventArgs(wplayer.controls.currentPosition));
        }

        public void Button1_Click(object sender, EventArgs e)
        {
            if (ClickStrels != null)
            {
                Pause();
                checkBox2.Checked = false;
                ClickStrels(this, new MediaEventArgs(PauseTimeSeconds));
            }
        }

        public void Pause()
        {
            IsPaused = true;
            wplayer.controls.pause();
            PauseTime = wplayer.controls.currentPosition;
            MediaPause(this, new MediaEventArgs(PauseTime));
        }
        private void SelectTrack(object sender, EventArgs e)
        {
            OpenFileDialog opg = new OpenFileDialog();
            opg.Filter = "MP3 Files|*.mp3";
            if(opg.ShowDialog() == DialogResult.OK)
            {
                Path = opg.FileName;
            }
        }
    }
    public class MediaEventArgs
    {
        public MediaEventArgs(double s) { TimesMS = s; }
        public double TimesMS { get; } // readonly
    }
}
