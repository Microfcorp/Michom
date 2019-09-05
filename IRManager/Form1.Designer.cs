namespace IRManager
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
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.типПультаToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.настройкиToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.адресШлюзаToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripTextBox1 = new System.Windows.Forms.ToolStripTextBox();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.переподключитьсяToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.сабвуферToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.автоматическоеПодключениеToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.даToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.нетToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.notifyIcon1 = new System.Windows.Forms.NotifyIcon(this.components);
            this.contextMenuStrip1 = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.toolStripMenuItem2 = new System.Windows.Forms.ToolStripMenuItem();
            this.входToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.режимToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.громчеToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.тишеToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.развернутьToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.выходToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.contextMenuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.типПультаToolStripMenuItem,
            this.настройкиToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(279, 24);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // типПультаToolStripMenuItem
            // 
            this.типПультаToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.сабвуферToolStripMenuItem});
            this.типПультаToolStripMenuItem.Name = "типПультаToolStripMenuItem";
            this.типПультаToolStripMenuItem.Size = new System.Drawing.Size(80, 20);
            this.типПультаToolStripMenuItem.Text = "Тип пульта";
            // 
            // настройкиToolStripMenuItem
            // 
            this.настройкиToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.адресШлюзаToolStripMenuItem,
            this.автоматическоеПодключениеToolStripMenuItem,
            this.toolStripSeparator1,
            this.переподключитьсяToolStripMenuItem});
            this.настройкиToolStripMenuItem.Name = "настройкиToolStripMenuItem";
            this.настройкиToolStripMenuItem.Size = new System.Drawing.Size(79, 20);
            this.настройкиToolStripMenuItem.Text = "Настройки";
            // 
            // адресШлюзаToolStripMenuItem
            // 
            this.адресШлюзаToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripTextBox1});
            this.адресШлюзаToolStripMenuItem.Name = "адресШлюзаToolStripMenuItem";
            this.адресШлюзаToolStripMenuItem.Size = new System.Drawing.Size(244, 22);
            this.адресШлюзаToolStripMenuItem.Text = "Адрес шлюза";
            // 
            // toolStripTextBox1
            // 
            this.toolStripTextBox1.Name = "toolStripTextBox1";
            this.toolStripTextBox1.Size = new System.Drawing.Size(100, 23);
            this.toolStripTextBox1.Text = "192.168.1.42";
            this.toolStripTextBox1.TextChanged += new System.EventHandler(this.ToolStripTextBox1_TextChanged);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(241, 6);
            // 
            // переподключитьсяToolStripMenuItem
            // 
            this.переподключитьсяToolStripMenuItem.Name = "переподключитьсяToolStripMenuItem";
            this.переподключитьсяToolStripMenuItem.Size = new System.Drawing.Size(244, 22);
            this.переподключитьсяToolStripMenuItem.Text = "Подключиться";
            this.переподключитьсяToolStripMenuItem.Click += new System.EventHandler(this.ПереподключитьсяToolStripMenuItem_Click);
            // 
            // pictureBox1
            // 
            this.pictureBox1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pictureBox1.Image = global::IRManager.Properties.Resources.rc58;
            this.pictureBox1.Location = new System.Drawing.Point(0, 24);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(279, 426);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox1.TabIndex = 1;
            this.pictureBox1.TabStop = false;
            this.pictureBox1.MouseDown += new System.Windows.Forms.MouseEventHandler(this.PictureBox1_MouseDown);
            // 
            // сабвуферToolStripMenuItem
            // 
            this.сабвуферToolStripMenuItem.Name = "сабвуферToolStripMenuItem";
            this.сабвуферToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.сабвуферToolStripMenuItem.Text = "Сабвуфер";
            this.сабвуферToolStripMenuItem.Click += new System.EventHandler(this.СабвуферToolStripMenuItem_Click);
            // 
            // автоматическоеПодключениеToolStripMenuItem
            // 
            this.автоматическоеПодключениеToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.даToolStripMenuItem,
            this.нетToolStripMenuItem});
            this.автоматическоеПодключениеToolStripMenuItem.Name = "автоматическоеПодключениеToolStripMenuItem";
            this.автоматическоеПодключениеToolStripMenuItem.Size = new System.Drawing.Size(244, 22);
            this.автоматическоеПодключениеToolStripMenuItem.Text = "Автоматическое подключение";
            // 
            // даToolStripMenuItem
            // 
            this.даToolStripMenuItem.Name = "даToolStripMenuItem";
            this.даToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.даToolStripMenuItem.Text = "Да";
            this.даToolStripMenuItem.Click += new System.EventHandler(this.ДаToolStripMenuItem_Click);
            // 
            // нетToolStripMenuItem
            // 
            this.нетToolStripMenuItem.Checked = true;
            this.нетToolStripMenuItem.CheckState = System.Windows.Forms.CheckState.Checked;
            this.нетToolStripMenuItem.Name = "нетToolStripMenuItem";
            this.нетToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.нетToolStripMenuItem.Text = "Нет";
            this.нетToolStripMenuItem.Click += new System.EventHandler(this.НетToolStripMenuItem_Click);
            // 
            // notifyIcon1
            // 
            this.notifyIcon1.ContextMenuStrip = this.contextMenuStrip1;
            this.notifyIcon1.Icon = ((System.Drawing.Icon)(resources.GetObject("notifyIcon1.Icon")));
            this.notifyIcon1.Text = "notifyIcon1";
            this.notifyIcon1.Visible = true;
            this.notifyIcon1.DoubleClick += new System.EventHandler(this.NotifyIcon1_DoubleClick);
            // 
            // contextMenuStrip1
            // 
            this.contextMenuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripMenuItem2,
            this.входToolStripMenuItem,
            this.режимToolStripMenuItem,
            this.громчеToolStripMenuItem,
            this.тишеToolStripMenuItem,
            this.toolStripSeparator2,
            this.развернутьToolStripMenuItem,
            this.выходToolStripMenuItem});
            this.contextMenuStrip1.Name = "contextMenuStrip1";
            this.contextMenuStrip1.Size = new System.Drawing.Size(136, 164);
            this.contextMenuStrip1.Text = "RC-58";
            // 
            // toolStripMenuItem2
            // 
            this.toolStripMenuItem2.Name = "toolStripMenuItem2";
            this.toolStripMenuItem2.Size = new System.Drawing.Size(180, 22);
            this.toolStripMenuItem2.Text = "Включить";
            this.toolStripMenuItem2.Click += new System.EventHandler(this.ToolStripMenuItem2_Click);
            // 
            // входToolStripMenuItem
            // 
            this.входToolStripMenuItem.Name = "входToolStripMenuItem";
            this.входToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.входToolStripMenuItem.Text = "Вход";
            this.входToolStripMenuItem.Click += new System.EventHandler(this.ВходToolStripMenuItem_Click);
            // 
            // режимToolStripMenuItem
            // 
            this.режимToolStripMenuItem.Name = "режимToolStripMenuItem";
            this.режимToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.режимToolStripMenuItem.Text = "Режим";
            this.режимToolStripMenuItem.Click += new System.EventHandler(this.РежимToolStripMenuItem_Click);
            // 
            // громчеToolStripMenuItem
            // 
            this.громчеToolStripMenuItem.Name = "громчеToolStripMenuItem";
            this.громчеToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.громчеToolStripMenuItem.Text = "Громче";
            this.громчеToolStripMenuItem.Click += new System.EventHandler(this.ГромчеToolStripMenuItem_Click);
            // 
            // тишеToolStripMenuItem
            // 
            this.тишеToolStripMenuItem.Name = "тишеToolStripMenuItem";
            this.тишеToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.тишеToolStripMenuItem.Text = "Тише";
            this.тишеToolStripMenuItem.Click += new System.EventHandler(this.ТишеToolStripMenuItem_Click);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(177, 6);
            // 
            // развернутьToolStripMenuItem
            // 
            this.развернутьToolStripMenuItem.Name = "развернутьToolStripMenuItem";
            this.развернутьToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.развернутьToolStripMenuItem.Text = "Развернуть";
            this.развернутьToolStripMenuItem.Click += new System.EventHandler(this.Open);
            // 
            // выходToolStripMenuItem
            // 
            this.выходToolStripMenuItem.Name = "выходToolStripMenuItem";
            this.выходToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.выходToolStripMenuItem.Text = "Выход";
            this.выходToolStripMenuItem.Click += new System.EventHandler(this.Clos);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(279, 450);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.menuStrip1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form1";
            this.Text = "IRManager";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.Resize += new System.EventHandler(this.Form1_Resize);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.contextMenuStrip1.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem типПультаToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem настройкиToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem адресШлюзаToolStripMenuItem;
        private System.Windows.Forms.ToolStripTextBox toolStripTextBox1;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem переподключитьсяToolStripMenuItem;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.ToolStripMenuItem сабвуферToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem автоматическоеПодключениеToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem даToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem нетToolStripMenuItem;
        private System.Windows.Forms.NotifyIcon notifyIcon1;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip1;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem2;
        private System.Windows.Forms.ToolStripMenuItem входToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem режимToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem громчеToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem тишеToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripMenuItem развернутьToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem выходToolStripMenuItem;
    }
}

