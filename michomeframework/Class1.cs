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

        public Image Getimage(string type)
        {
            Image img;
            request = WebRequest.Create("http://" + ip + "/michome/grafick.php?type=" + type);
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

        public string[] Getdeviceip()
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

            JObject obj = JObject.Parse(text);
            //MessageBox.Show(obj["barcode"].ToString());
            //string[] mas = { obj["barcode"].ToString(), obj["statys"].ToString(), obj["poluk"]["index"].ToString(), obj["poluk"]["name"].ToString(), obj["typeot"].ToString(), obj["massa"].ToString(), obj["user"]["ot"].ToString(), obj["user"]["do"].ToString() };
            string[] nums = new string[(Int32)obj["col"]];

            for (int i = 0; i < (Int32)obj["col"]; i++)
            {
                nums[i] = obj["ips"][i].ToString();
            }
            return nums;
        }
        public string[] Getdevicename()
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

            JObject obj = JObject.Parse(text);
            //MessageBox.Show(obj["barcode"].ToString());
            //string[] mas = { obj["barcode"].ToString(), obj["statys"].ToString(), obj["poluk"]["index"].ToString(), obj["poluk"]["name"].ToString(), obj["typeot"].ToString(), obj["massa"].ToString(), obj["user"]["ot"].ToString(), obj["user"]["do"].ToString() };
            string[] nums = new string[(Int32)obj["col"]];

            for (int i = 0; i < (Int32)obj["col"]; i++)
            {
                nums[i] = obj["devicename"][i].ToString();
            }
            return nums;
        }
        public string[] Getdevicetype()
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

            JObject obj = JObject.Parse(text);
            //MessageBox.Show(obj["barcode"].ToString());
            //string[] mas = { obj["barcode"].ToString(), obj["statys"].ToString(), obj["poluk"]["index"].ToString(), obj["poluk"]["name"].ToString(), obj["typeot"].ToString(), obj["massa"].ToString(), obj["user"]["ot"].ToString(), obj["user"]["do"].ToString() };
            string[] nums = new string[(Int32)obj["col"]];

            for (int i = 0; i < (Int32)obj["col"]; i++)
            {
                nums[i] = obj["devicetype"][i].ToString();
            }
            return nums;
        }
    }
}
