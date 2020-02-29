using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace RemakeSchoolMatlabProject.MatLabObjects
{
    public static class MatLabConstants
    {
        public static string FunctionFolder = Directory.GetParent(Directory.GetCurrentDirectory()).Parent.FullName + "\\MatLabObjects\\";
        public static string AmplitudeFilePath = FunctionFolder + "amplitude.m";
        public static string ODEExecuteFilePath = FunctionFolder + "odeExecute.m";
        public static string runScriptFilePath = FunctionFolder + "runScript.m";
    }
}
