# MUSA MAHMOOD - Copyright 2018
# Python 3.6.3
# TF 1.8.0

# Imports:
import os

import numpy as np
from keras.layers import Conv1D, LeakyReLU, Input, Activation, Flatten, Dense, Reshape
from keras.layers import Dropout, BatchNormalization
from keras.layers.convolutional import UpSampling1D
from keras.models import Model, Sequential, load_model
from keras.optimizers import Adam
from keras.utils import to_categorical
from scipy.io import savemat, loadmat
from sklearn.model_selection import train_test_split

import tf_shared_k as tfs

# Setup:
SAVE_MODEL = True
LOAD_MODEL = True

TRAIN = False
TEST = True
SAVE_PREDICTIONS = False
SAVE_HIDDEN = False
EXPORT_OPT_BINARY = True

DATASET = 'adv'

batch_size = 256
half_batch = batch_size // 2
epochs = 1000
previous_epochs = 0

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
elif DATASET == 'adv':
    num_classes = 2
    data_directory = 'data/ptb_adv'

learn_rate = 0.0002

description = DATASET + '_classify'
keras_model_name = description
model_dir = tfs.prep_dir('model_exports/')
keras_file_prefix = model_dir + keras_model_name

disc_file = keras_file_prefix + '_disc.h5'
gen_file = keras_file_prefix + '_gen.h5'
combined_file = keras_file_prefix + '_combined.h5'
train_stat_file_mat = keras_file_prefix + '_record.mat'
key_epochs = 'epochs'
all_files_as_list = [disc_file, gen_file, combined_file, train_stat_file_mat]

output_folder = 'classify_data_out/' + description + '/'
seq_length = 2000
seq_init_length = 250
input_length = seq_length
x_shape = [seq_length, num_channels]
y_shape = [1]
latent_dim = 75
optimizer = Adam(lr=learn_rate, beta_1=0.5, beta_2=0.999)  # epsilon=1e-08

# Start Timer:
start_time_ms = tfs.current_time_ms()

# Load Data:
x_tt, y_tt = tfs.load_data_v2(data_directory, x_shape, y_shape, 'X', 'Y')

if num_channels < 2 and not DATASET == 'incart':
    x_tt = np.reshape(x_tt[:, :, 0], [-1, seq_length, 1])

x_train, x_test, y_train, y_test = train_test_split(x_tt, y_tt, train_size=0.75, random_state=1)
print("Train/Test Split: {},{}".format(x_train.shape[0], x_test.shape[0]))


def get_stats(mat_file):
    return loadmat(mat_file).get(key_epochs)


def save_stats(mat_file, curr_epoch):
    savemat(mat_file, mdict={key_epochs: curr_epoch})


def f_exists(fnames):
    exists = [f for f in fnames if os.path.isfile(f)]
    if len(exists) == len(fnames):
        return True
    else:
        return False


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

    noise_ = Input(shape=(latent_dim,))
    input_sample_ = model(noise_)
    return Model(noise_, input_sample_)


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

    input_sample_ = Input(shape=(input_length, 1))
    features = model(input_sample_)
    valid_ = Dense(1, activation='sigmoid')(features)
    label = Dense(num_classes + 1, activation='softmax')(features)
    return Model(input_sample_, [valid_, label])


def extract_samples():
    input_noise = np.random.normal(0, 1, (seq_init_length, latent_dim))
    gen_outputs = gen.predict(input_noise)
    return gen_outputs


def train_model(total_epochs, sample_interval=100):
    # Class weights
    cw1 = {0: 1, 1: 1}
    cw2 = {i: num_classes / half_batch for i in range(num_classes)}
    cw2[num_classes] = 1 / half_batch

    # Adversarial ground truths:
    valid_labels = np.ones((batch_size, 1))
    fake = np.zeros((batch_size, 1))

    for epoch in range(total_epochs + 1):
        # 1. Train Discriminator:
        index = np.random.randint(0, x_train.shape[0], batch_size)
        input_sample_ = x_train[index]
        noise_ = np.random.normal(0, 1, (batch_size, latent_dim))
        gen_samples = gen.predict(noise_)

        labels = to_categorical(y_train[index], num_classes=num_classes + 1)
        fake_labels = to_categorical(np.full((batch_size, 1), num_classes), num_classes=num_classes + 1)

        # Train the discriminator:
        d_loss_real = disc.train_on_batch(input_sample_, [valid_labels, labels], class_weight=[cw1, cw2])
        d_loss_fake = disc.train_on_batch(gen_samples, [fake, fake_labels], class_weight=[cw1, cw2])
        d_loss = 0.5 * np.add(d_loss_real, d_loss_fake)

        # Train Generator:

        g_loss = combined_model.train_on_batch(noise_, valid_labels, class_weight=[cw1, cw2])

        print("%d [D loss: %f, acc: %.2f%%, op_acc: %.2f%%] [G loss: %f]" %
              (epoch, d_loss[0], 100 * d_loss[3], 100 * d_loss[4], g_loss))

        if (epoch % sample_interval) == 0 and epoch > 0:
            total_training_steps = previous_epochs + epoch
            new_samples = extract_samples()
            savemat(tfs.prep_dir('gen_out/') + 'gen_samples_e' + str(total_training_steps) + '.mat',
                    mdict={'outputs': new_samples})
            print('Saved samples: gen_out/gen_samples_e{}.mat'.format(total_training_steps))


if LOAD_MODEL and f_exists(all_files_as_list):
    previous_epochs = get_stats(mat_file=train_stat_file_mat)[0, 0]
    print("Model trained to {} epochs".format(previous_epochs))
    disc = load_model(disc_file)
    disc.compile(loss=['binary_crossentropy', 'categorical_crossentropy'], loss_weights=[0.5, 0.5],
                 optimizer=optimizer, metrics=['accuracy'])
    gen = load_model(gen_file)
    # Compile Models:
    noise = Input(shape=(latent_dim,))
    input_sample = gen(noise)
    # Disable discriminator training.
    disc.trainable = False
    # Determines validity:
    valid, _ = disc(input_sample)
    combined_model = Model(noise, valid)
    combined_model.compile(loss=['binary_crossentropy'], optimizer=optimizer)
else:
    save_stats(train_stat_file_mat, previous_epochs)  # 0
    disc = build_discriminator()
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

if TRAIN:
    # Train Model:
    print("Training Model for {} Epochs".format(epochs))
    train_model(total_epochs=epochs, sample_interval=100)

    if SAVE_MODEL:
        # Update stats:
        gen.save(gen_file)
        disc.save(disc_file)
        combined_model.save(combined_file)
        new_stat_epochs = previous_epochs + epochs
        save_stats(train_stat_file_mat, new_stat_epochs)
        print("Model updated to {} epochs, saved!".format(new_stat_epochs))


if TEST:  # Temporary condition
    y_test_arrange = [np.ones(shape=[x_test.shape[0], 1]), to_categorical(y_test, num_classes=num_classes + 1)]
    d_loss = disc.evaluate(x_test, y_test_arrange, batch_size=128, verbose=1)
    print("Test: [D loss: %f, acc: %.2f%%, op_acc: %.2f%%]" % (d_loss[0], 100 * d_loss[3], 100 * d_loss[4]))

# if SAVE_PREDICTIONS:
#     # predict
#     yy_probabilities = disc.predict(x_test, batch_size=batch_size)
#     yy_predicted = tfs.maximize_output_probabilities(yy_probabilities)
#     data_dict = {'x_val': x_test, 'y_val': y_test, 'y_prob': yy_probabilities, 'y_out': yy_predicted}
#     savemat(tfs.prep_dir(output_folder) + description + '.mat', mdict=data_dict)

# if SAVE_HIDDEN:
#     layers_of_interest = ['conv1d_1', 'conv1d_2', 'conv1d_3', 'conv1d_4']
#     np.random.seed(0)
#     rand_indices = np.random.randint(0, x_test.shape[0], 250)
#     print('Saving hidden layers: ', layers_of_interest)
#     tfs.get_keras_layers(disc, layers_of_interest, x_test[rand_indices], y_test[rand_indices],
#                          output_dir=tfs.prep_dir('classify_data_out/hidden_layers/'),
#                          fname='h_' + description + '.mat')

print('Elapsed Time (ms): ', tfs.current_time_ms() - start_time_ms)
print('Elapsed Time (min): ', (tfs.current_time_ms() - start_time_ms) / 60000)

# TODO: Fix this for DISC:
if EXPORT_OPT_BINARY:
    tfs.export_model_keras(disc_file, export_dir=tfs.prep_dir("graph"), model_name=description, sequential=False)
