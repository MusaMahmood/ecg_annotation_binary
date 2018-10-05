%% analyze ptb outputs:
clr;
load('combined_annotate\combined_annotate.mat');
idx = 1;
if exist('x_val', 'var')
    samples = size(x_val, 1);
    figure(1);
    for i = 48:samples
        fprintf('Sample #%d \n', i);
        grnd_trth = vec2ind(squeeze(y_val(i, :, :))');
        outputs = vec2ind(squeeze(y_out(i, :, :))');
        accuracy = sum(grnd_trth == outputs)./2000
        if accuracy < 0.66 %sum(grnd_trth == 2)
            subplot(4, 1, 1); plot(x_val(i, :));
            subplot(4, 1, 2); plot(squeeze(y_prob(i, :, :)));
            subplot(4, 1, 3); plot(squeeze(y_out(i, :, :)));
            subplot(4, 1, 4); plot(squeeze(y_val(i, :, :))); title('true vals');
            aaaaa = input('Continue? \n');
        end
    end
end