using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace michomeframework.Modules.StaticController
{
    public class Module
    {
        /// <summary>
        /// Адрес модуля
        /// </summary>
        public string IP
        {
            get;
            set;
        }
        /// <summary>
        /// Установлен ли IP адрес 
        /// </summary>
        public bool IsIP
        {
            get
            {
                return (IP != null) & (IP != "");
            }
        }
        /// <summary>
        /// Использование параллельного Telnet
        /// </summary>
        public bool IsPharallelTelnet
        {
            get;
            set;
        }
        /// <summary>
        /// Тип соеденения
        /// </summary>
        public Gateway.TypeConnect TypeConnect
        {
            get;
            set;
        }

        /// <summary>
        /// Инициализация базового класса Модуля
        /// </summary>
        public Module()
        {
            IsPharallelTelnet = false;
        }

        private Thread fft = new Thread(new ParameterizedThreadStart(thread));

        private static void thread(object sender)
        {
            try
            {
                var s = sender as EventArgsParam;
                Gateway.SendTelnet(s.address, s.message, s.port);
            }
            catch { }
        }

        private class EventArgsParam
        {
            public String address;
            public String message;
            public Int32 port;
            public EventArgsParam(String address, String message, Int32 port = 23)
            {
                this.address = address;
                this.message = message;
                this.port = port;
            }
        }

        /// <summary>
        /// Отправить Telnet запрос
        /// </summary>
        /// <param name="message">Сообщение</param>
        /// <param name="port">Порт</param>
        public void SendTelnet(String message, Int32 port = 23)
        {
            if (!IsIP)
                return;

            if (IsPharallelTelnet)
                SendParallelTelnet(IP, message, port);
            else
                Gateway.SendTelnet(IP, message, port);
        }

        /// <summary>
        /// Отправить параллельный Telnet запрос на модуль
        /// </summary>
        /// <param name="address">Адрес</param>
        /// <param name="message">Сообщение</param>
        /// <param name="port">Порт</param>
        public void SendParallelTelnet(String address, String message, Int32 port = 23)
        {                       
            if(fft.IsAlive)
                fft.Abort();
            if (!fft.IsAlive)
            {
                fft = new Thread(new ParameterizedThreadStart(thread));
                fft.Start(new EventArgsParam(address, message, port));
                fft.IsBackground = true;
            }
        }
    }
}
