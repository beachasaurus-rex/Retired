classdef PointForceTable < StimuliTable
    
    %read-only properties
    properties (SetAccess = protected, GetAccess = public)
        XYAngles
        XZAngles
    end
    
    %methods
    methods (Access = public)
        
        %ctor
        function this = PointForceTable(pointForces)
            this.Stimuli = pointForces;
            this.PopulateAngles();
        end
        
        function PopulateAngles(this)
            numEles = numel(this.Stimuli);
            this.XYAngles = zeros(numEles,1);
            this.XZAngles = zeros(numEles,1);
            
            for i = 1:numEles
                this.XYAngles(i) = this.Stimuli(i).XYAngle;
                this.XZAngles(i) = this.Stimuli(i).XZAngle;
            end
        end
    end
end

