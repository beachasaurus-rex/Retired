function ele = DirectSpringElementalMatrix(numberOfDimensions)
    syms k real
    
    if numberOfDimensions == 1
        ele = k * [1 -1; -1 1];
    elseif numberOfDimensions == 2
        z = zeros(1,4);
        ele = k * [1 0 -1 0; z; -1 0 1 0; z];
    elseif numberOfDimensions == 3
        z = zeros(1,2);
        ele = k * [1 z -1 z; z z z; z z z; -1 z 1 z; z z z; z z z];
    end
end
