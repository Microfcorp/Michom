namespace WindowsFormsApplication1
{
    partial class Form1
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.backgroundWorker1 = new System.ComponentModel.BackgroundWorker();
            this.richTextBox1 = new System.Windows.Forms.RichTextBox();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.michomToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.неБеспокоитьToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.отладкаToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.отчистьтьКонсольToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.cOMВзаимодействиеToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.портToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripTextBox1 = new System.Windows.Forms.ToolStripTextBox();
            this.скоростьToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripTextBox3 = new System.Windows.Forms.ToolStripTextBox();
            this.бодToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.соединениеToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.выходToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.звонокToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.дзыыньToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.погодаToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.значнияПогодыToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.устройстваToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.добавитьПоIpToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripTextBox2 = new System.Windows.Forms.ToolStripTextBox();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.добавитьToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.автопоискToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.удалитьToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.webBrowser1 = new System.Windows.Forms.WebBrowser();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.notifyIcon1 = new System.Windows.Forms.NotifyIcon(this.components);
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.panel1 = new System.Windows.Forms.Panel();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.comboBox2 = new System.Windows.Forms.ComboBox();
            this.backgroundWorker2 = new System.ComponentModel.BackgroundWorker();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.backgroundWorker3 = new System.ComponentModel.BackgroundWorker();
            this.backgroundWorker4 = new System.ComponentModel.BackgroundWorker();
            this.menuStrip1.SuspendLayout();
            this.panel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // backgroundWorker1
            // 
            this.backgroundWorker1.WorkerReportsProgress = true;
            this.backgroundWorker1.WorkerSupportsCancellation = true;
            this.backgroundWorker1.DoWork += new System.ComponentModel.DoWorkEventHandler(this.backgroundWorker1_DoWork);
            // 
            // richTextBox1
            // 
            this.richTextBox1.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.richTextBox1.Location = new System.Drawing.Point(12, 40);
            this.richTextBox1.Name = "richTextBox1";
            this.richTextBox1.ReadOnly = true;
            this.richTextBox1.Size = new System.Drawing.Size(823, 472);
            this.richTextBox1.TabIndex = 1;
            this.richTextBox1.Text = "";
            this.richTextBox1.TextChanged += new System.EventHandler(this.richTextBox1_TextChanged);
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.michomToolStripMenuItem,
            this.звонокToolStripMenuItem,
            this.погодаToolStripMenuItem,
            this.устройстваToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.RenderMode = System.Windows.Forms.ToolStripRenderMode.Professional;
            this.menuStrip1.Size = new System.Drawing.Size(847, 24);
            this.menuStrip1.TabIndex = 2;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // michomToolStripMenuItem
            // 
            this.michomToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.неБеспокоитьToolStripMenuItem,
            this.отладкаToolStripMenuItem,
            this.cOMВзаимодействиеToolStripMenuItem,
            this.toolStripSeparator1,
            this.выходToolStripMenuItem});
            this.michomToolStripMenuItem.Name = "michomToolStripMenuItem";
            this.michomToolStripMenuItem.Size = new System.Drawing.Size(64, 20);
            this.michomToolStripMenuItem.Text = "Michom";
            // 
            // неБеспокоитьToolStripMenuItem
            // 
            this.неБеспокоитьToolStripMenuItem.Name = "неБеспокоитьToolStripMenuItem";
            this.неБеспокоитьToolStripMenuItem.Size = new System.Drawing.Size(194, 22);
            this.неБеспокоитьToolStripMenuItem.Text = "Не беспокоить";
            this.неБеспокоитьToolStripMenuItem.Click += new System.EventHandler(this.неБеспокоитьToolStripMenuItem_Click);
            // 
            // отладкаToolStripMenuItem
            // 
            this.отладкаToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.отчистьтьКонсольToolStripMenuItem});
            this.отладкаToolStripMenuItem.Name = "отладкаToolStripMenuItem";
            this.отладкаToolStripMenuItem.Size = new System.Drawing.Size(194, 22);
            this.отладкаToolStripMenuItem.Text = "Отладка";
            // 
            // отчистьтьКонсольToolStripMenuItem
            // 
            this.отчистьтьКонсольToolStripMenuItem.Name = "отчистьтьКонсольToolStripMenuItem";
            this.отчистьтьКонсольToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.отчистьтьКонсольToolStripMenuItem.Text = "Отчистить консоль";
            this.отчистьтьКонсольToolStripMenuItem.Click += new System.EventHandler(this.отчистьтьКонсольToolStripMenuItem_Click);
            // 
            // cOMВзаимодействиеToolStripMenuItem
            // 
            this.cOMВзаимодействиеToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.портToolStripMenuItem,
            this.скоростьToolStripMenuItem,
            this.соединениеToolStripMenuItem});
            this.cOMВзаимодействиеToolStripMenuItem.Name = "cOMВзаимодействиеToolStripMenuItem";
            this.cOMВзаимодействиеToolStripMenuItem.Size = new System.Drawing.Size(194, 22);
            this.cOMВзаимодействиеToolStripMenuItem.Text = "COM взаимодействие";
            // 
            // портToolStripMenuItem
            // 
            this.портToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripTextBox1});
            this.портToolStripMenuItem.Name = "портToolStripMenuItem";
            this.портToolStripMenuItem.Size = new System.Drawing.Size(141, 22);
            this.портToolStripMenuItem.Text = "Порт";
            // 
            // toolStripTextBox1
            // 
            this.toolStripTextBox1.Name = "toolStripTextBox1";
            this.toolStripTextBox1.Size = new System.Drawing.Size(100, 23);
            // 
            // скоростьToolStripMenuItem
            // 
            this.скоростьToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripTextBox3,
            this.бодToolStripMenuItem});
            this.скоростьToolStripMenuItem.Name = "скоростьToolStripMenuItem";
            this.скоростьToolStripMenuItem.Size = new System.Drawing.Size(141, 22);
            this.скоростьToolStripMenuItem.Text = "Скорость";
            // 
            // toolStripTextBox3
            // 
            this.toolStripTextBox3.Name = "toolStripTextBox3";
            this.toolStripTextBox3.Size = new System.Drawing.Size(100, 23);
            // 
            // бодToolStripMenuItem
            // 
            this.бодToolStripMenuItem.Enabled = false;
            this.бодToolStripMenuItem.Name = "бодToolStripMenuItem";
            this.бодToolStripMenuItem.Size = new System.Drawing.Size(160, 22);
            this.бодToolStripMenuItem.Text = "бод";
            // 
            // соединениеToolStripMenuItem
            // 
            this.соединениеToolStripMenuItem.Name = "соединениеToolStripMenuItem";
            this.соединениеToolStripMenuItem.Size = new System.Drawing.Size(141, 22);
            this.соединениеToolStripMenuItem.Text = "Соединение";
            this.соединениеToolStripMenuItem.Click += new System.EventHandler(this.соединениеToolStripMenuItem_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(191, 6);
            // 
            // выходToolStripMenuItem
            // 
            this.выходToolStripMenuItem.Name = "выходToolStripMenuItem";
            this.выходToolStripMenuItem.Size = new System.Drawing.Size(194, 22);
            this.выходToolStripMenuItem.Text = "Выход";
            this.выходToolStripMenuItem.Click += new System.EventHandler(this.выходToolStripMenuItem_Click);
            // 
            // звонокToolStripMenuItem
            // 
            this.звонокToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.дзыыньToolStripMenuItem});
            this.звонокToolStripMenuItem.Name = "звонокToolStripMenuItem";
            this.звонокToolStripMenuItem.Size = new System.Drawing.Size(59, 20);
            this.звонокToolStripMenuItem.Text = "Звонок";
            // 
            // дзыыньToolStripMenuItem
            // 
            this.дзыыньToolStripMenuItem.Name = "дзыыньToolStripMenuItem";
            this.дзыыньToolStripMenuItem.Size = new System.Drawing.Size(118, 22);
            this.дзыыньToolStripMenuItem.Text = "Дзыынь";
            this.дзыыньToolStripMenuItem.Click += new System.EventHandler(this.дзыыньToolStripMenuItem_Click);
            // 
            // погодаToolStripMenuItem
            // 
            this.погодаToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.значнияПогодыToolStripMenuItem});
            this.погодаToolStripMenuItem.Name = "погодаToolStripMenuItem";
            this.погодаToolStripMenuItem.Size = new System.Drawing.Size(59, 20);
            this.погодаToolStripMenuItem.Text = "Погода";
            // 
            // значнияПогодыToolStripMenuItem
            // 
            this.значнияПогодыToolStripMenuItem.Name = "значнияПогодыToolStripMenuItem";
            this.значнияПогодыToolStripMenuItem.Size = new System.Drawing.Size(165, 22);
            this.значнияПогодыToolStripMenuItem.Text = "Значния погоды";
            this.значнияПогодыToolStripMenuItem.Click += new System.EventHandler(this.значнияПогодыToolStripMenuItem_Click);
            // 
            // устройстваToolStripMenuItem
            // 
            this.устройстваToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.добавитьПоIpToolStripMenuItem,
            this.автопоискToolStripMenuItem,
            this.удалитьToolStripMenuItem});
            this.устройстваToolStripMenuItem.Name = "устройстваToolStripMenuItem";
            this.устройстваToolStripMenuItem.Size = new System.Drawing.Size(81, 20);
            this.устройстваToolStripMenuItem.Text = "Устройства";
            // 
            // добавитьПоIpToolStripMenuItem
            // 
            this.добавитьПоIpToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripTextBox2,
            this.toolStripSeparator2,
            this.добавитьToolStripMenuItem});
            this.добавитьПоIpToolStripMenuItem.Name = "добавитьПоIpToolStripMenuItem";
            this.добавитьПоIpToolStripMenuItem.Size = new System.Drawing.Size(156, 22);
            this.добавитьПоIpToolStripMenuItem.Text = "Добавить по ip";
            // 
            // toolStripTextBox2
            // 
            this.toolStripTextBox2.Name = "toolStripTextBox2";
            this.toolStripTextBox2.Size = new System.Drawing.Size(100, 23);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(157, 6);
            // 
            // добавитьToolStripMenuItem
            // 
            this.добавитьToolStripMenuItem.Name = "добавитьToolStripMenuItem";
            this.добавитьToolStripMenuItem.Size = new System.Drawing.Size(160, 22);
            this.добавитьToolStripMenuItem.Text = "Добавить";
            this.добавитьToolStripMenuItem.Click += new System.EventHandler(this.добавитьToolStripMenuItem_Click);
            // 
            // автопоискToolStripMenuItem
            // 
            this.автопоискToolStripMenuItem.Name = "автопоискToolStripMenuItem";
            this.автопоискToolStripMenuItem.Size = new System.Drawing.Size(156, 22);
            this.автопоискToolStripMenuItem.Text = "Автопоиск";
            this.автопоискToolStripMenuItem.Visible = false;
            this.автопоискToolStripMenuItem.Click += new System.EventHandler(this.автопоискToolStripMenuItem_Click);
            // 
            // удалитьToolStripMenuItem
            // 
            this.удалитьToolStripMenuItem.Name = "удалитьToolStripMenuItem";
            this.удалитьToolStripMenuItem.Size = new System.Drawing.Size(156, 22);
            this.удалитьToolStripMenuItem.Text = "Удалить";
            this.удалитьToolStripMenuItem.Visible = false;
            // 
            // webBrowser1
            // 
            this.webBrowser1.Location = new System.Drawing.Point(463, 48);
            this.webBrowser1.MinimumSize = new System.Drawing.Size(20, 20);
            this.webBrowser1.Name = "webBrowser1";
            this.webBrowser1.Size = new System.Drawing.Size(250, 250);
            this.webBrowser1.TabIndex = 3;
            this.webBrowser1.Url = new System.Uri("", System.UriKind.Relative);
            this.webBrowser1.Visible = false;
            this.webBrowser1.DocumentCompleted += new System.Windows.Forms.WebBrowserDocumentCompletedEventHandler(this.webBrowser1_DocumentCompleted);
            // 
            // timer1
            // 
            this.timer1.Interval = 5000;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // notifyIcon1
            // 
            this.notifyIcon1.Icon = ((System.Drawing.Icon)(resources.GetObject("notifyIcon1.Icon")));
            this.notifyIcon1.Text = "Michom console";
            this.notifyIcon1.Visible = true;
            this.notifyIcon1.Click += new System.EventHandler(this.notifyIcon1_MouseClick);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label2.Location = new System.Drawing.Point(8, 525);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(178, 20);
            this.label2.TabIndex = 4;
            this.label2.Text = "Отправить команду";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Bold);
            this.label3.Location = new System.Drawing.Point(396, 525);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(35, 24);
            this.label3.TabIndex = 7;
            this.label3.Text = "На";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(670, 525);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(165, 21);
            this.button1.TabIndex = 8;
            this.button1.Text = "Отправить";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // comboBox1
            // 
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Location = new System.Drawing.Point(451, 525);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(194, 21);
            this.comboBox1.TabIndex = 9;
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(255)))), ((int)(((byte)(255)))));
            this.panel1.Controls.Add(this.label6);
            this.panel1.Controls.Add(this.label5);
            this.panel1.Controls.Add(this.label4);
            this.panel1.Controls.Add(this.label1);
            this.panel1.Location = new System.Drawing.Point(315, 210);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(231, 122);
            this.panel1.TabIndex = 10;
            this.panel1.Visible = false;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(107, 39);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(13, 13);
            this.label6.TabIndex = 3;
            this.label6.Text = "0";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(107, 11);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(13, 13);
            this.label5.TabIndex = 2;
            this.label5.Text = "0";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(13, 39);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(63, 13);
            this.label4.TabIndex = 1;
            this.label4.Text = "Влажность";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(13, 11);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(74, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Температура";
            // 
            // comboBox2
            // 
            this.comboBox2.FormattingEnabled = true;
            this.comboBox2.Items.AddRange(new object[] {
            "refresh",
            "setlight",
            "getlight",
            "calling",
            "restart",
            "getid"});
            this.comboBox2.Location = new System.Drawing.Point(192, 525);
            this.comboBox2.Name = "comboBox2";
            this.comboBox2.Size = new System.Drawing.Size(183, 21);
            this.comboBox2.TabIndex = 11;
            // 
            // backgroundWorker2
            // 
            this.backgroundWorker2.WorkerReportsProgress = true;
            this.backgroundWorker2.WorkerSupportsCancellation = true;
            this.backgroundWorker2.DoWork += new System.ComponentModel.DoWorkEventHandler(this.backgroundWorker2_DoWork);
            // 
            // serialPort1
            // 
            this.serialPort1.BaudRate = 115200;
            // 
            // backgroundWorker3
            // 
            this.backgroundWorker3.WorkerReportsProgress = true;
            this.backgroundWorker3.WorkerSupportsCancellation = true;
            this.backgroundWorker3.DoWork += new System.ComponentModel.DoWorkEventHandler(this.backgroundWorker3_DoWork);
            // 
            // backgroundWorker4
            // 
            this.backgroundWorker4.DoWork += new System.ComponentModel.DoWorkEventHandler(this.backgroundWorker4_DoWork);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(847, 565);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.comboBox2);
            this.Controls.Add(this.comboBox1);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.richTextBox1);
            this.Controls.Add(this.menuStrip1);
            this.Controls.Add(this.webBrowser1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form1";
            this.Text = "Michom Console";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Closing);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.ComponentModel.BackgroundWorker backgroundWorker1;
        private System.Windows.Forms.RichTextBox richTextBox1;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem michomToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem отладкаToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem выходToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem звонокToolStripMenuItem;
        private System.Windows.Forms.WebBrowser webBrowser1;
        private System.Windows.Forms.Timer timer1;
        public System.Windows.Forms.NotifyIcon notifyIcon1;
        private System.Windows.Forms.ToolStripMenuItem неБеспокоитьToolStripMenuItem;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.ToolStripMenuItem дзыыньToolStripMenuItem;
        private System.Windows.Forms.ComboBox comboBox1;
        private System.Windows.Forms.ToolStripMenuItem отчистьтьКонсольToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem погодаToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem значнияПогодыToolStripMenuItem;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox comboBox2;
        private System.Windows.Forms.ToolStripMenuItem cOMВзаимодействиеToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem портToolStripMenuItem;
        private System.Windows.Forms.ToolStripTextBox toolStripTextBox1;
        private System.Windows.Forms.ToolStripMenuItem соединениеToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem устройстваToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem добавитьПоIpToolStripMenuItem;
        private System.Windows.Forms.ToolStripTextBox toolStripTextBox2;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripMenuItem добавитьToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem автопоискToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem удалитьToolStripMenuItem;
        private System.ComponentModel.BackgroundWorker backgroundWorker2;
        private System.IO.Ports.SerialPort serialPort1;
        private System.ComponentModel.BackgroundWorker backgroundWorker3;
        private System.Windows.Forms.ToolStripMenuItem скоростьToolStripMenuItem;
        private System.Windows.Forms.ToolStripTextBox toolStripTextBox3;
        private System.Windows.Forms.ToolStripMenuItem бодToolStripMenuItem;
        private System.ComponentModel.BackgroundWorker backgroundWorker4;
    }
}

