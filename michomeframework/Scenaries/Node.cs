using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace michomeframework.Scenaries
{
    /// <summary>
    /// Один сценарий
    /// </summary>
    public struct SceneNode
    {
        /// <summary>
        /// ID сценария
        /// </summary>
        public uint ID;
        /// <summary>
        /// Название сценария
        /// </summary>
        public string Name;
        /// <summary>
        /// Время начала выполнения
        /// </summary>
        public DateTime StartTime;
        /// <summary>
        /// Время окончания выполнения
        /// </summary>
        public DateTime EndTime;
        /// <summary>
        /// Модуль
        /// </summary>
        public string Modules;
        /// <summary>
        /// Отправлять во время выполнения
        /// </summary>
        public string SendThen;
        /// <summary>
        /// Отправлять по окончанию выполнения
        /// </summary>
        public string SendEnd;
        /// <summary>
        /// Время последней отправки
        /// </summary>
        public DateTime CSE;
        /// <summary>
        /// Тайм-аут отправки
        /// </summary>
        public int Timeout;
        /// <summary>
        /// Включен ли
        /// </summary>
        public bool Enable;
        /// <summary>
        /// Время начала рассвета
        /// </summary>
        public string DateSunrise;
        /// <summary>
        /// Время начала заката
        /// </summary>
        public string DateSunset;

        public SceneNode(uint iD, string name, DateTime startTime, DateTime endTime, string modules, string sendThen, string sendEnd, DateTime cse, int timeout, bool enable, string st, string se)
        {
            ID = iD;
            Name = name;
            StartTime = startTime;
            EndTime = endTime;
            Modules = modules;
            SendThen = sendThen;
            SendEnd = sendEnd;
            CSE = cse;
            Timeout = timeout;
            Enable = enable;
            DateSunrise = st;
            DateSunset = se;
        }

        /// <summary>
        /// Получает коллекцию из всех параметров
        /// </summary>
        /// <returns></returns>
        public ParametersCollection GetParametersCollection()
        {
            return new ParametersCollection(Name + " " + SendThen + " " + SendEnd);
        }
        /// <summary>
        /// Получает коллекцию из параметров "Имени"
        /// </summary>
        /// <returns></returns>
        public ParametersCollection GetParametersCollectionName()
        {
            return new ParametersCollection(Name);
        }
        /// <summary>
        /// Получает коллекцию из параметров "отправить при работе"
        /// </summary>
        /// <returns></returns>
        public ParametersCollection GetParametersCollectionThen()
        {
            return new ParametersCollection(SendThen);
        }
        /// <summary>
        /// Получает коллекцию из параметров "отправить при окончании работы"
        /// </summary>
        /// <returns></returns>
        public ParametersCollection GetParametersCollectionEnd()
        {
            return new ParametersCollection(SendEnd);
        }
        /// <summary>
        /// Паршеное время начала
        /// </summary>
        public DateTime StartDateParse
        {
            get
            {
                var col = GetParametersCollectionName();
                if(col.IsParameter(GeneralParameters.ParametersName.SDS)) return DateTime.Parse(DateSunrise);
                else if(col.IsParameter(GeneralParameters.ParametersName.SDE)) return DateTime.Parse(DateSunset);
                else return StartTime;
            }
        }
        /// <summary>
        /// Паршеное время окончания
        /// </summary>
        public DateTime EndDateParse
        {
            get
            {
                var col = GetParametersCollectionName();
                if (col.IsParameter(GeneralParameters.ParametersName.EDS)) return DateTime.Parse(DateSunrise);
                else if (col.IsParameter(GeneralParameters.ParametersName.EDE)) return DateTime.Parse(DateSunset);
                else return EndTime;
            }
        }
    }
}
