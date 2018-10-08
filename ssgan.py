# MUSA MAHMOOD - Copyright 2018
# Python 3.6.3
# TF 1.8.0

# Imports:

import numpy as np
from keras.layers import Conv1D, LeakyReLU, Input, Activation, Flatten, Dense, Reshape
from keras.layers import Dropout, BatchNormalization
from keras.layers.convolutional import UpSampling1D
from keras.models import Model, Sequential
from keras.optimizers import Adam
from keras.utils import to_categorical
from scipy.io import savemat
from sklearn.model_selection import train_test_split

import tf_shared_k as tfs

# Sources: (Ctrl-LMB in Pycharm)
# Instance Normalization: https://arxiv.org/abs/1701.02096

# Setup:
TRAIN = True
TEST = True
SAVE_PREDICTIONS = False
SAVE_HIDDEN = False
EXPORT_OPT_BINARY = False

DATASET = 'combined_adv'

batch_size = 256
half_batch = batch_size // 2
epochs = 10

# These variables are set based on the dataset we are looking at.
num_channels = 1
num_classes = 0
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
elif DATASET == 'combined':
    num_classes = 2
    data_directory = 'data/incart_ptb_all'
elif DATASET == 'combined_adv':
    num_classes = 2
    data_directory = 'data/ptb_adv'

learn_rate = 0.0002

description = DATASET + '_annotate'
keras_model_name = description + '.h5'
model_dir = tfs.prep_dir('model_exports/')
keras_file_location = model_dir + keras_model_name

output_folder = 'classify_data_out/' + description + '/'
seq_length = 2000
seq_init_length = 250
input_length = seq_length
x_shape = [seq_length, num_channels]
y_shape = [1]
latent_dim = 75

# Start Timer:
start_time_ms = tfs.current_time_ms()

# Load Data:
x_tt, y_tt = tfs.load_data_v2(data_directory, x_shape, y_shape, 'X', 'Y')

if num_channels < 2 and not DATASET == 'incart':
    x_tt = np.reshape(x_tt[:, :, 0], [-1, seq_length, 1])

x_train, x_test, y_train, y_test = train_test_split(x_tt, y_tt, train_size=0.75, random_state=1)


def build_generator():
    model = Sequential()
    model.add(Dense(128 * seq_init_length * 1, activation='relu', input_dim=latent_dim))
    model.add(Reshape((seq_init_length, 128)))
    model.add(BatchNormalization(momentum=0.8))
    model.add(UpSampling1D(size=2))
    model.add(Conv1D(128, kernel_size=6, padding='same'))
    model.add(Activation('relu'))
    model.add(BatchNormalization(momentum=0.8))
    model.add(UpSampling1D(size=2))
    model.add(Conv1D(64, kernel_size=9, padding='same'))
    model.add(Activation('relu'))
    model.add(BatchNormalization(momentum=0.8))
    model.add(UpSampling1D(size=2))
    model.add(Conv1D(1, kernel_size=12, padding='same'))
    model.add(Activation('tanh'))

    model.summary()

    noise = Input(shape=(latent_dim,))
    input_sample = model(noise)

    return Model(noise, input_sample)


def build_discriminator():
    model = Sequential()
    model.add(Conv1D(32, kernel_size=12, strides=2, padding='same', input_shape=(input_length, 1)))
    model.add(LeakyReLU(alpha=0.2))
    model.add(Dropout(0.25))
    model.add(Conv1D(64, kernel_size=9, strides=2, padding='same'))
    model.add(LeakyReLU(alpha=0.2))
    model.add(Dropout(0.25))
    model.add(BatchNormalization(momentum=0.8))
    model.add(Conv1D(128, kernel_size=6, strides=2, padding='same'))
    model.add(LeakyReLU(alpha=0.2))
    model.add(Dropout(0.25))
    model.add(BatchNormalization(momentum=0.8))
    model.add(Conv1D(256, kernel_size=4, strides=2, padding='same'))
    model.add(LeakyReLU(alpha=0.2))
    model.add(Dropout(0.25))
    model.add(Flatten())

    model.summary()

    input_sample = Input(shape=(input_length, 1))

    features = model(input_sample)

    valid = Dense(1, activation='sigmoid')(features)
    label = Dense(num_classes + 1, activation='softmax')(features)

    return Model(input_sample, [valid, label])


def extract_samples():
    input_noise = np.random.normal(0, 1, (seq_init_length, latent_dim))
    gen_outputs = gen.predict(input_noise)
    return gen_outputs


def train_model(total_epochs, sample_interval=20):
    # Class weights
    cw1 = {0: 1, 1: 1}
    cw2 = {i: num_classes / half_batch for i in range(num_classes)}
    cw2[num_classes] = 1 / half_batch

    # Adversarial ground truths:
    valid = np.ones((batch_size, 1))
    fake = np.zeros((batch_size, 1))

    for epoch in range(total_epochs):
        # 1. Train Discriminator:
        index = np.random.randint(0, x_train.shape[0], batch_size)
        input_sample = x_train[index]
        noise = np.random.normal(0, 1, (batch_size, latent_dim))
        gen_samples = gen.predict(noise)

        labels = to_categorical(y_train[index], num_classes=num_classes + 1)
        fake_labels = to_categorical(np.full((batch_size, 1), num_classes), num_classes=num_classes + 1)

        # Train the discriminator:
        d_loss_real = disc.train_on_batch(input_sample, [valid, labels], class_weight=[cw1, cw2])
        d_loss_fake = disc.train_on_batch(gen_samples, [fake, fake_labels], class_weight=[cw1, cw2])
        d_loss = 0.5 * np.add(d_loss_real, d_loss_fake)

        # Train Generator:

        g_loss = combined_model.train_on_batch(noise, valid, class_weight=[cw1, cw2])

        print("%d [D loss: %f, acc: %.2f%%, op_acc: %.2f%%] [G loss: %f]" %
              (epoch, d_loss[0], 100 * d_loss[3], 100 * d_loss[4], g_loss))

        if (epoch % sample_interval) == 0:
            new_samples = extract_samples()
            savemat(tfs.prep_dir('gen_out/') + 'gen_samples_e' + str(epoch) + '.mat', mdict={'outputs': new_samples})
            print('epoch \n')


if TRAIN:
    # if os.path.isfile(keras_file_location):
    #     # model = load_model(keras_file_location)
    #     print('Not yet implemented.')
    #     exit(-1)
    # else:
    disc = build_discriminator()
    optimizer = Adam(lr=learn_rate, beta_1=0.5, beta_2=0.999)  # epsilon=1e-08
    disc.compile(loss=['binary_crossentropy', 'categorical_crossentropy'], loss_weights=[0.5, 0.5],
                 optimizer=optimizer, metrics=['accuracy'])
    gen = build_generator()
    noise = Input(shape=(latent_dim,))
    input_sample = gen(noise)

    # Disable discriminator training.
    disc.trainable = False

    # Determines validity:
    valid, _ = disc(input_sample)

    # Combine Model:
    combined_model = Model(noise, valid)
    combined_model.compile(loss=['binary_crossentropy'], optimizer=optimizer)

    # Train Model:
    train_model(total_epochs=epochs, sample_interval=20)

    # TODO: Save gen/disc/combined_model

    if TEST:  # Temporary condition
        y_test_arrange = [np.ones(shape=[x_test.shape[0], 1]), to_categorical(y_test, num_classes=num_classes + 1)]
        all_out = disc.evaluate(x_test, y_test_arrange, batch_size=128, verbose=1)
        print("Loss information :", all_out)
        # binary_loss, categorical_loss, acc
        # print('Test scores(bin/cat): {},{} , Test accuracy: {}'.format(binary_loss, categorical_loss, acc))
        # y_prob = disc.predict(x_test)
        # tfs.print_confusion_matrix(y_prob, to_categorical(y_train, num_classes=num_classes + 1))

# if os.path.isfile(keras_file_location):
#     if not TRAIN:
#         disc = load_model(keras_file_location)
#         print(disc.summary())
#         if TEST:
#             score, acc = disc.evaluate(x_test, y_test, batch_size=128, verbose=1)
#             print('Test score: {} , Test accuracy: {}'.format(score, acc))
#             y_prob = disc.predict(x_test)
#             tfs.print_confusion_matrix(y_prob, y_test)
#     else:
#         if TEST and disc is not None:
#             score, acc = disc.evaluate(x_test, y_test, batch_size=128, verbose=1)
#             print('Test score: {} , Test accuracy: {}'.format(score, acc))
#             y_prob = disc.predict(x_test)
#             tfs.print_confusion_matrix(y_prob, y_test)
#         else:
#             print('This should never happen: model does not exist')
#             exit(-1)
# else:
#     print("Model Not Found!")
#     if not TRAIN:
#         exit(-1)

# if SAVE_PREDICTIONS:
#     # predict
#     yy_probabilities = disc.predict(x_test, batch_size=batch_size)
#     yy_predicted = tfs.maximize_output_probabilities(yy_probabilities)
#     data_dict = {'x_val': x_test, 'y_val': y_test, 'y_prob': yy_probabilities, 'y_out': yy_predicted}
#     savemat(tfs.prep_dir(output_folder) + description + '.mat', mdict=data_dict)

# if SAVE_HIDDEN:
#     layers_of_interest = ['conv1d_1', 'conv1d_2', 'conv1d_3', 'conv1d_4', 'conv1d_5', 'concatenate_1', 'conv1d_6',
#                           'concatenate_2', 'conv1d_7', 'concatenate_3', 'conv1d_8']
#     np.random.seed(0)
#     rand_indices = np.random.randint(0, x_test.shape[0], 250)
#     print('Saving hidden layers: ', layers_of_interest)
#     tfs.get_keras_layers(disc, layers_of_interest, x_test[rand_indices], y_test[rand_indices],
#                          output_dir=tfs.prep_dir('classify_data_out/hidden_layers/'),
#                          fname='h_' + description + '.mat')

# TODO: Save hidden Layers
print('Elapsed Time (ms): ', tfs.current_time_ms() - start_time_ms)
print('Elapsed Time (min): ', (tfs.current_time_ms() - start_time_ms) / 60000)

# TODO: Fix this for DISC:
if EXPORT_OPT_BINARY:
    tfs.export_model_keras(keras_file_location, export_dir=tfs.prep_dir("graph"),
                           model_name=description, sequential=False)
