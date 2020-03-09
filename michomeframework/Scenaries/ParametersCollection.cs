using System.Collections.Generic;
using System;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace michomeframework.Scenaries
{
    public class ParametersCollection
    {
        string param;
        List<GeneralParameters> paramss = new List<GeneralParameters>();
        /// <summary>
        /// Ключ для замены параметров
        /// </summary>
        public const string Keys = "|is";
        /// <summary>
        /// Ключ для окончания замены параметров
        /// </summary>
        public const string KeysEnd = "|as";
        /// <summary>
        /// Инициализация каллекции параметров по заданной строке
        /// </summary>
        /// <param name="paramsq"></param>
        public ParametersCollection(string paramsq)
        {
            this.param = paramsq;
            if (!param.Contains("^")) return;
            var lists = param.Split('^', ';');

            while (IsParameters(GeneralParameters.ParametersName.SDS) && !paramss.Contains(new Scenaries.ParametersSDS())) Add(new Scenaries.ParametersSDS(), ref param);
            while (IsParameters(GeneralParameters.ParametersName.SDE) && !paramss.Contains(new Scenaries.ParametersSDE())) Add(new Scenaries.ParametersSDE(), ref param);
            while (IsParameters(GeneralParameters.ParametersName.EDS) && !paramss.Contains(new Scenaries.ParametersEDS())) Add(new Scenaries.ParametersEDS(), ref param);
            while (IsParameters(GeneralParameters.ParametersName.EDE) && !paramss.Contains(new Scenaries.ParametersEDE())) Add(new Scenaries.ParametersEDE(), ref param);
            while (IsParameters(GeneralParameters.ParametersName.NOS) && !paramss.Contains(new Scenaries.ParametersNOS())) Add(new Scenaries.ParametersNOS(), ref param);
            while (IsParameters(GeneralParameters.ParametersName.CBP) && !paramss.Contains(new Scenaries.ParametersCBP())) Add(new Scenaries.ParametersCBP(), ref param);
            while (IsParameters(GeneralParameters.ParametersName.PBP) && !paramss.Contains(new Scenaries.ParametersPBP())) Add(new Scenaries.ParametersPBP(), ref param);

            while (IsParameters(GeneralParameters.ParametersName.RM)) Add(new Scenaries.ParametersRM(param, paramss.ToArray()), ref param);
            while (IsParameters(GeneralParameters.ParametersName.BT)) Add(new Scenaries.ParametersBT(param, paramss.ToArray()), ref param);
            while (IsParameters(GeneralParameters.ParametersName.SN)) Add(new Scenaries.ParametersSN(param, paramss.ToArray()), ref param);
            while (IsParameters(GeneralParameters.ParametersName.IF)) Add(new Scenaries.ParametersIF(param, paramss.ToArray()), ref param);

            return;
        }
        /// <summary>
        /// Возвращает массив параметров с заданым типом
        /// </summary>
        /// <param name="pn">Тип</param>
        /// <returns></returns>
        public GeneralParameters[] GetParameters(GeneralParameters.ParametersName pn)
        {
            var p = paramss.Where(tmp => tmp.Name == pn).ToArray();
            return p ?? (new GeneralParameters[] { });
        }
        /// <summary>
        /// Возвращает первый параметр с заданым типом
        /// </summary>
        /// <param name="pn">Тип</param>
        /// <returns></returns>
        public GeneralParameters GetParameter(GeneralParameters.ParametersName pn)
        {
            return paramss.Where(tmp => tmp.Name == pn).ToArray().FirstOrDefault();
        }
        /// <summary>
        /// Есть ли в коллекции данный параметр
        /// </summary>
        /// <param name="param"></param>
        /// <returns></returns>
        private bool IsParameters(GeneralParameters.ParametersName paramn)
        {
            return param.ToLower().Contains("^"+paramn.ToString().ToLower());
            //return paramss.Where(tmp => tmp.Name == paramn).Any();
        }
        /// <summary>
        /// Есть ли в коллекции данный параметр
        /// </summary>
        /// <param name="param"></param>
        /// <returns></returns>
        public bool IsParameter(GeneralParameters.ParametersName paramn)
        {
            //return param.ToLower().Contains("^" + paramn.ToString().ToLower());
            return paramss.Where(tmp => tmp.Name == paramn).Any();
        }
        /// <summary>
        /// Есть ли в строке данный параметр
        /// </summary>
        /// <param name="param"></param>
        /// <returns></returns>
        public bool IsParameters(GeneralParameters.ParametersName paramn, string str)
        {
            return str.ToLower().Contains("^"+paramn.ToString().ToLower());
        }
        /// <summary>
        /// Возвращает наличие параметра в строке и затем удаляет его из строки
        /// </summary>
        /// <param name="param"></param>
        /// <returns></returns>
        public bool IsParametersThenNull(GeneralParameters.ParametersName paramn)
        {
            var nparam = param.ToLower().Contains(paramn.ToString().ToLower());
            if (!nparam) return false;

            if (paramn == GeneralParameters.ParametersName.IF || paramn == GeneralParameters.ParametersName.SN || paramn == GeneralParameters.ParametersName.BT || paramn == GeneralParameters.ParametersName.RM)
            {
                var start = param.IndexOf("^" + paramn.ToString().ToLower());
                var end = param.IndexOf(";")+1;               
                param = param.Remove(start, Math.Abs(start - end));
                param = param.Insert(start, Keys+paramss.Count);
            }

            return nparam;
        }

        /// <summary>
        /// Добавляет эквивалентное данному строковому представлению параметр и затем удаляет его из строки
        /// </summary>
        /// <param name="p">Строковое представление параметра</param>
        /// <param name="pa">Эквивалент параметра</param>
        public void Add(GeneralParameters pa, ref string p)
        {
            paramss.Add(pa);
            if (!IsParameters(pa.Name, p)) return;
            Count++;
            var start = p.IndexOf("^" + pa.Name.ToString().ToLower());
            var end = 0;

            if (pa.IsEndSymbols)
                end = p.IndexOf(";") + 1;
            else
                end = start + 4;

            p = p.Remove(start, Math.Abs(start - end));
            p = p.Insert(start, Keys + (paramss.Count-1) + KeysEnd);
        }
        /// <summary>
        /// Добавляет эквивалентное данному строковому представлению параметр
        /// </summary>
        /// <param name="pa">Эквивалент параметра</param>
        public void Add(GeneralParameters pa, bool AddString = false)
        {
            paramss.Add(pa);
            if(AddString) param += pa.ToStringChildren + " ";
        }
        /// <summary>
        /// Добавляет эквивалентное данному строковому представлению параметр
        /// </summary>
        /// <param name="pa">Эквивалент параметра</param>
        public void Add(GeneralParameters[] pa, bool AddString = false)
        {
            foreach (var item in pa)           
                Add(item, AddString);           
        }
        /// <summary>
        /// Удаляет заданный параметр
        /// </summary>
        /// <param name="pa">Эквивалент параметра</param>
        public void Remove(GeneralParameters pa)
        {
            param = param.Replace(Keys + paramss.IndexOf(pa) + KeysEnd, "");
            paramss.Remove(pa);
        }
        /// <summary>
        /// Удаляет заданный параметр
        /// </summary>
        /// <param name="pa">Эквивалент параметра</param>
        public void Remove(GeneralParameters.ParametersName pa)
        {
            if (!IsParameter(pa)) return;
            paramss.Where(tmp => tmp.Name == pa).ToList().ForEach(tmp => Remove(tmp));
        }
        /// <summary>
        /// Возвращает или задает текстовое представление без спец символов
        /// </summary>
        /// 
        public string Text
        {
            get
            {
                var tmp = param;
                while (tmp.Contains(Keys))
                {
                    var start = tmp.IndexOf(Keys);
                    var lent = tmp.Substring(start).IndexOf(KeysEnd);
                    var s = tmp.Substring(start, lent);
                    tmp = tmp.Remove(start + lent, KeysEnd.Length);
                    tmp = tmp.Replace(s, "");
                }
                return tmp.Trim();
            }
            set
            {
                param = param.Replace(Text, value);
            }
        }
        /// <summary>
        /// Возвращает строковое представление
        /// </summary>
        public new string ToString
        {
            get
            {
                var tmp = param;
                while (tmp.Contains(Keys))
                {
                    var start = tmp.IndexOf(Keys);
                    var lent = tmp.Substring(start).IndexOf(KeysEnd);
                    var s = tmp.Substring(start, lent);
                    tmp = tmp.Remove(start+ lent, KeysEnd.Length);
                    tmp = tmp.Replace(s, paramss[int.Parse(s.Substring(Keys.Length))].ToString);                    
                }
                return tmp;
            }
            set
            {
                param = value;
            }
        }

        /// <summary>
        /// Возвращает количсество элементов
        /// </summary>
        public int Count
        {
            get;
            private set;
        }
    }
}
