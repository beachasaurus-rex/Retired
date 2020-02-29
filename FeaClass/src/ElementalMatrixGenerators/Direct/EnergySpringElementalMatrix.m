function ele = EnergySpringElementalMatrix(numberOfDimensions)
    syms pPi k u1 u2 fx1 fx2 real
    
    pPi = 0.5 * k * (u2 - u1)^2 - fx1*u1 - fx2*u2;
    ddu1 = diff(diff(pPi, u1),u1);
    du1du2 = diff(diff(pPi, u1),u2);
    du2du1 = diff(diff(pPi, u2),u1);
    ddu2 = diff(diff(pPi, u2),u2);
    
    if numberOfDimensions == 1
        ele = [ddu1 du1du2; du2du1 ddu2];
    elseif numberOfDimensions == 2
        z = zeros(1,4);
        ele = [ddu1 0 du1du2 0; z; du2du1 0 ddu2 0; z];
    elseif numberOfDimensions == 3
        z = zeros(1,2);
        ele = [ddu1 z du1du2 z; z z z; z z z; du2du1 z ddu2 z; z z z; z z z];
    end
end
