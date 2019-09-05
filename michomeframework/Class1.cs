using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;
using Newtonsoft.Json.Linq;
using System.Threading.Tasks;
using System.IO;
using System.Drawing;

namespace michomeframework
{
    public class Gateway
    {
        WebRequest request;
        private string ip = null;

        /// <summary>
        /// Подключение к шлюзу
        /// </summary>
        /// <param name="Gatewayip">Адрес шлюза</param>
        public void Connect(string Gatewayip)
        {
            ip = Gatewayip;
        }

        /// <summary>
        /// Отключение от шлюза
        /// </summary>
        public void Disconnect()
        {
            request = null;
        }
        /// <summary>
        /// Запрос данных
        /// </summary>
        /// <param name="device">Адрес модуля</param>
        /// <param name="type">Тип данных</param>
        /// <returns></returns>
        public string Getdata(string device, string type)
        {
            request = WebRequest.Create("http://" + ip + "/michome/api/getdata.php?device=" + device + "&cmd=" + type);
            string text = "";
            if (request != null)
            {
                WebResponse response = request.GetResponse();
                using (Stream stream = response.GetResponseStream())
                {
                    using (StreamReader reader = new StreamReader(stream))
                    {
                        string line = "";

                        while ((line = reader.ReadLine()) != null)
                        {
                            text += line;
                        }

                    }
                }
                response.Close();
            }
            else
            {
                throw new System.InvalidOperationException("Не было произведено подключение к серверу");
            }
            return text;
        }
        /// <summary>
        /// Отправить данные на модуль
        /// </summary>
        /// <param name="device">Адрес модуля</param>
        /// <param name="data">Данные</param>
        /// <returns></returns>
        public string Setdata(string device, string data)
        {
            request = WebRequest.Create("http://" + ip + "/michome/api/setcmd.php?device=" + device + "&cmd=" + data.Replace("&", "%26"));
            string text = "";
            if (request != null)
            {
                WebResponse response = request.GetResponse();
                using (Stream stream = response.GetResponseStream())
                {
                    using (StreamReader reader = new StreamReader(stream))
                    {
                        string line = "";

                        while ((line = reader.ReadLine()) != null)
                        {
                            text += line;
                        }

                    }
                }
                response.Close();
            }
            else
            {
                throw new System.InvalidOperationException("Не было произведено подключение к серверу");
            }
            return text;
        }

        /// <summary>
        /// Отправить данные на модуль
        /// </summary>
        /// <param name="device">Адрес модуля</param>
        /// <param name="data">Данные</param>
        /// <param name="page">Страница модуля</param>
        /// <returns></returns>
        public string Setdata(string device, SortedList<string, string> data, string page)
        {
            string dat = "";

            foreach (var item in data)
            {
                dat += item.Key.Replace("&", "%26") + "=" + item.Value.Replace("&", "%26") + "&";
            }

            request = WebRequest.Create("http://" + ip + "/michome/api/setdata.php?device=" + device + "&cmd=" + page + "?" + dat);
            string text = "";
            if (request != null)
            {
                WebResponse response = request.GetResponse();
                using (Stream stream = response.GetResponseStream())
                {
                    using (StreamReader reader = new StreamReader(stream))
                    {
                        string line = "";

                        while ((line = reader.ReadLine()) != null)
                        {
                            text += line;
                        }

                    }
                }
                response.Close();
            }
            else
            {
                throw new System.InvalidOperationException("Не было произведено подключение к серверу");
            }
            return text;
        }

        #region Получение графиков
        /// <summary>
        /// Получить график
        /// </summary>
        /// <param name="type">Тип данных</param>
        /// <param name="period">Количество измерений</param>
        /// <param name="start">Начальная точка отсчета</param>
        /// <returns></returns>
        public Image Getimage(string type, int period, int start)
        {
            Image img;
            request = WebRequest.Create(string.Format("http://" + ip + "/michome/grafick.php?type={0}&period={1}&start={2}",type,period,start));
            //string text = "";
            if (request != null)
            {
                WebResponse response = request.GetResponse();
                using (Stream stream = response.GetResponseStream())
                {
                    img = Image.FromStream(stream);

                }
                response.Close();
            }
            else
            {
                throw new System.InvalidOperationException("Не было произведено подключение к серверу");
            }
            

            return img;
        }
        /// <summary>
        /// Получить график
        /// </summary>
        /// <param name="type">Тип данных</param>
        /// <param name="period">Количество измерений</param>
        /// <param name="start">Начальная точка отсчета</param>
        /// <param name="ips">Адрес модуля</param>
        /// <returns></returns>
        public Image Getimage(string type, int period, int start, string ips)
        {
            Image img;
            request = WebRequest.Create(string.Format("http://" + ip + "/michome/grafick.php?type={0}&period={1}&start={2}&ip={3}", type, period, start, ips));
            //string text = "";
            if (request != null)
            {
                WebResponse response = request.GetResponse();
                using (Stream stream = response.GetResponseStream())
                {
                    img = Image.FromStream(stream);

                }
                response.Close();
            }
            else
            {
                throw new System.InvalidOperationException("Не было произведено подключение к серверу");
            }


            return img;
        }
        /// <summary>
        /// Получить график
        /// </summary>
        /// <param name="type">Тип данных</param>
        /// <param name="period">Количество измерений</param>
        /// <param name="ips">Адрес модуля</param>
        /// <returns></returns>
        public Image Getimage(string type, int period, string ips)
        {
            Image img;
            request = WebRequest.Create(string.Format("http://" + ip + "/michome/grafick.php?type={0}&period={1}&ip={2}", type, period, ips));
            //string text = "";
            if (request != null)
            {
                WebResponse response = request.GetResponse();
                using (Stream stream = response.GetResponseStream())
                {
                    img = Image.FromStream(stream);

                }
                response.Close();
            }
            else
            {
                throw new System.InvalidOperationException("Не было произведено подключение к серверу");
            }


            return img;
        }
        /// <summary>
        /// Получить график
        /// </summary>
        /// <param name="type">Тип данных</param>
        /// <param name="period">Количество измерений</param>
        /// <returns></returns>
        public Image Getimage(string type, int period)
        {
            Image img;
            request = WebRequest.Create(string.Format("http://" + ip + "/michome/grafick.php?type={0}&period={1}", type, period));
            //string text = "";
            if (request != null)
            {
                WebResponse response = request.GetResponse();
                using (Stream stream = response.GetResponseStream())
                {
                    img = Image.FromStream(stream);

                }
                response.Close();
            }
            else
            {
                throw new System.InvalidOperationException("Не было произведено подключение к серверу");
            }


            return img;
        }

        #endregion

        /// <summary>
        /// Получить список всех устройств в сети
        /// </summary>
        /// <returns></returns>
        public NameAndID[] GetDevice()
        {
            request = WebRequest.Create("http://" + ip + "/michome/api/getdevice.php");
            string text = "";
            if (request != null)
            {
                WebResponse response = request.GetResponse();
                using (Stream stream = response.GetResponseStream())
                {
                    using (StreamReader reader = new StreamReader(stream))
                    {
                        string line = "";

                        while ((line = reader.ReadLine()) != null)
                        {
                            text += line;
                        }

                    }
                }
                response.Close();
            }
            else
            {
                throw new System.InvalidOperationException("Не было произведено подключение к серверу");
            }

            if (!text.StartsWith("<"))
            {
                JObject obj = JObject.Parse(text);
                NameAndID[] tmp = new NameAndID[(Int32)obj["col"]];

                for (int i = 0; i < (Int32)obj["col"]; i++)
                {
                    tmp[i] = new NameAndID
                    {
                        Name = obj["devicename"][i].ToString(),
                        ID = obj["devicetype"][i].ToString(),
                        IP = obj["ips"][i].ToString()
                    };
                }
                return tmp;
            }
            return new NameAndID[0];
        }

        /// <summary>
        /// Получить временной промежуток
        /// </summary>
        /// <param name="type">Тип промежутка</param>
        /// <param name="device">Адрес модуля</param>
        /// <returns></returns>
        public string TimeIns(string type, string device = "0")
        {
            request = WebRequest.Create(string.Format("http://" + ip + "/michome/api/timeins.php?device={0}&type={1}", device, type));
            string text = "";
            if (request != null)
            {
                WebResponse response = request.GetResponse();
                using (Stream stream = response.GetResponseStream())
                {
                    using (StreamReader reader = new StreamReader(stream))
                    {
                        string line = "";

                        while ((line = reader.ReadLine()) != null)
                        {
                            text += line;
                        }

                    }
                }
                response.Close();
            }
            else
            {
                throw new System.InvalidOperationException("Не было произведено подключение к серверу");
            }
            return text;
        }
        /// <summary>
        /// Получить временной промежуток
        /// </summary>
        /// <param name="type">Тип промежутка</param>
        /// <param name="date">Начальная дата</param>
        /// <param name="device">Адрес модуля</param>
        /// <returns></returns>
        public TimeInsSelDay TimeIns(string type, string date, string device = "0")
        {
            request = WebRequest.Create(string.Format("http://" + ip + "/michome/api/timeins.php?device={0}&type={1}&date={2}", device, type, date));
            string text = "";
            if (request != null)
            {
                WebResponse response = request.GetResponse();
                using (Stream stream = response.GetResponseStream())
                {
                    using (StreamReader reader = new StreamReader(stream))
                    {
                        string line = "";

                        while ((line = reader.ReadLine()) != null)
                        {
                            text += line;
                        }

                    }
                }
                response.Close();
            }
            else
            {
                throw new System.InvalidOperationException("Не было произведено подключение к серверу");
            }
            string[] tmp = text.Split(';');
            return new TimeInsSelDay(Convert.ToInt32(tmp[2]), Convert.ToInt32(tmp[1]), Convert.ToInt32(tmp[0]));
        }

        /// <summary>
        /// Получить данный за текущие сутки
        /// </summary>
        /// <param name="device">Адрес модуля</param>
        /// <returns></returns>
        public TimeInsSelDay TimeInsCurDay(string device = "0")
        {
            return TimeIns(TimeInsType.SelDay, DateTime.Now.Year.ToString() + "-" + DateTime.Now.Month.ToString() + "-" + DateTime.Now.Day.ToString(), device);
        }

        /// <summary>
        /// Отправить IR комманду
        /// </summary>
        /// <param name="device">Адрес модуля</param>
        /// <param name="code">Код</param>
        /// <returns></returns>
        public string SendIRCode(string device, string code)
        {
            return Setdata(device, "ir?code=" + code);
        }
    }
    static public class TimeInsType
    {
        /// <summary>
        /// Текущие сутки
        /// </summary>
        public static string OneDay
        {
            get { return "oneday"; }
        }
        /// <summary>
        /// Выбранная дата
        /// </summary>
        public static string SelDay
        {
            get { return "selday"; }
        }
        /// <summary>
        /// Диапазон дат
        /// </summary>
        public static string Deap
        {
            get { return "diap"; }
        }
    }
    public class TimeInsSelDay
    {
        internal TimeInsSelDay(int Col, int Max, int Min)
        {
            this.Col = Col;
            this.Max = Max;
            this.Min = Min;
        }
        /// <summary>
        /// Количество данных
        /// </summary>
        public int Col
        {
            get;
            internal set;
        }
        /// <summary>
        /// Конечная точка
        /// </summary>
        public int Max
        {
            get;
            internal set;
        }
        /// <summary>
        /// Начальная точка
        /// </summary>
        public int Min
        {
            get;
            internal set;
        }
    }
    public class NameAndID
    {
        internal NameAndID()
        {

        }
        /// <summary>
        /// Название модуля
        /// </summary>
        public string Name
        {
            get;
            internal set;
        }
        /// <summary>
        /// ID Модуля
        /// </summary>
        public string ID
        {
            get;
            internal set;
        }
        /// <summary>
        /// Адрес модуля
        /// </summary>
        public string IP
        {
            get;
            internal set;
        }
    }
}
