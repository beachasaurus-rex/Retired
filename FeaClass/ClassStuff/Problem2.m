clear

%forces
%units = N
F1 = -100;

%stiffnesses
%units = N/m
k1 = 100;
k2 = 200;
k3 = 300;
k4 = k3;

%global force matrix
Fg = zeros(5,1);
Fg(1) = F1;

%global displacement matrix
Ug = zeros(5,1);

%global stiffness matrix
Kg = zeros(5,5);

%make a pointer to an anonymous function
Ke = @(x) [x -x; -x x];

%make the elemental stiffness matrices
ke1 = Ke(k1);
ke2 = Ke(k2);
ke3 = Ke(k3);
ke4 = Ke(k4);

%assemble the global stiffness matrix from the elementals
Kg([1 2], [1 2]) = ke1 + Kg([1 2], [1 2]);
Kg([2 3], [2 3]) = ke2 + Kg([2 3], [2 3]);
Kg([2 4], [2 4]) = ke3 + Kg([2 4], [2 4]);
Kg([2 5], [2 5]) = ke4 + Kg([2 5], [2 5]);

%reduce matrix size based on constants
Kgr = Kg(1:2,1:2);
Fgr = Fg(1:2,1);

%solve for displacement
Ugr = Kgr\Fgr;

%solve for reaction force
Ug(1:2,1) = Ugr;

Fg = Kg*Ug;

fprintf('A:\n');
disp(Kg)

fprintf('x:\n');
disp(Ug)

fprintf('b:\n');
disp(Fg)