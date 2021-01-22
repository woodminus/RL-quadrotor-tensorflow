import numpy as np
import tempfile
import tensorflow as tf

from tf_rl.controller import DiscreteDeepQ
#from tf_rl.simulation import KarpathyGame
from tf_rl import simulate
from tf_rl.models import MLP
from tf_rl.models import SeparatedMLP

#tf.ops.reset_default_graph()
session = tf.Session()

# This little guy will let us run tensorboard
#      tensorboard --logdir [LOG_DIR]
journalist = tf.train.SummaryWriter("/Users/anton/devel/unity/QuadrocopterHabr/TensorflowLog")

observation_size = 7;
observations_in_seq = 1;
input_size = observation_size*observations_in_seq;

# actions
num_actions = 5;

#brain = MLP([input_size,], [5, 5, 5, num_actions], 
#            [tf.tanh, tf.tanh, tf.tanh, tf.identity])
#brain = MLP([input_size,], [20, 20, 20, 20, num_actions], 
#            [tf.tanh, tf.tanh, tf.tanh, tf.tanh, tf.identity])

brain = SeparatedMLP ([
        MLP([input_size,], [8, 8, 1], [tf.nn.relu, tf.nn.relu, tf.identity], scope="mlp_action1"),
        MLP([input_size,], [8, 8, 1], [tf.nn.relu, tf.nn.relu, tf.identity], scope="mlp_action2"),
        MLP([input_size,], [8, 8, 1], [tf.nn.relu, tf.nn.relu, tf.identity], scope="mlp_action3"),
        MLP([input_size,], [8, 8, 1], [tf.nn.relu, tf.nn.relu, tf.identity], scope="mlp_action4"),
        MLP([input_size,], [8, 8, 1], [tf.nn.relu, tf.nn.relu, tf.identity], scope="mlp_action5"),
        ])

# The optimizer to use. Here we use RMSProp as recommended
# by the publication
#optimizer = tf.train.RMSPropOptimizer(learning_rate= 0.0001, decay=0.9)
optimizer = tf.train.RMSPropOptimizer(learning_rate= 0.0001, decay=0.9)

# DiscreteDeepQ object
current_controller = DiscreteDeepQ(input_size, num_actions, brain, optimizer, session, discount_r