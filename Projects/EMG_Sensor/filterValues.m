%% Inverting amplifier with a band-pass filter
gain = 1.6; % -rF/r1
fupper = 300
flower = 100

r1 = 1000
rF = gain*r1
c1 = 1/(2*pi*flower)/r1
cF = 1/(2*pi*fupper)/rF


%% Notch filter
clear all
fnotch = 60     % frequency of power outlets, etc
Q = 10

r1 = 100e3
r2 = r1
r3 = r1/2/Q
r4 = r3


c1 = 1/2/pi/fnotch/r3
c2 = c1 
cin = 100*c1

100e-9
