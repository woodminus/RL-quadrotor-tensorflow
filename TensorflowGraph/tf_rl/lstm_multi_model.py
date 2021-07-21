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
#            self.multi_cell = tf.nn.rnn_cell.MultiRNNCell([cell] * self.layers_count, state_is_tuple=True)
            
            self.states  = tf.nn.rnn_cell.LSTMStateTuple (tf.placeholder(tf.float32, (None, self.layer_size), name="state_c"), tf.placeholder(tf.float32, (None, self.layer_size), name="state_h"))
            xs  = tf.placeholder(tf.float32, (None, input_size), name="xs")
            xs_prev  = tf.placeholder(tf.float32, (None, input_size), name="xs_prev")
            
            val, state = self.cell  (xs, self.states)
            val, state = self.cell2 (xs_prev, state)

            w = tf.truncated_normal([self.layer_size, self.output_size]);
            self.weight = tf.get_variable ("weight", w.get_shape(), initializer=lambda x,dtype=tf.float32: w)

            b = tf.constant(0.1, shape=[self.output_size])
            self.bias = tf.get_variable ("bias", b.get_shape(), initializer=lambda