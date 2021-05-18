import tensorflow as tf
import numpy as np

from .models import MLP

from .utils import base_name2

class CNN(object):
    def __init__(self, cnn_input_size, addition_size, cnn_weights, cnn_strides, cnn_maxpooling, cnn_nonlinearities, mlp_input, mlp_hiddens, mlp_nonlinearities, scope=None, reuse=False):
        
        self.cnn_input_size = cnn_input_size
        self.cnn_input_flatten_size = cnn_input_size[0]*cnn_input_size[1]
        self.addition_size = addition_size
        self.cnn_weights = cnn_