%  ME 476: INTRODUCTION TO ROBOTICS,
%  Homework 5 | Spring 2019
%  Problem - 1,2,3
%........................................................................
clc
clear all
digits(5)
% Mass, Coriolis, Gravity
% ExoRob Position Check
%=========================================================================
syms Ixx1  Ixx2 Ixx3 real;      % Inertia tensor in x axix
syms Iyy1  Iyy2 Iyy3 real;      % Inertia tensor in Y axix
syms Izz1  Izz2 Izz3 real;      % Inertia tensor in Z axix

syms q1 q2 q3 real;
syms q1d q2d q3d real;
syms q1dd q2dd q3dd real;

syms  m1 m2 m3 real;   % mass of links
syms L1 L2 Ltip g real;
syms fx fy fz taux tauy tauz real   % Force and torque at end effector

%q2=pi/2+q2;  % DH Parameter correction

m1=1.5; m2 = 1.25; m3=1;    % in kg
L1=0.2; L2=0.30; Ltip=0.15;

% Cntr f Gravity
Pc11=[0;0;-L1/3];     % Both Joint 1 and 2 are at same point
Pc22=[(2*L2)/3;0;0];
Pc33=[(2*Ltip)/3;0;0];     % Both Joint 3 and 4 are at same point
            
Ixx1=0.0035;   Iyy1=0.0035;   Izz1=0.0035;
Ixx2=0.0022;   Iyy2=0.0022;   Izz2=0.0022;
Ixx3=0.0015;   Iyy3=0.0015;   Izz3=0.0015;

%=========================================================================

q = [q1 q2 q3];
qd = [q1d q2d q3d];
qdd = [q1dd q2dd q3dd];
% -------------------------------------------------------------------------
% Direct Approch
% -------------------------------------------------------------------------
% Link Transformation T(i->(i-1))
%==========================================
% Transformatiom (joint to joint 0 1 2 3 4 5 6 7)
%================================================
%========================================
T10=[ cos(q1) -sin(q1)  0       0;
      sin(q1)  cos(q1)  0       0;
        0        0      1       L1;
        0        0      0       1 ];
    %....................................
R10=T10([1 2 3],[1 2 3]);
R01=R10';
P10=T10([1 2 3],[4]);
%========================================
T21=[ cos(q2-pi/2)  -sin(q2-pi/2)     0       0;
        0                0            1       0;
     -sin(q2-pi/2)    -cos(q2-pi/2)   0       0;
        0                0            0       1];
    %.....................................
R21=T21([1 2 3],[1 2 3]);
R12=R21';
P21=T21([1 2 3],[4]); 

%========================================
T32=[ cos(q3)    -sin(q3)     0       L2;
      sin(q3)     cos(q3)     0       0;
        0           0         1       0;
        0           0         0       1 ];
    %....................................
R32 =T32([1 2 3],[1 2 3]);
R23=R32';
P32 =T32([1 2 3],[4]); 

%  Tip(End-Effector) Frame, {4}
%---------------------------------------
T43=[ 1  0   0    Ltip;
      0  1   0    0;
      0  0   1    0;
      0  0   0    1];
    %....................................
R43 =T43([1 2 3],[1 2 3]);
R34 =R43';
P43 =T43([1 2 3],[4]);
%========================================
T40=T10*T21*T32*T43;
%========================================
I1c1   = [Ixx1 0 0;0 Iyy1 0;0 0 Izz1];
I2c2   = [Ixx2 0 0;0 Iyy2 0;0 0 Izz2];    %  Point mass assumption bet^n {2}-{3}
I3c3   = [Ixx3 0 0;   0 Iyy3 0;   0 0 Izz3];

         


%=======================================================================
% The Iterative Newton Euler Dynamics Begins
%=====================================================================
w00 = zeros(3,1);     % As the base of the robots is not moving {0}
wd00 = zeros(3,1);    % As the base of the robots is not moving {0}
vd00 = [0 0 g]';     % Gravity +ve in upward direction of {Z0}

%Outward iteration for link 1, i=0 (where [i:0,1,2]:3)
% frame {0}, {1} are at same point
w11  = R01*w00+[0 0 q1d]';
wd11 = R01*wd00+cross(R01*w00,[0 0 q1d]')+[0 0 q1dd]';
vd11 = R01*(cross(wd00,P10)+cross(w00,cross(w00,P10))+vd00);
vdc11= cross(wd11,Pc11)+cross(w11,cross(w11,Pc11))+vd11;
F11  = m1*vdc11;
N11  = I1c1*wd11+cross(w11,I1c1*w11);

%Outward iteration for link 2, i=1 (where [i:0,1,2]:3)
%frame {2}, {3} are at same point
w22  = R12*w11+[0 0 q2d]';
wd22 = R12*wd11+cross(R12*w11,[0 0 q2d]')+[0 0 q2dd]';
vd22 = R12*(cross(wd11,P21)+cross(w11,cross(w11,P21))+vd11);
vdc22= cross(wd22,Pc22)+cross(w22,cross(w22,Pc22))+vd22;
F22  = m2*vdc22;
N22  = I2c2*wd22+cross(w22,I2c2*w22);

%Outward iteration for link 3, i=2 (where [i:0,1,2]:3)
%frame {2}, {3} are at same point
w33   = R23*w22+[0 0 q3d]';
wd33  = R23*wd22+cross(R23*w22,[0 0 q3d]')+[0 0 q3dd]';
vd33  = R23*(cross(wd22,P32)+cross(w22,cross(w22,P32))+vd22);
vdc33 = cross(wd33,Pc33)+cross(w33,cross(w33,Pc33))+vd33;
F33   = m3*vdc33;
N33   = I3c3*wd33+cross(w33,I3c3*w33);
%-------------------------------------------------------------------------
%Inward iteration for link 3, i=3 (where [i:3,2,1]:0)
% n44=[taux;tauy;tauz];         
% f44=[fx;fy;fz];      
n44=[0;0;0];    % No interection with envirnment       
f44=[0;0;0];   % No interection with envirnment   
f33   = R43*f44+F33;
n33   = N33+R43*n44+cross(Pc33,F33)+cross(P43,R43*f44);
% tau3  = simplify(simple(n33(3)));
tau3  =n33([3],:);

%Inward iteration for link 2, i=2 (where [i:3,2,1]:0)
%frame {3}, {2} are at same point
f22   = R32*f33+F22;
n22   = N22+R32*n33+cross(Pc22,F22)+cross(P32,R32*f33);
% tau2  = simplify(simple(n22(3)));
tau2   =n22([3],:);

%Inward iteration for link 1, i=1 (where [i:3,2,1]:0)
%frame {1}, {0} are at same point
f11   = R21*f22+F11;
n11   = N11+R21*n22+cross(Pc11,F11)+cross(P21,R21*f22);
% tau1  = simplify(simple(n11(3)));
tau1  =n11([3],:);
% =======================================================
% Extracting Mass/Inertia elememts from torque
%-------------------------------------------------------

m11=simplify(diff(tau1, q1dd));
m21=simplify(diff(tau2, q1dd));
m31=simplify(diff(tau3, q1dd));

m12=simplify(diff(tau1, q2dd));
m22=simplify(diff(tau2, q2dd)); 
m32=simplify(diff(tau3, q2dd));

m13=simplify(diff(tau1, q3dd));
m23=simplify(diff(tau2, q3dd));
m33=simplify(diff(tau3, q3dd));
%------------------------------------------------------
%disp('The mass matrix is given below as calculated')
M=[m11 m12 m13;
   m21 m22 m23;
   m31 m32 m33];
save M
fprintf('Mass Matrix of developed dynamic model M=\n[%s   %s   %s\n   %s     %s    %s\n   %s    %s     %s ]\n\n',m11,m12,m13,m21,m22,m23,m31,m32,m33);


      matlabFunction(M,'file','PM3.m','vars',{q});
% =======================================================
% Extracting Gravity elememts from torque
%-------------------------------------------------------
g11=simplify(diff(tau1, g));
g21=simplify(diff(tau2, g));
g31=simplify(diff(tau3, g));
%disp('The gravity matrix is G')
G=g*[g11; g21; g31];
save G

fprintf('Gravity Vector of developed dynamic model, G=\n[\t\t\t%s\n\n%s\n\n\t\t%s]\n\n',g11,g21,g31);

matlabFunction(G,'file','PG3.m','vars',{q,g});

% =======================================================
% Extracting Corilolis/Centrifugal terms from torque
%-------------------------------------------------------
q1dd=0; q2dd=0; q3dd=0; g=0;

V1t=vpa(subs(tau1));
 save V1t
V2t=vpa(subs(tau2));
 save V2t
V3t=vpa(subs(tau3));
 save V3t

 V=[V1t V2t V3t]';
 save V
 
fprintf('Velocity Vector of developed dynamic model, V=\n[%s\n\n%s\n\n%s]\n\n',V1t,V2t,V3t);

 matlabFunction(V,'file','PV3.m','vars',{q,qd});
 %=========================================================================
 %                           Dynamic check
 %=========================================================================
 g=9.8; 
 q1=(80)*(pi/180); q2=(80)*(pi/180); q3=(80)*(pi/180);
 q1dd=(60)*(pi/180); q2dd=(60)*(pi/180); q3dd=(60)*(pi/180); 
 q1d=(75)*(pi/180); q2d=(75)*(pi/180); q3d=(75)*(pi/180); 
 qddr=[q1dd q2dd q3dd]';
 %-------------------------------------------------------------------------
fprintf('Torque using Recursive equation        : [%0.2f %0.2f %0.2f]\n\n', vpa((subs([tau1 tau2 tau3])')));
fprintf('Torque using developed M,V,and G Terms : [%0.2f %0.2f %0.2f]\n\n', ((vpa(subs(M))*vpa(subs(qddr)))+vpa(subs(V))+vpa(subs(G)))');
