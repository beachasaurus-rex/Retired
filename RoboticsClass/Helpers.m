classdef Helpers
    
    methods (Static = true)
        
        %builds an environment based upon input DH Paramenters.
        %   -utilizes FORWARD mapping // does not support RollPitchYaw
        %DH parameter matrix conventions:
        %   -size = i x 4 matrix
        %   -column1 = a_i-1
        %   -column2 = alpha_i-1
        %   -column3 = d_i
        %   -column4 = theta_i
        function outEnv = BuildFromDhParams(dhParams, InDegrees)
            outEnv = Environment();
            
            %build frame array
            %# of rows = # of RelativeFrames
            [numFrames, ~] = size(dhParams);
            frms = cell(numFrames, 1);
            for i = 1:numFrames
                name = sprintf("Frame %d", i);
                %make new frame
                curFrm = RelativeFrame(name);

                frms{i,1} = curFrm;
            end

            %affix frames to each other
            for i = 1:numFrames
                %gets a frame
                curFrm = frms{i,1};

                %get the DH parameters for the current frame
                curParams = dhParams(i,:);

                %rotation vector.
                %   -this assumes rotation about Z, then X, then Z axes.
                rot = [curParams(4) curParams(2) 0];
                fMap = ForwardMap(rot, false);
                
                %distance of the new frame with respect to the previous frame
                %   -x, y, z
                oldPos = [curParams(1) 0 0];
                newPos = [0 0 curParams(3)];
                newPos = Helpers.ReorientPosition(newPos, fMap.Matrix)';
                oldPos = oldPos + newPos;
                
                %affix frames
                if (i == 1)
                    if InDegrees
                        outEnv.AffixFrame(curFrm, outEnv.Origin, fMap.Matrix, oldPos);
                    else
                        outEnv.AffixFrame(curFrm, outEnv.Origin, fMap.Matrix, oldPos);
                    end
                else
                    if InDegrees
                        outEnv.AffixFrame(curFrm, prevFrm, fMap.Matrix, oldPos);
                    else
                        outEnv.AffixFrame(curFrm, prevFrm, fMap.Matrix, oldPos);
                    end
                end
                
                prevFrm = curFrm;
            end

            %map the frames to the reference frame
            outEnv.MapToOrigin();
        end
        
        %outputs a rotation matrix describing rotation about a single axis
        function rotMat = BuildUnitRotation(rotation, axis, InDegrees)
            if axis == Axis.X
                if InDegrees
                    rotMat = [1 0 0;...
                            0 cosd(rotation) -sind(rotation);...
                            0 sind(rotation) cosd(rotation)];
                else
                    rotMat = [1 0 0;...
                            0 cos(rotation) -sin(rotation);...
                            0 sin(rotation) cos(rotation)];
                end

%                 rotMat(abs(rotMat) < 10e-10) = 0;
            elseif axis == Axis.Y
                if InDegrees
                    rotMat = [cosd(rotation) 0 sind(rotation);...
                            0 1 0;...
                            -sind(rotation) 0 cosd(rotation)];
                else
                    rotMat = [cos(rotation) 0 sin(rotation);...
                            0 1 0;...
                            -sin(rotation) 0 cos(rotation)];
                end

%                 rotMat(abs(rotMat) < 10e-10) = 0;
            elseif axis == Axis.Z
                if InDegrees
                    rotMat = [cosd(rotation) -sind(rotation) 0;...
                            sind(rotation) cosd(rotation) 0;...
                            0 0 1];
                else
                    rotMat = [cos(rotation) -sin(rotation) 0;...
                            sin(rotation) cos(rotation) 0;...
                            0 0 1];
                end

%                 rotMat(abs(rotMat) < 10e-10) = 0;
            end
        end
        
        %recursively flattens fixed frame cell arrays into one array
        function outCell = FlattenAffixedFrames(cellArr)
            outCell = cell.empty;
            curFrm = cellArr{1};
            curTM = cellArr{2};
            if (numel(cellArr) > 0)
                outCell = vertcat(outCell, {curFrm curTM});

                if (numel(curFrm.AffixedFrames) > 0)
                    outCell = vertcat(outCell, Helpers.FlattenAffixedFrames(curFrm.AffixedFrames));
                end
            end
        end
        
        %reorients a position by rotating using a rotation matrix
        function newPos = ReorientPosition(position, rotationMatrix)
            [i,j] = size(position);
            if (i ~= 3) && (j ~= 1)

                if (i == 1) && (j == 3)
                    position = position';
                else
                    error("Input arg 'position' for function TransformPosition must be a 3x1 matrix.")
                end
            end

            newPos = rotationMatrix * position;
        end
        
        %transform an input position using an input transformation matrix
        %   -position must be a 3x1 matrix
        function transformedPosition = TransformPosition(position, ...
                                                         transformMatrix)
            [i,j] = size(position);
            if (i ~= 3) && (j ~= 1)

                if (i == 1) && (j == 3)
                    position = position';
                else
                    error("Input arg 'position' for function TransformPosition must be a 3x1 matrix.")
                end
            end
            pos = vertcat(position ,1);
            transformedPosition = transformMatrix * pos;
            transformedPosition = transformedPosition(1:3);
        end
        function T = LinkTransformation(a,alpha,d,theta)
            % Homegenous transformation of frame {i} w.r.t frame {i-1}
            T = [ cos(theta) -sin(theta) 0 a;
                sin(theta)*cos(alpha) cos(theta)*cos(alpha) -sin(alpha) -sin(alpha)*d;
                sin(theta)*sin(alpha) cos(theta)*sin(alpha) cos(alpha) cos(alpha)*d;
                0 0 0 1];
        end
    end
end

