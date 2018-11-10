clr;
%  Load Data:
sample = 9000;
fn = ['gen_samples_e' num2str(sample) '.mat'];
load(fn);

for i=1:25
    subplot(5, 5, i);
    plot(outputs(i, :));
end