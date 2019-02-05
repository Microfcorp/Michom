using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LightModulesConfigurator.Module
{
    class StroboPro : Main
    {
        public new string name { get; set; }
        public string pin { get; set; }
        public string col { get; set; }
        public string nostrob { get; set; }
        public string times { get; set; }
        public string waiting { get; set; }
        public StroboPro(string name, string pin, string col, string waiting, string times, string nostrob)
        {
            this.name = name;
            this.pin = pin;
            this.col = col;
            this.nostrob = nostrob;
            this.times = times;
            this.waiting = waiting;
        }
    }
}
