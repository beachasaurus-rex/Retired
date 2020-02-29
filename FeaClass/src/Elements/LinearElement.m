classdef (Abstract) LinearElement < Element
    
    %methods
    methods (Access = protected)
        
        %ctor
        function this = LinearElement(id)
            this@Element(id);
        end
    end
end

