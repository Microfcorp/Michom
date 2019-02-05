using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LightModulesConfigurator.Module
{
    class Light : Main
    {
        public new string name { get; set; }
        public string pin { get; set; }
        public string brightness { get; set; }
        public Light(string name, string pin, string br)
        {
            this.name = name;
            this.pin = pin;
            this.brightness = br;
        }
    }
}
