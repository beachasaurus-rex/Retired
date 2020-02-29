clear

%forces
%units = kN
F3 = 1;
F5 = 5;
F8 = 3;

%stiffnesses
%units = kN/m
k1 = 10;
k2 = 15;
k3 = 5;
k4 = 25;
k5 = 30;
k6 = 15;
k7 = 25;

%global force matrix
Fg = zeros(8,1);
Fg(3) = F3;
Fg(5) = F5;
Fg(8) = F8;

%global displacement matrix
Ug = zeros(8,1);

%global stiffness matrix
Kg = zeros(8,8);

%make a pointer to an anonymous function
Ke = @(x) [x -x; -x x];

%make the elemental stiffness matrices
ke1 = Ke(k1);
ke2 = Ke(k2);
ke3 = Ke(k3);
ke4 = Ke(k4);
ke5 = Ke(k5);
ke6 = Ke(k6);
ke7 = Ke(k7);

%assemble the global stiffness matrix from the elementals
Kg([1 3], [1 3]) = ke1 + Kg([1 3], [1 3]);
Kg([2 3], [2 3]) = ke2 + Kg([2 3], [2 3]);
Kg([3 5], [3 5]) = ke3 + Kg([3 5], [3 5]);
Kg([4 5], [4 5]) = ke4 + Kg([4 5], [4 5]);
Kg([5 6], [5 6]) = ke5 + Kg([5 6], [5 6]);
Kg([6 7], [6 7]) = ke6 + Kg([6 7], [6 7]);
Kg([6 8], [6 8]) = ke7 + Kg([6 8], [6 8]);

%reduce matrix size based on constants
Kgr = Kg([3 5 6 8],[3 5 6 8]);
Fgr = Fg([3 5 6 8], 1);

%solve for displacement
Ugr = Kgr\Fgr;

%solve for reaction force
Ug([3 5 6 8],1) = Ugr;

Fg = Kg*Ug;

fprintf('A:\n');
disp(Kg)

fprintf('x:\n');
disp(Ug)

fprintf('b:\n');
disp(Fg)