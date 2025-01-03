function [beginning, continuation, ending, F] = saxnotes(f, n, x1, x2, v)
    % Load the WAV file
    [y, Fs] = audioread("sax-short-single-note_G.wav");
    beginning = round(y(1:x1-1)*100);
    ending = round(y(x2+1:length(y))*100);
    continuation = round(y(x1:x2)*100);
    y = [beginning; repmat(continuation, n, 1); ending];
    % Change the frequency
    plot(1:length(y), v*y)
    F = f*Fs;
    % Produce the sound file
    % sound(y/100, F);
 end

