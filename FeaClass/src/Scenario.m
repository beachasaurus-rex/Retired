classdef Scenario < handle
    
    %read-only properties
    properties (SetAccess = protected, GetAccess = public)
        Name
        StimuliData
        ElementData
        NodeData
        DegreesOfFreedom
        Dimensions
        Method
        A
        %initial variables
        x0
        b0
        %solved variables
        x
        b
    end
    
    %methods
    methods (Access = public)
        
        %ctor
        function this = Scenario(name, elements, nodes, stimuli, dimensions)
            this.Name = name;
            this.Dimensions = dimensions;
            this.BuildElementData(elements);
            this.BuildNodeData(nodes);
            this.BuildStimuliData(stimuli);
            this.DegreesOfFreedom = this.NodeData.Nodes(1).DegreesOfFreedom;
            this.Method = this.ElementData.Elements(1).Method;
            
            this.SetupProblem();
        end
        
        function Solve(this)
            [this.x, this.b] = MatrixSolver(this.A, this.x0, this.b0);
        end
    end
    
    %internal helpers
    methods (Access = protected)
        
        function BuildElementData(this, elements)
            sample = elements(1);
            
            if isa(sample, 'Spring')
                this.ElementData = SpringTable(elements);
            end
        end
        
        function BuildNodeData(this, nodes)
            this.NodeData = NodeTable(nodes);
        end
        
        %revisit this
        function BuildStimuliData(this, stimuli)
            pointForces = [];
            
            %sort the indices based on subclass
            for i = 1:numel(stimuli)
                if isa(stimuli(i), 'PointForce')
                    pointForces = [pointForces; stimuli(i)];
                end
            end
            
            %build the appropriate tables for each subclass
            if numel(pointForces) > 0
                pointForceData = PointForceTable(pointForces);
            end
            
            %merge into a vector
            this.StimuliData = pointForceData; 
        end
        
        function SetupProblem(this)
            this.BuildAMatrix();
            this.BuildXMatrix();
            this.BuildBMatrix();
        end
        
        function BuildBMatrix(this)
            dof = this.DegreesOfFreedom;
            stimuli = this.StimuliData.Stimuli;
            numNodes = numel(this.NodeData.Nodes);
            numVars = dof*numNodes;
            numStims = numel(stimuli);
            
            bg = zeros(numVars,1);
            
            for i = 1:numStims
                curStim = stimuli(i);
                nodeId = curStim.AffectedNodeId;
                bg(nodeId:nodeId+dof-1) = curStim.Vector;
            end
            
            this.b0 = bg;
        end
        
        function BuildXMatrix(this)
            dof = this.DegreesOfFreedom;
            nodes = this.NodeData.Nodes;
            numVars = numel(nodes) * dof;
            
            xtemp = zeros(numVars,1);
            for i = 1:dof:numVars
                if i == 1
                    xtemp(i:dof,1) = nodes(i).BoundaryConditions.Values;
                else
                    xtemp(i:dof+i-1,1) = nodes(i).BoundaryConditions.Values;
                end
            end
            
            this.x0 = xtemp;
        end
        
        function BuildAMatrix(this)
            if isa(this.ElementData, 'SpringTable')
                aLocals = this.MapSpringMatrices();
                this.BuildLinearElementAMatrix(aLocals);
            end
        end
        
        function BuildLinearElementAMatrix(this, aLocals)
            dof = this.DegreesOfFreedom;
            numVars = numel(this.NodeData.Nodes) * dof;
            
            Atemp = zeros(numVars, numVars);
            eles = this.ElementData.Elements;
            j = 0;
            for i = 1:numel(eles)
                ids = this.NodeData.Ids;
                inNodeId = ids(ids == eles(i).InputNode.Id);
                outNodeId = ids(ids == eles(i).OutputNode.Id);
                
                if i == 1
                    indices = [inNodeId:(inNodeId+dof-1) ...
                        outNodeId:(outNodeId+dof-1)];
                else
                    indices = [(inNodeId):(inNodeId+dof-1) ...
                        (outNodeId):(outNodeId+dof-1)];
                    j = j + 1;
                end
                
                Atemp(indices, indices) = Atemp(indices, indices) + aLocals{i};
            end
            
            this.A = Atemp;
        end
        
        function aLocals = MapSpringMatrices(this)
            degreesOfFreedom = this.DegreesOfFreedom;
            numEles = numel(this.ElementData.Elements);
            aLocals = cell(numEles,1);
            
            if degreesOfFreedom == 1
                for i = 1:numEles
                    aLocals{i} = this.ElementData.Elements(i).A;
                end
            elseif degreesOfFreedom == 2
                for i = 1:numEles
                    ele = this.ElementData.Elements(i);
                    xy = this.ElementData.XYAngles(i);
                    T = Coordinates.CylindricalTransformMatrix(xy);
                    
                    aLocals{i} = T' * ele.A * T;
                end
            elseif degreesOfFreedom == 3
                for i = 1:numEles
                    ele = this.ElementData.Elements(i);
                    xy = this.ElementData.XYAngles(i);
                    xz = this.ElementData.XZAngles(i);
                    T = Coordinates.SphericalTransformMatrix(xy,xz);
                    
                    aLocals{i} = T' * ele.A * T;
                end
            end
        end
    end
end

