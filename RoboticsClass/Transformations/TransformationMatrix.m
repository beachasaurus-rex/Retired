classdef TransformationMatrix
    
    %EXPOSED PROPERTIES
    properties (SetAccess = public)
        Matrix
    end
    
    %EXPOSED METHODS
    methods (Access = public)
        
        %constructor
        %
        %relativePosition needs to be a 3x1 matrix
        function this = TransformationMatrix(relativePosition, rotMat)
            relPos = ones(4,1);
            relPos(1:3) = relativePosition;
            
            transMat = vertcat(rotMat, [0 0 0]);
            transMat = horzcat(transMat, relPos);
            
            this.Matrix = transMat;
        end
    end
end

