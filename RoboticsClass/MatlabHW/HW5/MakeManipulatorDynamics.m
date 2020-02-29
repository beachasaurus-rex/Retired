function Dyns = MakeManipulatorDynamics(Ms, Pcs, Is, thdots, th2dots, tMats, g)
    [y,~] = size(tMats);
    
    %preallocation
    w = cell(y - 1,1);
    wdot = cell(y - 1,1);
    vdot = cell(y - 1,1);
    vCdot = cell(y - 1,1);
    F = cell(y - 1,1);
    N = cell(y - 1,1);
    f = cell(y,1);
    n = cell(y,1);
    tau = cell(y,1);
    
%     T10 = tMats{1,1};
%     R10 = T10(1:3, 1:3);
%     P10 = T10(1:3, 4);
%     
%     T21 = tMats{2,1};
%     R21 = T21(1:3, 1:3);
%     P21 = T21(1:3, 4);
%     
%     T32 = tMats{3,1};
%     R32 = T32(1:3, 1:3);
%     P32 = T32(1:3, 4);
%     
%     TEE3 = tMats{4,1};
%     REE3 = TEE3(1:3, 1:3);
%     PEE3 = TEE3(1:3, 4);
%     
%     %outward iterations
%     w{1,1} = R10'*[0;0;0] + thdots{1};
%     wdot{1,1} = R10'*[0;0;0] + cross(R10'*[0;0;0], thdots{1}) + th2dots{1};
%     vdot{1,1} = R10'*(cross([0;0;0], P10) + cross([0;0;0], cross([0;0;0], P10)) + [0 0 g]');
%     vCdot{1,1} = cross(wdot{1,1}, Pcs{1}) + cross(w{1,1}, cross(w{1,1}, Pcs{1})) + vdot{1,1};
%     F{1,1} = Ms(1)*vCdot{1,1};
%     N{1,1} = (Is{1}*wdot{1,1}) + cross(w{1,1}, (Is{1}*w{1,1}));
%     
%     w{2,1} = (R21'*w{1,1}) + thdots{2};
%     wdot{2,1} = (R21'*wdot{1,1}) + cross(R21'*w{1,1},thdots{2}) + th2dots{2};
%     vdot{2,1} = R21'*(cross(wdot{1,1}, P21) + cross(wdot{1,1}, cross(wdot{1,1}, P21)) + vdot{1,1});
%     vCdot{2,1} = cross(wdot{2,1}, Pcs{2}) + cross(w{2,1}, cross(w{2,1}, Pcs{2})) + vdot{2,1};
%     F{2,1} = Ms(2)*vCdot{2,1};
%     N{2,1} = (Is{2}*wdot{2,1}) + cross(w{2,1}, (Is{2}*w{2,1}));
%     
%     w{3,1} = (R32'*w{2,1}) + thdots{3};
%     wdot{3,1} = (R32'*wdot{2,1}) + cross(R32'*w{2,1},thdots{3}) + th2dots{3};
%     vdot{3,1} = R32'*(cross(wdot{2,1}, P32) + cross(wdot{2,1}, cross(wdot{2,1}, P32)) + vdot{2,1});
%     vCdot{3,1} = cross(wdot{3,1}, Pcs{3}) + cross(w{3,1}, cross(w{3,1}, Pcs{3})) + vdot{3,1};
%     F{3,1} = Ms(3)*vCdot{3,1};
%     N{3,1} = (Is{3}*wdot{3,1}) + cross(w{3,1}, (Is{3}*w{3,1}));
%     
%     %inward iterations
%     f{4,1} = zeros(3,1);
%     n{4,1} = zeros(3,1);
%     
%     f{3,1} = (R32*f{4,1}) + F{3,1};
%     n{3,1} = N{3,1} + (R32*n{4,1}) + cross(Pcs{3},F{3,1}) + cross(P32,(R32*f{4,1}));
%     nM = n{3,1};
%     tau3 = nM(3,:);
%     
%     f{2,1} = (R21*f{3,1}) + F{2,1};
%     n{2,1} = N{2,1} + (R21*n{3,1}) + cross(Pcs{2},F{2,1}) + cross(P21,(R21*f{3,1}));
%     nM = n{2,1};
%     tau2 = nM(3,:);
%     
%     f{1,1} = (R10*f{2,1}) + F{1,1};
%     n{1,1} = N{1,1} + (R10*n{2,1}) + cross(Pcs{1},F{1,1}) + cross(P10,(R10*f{2,1}));
%     nM = n{1,1};
%     tau1 = nM(3,:);
    
    %outward iterations
    for i=1:(y-1)
        T = tMats{i,1};
        R = T(1:3, 1:3);
        P = T(1:3, 4);
        I = Is{i};
        Pc = Pcs{i};
        m = Ms(i);
        thdot = thdots{i};
        th2dot = th2dots{i};
        
        if i == 1
            w{i,1} = (R'*[0;0;0]) + thdot;
            wdot{i,1} = (R'*[0;0;0]) + cross(R'*[0;0;0],thdot) + th2dot;
            vdot{i,1} = R'*(cross([0;0;0], P) + cross([0;0;0], cross([0;0;0], P)) + [0;0;g]);
        else
            w{i,1} = (R'*w{i-1,1}) + thdot;
            wdot{i,1} = (R'*wdot{i-1,1}) + cross(R'*w{i-1,1},thdot) + th2dot;
            vdot{i,1} = R'*(cross(wdot{i-1,1}, P) + cross(wdot{i-1,1}, cross(wdot{i-1,1}, P)) + vdot{i-1,1});
        end
        
        vCdot{i,1} = cross(wdot{i,1}, Pc) + cross(w{i,1}, cross(w{i,1}, Pc)) + vdot{i,1};
        F{i,1} = m*vCdot{i,1};
        N{i,1} = (I*wdot{i,1}) + cross(w{i,1}, (I*w{i,1}));
    end
    
    %inward iterations
    for i = y:-1:1
        if i ~= y
            T = tMats{i+1,1};
            R = T(1:3, 1:3);
            P = T(1:3, 4);
            Pc = Pcs{i};
        end
        
        
        if i == y
            f{i,1} = zeros(3,1);
            n{i,1} = zeros(3,1);
        else
            f{i,1} = (R*f{i+1,1}) + F{i,1};
            n{i,1} = N{i,1} + (R*n{i+1,1}) + cross(Pc,F{i,1}) + cross(P,(R*f{i+1,1}));
        end
        
        nM = n{i,1};
        tau{i,1} = nM(3,:);
    end
    
%     simplify everything
%     i = 1;
%     while i < y
%         w{i,1} = simplify(w{i,1});    
%         wdot{i,1} = simplify(wdot{i,1});
%         vdot{i,1} = simplify(vdot{i,1});
%         vCdot{i,1} = simplify(vCdot{i,1});
%         F{i,1} = simplify(F{i,1});
%         N{i,1} = simplify(N{i,1});  
%         f{i,1} = simplify(f{i,1});
%         n{i,1} = simplify(n{i,1});
%         tau{i,1} = simplify(tau{i,1});
%         
%         i = i + 1;
%     end
    
%     f = f(1:y-1,1);
%     n = n(1:y-1,1);
%     tau = [tau1; tau2; tau3];
    
    Dyns.w = w;
    Dyns.wdot = wdot;
    Dyns.vdot = vdot;
    Dyns.vCdot = vCdot;
    Dyns.F = F;
    Dyns.N = N;
    Dyns.f = f(1:y-1,1);
    Dyns.n = n(1:y-1,1);
    Dyns.tau = tau(1:y-1,1);
end

