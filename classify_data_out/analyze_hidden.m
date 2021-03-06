%% INCART Dataset - Using transformative annotation method:
% Load Data:
% load('hidden_layers\h_combined_annotate.mat');
load('hidden_layers\h_combined_annotate_mini.mat');
l_titles = {'input', 'conv1d_1', 'conv1d_2', 'conv1d_3', 'conv1d_4', 'conv1d_5', 'concatenate_1', 'conv1d_6', 'concatenate_2', 'conv1d_7', 'concatenate_3', 'conv1d_8', 'y_true'};
layers = {inputs, conv1d_1, conv1d_2, conv1d_3, conv1d_4, conv1d_5, concatenate_1, conv1d_6, concatenate_2, conv1d_7, concatenate_3, conv1d_8, y_true};
clear conv1d_1 conv1d_2 conv1d_3 conv1d_4 conv1d_5 concatenate_1 conv1d_6 concatenate_2 conv1d_7 concatenate_3 conv1d_8 y_true
samples = size(inputs, 1);
x_axis = [0, 640, 640*2, 640*3, 640*4, 640*5, 1, 640, 640*2, 640*3, 640*4, 640*5, 640*6]
y_axis = [0, 500, 500, 500, 500, 500, 1, 1, 1, 1, 1, 1, 1]
for s = 170
    h = figure(1); plot(squeeze(layers{1}(s, :, :))); title(l_titles{1}); set(h, 'Position', [1, 500, 640, 500]);
    for i = 2:length(layers)
        h = figure(i); set(h, 'Position', [x_axis(i), y_axis(i), 640, 500]);
        imagesc(squeeze(layers{i}(s, :, :))'); title(l_titles{i});
        colorbar; 
        if i>11
            colormap(gray)
        else
            colormap(jet); % Set the 'visible' property 'off'
        end
        ax = gca; ax.Visible = 'off';
        % save: 
        mkdir('out_figs');
        saveas(gcf, ['out_figs/' num2str(i) '. ' l_titles{i} '.png']);
    end
%     in = input('Continue? \n');
end
