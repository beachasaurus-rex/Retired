classdef (Abstract) Element < handle & matlab.mixin.Heterogeneous
    
    %read-only properties
    properties (SetAccess = private, GetAccess = public)
        Id
    end
    
    %methods
    methods (Access = protected)
        
        %ctor
        function this = Element(id)
            if numel(id) == 1 && isa(id, 'double')
                this.Id = id;
            else
                error('Element:Ctor:Id', ...
                    'The Id of an Element must be a single number.');
            end
        end
    end
end

