classdef Coordinates
    
    methods (Static, Access = public)
        
        function T = TransformationMatrix(numberOfDimensions,numberOfVariables, ...
                xyAngle, xzAngle)
            if nargin < 4
                xzAngle = 0;
            end
            
            if numberOfDimensions == 2
                T = Coordinates.PolarTransform(xyAngle);
            elseif numberOfDimensions == 3
                T = Coordinates.SphericalTransform(xyAngle, xzAngle);
            else
                T = 1;
                return;
            end
            temp = repmat({T}, numberOfVariables, 1);
            T = blkdiag(temp{:});
        end
        
        function R = BuildVector(numDimensions, magnitude, xy, xz)
            syms az pol r real
            
            if nargin < 4
                xz = 0;
            end
            
            if numDimensions == 2
                x = r*cos(az);
                y = r*sin(az);
                
                R = [x; y];
                R = subs(R, [az r],[xy magnitude]);
            elseif numDimensions == 3
                x = r*sin((pi/2) - pol)*cos(az);
                y = r * sin((pi/2) - pol) * sin(az);
                z = r*cos((pi/2) - pol);
                
                R = [x; y; z];
                R = subs(R, [az pol r],[xy xz magnitude]);
            else
                R = magnitude;
            end
            
            R = double(R);
        end
    end
    
    methods (Static, Access = private)
        
        function T = PolarTransform(xy)
            syms az r real
            x = r*cos(az);
            y = r*sin(az);
            T = jacobian([x; y], [r az]);
            T = double(subs(T, [az r], [xy 1]));
        end
        
        function T = SphericalTransform(xy,xz)
            syms az pol r real
            x = r*sin((pi/2) - pol)*cos(az);
            y = r * sin((pi/2) - pol) * sin(az);
            z = r*cos((pi/2) - pol);
            T = jacobian([x; y; z], [r az pol]);
            T = double(subs(T, [az pol r], [xy xz 1]));
        end
    end
    
    methods (Access = private)
        function this = Coordinates()
        end
    end
end

