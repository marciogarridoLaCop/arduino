clear all
close all
clc
delete(instrfind);
arduino=serial('COM9');
set(arduino,'BaudRate',230400);
fopen(arduino);
    % Now get the data from arduino
    for j=1:10     % 10 Trial Loop
        
        fprintf(arduino,'R'); % Send Read Request to Arduino
        disp('Measuring...');
        pause(1)
        
        output = '';
        while (output == 'D')
            output = fscanf(arduino); % is Arduino done? Check and get data if so.
        end
        output = fscanf(arduino); % is Arduino done? Check and get data if so.
        % get 200x4 arrays from MATLAB and save it into a mat file
        array1 = zeros(200,1);
        array2 = zeros(200,1);
        array3 = zeros(200,1);
        array4 = zeros(200,1);
        for i=1:200 % get encoded arrays from arduino.
            data = fscanf(arduino);
            commas = strfind(data,',');
            array1(i) = str2num(data(1:commas(1)-1));
            array2(i) = str2num(data(commas(1):commas(2)-1));
            array3(i) = str2num(data(commas(2):commas(3)-1));
            array4(i) = str2num(data(commas(3):end));
        end
        % save all those 4 arrays into the related mat file.             
        filename = sprintf('sample_gesture_%d_trial_%d.mat',k,j);
        save(filename,'array1','array2','array3','array4')
        
        disp('Measured for this trial');
        % move on to other trial
        pause(1)
    end
% Close serial port
fclose(arduino);
delete(arduino);
clear arduino;
