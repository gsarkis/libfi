close all;
clear all;

%Define constants for signedness
SIGNED=1;
UNSIGNED=0;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%Rounding mode.
rounding = 'fix';

%Overflow handling mode
overflow = 'saturate';

W=8;
F=4;
S=SIGNED;
T = numerictype('Signed', S == SIGNED, 'WordLength', W, 'FractionLength', ...
                F)

%Conifguration object. ProductMode and SumMode must always be
%SpeficyPrecision; otherwise, the width of the number will grow.

FM=fimath('RoundMode', rounding, ...
         'OverflowMode', overflow, ...
         'ProductMode', 'SpecifyPrecision', ...
         'SumMode', 'SpecifyPrecision', ...
         'ProductWordLength', W, ...
         'ProductFractionLength', F, ...
         'SumWordLength', W, ...
         'SumFractionLength', F);

%%%%%%%%%%
%Construction from floating point
ad = [1e20, 9.0, 7.9375, 4.123, 1.0, 0.0, -0.0, -1.0, 4.123, -8.0, ...
      -9.0, -1e20]'
a = fi(ad, S, W, F, FM)

ad = rand(20, 1)*16 - 8
a = fi(ad, S, W, F, FM)

%%%%%%%%%%
%Construction from string
ad = [1000000000000000000000000.0, 9.0, 7.9375, 4.123, 1.0, 0.0, ...
      -0.0, -1.0, -4.123, -8.0, -9.0]'
a = fi(ad, S, W, F, FM)

ad = rand(20, 1)*16 - 8
a = fi(ad, S, W, F, FM)

%%%%%%%%%%
%Addition
ad = [1.0, 3.0, 6.0, -1, -5, -4.3, -5.5, -5]'
bd = [3.0, 1.0, 3, 3, 3, 3.123, -1.25, -4]'

a = fi(ad, S, W, F, FM);
b = fi(bd, S, W, F, FM);

a + b

%%%%%%%%%%
%Subtraction
ad = [1.24, 3.24, 6, -1, -3, -4.3, -5]'
bd = [3.24, 1.23, -3, 3, -5, 3.123, 4]'

a = fi(ad, S, W, F, FM);
b = fi(bd, S, W, F, FM);

a - b

%%%%%%%%%%
%Multiplication
ad = [0, -1.234, -1.125, 1, 7.9375, -8, 7.9375, -8]'
bd = [6.234, 0, 1.0, 1.125, 7.9375, 7.9375, -8.0, -8.0]'

a = fi(ad, S, W, F, FM);
b = fi(bd, S, W, F, FM);

a .* b

ad = rand(20, 1)*16 - 8
bd = rand(20, 1)*16 - 8

a = fi(ad, S, W, F, FM);
b = fi(bd, S, W, F, FM);

a .* b

%%%%%%%%%%
%Division
ad = [0, -1.125, 6.125]'
bd = [6.234, 1, 1]'

a = fi(ad, S, W, F, FM);
b = fi(bd, S, W, F, FM);

T.divide(a, b)

ad = rand(20, 1)*16 - 8
bd = rand(20, 1)*16 - 8
a = fi(ad, S, W, F, FM);
b = fi(bd, S, W, F, FM);

T.divide(a, b)
