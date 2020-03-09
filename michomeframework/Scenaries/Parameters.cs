using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace michomeframework.Scenaries
{
    /// <summary>
    /// Представляет универсальные функции для параметров
    /// </summary>
    public class GeneralParameters
    {
        internal GeneralParameters()
        {
            Children = new SortedList<string, GeneralParameters>();
        }
        /// <summary>
        /// Производит заполнение дочерними элементами
        /// </summary>
        /// <param name="param">Строка с параметрами</param>
        /// <param name="gn">Массив с параметрами</param>
        public void GetChildrens(string param, GeneralParameters[] gn)
        {
            var tmp = param;
            while (tmp.Contains(ParametersCollection.Keys))
            {
                var start = tmp.IndexOf(ParametersCollection.Keys);
                var lent = tmp.Substring(start).IndexOf(ParametersCollection.KeysEnd);
                var s = tmp.Substring(start, lent);
                tmp = tmp.Remove(start + lent, ParametersCollection.KeysEnd.Length);
               
                Children.Add(s.Substring(ParametersCollection.Keys.Length), gn[int.Parse(s.Substring(ParametersCollection.Keys.Length))]);

                tmp = tmp.Replace(s, "");
            }
        }
        /// <summary>
        /// Возвращает строковое представление данного параметра с включенными в него параметрами
        /// </summary>
        public string ToStringChildren
        {
            get => GetStringChildren(ToString);
        }
        /// <summary>
        /// Возвращает строку с дочерними элементами
        /// </summary>
        /// <param name="param">Строка с параметрами</param>
        /// <returns></returns>
        public string GetStringChildren(string param)
        {
            var tmp = param;
            while (tmp.Contains(ParametersCollection.Keys))
            {
                var start = tmp.IndexOf(ParametersCollection.Keys);
                var lent = tmp.Substring(start).IndexOf(ParametersCollection.KeysEnd);
                var s = tmp.Substring(start, lent);
                tmp = tmp.Remove(start + lent, ParametersCollection.KeysEnd.Length);
                tmp = tmp.Replace(s, Children[s.Substring(ParametersCollection.Keys.Length)].ToString);
            }
            return tmp;
        }
        /// <summary>
        /// Название параметра
        /// </summary>
        public enum ParametersName
        {
            /// <summary>
            /// Старт по началу дня
            /// </summary>
            SDS,
            /// <summary>
            /// Старт по окончанию дня
            /// </summary>
            SDE,
            /// <summary>
            /// Конец по старту дня
            /// </summary>
            EDS,
            /// <summary>
            /// Окончание по концу дня
            /// </summary>
            EDE,
            /// <summary>
            /// Не проверять, были ли отправлены данные
            /// </summary>
            NOS,
            /// <summary>
            /// Количество нажатий клавиши
            /// </summary>
            CBP,
            /// <summary>
            /// Пин нажатой клавиши
            /// </summary>
            PBP,
            /// <summary>
            /// Чтений данных с модуля
            /// </summary>
            RM,
            /// <summary>
            /// Отправка уведомления
            /// </summary>
            SN,
            /// <summary>
            /// Условие
            /// </summary>
            IF,
            /// <summary>
            /// Обработка нажатия клавиши
            /// </summary>
            BT,
        }
        /// <summary>
        /// Оператор выражения
        /// </summary>
        public enum Operator
        {
            Больше,
            Меньше,
            Равно,
            Неравно,
            БольшеРавно,
            МеньшеРавно,
        }
        /// <summary>
        /// Переводит оператор в строковое представление
        /// </summary>
        /// <param name="op">Оператор</param>
        /// <returns></returns>
        public string OperatorToString(Operator op)
        {
            if (op == Operator.Больше) return ">";
            else if (op == Operator.БольшеРавно) return ">=";
            else if (op == Operator.Меньше) return "<";
            else if (op == Operator.МеньшеРавно) return "<=";
            else if (op == Operator.Неравно) return "!=";
            else if (op == Operator.Равно) return "==";
            else return "";
        }
        /// <summary>
        /// Переводит строковое представление оператора в оператор
        /// </summary>
        /// <param name="op">Оператор</param>
        /// <returns></returns>
        public Operator StringToOperator(string op)
        {
            if (op.Contains(">=")) return Operator.БольшеРавно;
            else if (op.Contains("<=")) return Operator.МеньшеРавно;
            else if (op.Contains(">")) return Operator.Больше;
            else if (op.Contains("<")) return Operator.Меньше;           
            else if (op.Contains("!=")) return Operator.Неравно;
            else if (op.Contains("==")) return Operator.Равно;
            else return Operator.Равно;
        }
        /// <summary>
        /// Коллекция дочерних элементов
        /// </summary>
        private SortedList<string, GeneralParameters> Children
        {
            get;
            set;
        }
        /// <summary>
        /// Массив всех дочерних элементов
        /// </summary>
        public GeneralParameters[] ChildrenNode
        {
            get => Children.Values.ToArray();
        }
        /// <summary>
        /// Название параметра
        /// </summary>
        public ParametersName Name
        {
            get;
            set;
        }
        /// <summary>
        /// Есть ли в строке данный параметр
        /// </summary>
        /// <param name="param"></param>
        /// <returns></returns>
        public bool IsParameters(ParametersName param)
        {
            return ToString.ToLower().Contains(param.ToString().ToLower());
        }

        /// <summary>
        /// Возвращает строковое представление данного параметра
        /// </summary>
        public virtual new string ToString
        {
            get;
            set;
        }
        /// <summary>
        /// Возращает символ окончания строки
        /// </summary>
        public char EndSymbols
        {
            get;
            internal set;
        }
        /// <summary>
        /// Возвращает, нужно ли использолвать символ окончания строки
        /// </summary>
        public bool IsEndSymbols
        {
            get
            {
                return EndSymbols == ';';
            }
        }
    }

    /// <summary>
    /// Старт по началу дня
    /// </summary>
    public class ParametersSDS : GeneralParameters
    {
        public ParametersSDS()
        {
            Name = ParametersName.SDS;
            ToString = "^" + Name.ToString().ToLower();
            EndSymbols = ' ';
        }
    }
    /// <summary>
    /// Старт по началу дня
    /// </summary>
    public class ParametersSDE : GeneralParameters
    {
        public ParametersSDE()
        {
            Name = ParametersName.SDE;
            ToString = "^" + Name.ToString().ToLower();
            EndSymbols = ' ';
        }
    }
    /// <summary>
    /// Старт по началу дня
    /// </summary>
    public class ParametersEDS : GeneralParameters
    {
        public ParametersEDS()
        {
            Name = ParametersName.EDS;
            ToString = "^" + Name.ToString().ToLower();
            EndSymbols = ' ';
        }
    }
    /// <summary>
    /// Старт по началу дня
    /// </summary>
    public class ParametersEDE : GeneralParameters
    {
        public ParametersEDE()
        {
            Name = ParametersName.EDE;
            ToString = "^" + Name.ToString().ToLower();
            EndSymbols = ' ';
        }
    }
    /// <summary>
    /// Не проверять, были ли отправлены данные
    /// </summary>
    public class ParametersNOS : GeneralParameters
    {
        public ParametersNOS()
        {
            Name = ParametersName.NOS;
            ToString = "^" + Name.ToString().ToLower();
            EndSymbols = ' ';
        }
    }
    /// <summary>
    /// Количество нажатий клавиши
    /// </summary>
    public class ParametersCBP : GeneralParameters
    {
        public ParametersCBP()
        {
            Name = ParametersName.CBP;
            ToString = "^" + Name.ToString().ToLower();
            EndSymbols = ' ';
        }

        public override bool Equals(object obj)
        {
            return obj.GetHashCode() == GetHashCode();
        }

        public override int GetHashCode()
        {            
            return base.GetHashCode() | (new Random((int)DateTime.Now.Ticks + 0xCB)).Next();
        }
    }
    /// <summary>
    /// Пин нажатой клавиши
    /// </summary>
    public class ParametersPBP : GeneralParameters
    {
        public ParametersPBP()
        {
            Name = ParametersName.PBP;
            ToString = "^" + Name.ToString().ToLower();
            EndSymbols = ' ';
        }
        public override bool Equals(object obj)
        {
            return obj.GetHashCode() == GetHashCode();
        }

        public override int GetHashCode()
        {
            return base.GetHashCode() | (new Random((int)DateTime.Now.Ticks + 0xFB)).Next();
        }
    }
    /// <summary>
    /// Чтение данных с модуля
    /// </summary>
    public class ParametersRM : GeneralParameters
    {
        /// <summary>
        /// Чтение данных с модуля
        /// </summary>
        public ParametersRM()
        {
            Name = ParametersName.RM;
            EndSymbols = ';';
        }
        /// <summary>
        /// Чтение данных с модуля
        /// </summary>
        public ParametersRM(string ip, string typedata) : this()
        {
            IP = ip;
            TypeData = typedata;
        }
        /// <summary>
        /// Чтение данных с модуля
        /// </summary>
        public ParametersRM(string param, GeneralParameters[] g) : this()
        {
            var st = param.Split('^', ';').Where(tmp => tmp.Contains(Name.ToString().ToLower())).FirstOrDefault();
            GetChildrens(st, g);
            IP = st.Split('_')[1];
            TypeData = st.Split('_')[2];
        }
        /// <summary>
        /// Адрес модуля
        /// </summary>
        public string IP;
        /// <summary>
        /// Тип данных
        /// </summary>
        public string TypeData;

        /// <summary>
        /// Возвращает строковое представление данного параметра
        /// </summary>
        public override string ToString
        {
            get { base.ToString = String.Format("^rm_{0}_{1};", IP, TypeData); return base.ToString; }
        }
        public override bool Equals(object obj)
        {
            return obj.GetHashCode() == GetHashCode();
        }

        public override int GetHashCode()
        {
            return base.GetHashCode() | (new Random((int)DateTime.Now.Ticks + 0xED)).Next();
        }
    }
    /// <summary>
    /// Отправка уведомления
    /// </summary>
    public class ParametersSN : GeneralParameters
    {
        /// <summary>
        /// Отправка уведомления
        /// </summary>
        public ParametersSN()
        {
            Name = ParametersName.SN;
            EndSymbols = ';';
            SendType = true;
        }
        /// <summary>
        /// Отправка уведомления
        /// </summary>
        public ParametersSN(string group, string message)
        {
            Group = group;
            Message = message;
        }

        /// <summary>
        /// Отправка уведомления
        /// </summary>
        public ParametersSN(string param, GeneralParameters[] g) : this()
        {
            var st = param.Split('^', ';').Where(tmp => tmp.Contains(Name.ToString().ToLower())).FirstOrDefault();
            GetChildrens(st, g);
            Group = st.Split('_')[1];
            Message = st.Split('_')[2];
        }

        /// <summary>
        /// Группа получателей
        /// </summary>
        public string Group;
        /// <summary>
        /// Сообщение для отправки
        /// </summary>
        public string Message;
        /// <summary>
        /// Поле только для редактирования. Сообщение для отправки
        /// </summary>
        public string ReadOnlyMessage
        {
            get => Message;
        }
        /// <summary>
        /// Отправлять при "данные в периоде"
        /// </summary>
        public bool SendType;

        /// <summary>
        /// Возвращает строковое представление данного параметра
        /// </summary>
        public override string ToString
        {
            get { base.ToString = String.Format("^sn_{0}_{1};", Group, Message); return base.ToString; }
        }
        public override bool Equals(object obj)
        {
            return obj.GetHashCode() == GetHashCode();
        }

        public override int GetHashCode()
        {
            return base.GetHashCode() | (new Random((int)DateTime.Now.Ticks + 0xEA)).Next();
        }
    }
    /// <summary>
    /// Условие
    /// </summary>
    public class ParametersIF : GeneralParameters
    {
        /// <summary>
        /// Условие
        /// </summary>
        public ParametersIF()
        {
            Name = ParametersName.IF;
            EndSymbols = ';';
        }
        /// <summary>
        /// Условие
        /// </summary>
        public ParametersIF(string viraz1, string viraz2, Operator operators) : this()
        {
            Viraz1 = viraz1;
            Viraz2 = viraz2;
            Operators = operators;
        }

        /// <summary>
        /// Условие
        /// </summary>
        public ParametersIF(string param, GeneralParameters[] g) : this()
        {         
            var st = param.Split('^', ';').Where(tmp => tmp.Contains(Name.ToString().ToLower())).FirstOrDefault();
            GetChildrens(st, g);
            Viraz1 = st.Split('_')[1].Split('=', '!', '>', '<').FirstOrDefault();
            Viraz2 = st.Split('_')[1].Split('=', '!', '>', '<').LastOrDefault();
            Operators = base.StringToOperator(st.Split('_')[1]);
        }

        /// <summary>
        /// Возвращает строковое представление данного ператора
        /// </summary>
        public string OperatorToString()
        {
            return base.OperatorToString(Operators);
        }

        /// <summary>
        /// Перевести и присвоить строковый эквивалент оператора оператору
        /// </summary>
        public new void StringToOperator(string operatora)
        {
            Operators = base.StringToOperator(operatora);
        }       

        /// <summary>
        /// Выражение 1
        /// </summary>
        public string Viraz1;
        /// <summary>
        /// Выражение 2
        /// </summary>
        public string Viraz2;
        /// <summary>
        /// Оператор
        /// </summary>
        public Operator Operators;

        /// <summary>
        /// Возвращает строковое представление данного параметра
        /// </summary>
        public override string ToString
        {
            get { base.ToString = String.Format("^if_{0}{1}{2};", Viraz1, OperatorToString(Operators), Viraz2); return base.ToString; }
        }
    }
    /// <summary>
    /// Отбработка нажатия клавиши
    /// </summary>
    public class ParametersBT : GeneralParameters
    {
        /// <summary>
        /// Отбработка нажатия клавиши
        /// </summary>
        public ParametersBT()
        {
            Name = ParametersName.BT;
            EndSymbols = ';';
        }
        /// <summary>
        /// Отбработка нажатия клавиши
        /// </summary>
        public ParametersBT(string module, string pin, string count)
        {
            Module = module;
            Pin = pin;
            Count = count;
        }

        /// <summary>
        /// Отбработка нажатия клавиши
        /// </summary>
        public ParametersBT(string param, GeneralParameters[] g) : this()
        {
            var st = param.Split('^', ';').Where(tmp => tmp.Contains(Name.ToString().ToLower())).FirstOrDefault();
            GetChildrens(st, g);
            Module = st.Split('_')[1];
            Pin = st.Split('_')[2];
            Count = st.Split('_').Length > 3 ? st.Split('_')[3] : "1";
        }

        /// <summary>
        /// Модуль
        /// </summary>
        public string Module;
        /// <summary>
        /// Пин
        /// </summary>
        public string Pin;
        /// <summary>
        /// Количество нажатий
        /// </summary>
        public string Count;

        /// <summary>
        /// Возвращает строковое представление данного параметра
        /// </summary>
        public override string ToString
        {
            get { base.ToString = String.Format("^bt_{0}_{1}_{2}_1;", Module, Pin, Count); return base.ToString; }
        }
    }
}
