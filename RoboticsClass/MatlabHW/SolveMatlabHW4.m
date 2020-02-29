clear
clc

%% PROBLEM 1
fprintf("Problem 1 - Inverse Kinematics:\n\n");

syms phi x y xy len1 len2 linkLens outKin

xy = [x; y];
linkLens = [len1; len2];

outKin = InvKin2Link3Dof(xy, linkLens, phi);

fprintf("Theta 1 = \n");
disp(outKin(1));

fprintf("\n\nTheta 2 = \n");
disp(outKin(2));

fprintf("\n\nTheta 3 = \n");
disp(outKin(2));

clear

%% PROBLEM 2
fprintf("Problem 2 - Cartesian Matrices:\n\n");

syms pEE0 flatFrms x y z s2 c2 s23 c23 thdot thdot1 thdot2 thdot3 th1 th2 th3 V00 V11 V22 V33 V30 VEE VEE0 W00 W11 W22 W33 W30 WEE WEE0 VW33 VW30 VWEE0 J33 J30 JEE0 dhParams env

len1 = 0.2;
len2 = 0.3;
lenEE = 0.15;
dhParams = [0 0 len1 th1; 0 pi/2 0 th2; len2 0 0 th3];
env = Helpers.BuildFromDhParams(dhParams, false);
pEE3 = [0.15;0;0];
env.Origin.MappedFrames{3,1}.AffixedPositions = vertcat(env.Origin.MappedFrames{3,1}.AffixedPositions, pEE3);
pEE0 = Helpers.ReorientPosition(pEE3, env.Origin.MappedFrames{3,2}.Matrix(1:3,1:3));
pEE3rot = diag(ones(1,3));
tMatEE3 = vertcat(horzcat(pEE3rot, pEE3), [0 0 0 1]);
tMatEE0 = env.Origin.MappedFrames{3,2}.Matrix * tMatEE3;

env.Origin.MappedPositions = vertcat(env.Origin.MappedPositions, {env.Origin.MappedFrames{3,1} , pEE0, tMatEE0});
flatFrms = Helpers.FlattenAffixedFrames(env.Origin.AffixedFrames);

V00 = [0;0;0];
W00 = [0;0;0];
V11 = flatFrms{1,2}.Matrix(1:3,1:3)'*(V00 + cross(W00,flatFrms{1,2}.Matrix(1:3,4)));
W11 = flatFrms{1,2}.Matrix(1:3,1:3)'*W00 + [0;0;thdot1];
V22 = flatFrms{2,2}.Matrix(1:3,1:3)'*(V11 + cross(W11,flatFrms{2,2}.Matrix(1:3,4)));
W22 = flatFrms{2,2}.Matrix(1:3,1:3)'*W11 + [0;0;thdot2];

V33 = simplify(flatFrms{3,2}.Matrix(1:3,1:3)'*(V22 + cross(W22, flatFrms{3,2}.Matrix(1:3,4))));
W33 = simplify(flatFrms{3,2}.Matrix(1:3,1:3)'*W22 + [0;0;thdot3]);
VW33 = vertcat(V33, W33);

VEE = tMatEE3(1:3,1:3)'*(V33 + cross(W33, tMatEE3(1:3,4)));
WEE = tMatEE3(1:3,1:3)'*W33;
VWEE = vertcat(VEE, WEE);

VEE0 = simplify(tMatEE0(1:3,1:3)*VEE);
WEE0 = simplify(tMatEE0(1:3,1:3)*WEE);
VWEE0 = vertcat(VEE0, WEE0);

V30 = simplify(env.Origin.MappedFrames{3,2}.Matrix(1:3,1:3)*V33);
W30 = simplify(env.Origin.MappedFrames{3,2}.Matrix(1:3,1:3)*W33);
VW30 = vertcat(V30, W30);

fprintf("VW33 = \n\n");
disp(VW33);

fprintf("VW30 = \n\n");
disp(VW30);


%% PROBLEM 3
fprintf("Problem 3 - Jacobian Matrices:\n\n");

thdot = [thdot1 thdot2 thdot3];
J33 = simplify(jacobian(VW33,thdot));
R30_big = vertcat(horzcat(env.Origin.MappedFrames{3,2}.Matrix(1:3,1:3), zeros(3,3)), horzcat(zeros(3,3),env.Origin.MappedFrames{3,2}.Matrix(1:3,1:3)));
J30 = simplify(R30_big*J33);

JEE = simplify(jacobian(VWEE, thdot));
REE0_big = vertcat(horzcat(tMatEE0(1:3,1:3), zeros(3,3)), horzcat(zeros(3,3),tMatEE0(1:3,1:3)));
JEE0 = simplify(REE0_big*JEE);


fprintf("Jacobian matrix of frame 3 relative to itself = \n\n");
disp(J33);

fprintf("Jacobian matrix of frame 3 relative to frame 0 = \n\n");
disp(J30);

%% PROBLEM 4
fprintf("Problem 4 - Jacobian Singularities:\n\n");

syms detJ

%det(J^2) = det(J*J')
detJ = 0 == sqrt(det(J30*J30'));

detJ = solve(detJ, th1, th2, th3);

disp("The robot loses rank when:")
fprintf("Theta 1 = 0\n\n")
fprintf("Theta 2 = 0\n\n")
fprintf("Theta 3 = 0\n\n")
disp("Or, in other words, when the robot is completely straight.");

%% PROBLEM 5
fprintf("\n\nProblem 5 - Forces & Torques:\n\n");

syms tauEE0

fEE0_1 = [2 0 0 0 3 0]';
fEE0_2 = [0 4 0 0 0 5]';
fEE0_3 = [0 0 6 0 0 0]';
fEE0_4 = [0 3 0 0 0 0]';

fprintf("\n\nProblem 5:1\n\n");
theta.th1 = 0;
theta.th2 = pi/2;
theta.th3 = 0;
fprintf("Iterative Method:\n\n");

fEE = fEE0_1(1:3);
nEE = fEE0_1(4:6);

f33 = vpa(subs(tMatEE3(1:3,1:3)*fEE, theta));
n33 = vpa(subs(tMatEE3(1:3,1:3)*nEE + cross(tMatEE3(1:3,4), f33), theta));

f22 = vpa(subs(flatFrms{3,2}.Matrix(1:3,1:3)*f33, theta));
n22 = vpa(subs(flatFrms{3,2}.Matrix(1:3,1:3)*n33 + cross(flatFrms{3,2}.Matrix(1:3,4), f22), theta));

f11 = vpa(subs(flatFrms{2,2}.Matrix(1:3,1:3)*f22, theta));
n11 = vpa(subs(flatFrms{2,2}.Matrix(1:3,1:3)*n22 + cross(flatFrms{2,2}.Matrix(1:3,4), f11), theta));

f00 = vpa(subs(flatFrms{1,2}.Matrix(1:3,1:3)*f11, theta));
n00 = vpa(subs(flatFrms{1,2}.Matrix(1:3,1:3)*n11 + cross(flatFrms{1,2}.Matrix(1:3,4), f00), theta));

fprintf("nEE = \n")
disp(nEE);
fprintf("n33 = \n")
disp(n33);
fprintf("n22 = \n")
disp(n22);
fprintf("n11 = \n")
disp(n11);
fprintf("n00 = \n")
disp(n00);

fprintf("Jacobian Method:\n");
tauEE0 = vpa(subs(JEE0'*fEE0_1, theta));
fprintf("tauEE0 = \n\n");
disp(tauEE0);

fprintf("\n\nProblem 5:2\n\n");
theta.th1 = 0;
theta.th2 = 0;
theta.th3 = pi/2;
fprintf("Iterative Method:\n\n");

fEE = fEE0_2(1:3);
nEE = fEE0_2(4:6);

f33 = vpa(subs(tMatEE3(1:3,1:3)*fEE, theta));
n33 = vpa(subs(tMatEE3(1:3,1:3)*nEE + cross(tMatEE3(1:3,4), f33), theta));

f22 = vpa(subs(flatFrms{3,2}.Matrix(1:3,1:3)*f33, theta));
n22 = vpa(subs(flatFrms{3,2}.Matrix(1:3,1:3)*n33 + cross(flatFrms{3,2}.Matrix(1:3,4), f22), theta));

f11 = vpa(subs(flatFrms{2,2}.Matrix(1:3,1:3)*f22, theta));
n11 = vpa(subs(flatFrms{2,2}.Matrix(1:3,1:3)*n22 + cross(flatFrms{2,2}.Matrix(1:3,4), f11), theta));

f00 = vpa(subs(flatFrms{1,2}.Matrix(1:3,1:3)*f11, theta));
n00 = vpa(subs(flatFrms{1,2}.Matrix(1:3,1:3)*n11 + cross(flatFrms{1,2}.Matrix(1:3,4), f00), theta));

fprintf("nEE = \n")
disp(nEE);
fprintf("n33 = \n")
disp(n33);
fprintf("n22 = \n")
disp(n22);
fprintf("n11 = \n")
disp(n11);
fprintf("n00 = \n")
disp(n00);

fprintf("Jacobian Method:\n");
tauEE0 = vpa(subs(JEE0'*fEE0_2, theta));
fprintf("tauEE0 = \n\n");
disp(tauEE0);

fprintf("\n\nProblem 5:3\n\n");
theta.th1 = pi/2;
theta.th2 = pi/2;
theta.th3 = 0;
fprintf("Iterative Method:\n\n");

fEE = fEE0_3(1:3);
nEE = fEE0_3(4:6);

f33 = vpa(subs(tMatEE3(1:3,1:3)*fEE, theta));
n33 = vpa(subs(tMatEE3(1:3,1:3)*nEE + cross(tMatEE3(1:3,4), f33), theta));

f22 = vpa(subs(flatFrms{3,2}.Matrix(1:3,1:3)*f33, theta));
n22 = vpa(subs(flatFrms{3,2}.Matrix(1:3,1:3)*n33 + cross(flatFrms{3,2}.Matrix(1:3,4), f22), theta));

f11 = vpa(subs(flatFrms{2,2}.Matrix(1:3,1:3)*f22, theta));
n11 = vpa(subs(flatFrms{2,2}.Matrix(1:3,1:3)*n22 + cross(flatFrms{2,2}.Matrix(1:3,4), f11), theta));

f00 = vpa(subs(flatFrms{1,2}.Matrix(1:3,1:3)*f11, theta));
n00 = vpa(subs(flatFrms{1,2}.Matrix(1:3,1:3)*n11 + cross(flatFrms{1,2}.Matrix(1:3,4), f00), theta));

fprintf("nEE = \n")
disp(nEE);
fprintf("n33 = \n")
disp(n33);
fprintf("n22 = \n")
disp(n22);
fprintf("n11 = \n")
disp(n11);
fprintf("n00 = \n")
disp(n00);

fprintf("Jacobian Method:\n");
tauEE0 = vpa(subs(JEE0'*fEE0_3, theta));
fprintf("tauEE0 = \n\n");
disp(tauEE0);

fprintf("\n\nProblem 5:4\n\n");
theta.th1 = 0;
theta.th2 = pi/2;
theta.th3 = 0;
fprintf("Iterative Method:\n\n");

fEE = fEE0_4(1:3);
nEE = fEE0_4(4:6);

f33 = vpa(subs(tMatEE3(1:3,1:3)*fEE, theta));
n33 = vpa(subs(tMatEE3(1:3,1:3)*nEE + cross(tMatEE3(1:3,4), f33), theta));

f22 = vpa(subs(flatFrms{3,2}.Matrix(1:3,1:3)*f33, theta));
n22 = vpa(subs(flatFrms{3,2}.Matrix(1:3,1:3)*n33 + cross(flatFrms{3,2}.Matrix(1:3,4), f22), theta));

f11 = vpa(subs(flatFrms{2,2}.Matrix(1:3,1:3)*f22, theta));
n11 = vpa(subs(flatFrms{2,2}.Matrix(1:3,1:3)*n22 + cross(flatFrms{2,2}.Matrix(1:3,4), f11), theta));

f00 = vpa(subs(flatFrms{1,2}.Matrix(1:3,1:3)*f11, theta));
n00 = vpa(subs(flatFrms{1,2}.Matrix(1:3,1:3)*n11 + cross(flatFrms{1,2}.Matrix(1:3,4), f00), theta));

fprintf("nEE = \n")
disp(nEE);
fprintf("n33 = \n")
disp(n33);
fprintf("n22 = \n")
disp(n22);
fprintf("n11 = \n")
disp(n11);
fprintf("n00 = \n")
disp(n00);

fprintf("Jacobian Method:\n")
tauEE0 = vpa(subs(JEE0'*fEE0_4, theta));
fprintf("tauEE0 = \n\n");
disp(tauEE0);
