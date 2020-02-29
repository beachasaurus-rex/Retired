classdef Environment < handle
    
    %EXPOSED PROPERTIES
    properties (SetAccess = public)
        Origin
    end
    
    %EXPOSED METHODS
    methods (Access = public)
        
        %constructor
        function this = Environment()
            this.Origin = ReferenceFrame();
        end
        
        %affixes a frame to another frame
        %   -unitRots must be either a 3x1 matrix with the indices:
        %       -element1 = rotation1 about some axis
        %       -element2 = rotation2 about some axis
        %       -element3 = rotation3 about some axis
        %   -translation must be a 3x1 or 1x3 matrix with the indices:
        %       -element1 = x translation
        %       -element2 = y translation
        %       -element3 = z translation
        %   -map is a 3x3 rotation matrix. this can be a compound rotation
        %    or a simple rotation
        function AffixFrame(~, toAffix, target, map, translation)
            
            %flip translation to be a 3x1 if it's a 1x3
            [row,col] = size(translation);
            if (row==1) && (col==3)
                translation = translation';
            end
            
            tMat = TransformationMatrix(translation, map);
            
            target.AffixedFrames = vertcat(target.AffixedFrames, {toAffix, tMat});
        end
        
        %maps all frames in the environment to the origin
        function MapToOrigin(this)
            flattenedFrms = Helpers.FlattenAffixedFrames(this.Origin.AffixedFrames);
            storeTm = TransformationMatrix([0;0;0],eye(3));
            [numFrms, ~] = size(flattenedFrms);

            %iterate through the flattened frames
            for i = 1:numFrms
                curFrm = flattenedFrms{i, 1};
                curTm = flattenedFrms{i, 2};

                %first frame doesn't require matrix multiplication
                if i == 1
                    this.Origin.MappedFrames = vertcat(this.Origin.MappedFrames, {curFrm, curTm});
                else
                    %do matrix multiplication from the current frame to the
                    %closest frame.
                    newTm = TransformationMatrix([0;0;0],eye(3));
                    for j = 1:i
                        iterTm = flattenedFrms{j, 2};

                        newTm.Matrix =  newTm.Matrix * iterTm.Matrix;
                    end
                    storeTm.Matrix = newTm.Matrix;

                    %add the frame + the new transformation matrix
                    this.Origin.MappedFrames = vertcat(this.Origin.MappedFrames, {curFrm, storeTm});
                end
            end
        end
    end
end

