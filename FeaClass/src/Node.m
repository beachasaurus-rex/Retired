classdef Node < handle
    
    %read-only properties
    properties (SetAccess = protected, GetAccess = public)
        Id
        BoundaryConditions
        DegreesOfFreedom
    end
    
    %methods
    methods (Access = public)
        
        %ctor
        function this = Node(id, boundaryConditions)
            if numel(id) == 1 && isa(id, 'double')
                this.Id = id;
            else
                error('Node:Ctor:Id', ...
                    'The Id of a Node must be a single number.');
            end
            
            if isa(boundaryConditions, 'BoundaryConditions')
                this.BoundaryConditions = boundaryConditions;
            else
                error('Node:Ctor:BoundaryConditions', ...
                    'The input boundary conditions of Node %s must be a BoundaryConditions object.', ...
                    this.Id);
            end
            
            this.DegreesOfFreedom = this.BoundaryConditions.DegreesOfFreedom;
        end
    end
end

