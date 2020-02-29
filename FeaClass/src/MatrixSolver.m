%assumptions:
%   -all inputs are NOT symbolic
function [X, B] = MatrixSolver(A, x, b)
    %initial input copying
    A0 = A;
    x0 = x;
    b0 = b;
    
    %indices of the fixed variables
    indXFixed = find(x0==0);
    
    %a logical array that represents the unsolved variables
    xUnsolved = isnan(x0);
    
    %a logical array that represents the known boundary conditions
    xKnown = x0 ~= 0 & ~isnan(x0);
    
    Ar = A0;
    br = b0;
    if any(xKnown)
        %get the indices of the known boundary conditions
        indXKnown = find(xKnown);
        
        numVars = numel(x0);
        for i = 1:numel(indXKnown)
            ind = indXKnown(i);
            
            %multiply the A column by the index's value
            Ar(:,ind) = Ar(:,ind) * x0(ind);
            
            %subtract the known row from all other rows
            for j = 1:numVars
                if j == ind
                    continue;
                end
                
                br(j) = br(j) - Ar(ind,j);
            end
        end
    end
    
    %clear out the rows & columns corresponding to the fixed variables
    Ar(indXFixed,:) = [];
    Ar(:,indXFixed) = [];
    br(indXFixed,:) = [];
    
    %solve for the unknown x variables
    xr = Ar\br;
    
    x0(xUnsolved) = xr;
    
    %solve for the unknown b variables
    b0 = A0 * x0;
    
    X = x0;
    B = b0;
end
