%% INCART Dataset - Using transformative annotation method:
% Load Data:
load('hidden_layers\h_combined_annotate.mat');
l_titles = {'input', 'conv1d_1', 'conv1d_2', 'conv1d_3', 'conv1d_4', 'conv1d_5', 'concatenate_1', 'conv1d_6', 'concatenate_2', 'conv1d_7', 'concatenate_3', 'conv1d_8', 'y_true'};
layers = {inputs, conv1d_1, conv1d_2, conv1d_3, conv1d_4, conv1d_5, concatenate_1, conv1d_6, concatenate_2, conv1d_7, concatenate_3, conv1d_8, y_true};
clear conv1d_1 conv1d_2 conv1d_3 conv1d_4 conv1d_5 concatenate_1 conv1d_6 concatenate_2 conv1d_7 concatenate_3 conv1d_8 y_true
samples = size(inputs, 1);
for s = 1:samples
    figure(1); plot(squeeze(layers{1}(s, :, :))); title(l_titles{1});
    for i = 2:length(layers)
        figure(i);
        imagesc(squeeze(layers{i}(s, :, :))); title(l_titles{i});
        colorbar; colormap(jet);
    end
    in = input('Continue? \n');
end
