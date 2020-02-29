classdef NodeUnitTests < UnitTestBase
    
    properties
        Id
        NodeBoundaryConditions
        TestNode
    end
    
    methods (TestClassSetup)
        
        function SetupUnitTest_Node(testCase)
            testCase.Id = 1;
            testCase.NodeBoundaryConditions = BoundaryConditions(3, [1 2 3]);
            
            testCase.TestNode = Node(testCase.Id, testCase.NodeBoundaryConditions);
        end
    end
    
    methods (Test)
        
        %constructor tests
        function Constructor__VerifyAssignment(testCase)
            testNode = testCase.TestNode;
            
            testCase.verifyEqual(testCase.Id, testNode.Id);
            testCase.verifyEqual(testNode.BoundaryConditions.DegreesOfFreedom, ...
                testNode.DegreesOfFreedom);
        end
    end
end

