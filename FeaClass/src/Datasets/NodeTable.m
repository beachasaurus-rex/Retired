classdef NodeTable < handle & matlab.mixin.Heterogeneous
    
    %read-only properties
    properties (SetAccess = protected, GetAccess = public)
        Nodes
        Ids
        DegreesOfFreedom
    end
    
    %methods
    methods (Access = public)
        
        %ctor
        function this = NodeTable(nodes)
            this.Nodes = nodes;
            this.DegreesOfFreedom = this.Nodes(1).DegreesOfFreedom;
            
            this.SetupTable();
        end
    end
    
    %internal helpers
    methods (Access = protected)
        
        function SetupTable(this)
            numNodes = numel(this.Nodes); 
            this.Ids = zeros(numNodes,1);
            for i = 1:numNodes
                this.Ids(i) = this.Nodes(i).Id;
            end
        end
    end
end

