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
            model_input = tf.concat (1, [model_input[0], model_input[1]])

        with tf.variable_scope(self.scope, reuse=reuse) as sc:
            
            cnn_input = tf.slice (model_input, [0, 0], [-1, self.cnn_input_flatten_size])
            mlp_input_addition = tf.slice (model_input, [0, self.cnn_input_flatten_size], [-1, self.addition_size])
            
            layerI = 0
            cnn_layer_input = tf.reshape (cnn_input, (-1, self.cnn_input_size[0], self.cnn_input_size[1], 1))
#            cnn_layer_input = tf.expand_dims(tf.expand_dims(cnn_input, 1), 3)
            for W, s, n, p in zip(self.cnn_weights, self.cnn_strides, self.cnn_nonlinearities, self.cnn_maxpooling):
                
                W_initializer = tf.truncated_normal_initializer ()
                W_var = tf.get_variable("cnn_layer_"+str(layerI)+"_w", W, initializer=W_initializer)
                cnn_layer_input = tf.nn.conv2d (cnn_layer_i