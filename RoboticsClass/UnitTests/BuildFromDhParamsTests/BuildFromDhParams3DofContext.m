classdef BuildFromDhParams3DofContext < matlab.unittest.TestCase
    
    properties
        DhParams
        Frame3TipPosition
    end
    
    methods (TestMethodSetup)
        
        function Build3DofContext(testCase)
            d1 = 0.15;
            th2 = -pi/2;
            th3 = pi/2;
            a12 = 0.3;
            a23 = 0.5;
            a3tip = 0.15;
            
            testCase.Frame3TipPosition = [a3tip; 0; 0];
            testCase.DhParams = [0 0 d1 pi/2;...
                                 a12 0 0 th2;...
                                 a23 0 0 th3];
        end
    end
    
    methods (Test)
        
        function BuildFromDhParams3DofContext_verify_mapped_position(testCase)
            exp = [0.5; 0.45; 0.15];
            
            env = Helpers.BuildFromDhParams(testCase.DhParams, false);
            tMat30 = env.Origin.MappedFrames{3,2};
            test = Helpers.TransformPosition(testCase.Frame3TipPosition, tMat30.Matrix);
            
            testCase.verifyEqual(test, exp, 'RelTol', 0.1);
        end
    end
end

