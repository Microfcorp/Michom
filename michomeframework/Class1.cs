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

        public void Connect(string Gatewayip)
        {
            ip = Gatewayip;
        }

        public void Disconnect()
        {
            request = null;
        }
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
        public string Setdata(string device, string data)
        {
            request = WebRequest.Create("http://" + ip + "/michome/api/getdata.php?device=" + device + "&cmd=" + data);
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
                    tmp[i] = new NameAndID();
                    tmp[i].Name = obj["devicename"][i].ToString();
                    tmp[i].ID = obj["devicetype"][i].ToString();
                    tmp[i].IP = obj["ips"][i].ToString();
                }
                return tmp;
            }
            return new NameAndID[0];
        }

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

        public TimeInsSelDay TimeInsCurDay(string device = "0")
        {
            return TimeIns(TimeInsType.SelDay, DateTime.Now.Year.ToString() + "-" + DateTime.Now.Month.ToString() + "-" + DateTime.Now.Day.ToString(), device);
        }
    }
    static public class TimeInsType
    {
        public static string OneDay
        {
            get { return "oneday"; }
        }
        public static string SelDay
        {
            get { return "selday"; }
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
        public int Col
        {
            get;
            internal set;
        }
        public int Max
        {
            get;
            internal set;
        }
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
        public string Name
        {
            get;
            internal set;
        }
        public string ID
        {
            get;
            internal set;
        }
        public string IP
        {
            get;
            internal set;
        }
    }
}
