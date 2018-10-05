# MUSA MAHMOOD - Copyright 2018
# Python 3.6.3
# TF 1.8.0

# Imports:
import os

import numpy as np
import tensorflow as tf
from keras.backend import tensorflow_backend as tf_backend
from keras.layers import Conv1D, LeakyReLU, Input, Concatenate
from keras.layers import Dropout
from keras.layers.convolutional import UpSampling1D
from keras.models import Model, load_model
from keras.optimizers import Adam
from keras_contrib.layers.normalization import InstanceNormalization
from scipy.io import savemat
from sklearn.model_selection import train_test_split

import tf_shared_k as tfs

# Sources: (Ctrl-LMB in Pycharm)
# Instance Normalization: https://arxiv.org/abs/1701.02096

# Setup:
TRAIN = False  # TRAIN ANYWAY FOR # epochs, or just evaluate
TEST = True
SAVE_PREDICTIONS = True
SAVE_HIDDEN = False
EXPORT_OPT_BINARY = False

DATASET = 'ptb6'

batch_size = 256
epochs = 50

num_channels = 1
num_classes = 5
data_directory = ''

if DATASET == 'mit':
    num_classes = 5
    num_channels = 2
    data_directory = 'data/extended_5_class/mit_bih_tlabeled_w8s_fixed_all'
elif DATASET == 'ptb':
    num_classes = 2
    data_directory = 'data/ptb_ecg_1ch_temporal_labels/lead_v2_all'
elif DATASET == 'ptb6':
    num_classes = 6
    data_directory = 'data/ptb_6class_temporal/lead_v2_all'
elif DATASET == 'incart':
    num_classes = 5
    data_directory = 'data/incartdb_v1_all'
learn_rate = 0.0002

description = DATASET + '_annotate'
keras_model_name = description + '.h5'
model_dir = tfs.prep_dir('model_exports/')
keras_file_location = model_dir + keras_model_name

output_folder = 'classify_data_out/' + description + '/'
seq_length = 2000
input_length = seq_length
x_shape = [seq_length, num_channels]
y_shape = [seq_length, num_classes]

# Start Timer:
start_time_ms = tfs.current_time_ms()

# Load Data:
x_tt, y_tt = tfs.load_data_v2(data_directory, x_shape, y_shape, 'X', 'Y')

# Additional Dataset:

x_i, y_i = tfs.load_data_v2('data/incartdb_v1_all', x_shape, [2000, 5], 'X', 'Y')

if num_channels < 2 and not DATASET == 'incart':
    x_tt = np.reshape(x_tt[:, :, 0], [-1, seq_length, 1])

x_train, x_test, y_train, y_test = train_test_split(x_tt, y_tt, train_size=0.75, random_state=1)


def build_annotator(input_channels=1, output_channels=1):
    def conv_layer(layer_input, filters, kernel_size=5, strides=2):
        d = Conv1D(filters, kernel_size, strides=strides, padding='same')(layer_input)
        d = LeakyReLU(alpha=0.20)(d)
        d = InstanceNormalization()(d)
        return d

    def deconv_layer(layer_input, skip_input, filters, f_size=4, dropout_rate=0):
        u = UpSampling1D(size=2)(layer_input)
        u = Conv1D(filters, f_size, strides=1, padding='same', activation='relu')(u)
        if dropout_rate:
            u = Dropout(dropout_rate)(u)
        u = InstanceNormalization()(u)
        u = Concatenate()([u, skip_input])
        return u

    # Input samples
    input_samples = Input(shape=(input_length, input_channels))

    # Downsampling:
    d1 = conv_layer(input_samples, 32, 8, 2)
    d2 = conv_layer(d1, 64, 8, 2)
    d3 = conv_layer(d2, 128, 8, 2)
    d4 = conv_layer(d3, 256, 8, 2)

    # Now Upsample:
    u1 = deconv_layer(d4, d3, 128, f_size=8)
    u2 = deconv_layer(u1, d2, 64, f_size=8)
    u3 = deconv_layer(u2, d1, 32, f_size=8)
    u4 = UpSampling1D(size=2)(u3)
    output_samples = Conv1D(output_channels, kernel_size=8, strides=1, padding='same', activation='softmax')(u4)
    return Model(input_samples, output_samples)


model = []
tf_backend.set_session(tfs.get_session(0.75))
with tf.device('/gpu:0'):
    if TRAIN:
        if os.path.isfile(keras_file_location):
            model = load_model(keras_file_location)
        else:
            model = build_annotator(input_channels=num_channels, output_channels=num_classes)
            adam = Adam(lr=learn_rate, beta_1=0.9, beta_2=0.999, epsilon=1e-08, decay=0.0)
            model.compile(loss='categorical_crossentropy', optimizer=adam, metrics=['accuracy'])

        print(model.summary())

        model.fit(x_train, y_train, batch_size=batch_size, epochs=epochs, verbose=1)
        model.save(keras_file_location)

    if os.path.isfile(keras_file_location):
        if not TRAIN:
            model = load_model(keras_file_location)
            print(model.summary())
            if TEST:
                score, acc = model.evaluate(x_test, y_test, batch_size=128, verbose=1)
                print('Test score: {} , Test accuracy: {}'.format(score, acc))
                y_prob = model.predict(x_test)
                tfs.print_confusion_matrix(y_prob, y_test)
        else:
            if TEST and model is not None:
                score, acc = model.evaluate(x_test, y_test, batch_size=128, verbose=1)
                print('Test score: {} , Test accuracy: {}'.format(score, acc))
                y_prob = model.predict(x_test)
                tfs.print_confusion_matrix(y_prob, y_test)
            else:
                print('This should never happen: model does not exist')
                exit(-1)
    else:
        print("Model Not Found!")
        if not TRAIN:
            exit(-1)

    if SAVE_PREDICTIONS:
        # predict
        yy_probabilities = model.predict(x_test, batch_size=batch_size)
        yy_predicted = tfs.maximize_output_probabilities(yy_probabilities)
        data_dict = {'x_val': x_test, 'y_val': y_test, 'y_prob': yy_probabilities, 'y_out': yy_predicted}
        savemat(tfs.prep_dir(output_folder) + description + '.mat', mdict=data_dict)

        yy_probabilities = model.predict(x_i, batch_size=batch_size)
        yy_predicted = tfs.maximize_output_probabilities(yy_probabilities)
        data_dict = {'x_val': x_i, 'y_val': y_i, 'y_prob': yy_probabilities, 'y_out': yy_predicted}
        savemat(tfs.prep_dir(output_folder) + 'incart_ptbModel' + '.mat', mdict=data_dict)

    if SAVE_HIDDEN:
        layers_of_interest = ['conv1d_1', 'conv1d_2', 'conv1d_3', 'conv1d_4', 'conv1d_5', 'concatenate_1', 'conv1d_6',
                              'concatenate_2', 'conv1d_7', 'concatenate_3', 'conv1d_8']
        np.random.seed(0)
        rand_indices = np.random.randint(0, x_test.shape[0], 250)
        print('Saving hidden layers: ', layers_of_interest)
        tfs.get_keras_layers(model, layers_of_interest, x_test[rand_indices], y_test[rand_indices],
                             output_dir=tfs.prep_dir('classify_data_out/hidden_layers/'),
                             fname='h_' + description + '.mat')

    # TODO: Save hidden Layers
    print('Elapsed Time (ms): ', tfs.current_time_ms() - start_time_ms)
    print('Elapsed Time (min): ', (tfs.current_time_ms() - start_time_ms) / 60000)

if EXPORT_OPT_BINARY:
    tfs.export_model_keras(keras_file_location, export_dir=tfs.prep_dir("graph"),
                           model_name=description, sequential=False)
