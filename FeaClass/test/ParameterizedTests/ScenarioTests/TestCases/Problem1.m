function [A, x, b, elements, nodes] = Problem1()
    %% Solve the problem using the method from the lab
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

    b = Fg;
    x = Ug;
    A = Kg;
    
    %% Build Classes for Test Case
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
end

