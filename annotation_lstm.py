# MUSA MAHMOOD - Copyright 2018
# Python 3.6.3
# TF 1.8.0

# Imports:
import os

import numpy as np
import tensorflow as tf
from keras import optimizers, regularizers
from keras.backend import tensorflow_backend as tf_backend
from keras.layers import Bidirectional, CuDNNLSTM, BatchNormalization
from keras.layers import Conv1D, Dense, Reshape
from keras.layers import Dropout
from keras.models import load_model, Sequential
from scipy.io import savemat
from sklearn.model_selection import train_test_split

import tf_shared_k as tfs

# Sources: (Ctrl-LMB in Pycharm)
# Instance Normalization: https://arxiv.org/abs/1701.02096

# Setup:
TRAIN = False
TEST = True
SAVE_PREDICTIONS = False
SAVE_HIDDEN = False
EXPORT_OPT_BINARY = False

DATASET = 'combined'

batch_size = 256
epochs = 10

# These variables are set based on the dataset we are looking at.
num_channels = 1
num_classes = 0
data_directory = ''

if DATASET == 'combined' or DATASET == 'combined_v2':
    num_classes = 2
    data_directory = 'data/incart_ptb_all'

learn_rate = 0.0002

description = DATASET + '_annotate_lstm'
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

# Load Test Data:
x_test0, y_test0 = tfs.load_data_v2('data/v2labtest', x_shape, y_shape, 'X', 'Y')

if num_channels < 2 and not DATASET == 'incart':
    x_tt = np.reshape(x_tt[:, :, 0], [-1, seq_length, 1])

x_train, x_test, y_train, y_test = train_test_split(x_tt, y_tt, train_size=0.8, random_state=1)


def build_annotator(output_channels=1):
    model = Sequential()
    model.add(Conv1D(32, 16, strides=2, padding='same', activation='relu', input_shape=(input_length, num_channels)))
    model.add(Conv1D(64, 8, strides=2, padding='same', activation='relu'))
    model.add(Reshape(target_shape=(seq_length, 64 // 4)))
    model.add(Bidirectional(CuDNNLSTM(32, return_sequences=True)))
    model.add(Dropout(0.2))
    model.add(BatchNormalization())
    model.add(Dense(64, activation='relu', kernel_regularizer=regularizers.l2(l=0.01)))
    model.add(Dropout(0.2))
    model.add(BatchNormalization())
    model.add(Dense(output_channels, activation='softmax'))
    adam = optimizers.adam(lr=0.001, beta_1=0.9, beta_2=0.999, epsilon=1e-08, decay=0.0)
    model.compile(loss='categorical_crossentropy', optimizer=adam, metrics=['accuracy'])
    print(model.summary())
    return model


model = []
tf_backend.set_session(tfs.get_session(0.75))
with tf.device('/gpu:0'):
    if TRAIN:
        if os.path.isfile(keras_file_location):
            model = load_model(keras_file_location)
        else:
            model = build_annotator(output_channels=num_classes)

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
                # Human Test Data:
                print('Lab Group Data: ')
                score, acc = model.evaluate(x_test0, y_test0, batch_size=128, verbose=1)
                print('Test score: {} , Test accuracy: {}'.format(score, acc))
                y_prob0 = model.predict(x_test0)
                tfs.print_confusion_matrix(y_prob0, y_test0)
        else:
            if TEST and model is not None:
                score, acc = model.evaluate(x_test, y_test, batch_size=128, verbose=1)
                print('Test score: {} , Test accuracy: {}'.format(score, acc))
                y_prob = model.predict(x_test)
                tfs.print_confusion_matrix(y_prob, y_test)
                # Human Test Data:
                print('Lab Group Data: ')
                score, acc = model.evaluate(x_test0, y_test0, batch_size=128, verbose=1)
                print('Test score: {} , Test accuracy: {}'.format(score, acc))
                y_prob0 = model.predict(x_test0)
                tfs.print_confusion_matrix(y_prob0, y_test0)
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

        yy_probabilities = model.predict(x_test0, batch_size=batch_size)
        yy_predicted = tfs.maximize_output_probabilities(yy_probabilities)
        data_dict = {'x_val': x_test0, 'y_val': y_test0, 'y_prob': yy_probabilities, 'y_out': yy_predicted}
        savemat(tfs.prep_dir(output_folder) + 'lab_data' + '.mat', mdict=data_dict)

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
