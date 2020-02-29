clear
clc

%%Problem 1, Section A:
fprintf("Problem 1, Section A:\n\n");

A = [1 3 5; 2 4 6];
B = [1 2; 3 4];
C = [1 4; 2 5; 3 6];

AB = A'*B;
AB

BA = B*A;
BA

AC = A*C;
AC

CA = C*A;
CA

BC = B*C';
BC

CB = C*B;
CB

ABxC = AB*C';
fprintf("(AB)C = \n\n")
disp(ABxC)

AxCB = A*CB;
fprintf("A(CB) = \n\n")
disp(AxCB)

%%Problem 1, Section B:
fprintf("Problem 1, Section B:\n\n");
clear

A = [1 2; 3 4];
B = [4 -1; -2 -3];
C = [0 0; 0 0];
D = [1 0; 2 3];
E = [2 0; 0 4];
F = [-1 0; 0 -3];
G = [1 2; -2 -4];

allMats = {A;B;C;D;E;F;G};
fprintf("Answers are in order from A to G.\n\n")
for i = 1:length(allMats)
    curMat = allMats{i};
    dMat = det(curMat);
    disp(dMat)
end

%%Problem 1, Section C:
fprintf("Problem 1, Section C:\n\n");
clear

A = [1 3 3; 1 4 3; 2 7 7];

A_inv = inv(A);
fprintf("A^-1 = \n\n")
disp(A_inv)

A_trans = A';
fprintf("A^T = \n\n");
disp(A_trans)

%%Problem 2
fprintf("Problem 1:\n\n");
clear

posA = [4;5;7];
offset = 40;
posAB = [10;12;5];

tAB = TransformationMatrix(posAB,offset,Axis.Y,true);

posB = TransformPosition(posA,tAB)