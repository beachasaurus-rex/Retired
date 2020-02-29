using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RemakeSchoolMatlabProject.MatLabObjects
{
    class MatLabFunction
    {
        private object[] _outputs = null;
        public object[] Outputs { get { return _outputs; } }
        private object[] _inputs = null;
        public object[] Inputs { get { return _inputs; } }
        private MLApp.MLApp _matlabInstance;
        public MLApp.MLApp MatLabInstance { get { return _matlabInstance; } }
        public string FunctionName { get; }
        public string FileLocation { get; }
        public int NumberOfOutputs { get; }

        //constructor
        public MatLabFunction(string functionName, 
                              string fileLocation,
                              MLApp.MLApp matlabInstance,
                              object[] inputs, int numberOfOutputs)
        {
            FunctionName = functionName;
            FileLocation = fileLocation;
            _matlabInstance = matlabInstance;
            _inputs = inputs;
            NumberOfOutputs = numberOfOutputs;

            Array.Resize<object>(ref _outputs, numberOfOutputs);
        }

        public object[] Execute()
        {
            object output;
            _matlabInstance.Execute(FileLocation);
            _matlabInstance.Feval(FunctionName,
                                  NumberOfOutputs,
                                  out output,
                                  _inputs);

            _outputs = output as object[];
            return _outputs;
        }

        public void Quit()
        {
            _matlabInstance.Quit();
            _matlabInstance = null;
        }
    }
}
