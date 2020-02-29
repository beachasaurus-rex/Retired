classdef ScenarioParamTests < ParameterizedTestBase
    
    properties (Constant)
        TestCaseDir = 'test//ParameterizedTests//ScenarioTests//TestCases//';
    end
    
    properties
        Elements
        Nodes
        expA
        expB
        expX
        TestScenarios
    end
    
    methods (TestClassSetup)
        
        function ParameterizedTests__SetupScenarios(testCase)
            files = ScenarioParamTests.GetTestFiles(testCase);
            numFiles = numel(files);
            
            preAllocCell = cell(numFiles,1);
            Ai = preAllocCell;
            xi = preAllocCell;
            bi = preAllocCell;
            elements = preAllocCell;
            nodes = preAllocCell;
            scenarios = preAllocCell;
            for i = 1:numFiles
                name = files(i).name(1:end-2);
                [Ai{i}, xi{i}, bi{i}, elements{i}, nodes{i}] = feval(name);
                
                scenarios{i} = Scenario(['ScenarioParamTest' sprintf('%d',i)], ...
                    elements{i}, nodes{i}, bi{i});
            end
            
            testCase.expA = Ai;
            testCase.expX = xi;
            testCase.expB = bi;
            testCase.Elements = elements;
            testCase.Nodes = nodes;
            testCase.TestScenarios = scenarios;
        end
    end
    
    methods (Test)
        
        %solve tests
        function Solve__VerifyOutputs(testCase)
            numCases = numel(testCase.TestScenarios);
            
            for i = 1:numCases
                scenario = testCase.TestScenarios{i};
                scenario.Solve;
                
                %need to remove anything close to 0 due to precision errs
                %for anything close to 0
                tol = 1e-10;
                testA = scenario.A;
                testX = scenario.x;
                testB = scenario.b;
                expAi = testCase.expA{i};
                expBi = testCase.expB{i};
                expXi = testCase.expX{i};
                
                testA(testA < tol) = 0;
                testX(testX < tol) = 0;
                testB(testB < tol) = 0;
                expAi(expAi < tol) = 0;
                expBi(expBi < tol) = 0;
                expXi(expXi < tol) = 0;
                testCase.verifyEqual(expAi, testA, 'RelTol', 0.0001);
                testCase.verifyEqual(expXi, testX, 'RelTol', 0.0001);
                testCase.verifyEqual(expBi, testB, 'RelTol', 0.0001);
            end
        end
    end
    
    methods (Static, Access = protected)
        
        function GetTestCases(testCase)
            files = GetTestFiles(testCase);
            
            A = {};
            x = {};
            b = {};
            elements = {};
            nodes = {};
            for i = 1:numel(files)
                name = files.name(1:end-2);
                [Ai, xi, bi, ei, ni] = name();
                
                A = vertcat(A, Ai);
                x = vertcat(x, xi);
                b = vertcat(b, bi);
                elements = vertcat(elements, ei);
                nodes = vertcat(nodes, ni);
            end
            
            testCase.A = A;
            testCase.x = x;
            testCase.b = b;
            testCase.Elements = elements;
            testCase.Nodes = nodes;
        end
        
        function files = GetTestFiles(testCase)
            files = dir(testCase.TestCaseDir);
            
            for i = numel(files):-1:1
                if files(i).isdir == 1
                    files(i) = [];
                end
            end
        end
    end
end

