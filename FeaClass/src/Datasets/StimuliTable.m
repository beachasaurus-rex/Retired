classdef StimuliTable < handle & matlab.mixin.Heterogeneous
    
    %read-only properties
    properties (SetAccess = protected, GetAccess = public)
        Stimuli
    end
end

