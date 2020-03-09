using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

/// <summary>
/// Класс статичных модулей
/// </summary>
namespace michomeframework.Modules.StaticController
{
    /// <summary>
    /// Клас модуля освещенности
    /// </summary>
    public class LightModule : Module
    {
        
        /// <summary>
        /// Максимальная яркость
        /// </summary>
        public short MaxDur
        {
            get
            {
                return 1023;
            }
        }
        /// <summary>
        /// Минимальная яркость
        /// </summary>
        public short MinDur
        {
            get
            {
                return 0;
            }
        }
        /// <summary>
        /// Количество выходов (нумерация с 0)
        /// </summary>
        public byte MaxOutputs
        {
            get
            {
                return 2;
            }
        }
        
        /// <summary>
        /// Тип модуля в сети 
        /// </summary>
        public static string ModuleID
        {
            get
            {
                return "StudioLight";
            }
        }   
        
        /// <summary>
        /// Вазвращает случайный канал света
        /// </summary>
        public static byte RandomChanel
        {
            get
            {
                Random rnd = new Random();
                return (byte)rnd.Next(0, 3);
            }
        }

        /// <summary>
        /// Объявление класса
        /// </summary>
        /// <param name="ip">Адрес модуля</param>
        /// <param name="type">Тип соеденения</param>
        public LightModule(string ip, Gateway.TypeConnect type) : base()
        {
            IP = ip;
            TypeConnect = type;
        }

        /// <summary>
        /// Отправить IR код
        /// </summary>
        /// <param name="code">Код</param>
        public void SendIR(string code) => Gateway.SetData(IP, "ir?code=" + code);

        /// <summary>
        /// Установить освещенность
        /// </summary>
        /// <param name="pin">Пин</param>
        /// <param name="duration">Яркость</param>
        public void SetLight(byte pin, short duration)
        {
            if (TypeConnect == Gateway.TypeConnect.HTTP)
            {
                var Req = String.Format("setlight?p={0}&d={1}", pin, duration);
                Gateway.SetData(IP, Req);
            }
            else if (TypeConnect == Gateway.TypeConnect.Telnet)
            {
                var Req = String.Format("setlight;{0};{1};;;", pin, duration);
                SendTelnet(Req);
            }
            //System.Threading.Thread.Sleep(50);
        }
        /// <summary>
        /// Установить освещенность всех пинов
        /// </summary>
        /// <param name="duration">Яркость</param>
        public void SetLightAll(short duration)
        {
            if (TypeConnect == Gateway.TypeConnect.HTTP)
            {
                var Req = String.Format("setlightall?p={0}", duration);
                Gateway.SetData(IP, Req);
            }
            else if (TypeConnect == Gateway.TypeConnect.Telnet)
            {
                var Req = String.Format("setlightall;{0};;;;;", duration);
                SendTelnet(Req);
            }
            //System.Threading.Thread.Sleep(50);
        }
        /// <summary>
        /// Стробоскоп
        /// </summary>
        /// <param name="pin">Пин</param>
        /// <param name="col">Количество</param>
        /// <param name="delay">Пауза</param>
        public void Strobo(byte pin, int col, int delay)
        {

            if (TypeConnect == Gateway.TypeConnect.HTTP) { var Req = String.Format("strobo?p={0}&c={1}&d={2}", pin, col, delay); Gateway.SetData(IP, Req); }
            else if (TypeConnect == Gateway.TypeConnect.Telnet) { var Req = String.Format("strobo;{0};{1};{2};;", pin, col, delay); SendTelnet(Req); }
            //System.Threading.Thread.Sleep(100);
        }
        /// <summary>
        /// Стробоскоп все
        /// </summary>
        /// <param name="col">Количество</param>
        /// <param name="delay">Пауза</param>
        public void StroboAll(int col, int delay)
        {

            if (TypeConnect == Gateway.TypeConnect.HTTP) { var Req = String.Format("stroboall?&c={0}&d={1}", col, delay); Gateway.SetData(IP, Req); }
            else if (TypeConnect == Gateway.TypeConnect.Telnet) { var Req = String.Format("stroboall;{0};{1};;;", col, delay); SendTelnet(Req); }
            //System.Threading.Thread.Sleep(50);
        }
        /// <summary>
        /// Расширенный стробоскоп
        /// </summary>
        /// <param name="pin">Пин</param>
        /// <param name="col">Количество</param>
        /// <param name="delay">Пауза горения</param>
        /// <param name="delay1">Пауза тишины</param>
        public void StroboPro(byte pin, int col, int delay, int delay1)
        {

            if (TypeConnect == Gateway.TypeConnect.HTTP) { var Req = String.Format("strobopro?p={0}&c={1}&d={2}&w={3}", pin, col, delay, delay1); Gateway.SetData(IP, Req); }
            else if (TypeConnect == Gateway.TypeConnect.Telnet) { var Req = String.Format("strobopro;{0};{1};{2};{3};", pin, col, delay, delay1); SendTelnet(Req); }
            //System.Threading.Thread.Sleep(100);
        }
        /// <summary>
        /// Расширенный стробоскоп всех
        /// </summary>
        /// <param name="col">Количество</param>
        /// <param name="delay">Пауза горения</param>
        /// <param name="delay1">Пауза тишины</param>
        public void StroboAllPro(int col, int delay, int delay1)
        {

            if (TypeConnect == Gateway.TypeConnect.HTTP) { var Req = String.Format("stroboallpro?&c={0}&d={1}&w={2}", col, delay, delay1); Gateway.SetData(IP, Req); }
            else if (TypeConnect == Gateway.TypeConnect.Telnet)
            {
                var Req = String.Format("strobo;{0};{1};{2};;", col, delay, delay1);
                SendTelnet(Req);
            }
            //System.Threading.Thread.Sleep(100);
        }
    }
}
