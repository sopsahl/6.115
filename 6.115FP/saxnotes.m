function [beginning, continuation, ending, F] = saxnotes(f, n, x1, x2, v)
    % Load the WAV file
    [y, Fs] = audioread("sax-short-single-note_G.wav");
    beginning = round((y(1:x1-1)*128/10 + 128));
    ending = round((y(x2+1:length(y))*128/10 + 128));
    continuation = round((y(x1:x2)*128/10 + 128));
    y = [beginning; repmat(continuation, n, 1); ending];
    ynew = (y-128)*v/128;
    % Change the frequency
    % plot(1:length(y), y*v - 128*(v-1))
    F = f*Fs;
    % Produce the sound file
    % sound(ynew, F);
 end

