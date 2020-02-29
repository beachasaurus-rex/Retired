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

%elemental function
ef = @(x) [x -x; -x x];

%define nodes
n1 = Node('n1', 1, 0);
n2 = Node('n2', 2, 0);
n3 = Node('n3', 3);
n4 = Node('n4', 4, 0);
n5 = Node('n5', 5);
n6 = Node('n6', 6);
n7 = Node('n7', 7, 0);
n8 = Node('n2', 8);
nodes = [n1;n2;n3;n4;n5;n6;n7;n8];

%define elements
e1 = Element('e1', ef, n1, n3, k1);
e2 = Element('e2', ef, n2, n3, k2);
e3 = Element('e3', ef, n3, n5, k3);
e4 = Element('e4', ef, n4, n5, k4);
e5 = Element('e5', ef, n5, n6, k5);
e6 = Element('e6', ef, n6, n7, k6);
e7 = Element('e7', ef, n6, n8, k7);
elements = [e1;e2;e3;e4;e5;e6;e7];

%define reaction forces
R = zeros(numel(nodes),1);
R(3) = F3;
R(5) = F5;
R(8) = F8;

%create scenario
s = Scenario('Problem 1', elements, nodes, R);
s.Solve;

fprintf('A new:\n');
disp(s.A);

fprintf('x new:\n');
disp(s.x);

fprintf('b new:\n');
disp(s.b);