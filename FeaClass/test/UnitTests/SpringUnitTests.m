classdef SpringUnitTests < UnitTestBase
    
    properties
        Id
        DoF
        SpringCoefficient
        InputNode
        OutputNode
        DirectSpring
        EnergySpring
    end
    
    methods (TestClassSetup)
        
        function SetupUnitTest_Element(testCase)
            testCase.Id = 1;
            testCase.DoF = 3;
            
            testCase.InputNode = Node(1, BoundaryConditions(testCase.DoF, [1 2 3]));
            testCase.OutputNode = Node(2, BoundaryConditions(testCase.DoF, [4 5 6]));
            testCase.SpringCoefficient = 10;
            
            testCase.DirectSpring = Spring(testCase.Id, testCase.InputNode, ...
                testCase.OutputNode, testCase.SpringCoefficient, ...
                SolutionMethod.Direct);
            
            testCase.EnergySpring = Spring(testCase.Id, testCase.InputNode, ...
                testCase.OutputNode, testCase.SpringCoefficient, ...
                SolutionMethod.Energy);
        end
    end
    
    methods (Test)
        
        %constructor tests
        function Constructor__VerifyAMatrixSetupDirectMethod(testCase)
            testSpring = testCase.DirectSpring;
            
            exp = DirectSpringElementalMatrix(testCase.DoF);
            exp = subs(exp, symvar(exp), testCase.SpringCoefficient);
            
            testCase.verifyEqual(testSpring.A, exp);
        end
        function Constructor__VerifyAMatrixSetupEnergyMethod(testCase)
            testSpring = testCase.EnergySpring;
            
            exp = EnergySpringElementalMatrix(testCase.DoF);
            exp = subs(exp, symvar(exp), testCase.SpringCoefficient);
            
            testCase.verifyEqual(testSpring.A, exp);
        end
        function Constructor__VerifyXMatrixSetup(testCase)
            testSpring = testCase.DirectSpring;
            exp = [testCase.InputNode.BoundaryConditions.Values; ...
                testCase.OutputNode.BoundaryConditions.Values];
            
            testCase.verifyEqual(testSpring.x, exp);
        end
    end
end

