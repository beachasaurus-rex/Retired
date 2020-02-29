function FileName = runScript(inputs) %mass,duration,dampRatio,springConst,initPosi,initVelo)
    mass = inputs{1}
    duration = inputs{2}
    dampRatio = inputs{3}
    springConst = inputs{4}
    initPosi = inputs{5}
    initVelo = inputs{6}
    
    [t,x] = odeExecute(@(t) t, @(x) x, mass, springConst, dampRatio, duration, initPosi, initVelo);
    
    set(0,'DefaultFigureVisible','off');
    
    %outputs graphs
    figure(1)
    subplot(3,1,1)
    plot(t,x(:,1)),...
        xlabel('Time (sec)'),...
        ylabel('Position (m)'),...
        title('Position vs Time')

    subplot(3,1,2)
    plot(t,x(:,2)),...
        xlabel('Time (sec)'),...
        ylabel('Velocity (m/s)'),...
        title('Velocity vs Time')

    subplot(3,1,3)
    plot(t,x(:,1),'o',t,x(:,2),'^'),...
        xlabel('Time (sec)'),...
        ylabel('Amplitude'),...
        title('Amplitude vs Time'),...
        legend('Position (m)', 'Velocity (m/s)')
    
    img = getframe(gcf);
    fileName = [tempname, '.png'];
    imwrite(img.cdata, fileName);
    
    set(0,'DefaultFigureVisible','on');
    
    FileName = fileName;
end