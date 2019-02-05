using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LightModulesConfigurator.Module
{
    class StroboAll : Main
    {
        public new string name { get; set; }
        public string col { get; set; }
        public string times { get; set; }
        public string waiting { get; set; }
        public StroboAll(string name, string col, string waiting, string times)
        {
            this.name = name;
            this.col = col;
            this.times = times;
            this.waiting = waiting;
        }
    }
}
