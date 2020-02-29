classdef BoundaryConditions < handle
    
    %read-only properties
    properties (SetAccess = protected, GetAccess = public)
        DegreesOfFreedom
        Values
    end
    
    %methods
    methods (Access = public)
        
        %ctor
        function this = BoundaryConditions(degreesOfFreedom, values)
            if nargin < 2
                values = nan*zeros(degreesOfFreedom, 1);
            end
            
            this.DegreesOfFreedom = degreesOfFreedom;
            
            %force Values to always be a column vector
            [i,j] = size(values);
            if i < j
                this.Values = values';
            else
                this.Values = values;
            end
            
            %substitute unspecified DoF boundaries with NaN values
            [i,~] = size(this.Values);
            if i < this.DegreesOfFreedom
                temp = zeros(this.DegreesOfFreedom,1);
                temp(1:i) = this.Values;
                temp(i+1:end) = nan;
                this.Values = temp;
            end
        end
    end
end

