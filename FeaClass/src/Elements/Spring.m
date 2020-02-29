classdef Spring < LinearElement
    
    %read-only properties
    properties (SetAccess = private, GetAccess = public)
        InputNode
        OutputNode
        SpringCoefficient
        Method
        DegreesOfFreedom
        SymbolicVariables
        Asym
        A
        x
    end
    
    %methods
    methods (Access = public)
        
        %ctor
        function this = Spring(id, inputNode, outputNode, ...
            springCoefficient, solutionMethod)
            this@LinearElement(id);
            
            if isa(inputNode, 'Node')
                this.InputNode = inputNode;
            else
                error('Spring:Ctor:InputNode', ...
                    'Input node for element %d must be a Node object.', ...
                    this.Id);
            end
            
            if isa(outputNode, 'Node')
                this.OutputNode = outputNode;
            else
                error('Spring:Ctor:OutputNode', ...
                    'Output node for element %d must be a Node object.', ...
                    this.Id);
            end
            
            this.DegreesOfFreedom = this.InputNode.DegreesOfFreedom;
            this.SpringCoefficient = springCoefficient;
            this.Method = solutionMethod;
            this.SetupElement();
        end
    end
    
    %internal helpers
    methods (Access = protected)
        
        function SetupElement(this)
            %make the elemental matrix
            this.Asym = ...
                Spring.MakeElementalMatrix(this.Method, this.DegreesOfFreedom);
            
            %get the symbolic variables from the elemental matrix
            this.SymbolicVariables = symvar(this.Asym);
            
            %substitute the actual values for the symbolic variables
            this.A = ...
                subs(this.Asym, this.SymbolicVariables, this.SpringCoefficient);
            
            %build the x matrix
            this.x = Spring.MakeXMatrix(this.InputNode, this.OutputNode);
        end
    end
    
    %static internal helpers
    methods (Static, Access = protected)
        
        function ele = MakeElementalMatrix(solutionMethod, ...
                degreesOfFreedom)
            if solutionMethod == SolutionMethod.Direct
                ele = DirectSpringElementalMatrix(degreesOfFreedom);
            elseif solutionMethod == SolutionMethod.Energy
                ele = EnergySpringElementalMatrix(degreesOfFreedom);
            else
                error('Spring:SetupElement:UnsupportedSolutionMethod', ...
                    'The given solution method %s is unsupported.', ...
                    char(solutionMethod));
            end
        end
        
        function x = MakeXMatrix(inputNode, outputNode)
            x = [inputNode.BoundaryConditions.Values;
                outputNode.BoundaryConditions.Values];
        end
    end
end

