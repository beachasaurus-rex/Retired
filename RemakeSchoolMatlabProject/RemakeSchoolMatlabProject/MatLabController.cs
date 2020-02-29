using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using RemakeSchoolMatlabProject.MatLabObjects;

namespace RemakeSchoolMatlabProject
{
    public static class MatLabController
    {
        public static void AddMatLabFilesToPath(MLApp.MLApp _session)
        {
            if (_session == null)
            {
                throw new ArgumentNullException("A MatLab session does not exist.");
            }

            string addPath = $"addpath({Char.ConvertFromUtf32(39)}{MatLabConstants.FunctionFolder}{Char.ConvertFromUtf32(39)})";
            _session.Execute(addPath);
        }

        public static string RunScript(MLApp.MLApp _session, object[] inputs)
        {
            MatLabFunction runScript = new MatLabFunction("runScript",
                                                          MatLabConstants.runScriptFilePath,
                                                          _session,
                                                          inputs,
                                                          1);
            object[] filePath = runScript.Execute();
            string FilePath = (string)filePath[0];
            return FilePath;
        }
    }
}
