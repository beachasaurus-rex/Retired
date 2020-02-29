classdef PointForce < handle & matlab.mixin.Heterogeneous
    
    %read-only properties
    properties (SetAccess = protected, GetAccess = public)
        Magnitude
        AffectedNodeId
        XYAngle
        XZAngle
        Vector
        NumberOfDimensions
    end
    
    %methods
    methods (Access = public)
        
        function this = PointForce(numDimensions, magnitude, affectedNodeId, ...
                xyAngle, xzAngle)
            if nargin < 4
               xyAngle = 0;
               xzAngle = 0;
            elseif nargin < 5
                xzAngle = 0;
            end
            
            this.NumberOfDimensions = numDimensions;
            this.Magnitude = magnitude;
            this.AffectedNodeId = affectedNodeId;
            this.XYAngle = xyAngle;
            this.XZAngle = xzAngle;
            this.Vector = Coordinates.BuildVector(this.NumberOfDimensions, ...
                this.Magnitude, this.XYAngle, this.XZAngle);
        end
    end
end

