function [N, u] = InterpolationFunctionGenerator(numRoots, boundaryConditions)
    syms L x N u uVars aVars equs real
    bounds = L*boundaryConditions;
    
    if numRoots == 1
        a = sym('a', [numRoots+1 1], 'real');
        u = sym('u', [numRoots+1 1], 'real');
        N = sym('N', [numRoots+1 1], 'real');
        equs = sym('equs', [numRoots+1 1], 'real');
        func = a(1) + a(2)*x;
        
        uVars = u;
        aVars = a;
        
        %solve for u
        for i = 1:numRoots+1
            u(i) = subs(func, x, bounds(i));
        end
        
        %setup the equations
        for i = 1:numRoots+1
            equs(i) = uVars(i) == u(i);
        end
        
        %solve for a
        for i = 1:numRoots+1
            if i == 1
                a(i) = solve(equs(i), aVars(i));
            else
                a(i) = subs(equs(i), aVars(i-1), uVars(i-1));
                a(i) = solve(a(i), aVars(i));
            end
        end
        
        %substitute a into the original function
        for i = 1:numRoots+1
                func = subs(func, aVars(i), a(i));
        end
        
        %solve for N
        for i = 1:numRoots+1
            N(i) = diff(func, uVars(i));
        end
    elseif numRoots == 2
        a = sym('a', [numRoots+1 1], 'real');
        u = sym('u', [numRoots+1 1], 'real');
        N = sym('N', [numRoots+1 1], 'real');
        equs = sym('equs', [numRoots+1 1], 'real');
        func = a(1) + a(2)*x + a(3)*x^2;
        
        uVars = u;
        aVars = a;
        
        %solve for u
        for i = 1:numRoots+1
            u(i) = subs(func, x, bounds(i));
        end
        
        %setup the equations
        for i = 1:numRoots+1
            equs(i) = uVars(i) == u(i);
        end
        
        %solve for a
        for i = 1:numRoots+1
            if i == 1
                a(i) = solve(equs(i), aVars(i));
            else
                a(i) = subs(equs(i), aVars(i-1), uVars(i-1));
                a(i) = solve(a(i), aVars(i));
            end
        end
        
        %substitute a into the original function
        for i = 1:numRoots+1
                func = subs(func, aVars(i), a(i));
        end
        
        %solve for N
        for i = 1:numRoots+1
            N(i) = diff(func, uVars(i));
        end
    elseif numRoots == 3
        a = sym('a', [numRoots+1 1], 'real');
        u = sym('u', [numRoots+1 1], 'real');
        N = sym('N', [numRoots+1 1], 'real');
        equs = 0*sym('equs', [numRoots+1 numRoots+1], 'real');
        func = a(1) + a(2)*x + a(3)*x^2 + a(4)*x^3;
        
        uVars = u;
        aVars = a;
        
        %solve for u
        j = 1;
        for i = 1:2:numRoots+1
            u(i) = subs(func, x, bounds(j));
            u(i+1) = subs(diff(func, x), x, bounds(j));
            j = j + 1;
        end
        
        %make matrix to solve for a
        for i = 1:numRoots+1
            for j = 1:numRoots+1
                equs(i,j) = diff(u(i), aVars(j));
            end
        end
        
        %solve for a
        a = equs\uVars;
        
        %substitute a into the original function
        for i = 1:numRoots+1
                func = subs(func, aVars(i), a(i));
        end
        
        %solve for N
        for i = 1:numRoots+1
            N(i) = diff(func, uVars(i));
        end
    end
    
    N = N';
    u = uVars;
end

