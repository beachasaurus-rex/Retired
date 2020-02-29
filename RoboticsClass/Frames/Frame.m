classdef (Abstract) Frame < handle
    
    properties (SetAccess = public)
        Name
        AffixedFrames
        %Index:
        %   -{ frame1, transformation matrix1}
        %   -{ frame2, transformation matrix2}
        
        AffixedPositions
        %Index:
        %   -{position 1}
        %   -{position 2}
    end
    
    
    methods (Access = public)
        
        %constructor
        function this = Frame(name)
            this.Name = name;
            this.AffixedFrames = cell.empty;
            this.AffixedPositions = cell.empty;
        end
    end
end

