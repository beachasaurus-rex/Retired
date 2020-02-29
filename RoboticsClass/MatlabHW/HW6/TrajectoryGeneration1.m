clear
close
clc

% The purpose of this script is to create variables for the following
% situation:
%   - sampling rate = 0.5ms.
%   - Joint 1 is stationary at theta = 0 for the entire simulation.
%   - Joint 2 rotates from 30deg to 120deg in 3 sec.
%   - Joint 3 is stationary at theta = 0 for the entire simulation.

%% Time-Parameter Assignment
%gravity
g = 9.814;

%sampling time
Ts = 0.5/1000;

%final time
t_f = 3;

%sample size
n = 1/Ts*t_f;

%simulation duration
TSim = t_f;

%% Variable Preallocation
%preallocate variable matrices
t0 = zeros(3,1);
tf = t_f*ones(3,1);
th0 = zeros(3,1);
thf = zeros(3,1);

%% Variable Assignment
%assign variables for the simulation
th0(2,1) = 30;
thf(2,1) = 120;

%convert to radians
th0 = (pi/180) * th0;
thf = (pi/180) * thf;

%% Trajectory Generation
%generate joint trajectories
[t, th, thd, thdd] = CubicPolynomial(t0, tf, th0, thf, n);

%% Concatenate Variable Matrices with Time Matrix
%angle v time
th1_desired = horzcat(t(1,:)', th(1,:)');
th2_desired = horzcat(t(2,:)', th(2,:)');
th3_desired = horzcat(t(3,:)', th(3,:)');

%angular velocity v time
thd1_desired = horzcat(t(1,:)', thd(1,:)');
thd2_desired = horzcat(t(2,:)', thd(2,:)');
thd3_desired = horzcat(t(3,:)', thd(3,:)');

%angular acceleration v time
thdd1_desired = horzcat(t(1,:)', thdd(1,:)');
thdd2_desired = horzcat(t(2,:)', thdd(2,:)');
thdd3_desired = horzcat(t(3,:)', thdd(3,:)');

r2d = 180/pi;

%% Plots
figure(1)
% joint 1
% angle plot
subplot(3,3,1), plot(t(1,:), r2d*th(1,:)), grid
      xlabel('Time (s)')
      ylabel('Angle (deg)')
      title('Joint-1')
      xlim([t(1,1) t(1,n)])

% angular velocity plot
subplot(3,3,4), plot(t(1,:), r2d*thd(1,:)), grid
      xlabel('Time (s)')
      ylabel('Angular Velocity (deg/s)')
      xlim([t(1,1) t(1,n)])    

% angular acceleration plot
subplot(3,3,7), plot(t(1,:), r2d*thdd(1,:)), grid
      xlabel('Time (s)')
      ylabel('Angular Acceleration (deg/s^2)')
      xlim([t(1,1) t(1,n)])
      
% joint 2
% angle plot
subplot(3,3,2), plot(t(2,:), r2d*th(2,:)), grid
      xlabel('Time (s)')
      ylabel('Angle (deg)')
      title('Joint-1')
      xlim([t(2,1) t(2,n)])

% angular velocity plot
subplot(3,3,5), plot(t(2,:), r2d*thd(2,:)), grid
      xlabel('Time (s)')
      ylabel('Angular Velocity (deg/s)')
      xlim([t(2,1) t(2,n)])  

% angular acceleration plot
subplot(3,3,8), plot(t(2,:), r2d*thdd(2,:)), grid
      xlabel('Time (s)')
      ylabel('Angular Acceleration (deg/s^2)')
      xlim([t(2,1) t(2,n)])
      
% joint 3
% angle plot
subplot(3,3,3), plot(t(3,:), r2d*th(3,:)), grid
      xlabel('Time (s)')
      ylabel('Angle (deg)')
      title('Joint-1')
      xlim([t(3,1) t(3,n)])

% angular velocity plot
subplot(3,3,6), plot(t(3,:), r2d*thd(3,:)), grid
      xlabel('Time (s)')
      ylabel('Angular Velocity (deg/s)')
      xlim([t(3,1) t(3,n)]) 

% angular acceleration plot
subplot(3,3,9), plot(t(3,:), r2d*thdd(3,:)), grid
      xlabel('Time (s)')
      ylabel('Angular Acceleration (deg/s^2)')
      xlim([t(3,1) t(3,n)])

%% Load Gain Matrices
PidGainMatrices1

%% Helpers
%Cubic Polynomial Function   
function [t, th, thd, thdd] = CubicPolynomial(t0,tf,th0,thf,n)
    % t0= initial time
    % tf= final time
    % th0= initial angle
    % thf= final angle
    % n= sample size
    
    x = numel(t0);
    
    %preallocate
    t = zeros(x,n);
    th = zeros(x,n);
    thd = zeros(x,n);
    thdd = zeros(x,n);
    
    %assign
    for i = 1:1:x
        a0 = th0(i,1);
        a1 = 0;
        a2 = (3/tf(i,1)^2) * (thf(i,1) - th0(i,1));
        a3 = -(2/tf(i,1)^3) * (thf(i,1)-th0(i,1));
        
        t(i,:) = linspace(t0(i,1), tf(i,1), n);

        th(i,:) = (a0 + a1*t(i,:) + a2*t(i,:).^2 + a3*t(i,:).^3);
        thd(i,:) = a1 + 2*a2*t(i,:) + 3*a3*t(i,:).^2;
        thdd(i,:) = (2*a2 + 6*a3*t(i,:));
    end
end