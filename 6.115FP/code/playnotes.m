function [beginning, middle, ending, freq] = playnotes()
    beginning = [];
    middle = [];
    ending = [];
    freq = [];
    freqs = [103.8	110.0	116.5	123.5 130.8	138.6	146.8	155.6	164.8	174.6	185.0	196.0	207.7	220.0	233.1	246.9 261.6	277.2	293.7	311.1	329.6	349.2	370.0	392.0	415.3	440.0	466.2	493.9];
    for i = 1:length(freqs)
        f = freqs(i)/392;
        [beginning, middle, ending, freq(i)] = saxnotes(f, 100, 2317, 2372, 10);
        % pause(0.5);
    end
    % writematrix(transpose(freq), "freq");
    % writematrix(transpose(beginning), "waveforms/beginning");
    % writematrix(transpose(middle), "waveforms/middle");
    % writematrix(transpose(ending), "waveforms/ending");
    % periods = round(24000000*1./freq);
    % writematrix(transpose(periods), "periods");
    plot(1:length(repmat([beginning; middle; ending], 10, 1)), repmat([beginning; middle; ending], 10, 1))
end