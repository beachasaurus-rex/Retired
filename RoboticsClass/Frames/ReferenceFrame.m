classdef ReferenceFrame < Frame
    
    %EXPOSED PROPERTIES
    properties (SetAccess = public)
        Origin
        MappedFrames
        MappedPositions
        %Index:
        %   -{ frame1, transformation matrix1 }
        %   -{ frame2, transformation matrix2 }
    end
    
    %EXPOSED METHODS
    methods (Access = public)
        
        %constructor
        function this = ReferenceFrame()
            name = "origin";
            this = this@Frame(name);
            this.MappedPositions = cell.empty;
            this.Origin = [0;0;0];
        end
    end
end



