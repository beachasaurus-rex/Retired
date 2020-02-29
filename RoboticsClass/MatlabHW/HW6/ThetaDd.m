function thetadd = ThetaDd(in)

    q2 = in(2);
    q3 = in(3);
    
    tvg1 = in(4);
    tvg2 = in(5);
    tvg3 = in(6);
    
    tvg = [tvg1; tvg2; tvg3];
    
    t2 = q2.*2.0;
    t3 = cos(q3);
    t4 = t3.*(3.0./1.0e2);
    t5 = t4+1.15e-2;
    M = reshape([t4-cos(q3.*2.0+t2)./2.0e2-cos(q3+t2).*(3.0./1.0e2)-cos(t2).*(7.0./1.0e2)+8.22e-2,0.0,0.0,0.0,t3.*(3.0./5.0e1)+1.537e-1,t5,0.0,t5,1.15e-2],[3,3]);

    if (det(M) == 0)
        iM = eye(3,3);
    else
        iM = inv(M);
    end
    
    thetadd = iM*tvg;
end

