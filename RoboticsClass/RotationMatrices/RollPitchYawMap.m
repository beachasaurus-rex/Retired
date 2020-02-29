classdef RollPitchYawMap < RotationMatrix
    
    %EXPOSED METHODS
    methods (Access = public)
        
        %constructor
        %this creates the following movement in order:
        %   -alpha degrees about the Z axis
        %   -beta degrees about the Y axis
        %   -gamma degrees about the X axis
        function this = RollPitchYawMap(alpha, beta, gamma, InDegrees)
            if InDegrees
                aZ = this.CalcZRotation(alpha, true);
                bY = this.CalcYRotation(beta, true);
                gX = this.CalcXRotation(gamma, true);
            else
                aZ = this.CalcZRotation(alpha, false);
                bY = this.CalcYRotation(beta, false);
                gX = this.CalcXRotation(gamma, false);
            end
            
            this.Matrix = (aZ*bY)*gX;
        end
    end
end

