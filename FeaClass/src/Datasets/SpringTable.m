classdef SpringTable < LinearElementTable
    
    %read-only properties
    properties (SetAccess = protected, GetAccess = public)
        Elements
        XYAngles
        XZAngles
        InputNodeId
        OutputNodeId
        DegreesOfFreedom
    end
    
    %methods
    methods (Access = public)
        
        %ctor
        function this = SpringTable(elements, xyAngles, xzAngles)
            if nargin == 1
                xyAngles = [];
                xzAngles = [];
            elseif nargin == 2
                xzAngles = [];
            end
            
            this.Elements = elements;
            this.DegreesOfFreedom = this.Elements(1).DegreesOfFreedom;
            this.XYAngles = xyAngles;
            this.XZAngles = xzAngles;
        end
    end
    
    %internal helpers
    methods (Access = protected)
        
        function SetupTable(this)
            for i = 1:numel(this.Elements)
                this.InputNodeId = this.Elements(i).InputNode.Id;
                this.OutputNodeId = this.Elements(i).OutputNode.Id;
            end
        end
    end
end

