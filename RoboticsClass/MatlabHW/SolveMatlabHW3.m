clear
clc

%% Problem 1
fprintf("Problem 1 - P-R-R Robot:\n\n")

d1 = 0.15;
th2 = -pi/2;
th3 = pi/2;
a12 = 0.3;
a23 = 0.5;
a3tip = 0.15;
tipPos_frm3 = [a3tip; 0; 0];

%dh parameters
dhParams = [0 0 d1 pi/2; a12 0 0 th2; a23 0 0 th3];

%build the P-R-R robot in problem 1
env = Helpers.BuildFromDhParams(dhParams, false);

%save the transformation matrix that relates frame 3 with frame 0
tMat30 = env.Origin.MappedFrames{3,2};

%get the tip position with respect to frame 0.
tip0 = Helpers.TransformPosition(tipPos_frm3, tMat30.Matrix);

fprintf("Transformation Matrix - Frame3 to Frame0:\n\n");
disp(tMat30.Matrix);

fprintf("End-effector position relative to Frame0:\n\n");
disp(tip0);

clear
%% Problem 2
fprintf("Problem 2 - R-R-R Robot:\n\n")

d2 = 0.5;
th1 = pi/2;
th2 = pi/2;
th3 = -pi/2;
a23 = 0.3;
a3tip = 0.4;
tipPos_frm3 = [a3tip; 0; 0];

%dh parameters
dhParams = [0 0 0 th1; 0 -pi/2 d2 th2; a23 0 0 th3];

%build the P-R-R robot in problem 1
env = Helpers.BuildFromDhParams(dhParams, false);

%save the transformation matrix that relates frame 3 with frame 0
tMat30 = env.Origin.MappedFrames{3,2};

%get the tip position with respect to frame 0.
tip0 = Helpers.TransformPosition(tipPos_frm3, tMat30.Matrix);

fprintf("Transformation Matrix - Frame3 to Frame0:\n\n");
disp(tMat30.Matrix);

fprintf("End-effector position relative to Frame0:\n\n");
disp(tip0);

clear
%% Problem 3
fprintf("Problem 3 - R-R-R Robot:\n\n")

d1 = 0.25;
th1 = pi/2;
th2 = pi/2;
th3 = -pi/2;
a23 = 0.22;
a3tip = 0.15;
tipPos_frm3 = [a3tip; 0; 0];

%dh parameters
dhParams = [0 0 d1 th1; 0 pi/2 0 th2; a23 0 0 th3];

%build the P-R-R robot in problem 1
env = Helpers.BuildFromDhParams(dhParams, false);

%save the transformation matrix that relates frame 3 with frame 0
tMat30 = env.Origin.MappedFrames{3,2};

%get the tip position with respect to frame 0.
tip0 = Helpers.TransformPosition(tipPos_frm3, tMat30.Matrix);

fprintf("Transformation Matrix - Frame3 to Frame0:\n\n");
disp(tMat30.Matrix);

fprintf("End-effector position relative to Frame0:\n\n");
disp(tip0);

clear
%% Problem 4
fprintf("Problem 4 - R-R-P Robot:\n\n")

d1 = 0.25;
d3 = 0.35;
th1 = pi/2;
th2 = pi/2;
a23 = 0.2;
a3tip = 0.5;
tipPos_frm3 = [0; 0; a3tip];

%dh parameters
dhParams = [0 0 d1 th1; 0 pi/2 0 th2; a23 pi/2 d3 0];

%build the P-R-R robot in problem 1
env = Helpers.BuildFromDhParams(dhParams, false);

%save the transformation matrix that relates frame 3 with frame 0
tMat30 = env.Origin.MappedFrames{3,2};

%get the tip position with respect to frame 0.
tip0 = Helpers.TransformPosition(tipPos_frm3, tMat30.Matrix);

fprintf("Transformation Matrix - Frame3 to Frame0:\n\n");
disp(tMat30.Matrix);

fprintf("End-effector position relative to Frame0:\n\n");
disp(tip0);
