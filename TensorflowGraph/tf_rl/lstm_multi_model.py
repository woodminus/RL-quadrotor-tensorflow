import tensorflow as tf

from .utils import base_name2

class LSTMMultiModel(object):
    def __init__(self, layer_size, layers_count, input_size, output_size, nonlinearity, scope=None):

        self.layer_size = layer_size
        self.layers_count = layers_count
        self.input_size = input_size
        self.output_size = output_size
        self.nonlinearity = nonlinearity
        self.scope = scope or "LSTM"

        #creating initial states for agents
        
        
        with tf.variable_scope(self.scope) as vs:

            self.cell = tf.nn.rnn_cell.LSTMCell(self.layer_size, state_is_tuple=True)
            self.cell2 = tf.nn.rnn_cell.LSTMCell(self.layer_size, state_is_tuple=True)
#      