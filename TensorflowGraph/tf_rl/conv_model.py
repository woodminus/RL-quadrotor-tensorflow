import tensorflow as tf
import numpy as np

from .models import MLP

from .utils import base_name2

class CNN(object):
    def __init__(self, cnn_input_size, addition_size, cnn_weights, cnn_strides, cnn_maxpooling, cnn_nonlinearities, mlp_input, mlp_hiddens, mlp_nonlinearities, scope=None, reuse=False):
        
        self.cnn_input_size = cnn_input_size
        self.cnn_input_flatten_size = cnn_input_size[0]*cnn_input_size[1]
        self.addition_size = addition_size
        self.cnn_weights = cnn_weights
        self.cnn_strides = cnn_strides
        self.cnn_maxpooling = cnn_maxpooling
        self.cnn_nonlinearities = cnn_nonlinearities
        self.mlp_input = mlp_input
        self.mlp_hiddens = mlp_hiddens
        self.mlp_nonlinearities = mlp_nonlinearities
        self.scope = scope
        
        fake_input = tf.placeholder(tf.float32, [None, self.cnn_input_flatten_size + addition_size])
        self.gen_model (fake_input, reuse=reuse)

        with tf.variable_scope(self.scope) as sc:
            
            self.model_variables = [v for v in tf.trainable_variables() if v.name.startswith(sc.name)]
            for v in self.model_variables:
                print ("CNN v: " + v.name)
        
    def gen_model(self, model_input, reuse=True):
        
        if (isinstance(model_input, list)):
            model_input = tf.concat (1, [model_input[0], model_input[1