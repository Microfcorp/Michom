using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LightModulesConfigurator.Module
{
    class Sleep : Main
    {
        public new string name { get; set; }
        public string time { get; set; }
        public Sleep(string name, string time)
        {
            this.name = name;
            this.time = time;
        }
    }
}
