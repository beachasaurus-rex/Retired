function transMats = MakeTransformationMatrices(L, th)
%     R10 = Helpers.BuildUnitRotation(th(1), Axis.Z, false);
% 
%     RotZ2 = Helpers.BuildUnitRotation(th(2), Axis.Z, false);
%     RotX2 = Helpers.BuildUnitRotation(th(2), Axis.X, false);
% 
%     R21 = RotX2*RotZ2;
% 
%     R32 = Helpers.BuildUnitRotation(th(3), Axis.Z, false);
    
    T10 = Helpers.LinkTransformation(0, 0, L(1), th(1));
%     T10 = horzcat(R10, [0; 0; L(1)]);
%     T10 = vertcat(T10, [0 0 0 1]);
    
    T21 = [cos(th(2)-pi/2) -sin(th(2)-pi/2) 0 0;...
        0 0 1 0;...
        -sin(th(2)-pi/2) -cos(th(2)-pi/2) 0 0;...
        0 0 0 1];
%     T21 = horzcat(R21, [0; 0; 0]);
%     T21 = vertcat(T21, [0 0 0 1]);
    
    T32 = Helpers.LinkTransformation(L(2), 0, 0, th(3));
%     T32 = horzcat(R32, [L(2); 0; 0]);
%     T32 = vertcat(T32, [0 0 0 1]);
    
    TEE3 = horzcat(eye(3,3), [L(3); 0; 0]);
    TEE3 = vertcat(TEE3, [0 0 0 1]);
    
    T30 = (T10 * T21) * T32;
    TEE0 = ((T10 * T21) * T32) * TEE3;
    
    transMats.T10 = T10;
    transMats.T21 = T21;
    transMats.T32 = T32;
    transMats.TEE3 = TEE3;
    transMats.T30 = T30;
    transMats.TEE0 = TEE0;
end