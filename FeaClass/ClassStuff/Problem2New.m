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

%define nodes
n1 = Node('n1', 1);
n2 = Node('n2', 2);
n3 = Node('n3', 3, 0);
n4 = Node('n4', 4, 0);
n5 = Node('n5', 5, 0);
nodes = [n1;n2;n3;n4;n5];

%elemental function
ef = @(x) [x -x; -x x];

%define elements
e1 = Element('e1', ef, n1, n2, k1);
e2 = Element('e2', ef, n2, n3, k2);
e3 = Element('e3', ef, n2, n4, k3);
e4 = Element('e4', ef, n2, n5, k4);
elements = [e1;e2;e3;e4];

%define reactions
R = zeros(numel(nodes),1);
R(1) = F1;

%create scenario
s = Scenario('Problem 2', elements, nodes, R);
s.Solve;

fprintf('A new:\n');
disp(s.A);

fprintf('x new:\n');
disp(s.x);

fprintf('b new:\n');
disp(s.b);