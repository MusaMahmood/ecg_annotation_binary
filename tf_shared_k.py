import glob
import os as os
import time

import numpy as np
import pandas as pd
import tensorflow as tf
from keras import backend as K
from keras.models import Sequential, load_model, Model
from scipy.io import loadmat, savemat
from sklearn.metrics import confusion_matrix
from tensorflow.python.tools import freeze_graph
from tensorflow.python.tools import optimize_for_inference_lib


def current_time_ms():
    return int(round(time.time() * 1000))


def load_mat(file_path, key, shape):
    x_array = loadmat(file_path).get(key)
    x_array = np.reshape(x_array, [x_array.shape[0], *shape])
    print("Loaded Data Shape: ", key, ': ', x_array.shape)
    return x_array


def maximize_output_probabilities(array):
    array_out = np.copy(array)
    for i in range(array.shape[0]):
        b = np.zeros_like(array[i, :, :])
        b[np.arange(len(array[i, :, :])), array[i, :, :].argmax(1)] = 1
        array_out[i, :, :] = b
    return array_out


def load_data_v2(data_directory, x_shape, y_shape, key_x, key_y, shuffle=False, ind2vec=False):
    x_train_data = np.empty([0, *x_shape], np.float32)
    y_train_data = np.empty([0, *y_shape], np.float32)
    training_files = glob.glob(data_directory + "/*.mat")
    for f in training_files:
        print('Loading file: ', f)
        x_array = loadmat(f).get(key_x)
        y_array = loadmat(f).get(key_y)
        if x_shape[1] == 1:
            x_array = np.reshape(x_array, [x_array.shape[0], *x_shape])
        x_train_data = np.concatenate((x_train_data, x_array), axis=0)
        y_train_data = np.concatenate((y_train_data, y_array), axis=0)
    if shuffle:
        np.random.shuffle(x_train_data)
    if ind2vec:
        y_train_data = np.reshape(y_train_data, [y_train_data.shape[0], ])
        y_train_data = np.asarray(pd.get_dummies(y_train_data).values).astype(np.float32)
    # return data_array
    print("Loaded Data Shape: X:", x_train_data.shape, " Y: ", y_train_data.shape)
    return x_train_data, y_train_data


def get_session(gpu_fraction=0.9, allow_soft_placement=False):
    # allocate % of gpu memory.
    num_threads = os.environ.get('OMP_NUM_THREADS')
    gpu_options = tf.GPUOptions(per_process_gpu_memory_fraction=gpu_fraction)
    if num_threads:
        return tf.Session(config=tf.ConfigProto(gpu_options=gpu_options, intra_op_parallelism_threads=num_threads,
                                                allow_soft_placement=allow_soft_placement))
    else:
        return tf.Session(config=tf.ConfigProto(gpu_options=gpu_options, allow_soft_placement=allow_soft_placement))


def prep_dir(directory):
    if not os.path.exists(directory):
        os.makedirs(directory)
    return directory


# Save graph/model:
def export_model_keras(keras_model='model.h5', export_dir="graph", model_name="temp_model_name", sequential=True,
                       custom_objects=None):
    K.clear_session()  # Clears existing graph.
    if os.path.isfile(keras_model):
        if custom_objects is None:
            model = load_model(keras_model)
        else:
            model = load_model(keras_model, custom_objects=custom_objects)
    else:
        return

    # All new operations will be in test mode from now on.
    K.set_learning_phase(0)

    # Serialize the model and get its weights, for quick re-building.
    config = model.get_config()
    weights = model.get_weights()

    # Re-build a model where the learning phase is now hard-coded to 0.
    if sequential:
        new_model = Sequential.from_config(config, custom_objects=custom_objects)
    else:
        new_model = Model.from_config(config, custom_objects=custom_objects)

    new_model.set_weights(weights)

    temp_dir = "graph"
    checkpoint_prefix = os.path.join(temp_dir, "saved_checkpoint")
    checkpoint_state_name = "checkpoint_state"
    input_graph_name = "untrained_input_graph.pb"

    # Temporary save graph to disk without weights included.
    saver = tf.train.Saver()
    checkpoint_path = saver.save(K.get_session(), checkpoint_prefix, global_step=0,
                                 latest_filename=checkpoint_state_name)
    tf.train.write_graph(K.get_session().graph, temp_dir, input_graph_name)

    input_graph_path = os.path.join(temp_dir, input_graph_name)
    # input_saver_def_path = ""
    input_saver_def_path = None
    input_binary = False
    input_node_names = [node.op.name for node in model.inputs]
    output_node_names = [node.op.name for node in model.outputs]
    print("Input layer name: ", input_node_names)
    print("Output layer name: ", output_node_names)
    restore_op_name = "save/restore_all"
    filename_tensor_name = "save/Const:0"
    output_graph_path = export_dir + '/frozen_' + model_name + '.pb'
    clear_devices = True  # Remove all the explicit device specifications for this node. This helps to
    # make the graph more portable.

    # Embed weights inside the graph and save to disk.
    freeze_graph.freeze_graph(input_graph_path, input_saver_def_path, input_binary, checkpoint_path, *output_node_names,
                              restore_op_name, filename_tensor_name, output_graph_path, clear_devices, "")

    input_graph_def = tf.GraphDef()
    with tf.gfile.Open(export_dir + '/frozen_' + model_name + '.pb', "rb") as f:
        input_graph_def.ParseFromString(f.read())
    output_graph_def = optimize_for_inference_lib.optimize_for_inference(input_graph_def, input_node_names,
                                                                         output_node_names, tf.float32.as_datatype_enum)
    with tf.gfile.FastGFile(export_dir + '/opt_' + model_name + '.pb', "wb") as f:
        f.write(output_graph_def.SerializeToString())

    print("Graph Saved - Output Directories: ")
    print("1 - Standard Frozen Model:", export_dir + '/frozen_' + model_name + '.pb')
    print("2 - Android Optimized Model:", export_dir + '/opt_' + model_name + '.pb')

    print_graph_nodes(export_dir + '/frozen_' + model_name + '.pb')

    return model


def print_graph_nodes(filename):
    g = tf.GraphDef()
    g.ParseFromString(open(filename, 'rb').read())
    print()
    print(filename)
    print("=======================INPUT=========================")
    print([n for n in g.node if n.name.find('input') != -1])
    print("=======================OUTPUT========================")
    print([n for n in g.node if n.name.find('output') != -1])
    print("===================KERAS_LEARNING=====================")
    print([n for n in g.node if n.name.find('keras_learning_phase') != -1])
    print("======================================================")
    print()


def print_confusion_matrix(y_prob, y_true):
    y_prob_maximized = maximize_output_probabilities(y_prob)
    y_prob_shape = y_prob.shape
    y_prob_r = np.argmax(np.reshape(y_prob_maximized, [y_prob_shape[0] * y_prob_shape[1], y_prob_shape[2]]), axis=1)
    y_test_shape = y_true.shape
    y_test_r = np.argmax(np.reshape(y_true, [y_test_shape[1] * y_test_shape[0], y_test_shape[2]]), axis=1)
    confusion = confusion_matrix(y_test_r, y_prob_r)
    print("Confusion Matrix: \n", confusion)


def get_keras_layers(model, layers_to_extract, data, y_true, output_dir, fname='hidden_all_outputs.mat'):
    d = {'inputs': data, 'y_true': y_true}
    for l in range(0, len(layers_to_extract)):
        layer_name = layers_to_extract[l]
        layer = model.get_layer(name=layer_name)
        intermediate_layer_model = Model(inputs=model.input, outputs=layer.output)
        d[layer_name] = intermediate_layer_model.predict(data)
    savemat(prep_dir(output_dir) + fname, mdict=d)
    print('Saving hidden layers: ', layers_to_extract, ' to: ', output_dir + fname)
