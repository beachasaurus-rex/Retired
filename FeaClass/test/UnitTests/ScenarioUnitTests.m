classdef ScenarioUnitTests < UnitTestBase
    
    properties (Constant)
        kArr = [10 15 5 25 30 15 25];
        bounds = [0 0 nan 0 nan nan 0 nan]';
        fArr = [0 0 1 0 5 0 0 3]';
    end
    
    properties
        Name
        Elements
        Nodes
        Stimuli
        TestScenario
        DegreesOfFreedom
        Dimensions
        Method
        Bounds
        A
        b0
        x0
    end
    
    methods (TestClassSetup)
        
        function SetupUnitTest_Scenario(testCase)
            testCase.Name = 'TestScenario';
            testCase.Method = SolutionMethod.Direct;
            testCase.Dimensions = 2;
            testCase.MakeTestElements();
            testCase.MakeTestStimuli();
            
            testCase.TestScenario = ...
                Scenario(testCase.Name, testCase.Elements, testCase.Nodes, ...
                testCase.Stimuli, testCase.Dimensions);
            testCase.A = testCase.TestScenario.A;
            testCase.b0 = testCase.TestScenario.b0;
            testCase.x0 = testCase.TestScenario.x0;
        end
    end
    
    methods (Test)
        
        %constructor tests
        function Constructor__VerifyAMatrixSetup(testCase)
            testScenario = testCase.TestScenario;
            
            expA = [10 0 -10 zeros(1,5); ...
                0 15 -15 zeros(1,5); ...
                -10 -15 30 0 -5 zeros(1,3); ...
                zeros(1,3) 25 -25 zeros(1,3); ...
                0 0 -5 -25 60 -30 0 0; ...
                zeros(1,4) -30 70 -15 -25; ...
                zeros(1,5) -15 15 0; ...
                zeros(1,5) -25 0 25];
            testCase.verifyEqual(testScenario.A, expA, 'RelTol', 1e-10);
        end
        function Constructor__VerifyXMatrixSetup(testCase)
            testScenario = testCase.TestScenario;
            
            testCase.verifyEqual(testScenario.x0, testCase.bounds, 'RelTol', 1e-10);
        end
        function Constructor__VerifyBMatrixSetup(testCase)
            testScenario = testCase.TestScenario;
            
            testCase.verifyEqual(testScenario.b0, testCase.fArr, 'RelTol', 1e-10);
        end
        
        %solve tests
        function Solve__VerifySolveOutputs(testCase)
            testScenario = testCase.TestScenario;
            
            expX = [0 0 0.0638 0 0.1830 0.1887 0 0.3087]';
            expB = [-0.6383 -0.9574 1.0000 -4.5745 5.0000 0 -2.8298 3.0000]';
            
            testScenario.Solve();
            
            testx = testScenario.x;
            testb = testScenario.b;
            
            testx(abs(testx) < 0.001) = 0;
            testb(abs(testb) < 0) = 0;
            
            testCase.verifyEqual(testx, expX, 'RelTol', 0.001);
            testCase.verifyEqual(testb, expB, 'RelTol', 0.001);
        end
    end
    
    methods (Access = protected)
        
        function MakeTestStimuli(testCase)
            pf1 = PointForce(1, 1, 3);
            pf2 = PointForce(1, 5, 5);
            pf3 = PointForce(1, 3, 8);
            
            testCase.Stimuli = [pf1;pf2;pf3];
        end
        
        function MakeTestElements(testCase)
            testCase.MakeTestNodes();
            
            e1 = Spring(1, testCase.Nodes(1), testCase.Nodes(3), ...
                testCase.kArr(1), testCase.Method);
            e2 = Spring(2, testCase.Nodes(2), testCase.Nodes(3), ...
                testCase.kArr(2), testCase.Method);
            e3 = Spring(3, testCase.Nodes(3), testCase.Nodes(5), ...
                testCase.kArr(3), testCase.Method);
            e4 = Spring(4, testCase.Nodes(4), testCase.Nodes(5), ...
                testCase.kArr(4), testCase.Method);
            e5 = Spring(5, testCase.Nodes(5), testCase.Nodes(6), ...
                testCase.kArr(5), testCase.Method);
            e6 = Spring(6, testCase.Nodes(6), testCase.Nodes(7), ...
                testCase.kArr(6), testCase.Method);
            e7 = Spring(7, testCase.Nodes(6), testCase.Nodes(8), ...
                testCase.kArr(7), testCase.Method);
            eles = [e1;e2;e3;e4;e5;e6;e7];
            
            testCase.Elements = eles;
        end
        
        function MakeTestNodes(testCase)
            testCase.MakeBoundaryConditions();
            
            n1 = Node(1, testCase.Bounds{1});
            n2 = Node(2, testCase.Bounds{2});
            n3 = Node(3, testCase.Bounds{3});
            n4 = Node(4, testCase.Bounds{4});
            n5 = Node(5, testCase.Bounds{5});
            n6 = Node(6, testCase.Bounds{6});
            n7 = Node(7, testCase.Bounds{7});
            n8 = Node(8, testCase.Bounds{8});
            nodes = [n1;n2;n3;n4;n5;n6;n7;n8];
            
            testCase.Nodes = nodes;
        end
        
        function bounds = MakeBoundaryConditions(testCase)
            bounds = cell(8,1);
            bounds{1} = BoundaryConditions(1, 0);
            bounds{2} = BoundaryConditions(1, 0);
            bounds{3} = BoundaryConditions(1);
            bounds{4} = BoundaryConditions(1, 0);
            bounds{5} = BoundaryConditions(1);
            bounds{6} = BoundaryConditions(1);
            bounds{7} = BoundaryConditions(1, 0);
            bounds{8} = BoundaryConditions(1);
            
            testCase.Bounds = bounds;
        end
    end
end

