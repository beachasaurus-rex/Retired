function [ xp ] = amplitude( t,x,m,k,eta )

xp = zeros(2,1);
xp(1) = x(2);
xp(2) = -x(2)*sqrt(k/m)*eta/m-(k/m)*x(1);
end

