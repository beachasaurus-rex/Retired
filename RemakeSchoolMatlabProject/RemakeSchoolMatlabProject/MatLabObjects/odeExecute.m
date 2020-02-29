function [ t,x ] = odeExecute( t,x,m,k,eta, t_f, x_0, dx_0 )

[t,x] = ode45(@(t,x) amplitude(t,x,m,k,eta), [0,t_f],[x_0,dx_0]);

end