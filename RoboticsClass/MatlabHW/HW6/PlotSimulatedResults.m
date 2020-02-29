r2d = 180/pi;

%measured time array
t_plot = TimeSim.Data';

%% Axes Limits
%torque
Tmin = -10;
Tmax = 10;

%error
Emin = -5;
Emax = 5;

%x-axis
Xmin = 0;
Xmax = TSim;

%y-angle
Y_AngleMin = -25;
Y_AngleMax = 125;

%y-angular velocity
Y_VelMin = -25;
Y_VelMax = 100;

%% Reference Trajectories
thRef = r2d * [th_ref.Data(:,1) ...
               th_ref.Data(:,2) ...
               th_ref.Data(:,3)];

thdRef = r2d * [thd_ref.Data(:,1) ...
                thd_ref.Data(:,2) ...
                thd_ref.Data(:,3)];

thddRef = r2d * [thdd_ref.Data(:,1) ...
                 thdd_ref.Data(:,2) ...
                 thdd_ref.Data(:,3)];

%% Measured Trajectories
thMeas = r2d * [th_meas.Data(:,1) ...
                th_meas.Data(:,2) ...
                th_meas.Data(:,3)];
            
thdMeas = r2d * [thd_meas.Data(:,1) ...
                 thd_meas.Data(:,2) ...
                 thd_meas.Data(:,3)];
             
thddMeas = r2d * [thdd_meas.Data(:,1) ...
                  thdd_meas.Data(:,2) ...
                  thdd_meas.Data(:,3)];

tauMeas = [tau.Data(:,1) ...
           tau.Data(:,2) ...
           tau.Data(:,3)];

figure(2)
%% Plotting Joint-1 Properties
%angle
subplot(5,3,1), plot(t_plot,thRef(:,1), ':r', 'LineWidth', 1.5),
    hold on
    plot(t_plot,thMeas(:,1)); 
    hold off

    xlabel('Time (s)')
    ylabel('Angle (deg)')
    title('Joint-1')   
    xlim([Xmin Xmax])
    ylim([Y_AngleMin Y_AngleMax])

    legend({'thRef','thMeas'},'Location','northwest')
    legend('boxoff')
    set(gca,'XMinorTick' , 'on')
    set(gca,'YMinorTick' , 'on')

%angular velocity
subplot(5,3,4), plot(t_plot,thdRef(:,1), ':r', 'LineWidth', 1.5),
    hold on
    plot(t_plot,thdMeas(:,1)); 
    hold off
    
    xlabel('Time (s)')
    ylabel('Ang. Vel. (deg/s)')
    xlim([Xmin Xmax])
    ylim([Y_VelMin Y_VelMax])
    legend({'thdRef','thdMeas'},'Location','northwest')
    legend('boxoff')
    set(gca,'XMinorTick' , 'on')
    set(gca,'YMinorTick' , 'on')

%angular acceleration
subplot(5,3,7), plot(t_plot,thddRef(:,1), ':r', 'LineWidth', 1.5),
    hold on
    plot(t_plot,thddMeas(:,1)); 
    hold off
    
    xlabel('Time (s)')
    ylabel('Ang. Acc. (deg^2/s)')
    xlim([Xmin Xmax])
    ylim([Y_VelMin Y_VelMax])
    legend({'thddRef','thddMeas'},'Location','northwest')
    legend('boxoff')
    set(gca,'XMinorTick' , 'on')
    set(gca,'YMinorTick' , 'on')

%torque
subplot(5,3,10),plot(t_plot,tauMeas(:,1)); ylim([Tmin Tmax])
    xlabel('Time(s)')
    ylabel('Torque (Nm)')
    xlim([Xmin Xmax])
    set(gca,'XMinorTick' , 'on')
    set(gca,'YMinorTick' , 'on')

%error
subplot(5,3,13),plot(t_plot,(thRef(:,1)- thMeas(:,1))); ylim([Emin Emax])
    xlabel('Time (s)')
    ylabel('Error (deg)')
    xlim([Xmin Xmax]) 
    set(gca,'XMinorTick' , 'on')
    set(gca,'YMinorTick' , 'on')

%% Plotting Joint-2 Properties
%angle
subplot(5,3,2), plot(t_plot,thRef(:,2), ':r', 'LineWidth', 1.5),
    hold on
    plot(t_plot,thMeas(:,2)); 
    hold off

    xlabel('Time (s)')
    ylabel('Angle (deg)')
    title('Joint-2')   
    xlim([Xmin Xmax])
    ylim([Y_AngleMin Y_AngleMax])

    legend({'thRef','thMeas'},'Location','northwest')
    legend('boxoff')
    set(gca,'XMinorTick' , 'on')
    set(gca,'YMinorTick' , 'on')

%angular velocity
subplot(5,3,5), plot(t_plot,thdRef(:,2), ':r', 'LineWidth', 1.5),
    hold on
    plot(t_plot,thdMeas(:,2)); 
    hold off
    
    xlabel('Time (s)')
    ylabel('Ang. Vel. (deg/s)')
    xlim([Xmin Xmax])
    ylim([Y_VelMin Y_VelMax])
    legend({'thdRef','thdMeas'},'Location','northwest')
    legend('boxoff')
    set(gca,'XMinorTick' , 'on')
    set(gca,'YMinorTick' , 'on')

%angular acceleration
subplot(5,3,8), plot(t_plot,thddRef(:,2), ':r', 'LineWidth', 1.5),
    hold on
    plot(t_plot,thddMeas(:,2)); 
    hold off
    
    xlabel('Time (s)')
    ylabel('Ang. Acc. (deg^2/s)')
    xlim([Xmin Xmax])
    ylim([Y_VelMin Y_VelMax])
    legend({'thddRef','thddMeas'},'Location','northwest')
    legend('boxoff')
    set(gca,'XMinorTick' , 'on')
    set(gca,'YMinorTick' , 'on')

%torque
subplot(5,3,11),plot(t_plot,tauMeas(:,2)); ylim([Tmin Tmax])
    xlabel('Time(s)')
    ylabel('Torque (Nm)')
    xlim([Xmin Xmax])
    set(gca,'XMinorTick' , 'on')
    set(gca,'YMinorTick' , 'on')

%error
subplot(5,3,14),plot(t_plot,(thRef(:,2)- thMeas(:,2))); ylim([Emin Emax])
    xlabel('Time (s)')
    ylabel('Error (deg)')
    xlim([Xmin Xmax]) 
    set(gca,'XMinorTick' , 'on')
    set(gca,'YMinorTick' , 'on')

%% Plotting Joint-3 Properties
%angle
subplot(5,3,3), plot(t_plot,thRef(:,3), ':r', 'LineWidth', 1.5),
    hold on
    plot(t_plot,thMeas(:,3)); 
    hold off

    xlabel('Time (s)')
    ylabel('Angle (deg)')
    title('Joint-3')   
    xlim([Xmin Xmax])
    ylim([Y_AngleMin Y_AngleMax])

    legend({'thRef','thMeas'},'Location','northwest')
    legend('boxoff')
    set(gca,'XMinorTick' , 'on')
    set(gca,'YMinorTick' , 'on')

%angular velocity
subplot(5,3,6), plot(t_plot,thdRef(:,3), ':r', 'LineWidth', 1.5),
    hold on
    plot(t_plot,thdMeas(:,3)); 
    hold off
    
    xlabel('Time (s)')
    ylabel('Ang. Vel. (deg^2/s)')
    xlim([Xmin Xmax])
    ylim([Y_VelMin Y_VelMax])
    legend({'thdRef','thdMeas'},'Location','northwest')
    legend('boxoff')
    set(gca,'XMinorTick' , 'on')
    set(gca,'YMinorTick' , 'on')

%angular acceleration
subplot(5,3,9), plot(t_plot,thddRef(:,3), ':r', 'LineWidth', 1.5),
    hold on
    plot(t_plot,thddMeas(:,3)); 
    hold off
    
    xlabel('Time (s)')
    ylabel('Ang. Acc. (deg^2/s)')
    xlim([Xmin Xmax])
    ylim([Y_VelMin Y_VelMax])
    legend({'thddRef','thddMeas'},'Location','northwest')
    legend('boxoff')
    set(gca,'XMinorTick' , 'on')
    set(gca,'YMinorTick' , 'on')

%torque
subplot(5,3,12),plot(t_plot,tauMeas(:,3)); ylim([Tmin Tmax])
    xlabel('Time(s)')
    ylabel('Torque (Nm)')
    xlim([Xmin Xmax])
    set(gca,'XMinorTick' , 'on')
    set(gca,'YMinorTick' , 'on')

%error
subplot(5,3,15),plot(t_plot,(thRef(:,3)- thMeas(:,3))); ylim([Emin Emax])
    xlabel('Time (s)')
    ylabel('Error (deg)')
    xlim([Xmin Xmax]) 
    set(gca,'XMinorTick' , 'on')
    set(gca,'YMinorTick' , 'on')
