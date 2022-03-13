% 100Mohms resistance when pushing lightly to 0.19Mohms when pushing super
% hard, converted all numbers to ohms for resistance in this document
R_fsr = 190000:1:100000000;

% Voltage in is 3.3V
Vx = 3.3;

% CHANGE THIS NUMBER: resistance in ohms
R = 5000000;

% Voltage divider formula:
Vout = Vx.*(R./(R+R_fsr));

% Plot the graph of R_fsr vs Vout, Vout as a function of R_fsr
plot(R_fsr,Vout)
% Make the graph show Y values from 0 to 3.3
ylim([0, 3.3])

