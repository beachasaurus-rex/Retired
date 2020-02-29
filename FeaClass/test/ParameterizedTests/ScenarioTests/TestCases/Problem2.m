function [A, x, b, elements, nodes] = Problem2()
    %% Solve the problem using the method from the lab
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
    
    A = Kg;
    b = Fg;
    x = Ug;

    %% Build the classes for the function output
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
end

