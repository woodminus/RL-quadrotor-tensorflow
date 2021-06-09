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
            print "placeholder state c: " + str(self.states [0])
            print "placeholder state h: " + str(self.states [1])

            xs  = tf.placeholder(tf.float32, (None, input_size), name="fake_xs")
            val, states = self.cell (xs, self.states)
#            if (needReuseVariables):
#                vs.reuse_variables()
            print "LSTMModel vs: ->" + vs.name + "<- reuse: " + str(vs.reuse)
            
            self.model_variables = [v for v in tf.trainable_variables()
                    if v.name.startswith(vs.name)]
            for v in self.model_variables:
                print "LSTMModel v: " + v.name

    def __call__(self, xs, states=None):
        with tf.variable_scope(self.scope, reuse=True) as vs:
            input_states = states or self.states
            val, states = self.cell (xs, self.states)
            self.out_state_c = tf.identity (sta