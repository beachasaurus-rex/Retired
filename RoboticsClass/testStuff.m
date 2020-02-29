syms T s1 s2 c1 c2 t1(T) t2(T) X Z ZX dX dZ dZX

s1 = sin(t1);
s2 = sin(t2);
c1 = cos(t1);
c2 = cos(t2);

Z = [c1 -s1 0; ...
    s1 c1 0; ...
    0 0 1];

X = [1 0 0; ...
    0 c2 -s2; ...
    0 s2 c2];

ZX = Z*X;

dZ = [-s1 -c1 0; ...
     c1 -s1 0; ...
     0 0 1];

dX = [1 0 0; ...
     0 -s2 -c2; ...
     0 c2 -s2];

dZX = dZ*dX;

if (dZX == ZX)
    disp("they're equal");
else
    disp("they're not equal");
end

ZX

dZX