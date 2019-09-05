using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace michomeframework.Settings
{
    public class SettingManager
    {
        public static void Save(Setting st)
        {
            st.Save(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + "MichomeSettings.set");
        }
        public static bool IsSetting()
        {
            return System.IO.File.Exists(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + "MichomeSettings.set");
        }
        public static Setting Create()
        {
            return new Setting();
        }
        public static Setting Load()
        {
            if (!IsSetting())
                return Create();

            string param = System.IO.File.ReadAllText(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + "MichomeSettings.set");
            Setting tmp = new Setting();

            foreach (var item in param.Split(Setting.ParametrsSeparator))
            {
                if(item.Split(Setting.KeyNameSeparator)[0] != "" & item.Split(Setting.KeyNameSeparator).Length > 1)
                    tmp.Parameters.Add(item.Split(Setting.KeyNameSeparator)[0], item.Split(Setting.KeyNameSeparator)[1]);
            }

            return tmp;
        }
    }

    public class Setting
    {
        public const char KeyNameSeparator = '|';
        public const char ParametrsSeparator = ';';

        public const string GatewayIP = "GatewayIP";
        public const string AutoConnect = "AutoConnect";

        public const string NullData = "FalseDataNull";

        public SortedList<string, string> Parameters
        {
            get;
            private set;
        }

        public bool AutoSave
        {
            get;
            set;
        }

        internal Setting()
        {
            Parameters = new SortedList<string, string>();
            AutoSave = true;
        }

        public bool IsKey(string key)
        {
            return Parameters.Keys.Contains(key);
        }

        public string GetData(string key)
        {
            if (!IsKey(key))
                return NullData;

            return Parameters[key];
        }

        public Setting SetData(string key, string value)
        {
            if (!IsKey(key))
                Parameters.Add(key, value);
            else
                Parameters[key] = value;

            if (AutoSave)
                SettingManager.Save(this);

            return this;
        }

        public void Save(string path)
        {
            string tmp = "";
            foreach (var item in Parameters)
            {
                tmp += item.Key + KeyNameSeparator + item.Value + ParametrsSeparator;
            }
            System.IO.File.WriteAllText(path, tmp);
        }
    }
}
