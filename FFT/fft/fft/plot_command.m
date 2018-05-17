figure(1)
subplot(3,1,1);
plot(frequency,pdMagnitude);
title('Magnitude');
grid on;

subplot(3,1,2);
plot(frequency,pdPhase);
title('Phase');
grid on;

subplot(3,1,3);
plot(frequency,pdCoherence);
title('Coherence');
grid on;
