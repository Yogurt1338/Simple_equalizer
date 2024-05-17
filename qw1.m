% Считывание аудиофайла
[input, Fs] = audioread('sample-3s.mp3');

[output, Fs] = audioread('output.wav');
% Временная шкала
t = (0:length(input)-1) / Fs;

% Построение графиков
subplot(2, 1, 1);
plot(t, input);
title('Input Signal');
xlabel('Time (s)');
ylabel('Amplitude');

t = (0:length(output)-1) / Fs;
subplot(2, 1, 2);
plot(t, output);
title('Output Signal after chaaf');
xlabel('Time (s)');
ylabel('Amplitude');