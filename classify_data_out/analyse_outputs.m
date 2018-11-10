%% analyze ptb outputs:
clr;
% load('combined_annotate\combined_annotate.mat');
% load('combined_annotate\lab_data.mat');
load('combined6_annotate_lstm\combined6_annotate_lstm.mat');
% load('combined6_annotate_lstm_mini\lab_data.mat');
idx = 1;
if exist('x_val', 'var')
    samples = size(x_val, 1);
    figure(1);
    for i = 1084:samples
        fprintf('Sample #%d \n', i);
        grnd_trth = vec2ind(squeeze(y_val(i, :, :))');
        outputs = vec2ind(squeeze(y_out(i, :, :))');
        accuracy = sum(grnd_trth == outputs)./2000
        temp = sum(squeeze(y_val(i, :, :)))
        if sum(temp(3:end)) %accuracy < 0.89\\sum(grnd_trth == 2)
            subplot(4, 1, 1); plot(x_val(i, :)); title('Input Data'); 
            subplot(4, 1, 2); plot(squeeze(y_prob(i, :, :))); title('Output Lables'); legend('1','2','3','4','5','6');
            subplot(4, 1, 3); plot(squeeze(y_out(i, :, :))); title('ArgMax(Output Labels)');
            subplot(4, 1, 4); plot(squeeze(y_val(i, :, :))); title('true vals');
            aaaaa = input('Continue? \n');
        end
    end
end