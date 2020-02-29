%proportional gain matrix
kpp1=150;
kpp2=150;
kpp3=150;

Kpp=diag([kpp1 kpp2 kpp3]);

%integral gain matrix
ki1=0.1;
ki2=0.1;
ki3=0.1;

Kii=diag([ki1 ki2 ki3]);  

%derivative gain matrix
kvv1=10;
kvv2=18;
kvv3=10;

Kvv=diag([kvv1 kvv2 kvv3]);  

%integral initial conditions
init_th = (pi/180)*[15;15;15];
init_thd = zeros(3,1);