using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CommonDefinitions
{
    public class Definitions
    {
        public enum LogLevel : byte
        {
            ALL = 0,
            DEBUG,
            INFO,
            WARN,
            ERROR,
            FATAL,
            OFF,
        }
    }
}
