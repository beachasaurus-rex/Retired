classdef ForwardMap < RotationMatrix
    
    %EXPOSED METHODS
    methods (Access = public)
        
        %constructor
        %this creates the following movement in order:
        %   -alpha degrees about the Z axis
        %   -beta degrees about the X axis
        %   -gamma degrees about the Z axis
        function this = ForwardMap(rotVector, InDegrees)
            [i,j] = size(rotVector);
            if ~(((i == 3) && (j == 1)) || ((i == 1) && (j == 3)))
                error("rotVector argument must be a 3-element vector.");
            end
            
            if InDegrees
                aZ = Helpers.BuildUnitRotation(rotVector(1), Axis.Z, true);
                bX = Helpers.BuildUnitRotation(rotVector(2), Axis.X, true);
                gZ = Helpers.BuildUnitRotation(rotVector(3), Axis.Z, true);
            else
                aZ = Helpers.BuildUnitRotation(rotVector(1), Axis.Z, false);
                bX = Helpers.BuildUnitRotation(rotVector(2), Axis.X, false);
                gZ = Helpers.BuildUnitRotation(rotVector(3), Axis.Z, false);
            end
            
            %this is the correct mapping equation
            this.Matrix = (aZ*bX)*gZ;
        end
    end
end

