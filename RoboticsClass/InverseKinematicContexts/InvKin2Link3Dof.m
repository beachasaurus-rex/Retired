%outputs the inverse kinematics for a 3-link planar manipulator

%Inputs:
%   -PTip_TipToBase: 1x2 matrix of the position of the tip relative to the base frame
%       --indices = [x; y]
%   -LinkLengths: 1x2 length matrix for link1, link2, and link3(frame3 to the tip)
%       --indices = [l1; l2]
function outKins = InvKin2Link3Dof(PTipRelBase, LinkLengths, offsetFromHorizontalInRadians)
    c2 = (PTipRelBase(1)^2 + PTipRelBase(2)^2 - (LinkLengths(1))^2 - (LinkLengths(2))^2) / (2*LinkLengths(1)*LinkLengths(2));
    s2 = sqrt(1-c2);
    th2 = atan2(s2, c2);
    
    k1 = LinkLengths(1) + (LinkLengths(2)*c2);
    k2 = LinkLengths(2)*s2;
    th1 = atan2(PTipRelBase(2),PTipRelBase(1)) - atan2(k2,k1);
    
    th3 = offsetFromHorizontalInRadians - th1 - th2;
    
    outKins = [th1;th2;th3];
end

