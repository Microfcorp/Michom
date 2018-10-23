using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace LightModulesConfigurator
{
    public class Sceene
    {
        public string name { get; set; }
        public List<Steep> Params { get; set; }
    }
    public class Steep
    {
        public string name { get; set; }
        public string file { get; set; }
        public string pin { get; set; }
        public string brightness { get; set; }
        public string time { get; set; }
        public string times { get; set; }
        public string col { get; set; }
        public string waiting { get; set; }
    }
}
