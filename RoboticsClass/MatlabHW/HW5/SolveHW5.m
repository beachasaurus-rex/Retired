clear
clc
digits(5)
syms th1 th2 th3 thdot1 thdot2 thdot3 th2dot1 th2dot2 th2dot3 g
  
L1 = 0.2;
L2 = 0.3;
L3 = 0.15;

L = [L1 L2 L3];
th = [th1 th2 th3];

subVars = {th1, th2, th3, thdot1, thdot2, thdot3, th2dot1, th2dot2, th2dot3, g};

tMats = MakeTransformationMatrices(L, th);
cellTs = {tMats.T10; tMats.T21; tMats.T32; tMats.TEE3};

Ms = [1.5; 1.25; 1];

Pc1 = [0; 0; -L1/3];
Pc2 = [(2*L2)/3; 0; 0];
Pc3 = [(2*L3)/3; 0; 0];
Pc = {Pc1; Pc2; Pc3};

I1 = 0.0035*eye(3,3);
I2 = 0.0022*eye(3,3);
I3 = 0.0015*eye(3,3);
I = {I1; I2; I3};

th_dot1 = [0 0 thdot1]';
th_dot2 = [0 0 thdot2]';
th_dot3 = [0 0 thdot3]';
thdot = {th_dot1; th_dot2; th_dot3};

th_2dot1 = [0 0 th2dot1]';
th_2dot2 = [0 0 th2dot2]';
th_2dot3 = [0 0 th2dot3]';
th2dot = {th_2dot1; th_2dot2; th_2dot3};

dyns = MakeManipulatorDynamics(Ms, Pc, I, thdot, th2dot, cellTs, g);

%% Problem 1
fprintf("Problem 1 - Dynamic Joint Torques:\n\n")
t = 80*(pi/180);
td = 75*(pi/180);
tdd = 60*(pi/180);

subVals = {t t t td td td tdd tdd tdd 9.8};
tauRec = vpa(subs(dyns.tau, subVars, subVals));
fprintf("Tau =\n");
disp(tauRec);

%% Problem 2
fprintf("\n\nProblem 2 - Symbolic Expressions of M, V, G:\n\n")
tau = dyns.tau;

th = [th1 th2 th3];
thdot = [thdot1 thdot2 thdot3];
th2dot = [th2dot1 th2dot2 th2dot3];

M = simplify(vpa(subs(tau, horzcat(thdot,g), zeros(1,4))))*th2dot;
M = simplify(vpa(subs(M, th2dot, ones(1,3))));
fprintf("M =\n\n");
disp(M);

% vpa(subs(M, [th th2dot], [t t t tdd tdd tdd]))

G = simplify(jacobian(tau, g)*g);
fprintf("\n\nG =\n\n");
disp(G);

V = simplify(vpa(subs(tau, horzcat(th2dot,g), zeros(1,4))));
fprintf("\n\nV =\n\n");
disp(V);

fprintf("\n\nComparison:\n\n")
fprintf("Tau Recursive =\n");
disp(tauRec);
fprintf("\n\nM V G =\n")
MVG = vpa(subs(M, subVars, subVals))*vpa(subs(th2dot', subVars, subVals)) + vpa(subs(V, subVars, subVals)) + vpa(subs(G, subVars, subVals));
disp(MVG);

% %% Generate the *.m files
matlabFunction(M,'file','Mass.m','vars', {th});
matlabFunction(G,'file','Gravity.m','vars', {th g});
matlabFunction(V,'file','Velocity.m','vars', {th thdot});