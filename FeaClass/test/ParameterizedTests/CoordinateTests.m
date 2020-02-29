classdef CoordinateTests < ParameterizedTestBase
    
    properties (TestParameter)
        XYAngleTrans = {0 pi pi/2 pi/3 pi/4 pi/5 pi/6 pi/7 pi/8 pi/9 pi/10};
        XZAngleTrans = {0 pi pi/2 pi/3 pi/4 pi/5 pi/6 pi/7 pi/8 pi/9 pi/10};
        Magnitude = {1 2 3 4 5 6 7 8 9 10 11};
        XYAngleVector = {0 pi pi/2 pi/3 pi/4 pi/5 pi/6 pi/7 pi/8 pi/9 pi/10};
        XZAngleVector = {0 pi pi/2 pi/3 pi/4 pi/5 pi/6 pi/7 pi/8 pi/9 pi/10};
    end
    
    %parameterized
    methods (Test)
        
        function Verify2DTransformationMatrixConstruction(testCase, XYAngleTrans)
            syms r az real
            
            %build expected
            x = r*cos(az);
            y = r*sin(az);
            exp = jacobian([x;y], [r az]);
            exp = double(subs(exp, [r az], [1 XYAngleTrans]));
            
            %build test
            test = Coordinates.TransformationMatrix(2,1,XYAngleTrans);
            
            testCase.verifyEqual(exp,test, 'RelTol', 1e-6);
        end
        
        function Verify3DTransformationMatrixConstruction(testCase, XYAngleTrans, XZAngleTrans)
            syms r az pol real
            
            %build expeted
            x = r*sin((pi/2) - pol)*cos(az);
            y = r * sin((pi/2) - pol) * sin(az);
            z = r*cos((pi/2) - pol);
            exp = jacobian([x; y; z], [r az pol]);
            exp = double(subs(exp, [az pol r], [XYAngleTrans XZAngleTrans 1]));
            
            %build test
            test = Coordinates.TransformationMatrix(3,1,XYAngleTrans, XZAngleTrans);
            
            testCase.verifyEqual(exp,test, 'RelTol', 1e-6);
        end
        
        function Verify2DVectorConstruction(testCase, Magnitude, XYAngleVector, XZAngleVector)
            
        end
    end
    
    %sanity
    methods (Test)
        
        function Verify2DTransformIsUnitX(testCase)
            exp = eye(2);
            test = Coordinates.TransformationMatrix(2,1,0);
            testCase.verifyEqual(exp,test, 'RelTol', 1e-6);
        end
        function Verify2DTransformIsUnitY(testCase)
            exp = [0 -1; 1 0];
            test = Coordinates.TransformationMatrix(2,1,pi/2);
            testCase.verifyEqual(exp,test, 'RelTol', 1e-6);
        end
        function Verify3DTransformIsUnitX(testCase)
            exp = eye(3);
            test = Coordinates.TransformationMatrix(3,1,0,0);
            testCase.verifyEqual(exp,test, 'RelTol', 1e-6);
        end
        function Verify3DTransformIsUnitY(testCase)
            exp = [0 -1 0; 1 0 0; 0 0 1];
            test = Coordinates.TransformationMatrix(3,1,pi/2,0);
            testCase.verifyEqual(exp,test, 'RelTol', 1e-6);
        end
        function Verify3DTransformIsUnitZ(testCase)
            exp = [0 0 -1; 0 0 0; 1 0 0];
            test = Coordinates.TransformationMatrix(3,1,0,pi/2);
            testCase.verifyEqual(exp,test, 'RelTol', 1e-6);
        end
    end
end

