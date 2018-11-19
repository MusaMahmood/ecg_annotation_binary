from scipy.io import savemat, loadmat
import numpy as np
from tf_shared import load_data_v2, prep_dir, ind2vec

num_classes = 5
seq_length = 2000
input_length = seq_length
suffix = '_train'
dir_1 = 'incartdb_5c_shift' + suffix
dir_2 = 'ptb_5c_shift' + suffix
dir_out = 'incart_ptb_5c'
key_x = 'X'
key_y = 'Y'
x_shape = []
y_shape = []
x_data, y_data = load_data_v2(dir_1, [seq_length, 1], [seq_length, num_classes], key_x, key_y)
x_data2, y_data2 = load_data_v2(dir_2, [seq_length, 1], [seq_length, num_classes], key_x, key_y)

x_data = np.concatenate([x_data, x_data2], axis=0)
y_data = np.concatenate([y_data, y_data2], axis=0)
print("Loaded Data Shape Final: X:", x_data.shape, " Y: ", y_data.shape)

savemat(prep_dir(dir_out + '_all' + suffix + '/') + 'all_data.mat', mdict={key_x: x_data, key_y: y_data})
