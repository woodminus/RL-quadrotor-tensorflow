import tensorflow as tf

from .utils import base_name2

class LSTMModel(object):
    def __init__(self, input_size, layer_size, scope=None, needReuseVariables=True):

        self.layer_size = layer_size
        self.input_size = input_size
        self.scope = scope or "LSTM"
        
        with tf.variable_scope(self.scope) as vs:

            self.cell = tf.nn.rnn_cell.LSTMCell(self.layer_size, state_is_tuple=True)

            self.states  = tf.nn.rnn_cell.LSTMStateTuple (tf.placeholder(tf.float32, (None, self.layer_size), name="state_c"), tf.placeholder(tf.float32, (None, self.layer_size), name="state_h"))
            print 