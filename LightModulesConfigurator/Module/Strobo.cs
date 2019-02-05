using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LightModulesConfigurator.Module
{
    class Strobo : Main
    {
        public new string name { get; set; }
        public string pin { get; set; }
        public string col { get; set; }
        public string times { get; set; }
        public string waiting { get; set; }
        public Strobo(string name, string pin, string col, string waiting, string times)
        {
            this.name = name;
            this.pin = pin;
            this.col = col;
            this.times = times;
            this.waiting = waiting;
        }
    }
}
