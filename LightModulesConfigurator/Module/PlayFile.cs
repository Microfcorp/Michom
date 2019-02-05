using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LightModulesConfigurator.Module
{
    class PlayFile : Main
    {
        public new string name { get; set; }
        public string file { get; set; }
        public PlayFile(string name, string file)
        {
            this.name = name;
            this.file = file;
        }
    }
}
