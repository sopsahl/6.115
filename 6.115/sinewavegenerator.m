x = 0:255;
y = round(255/2*(sin(x/256*2*pi) + 1));
% plot(x, y)
z = dec2hex(y);
fileID = fopen('hex_values.txt', 'w');
fprintf(fileID, '#0%sh', z(1, :));
for i = 2:256
    fprintf(fileID, ', #0%sh', z(i, :));
end
fclose(fileID);
disp('Hexadecimal values written to hex_values.txt');