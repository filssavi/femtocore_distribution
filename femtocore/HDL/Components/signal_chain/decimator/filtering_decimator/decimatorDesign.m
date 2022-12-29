clear all

decimation_factor = 10;

CICDecim = dsp.CICDecimator('DecimationFactor', decimation_factor,'NumSections', 6);

fs = 120e3;     % Sampling frequency of input of compensation decimator
fPass = 50e3;   % Passband frequency
fStop = 55e3; % Stopband frequency

CICCompDecim = dsp.CICCompensationDecimator(CICDecim);
CICCompDecim.DecimationFactor =1;
CICCompDecim.PassbandFrequency = fPass;
CICCompDecim.StopbandFrequency = fStop;
CICCompDecim.SampleRate = fs;

filtCasc = cascade(CICDecim, CICCompDecim);

f = fvtool(CICDecim, CICCompDecim, filtCasc);
f.Fs = [fs*decimation_factor fs fs*decimation_factor];
f.NormalizeMagnitudeto1 = 'on';
legend(f,'CIC Decimator','CIC Compensation Decimator', ...
    'Overall Response');

firComp = dfilt.dffir(coeffs(CICCompDecim).Numerator);
set(firComp,'arithmetic','fixed');
coewrite(firComp,16,'compensator_half_rate.coe');

%  
%  t = 0:1/1e6:2;
%  x = chirp(t,0,1,120e3);
%  y = filtCasc(x(1:end-1)');
%  
%  L = length(y);      % Signal length
%  
%  t2 = 0:2/(L-1):2;
%  plot(t2,y');
%  
%  
%  n = 2^nextpow2(L);
%  Y = fft(y,n);
%  f = 120e3*(0:(n/2))/n;
%  P = abs(Y/n);
%  
%  plot(f,P(1:n/2+1)) 
%  title('Gaussian Pulse in Frequency Domain')
%  xlabel('Frequency (f)')
%  ylabel('|P(f)|')
