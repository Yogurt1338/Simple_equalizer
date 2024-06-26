% Заданные параметры
fs = 44100;
duration = 1; % Продолжительность каждого сигнала в секундах

% Время
t = 0:1/fs:duration-1/fs;

% Создание трех синусоидальных сигналов
y1 = 0.5 * sin(2 * pi * 2000 * t); 
y2 = 0.2 * sin(2 * pi * 5000 * t); 
y3 = 0.3 * sin(2 * pi * 15000 * t); 

% Объединение сигналов в один массив
y = [y1, y2, y3];

% Нормализация сигнала для предотвращения клиппинга
y = y / max(abs(y));

% Запись в аудиофайл
audiowrite('three_sinusoids.mp3', y, fs);
