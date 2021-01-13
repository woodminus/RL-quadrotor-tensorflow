import numpy as np
import tempfile
import tensorflow as tf

from tf_rl.controller import ContinuousDeepQ
#from tf_rl.simulation import KarpathyGame
from tf_rl import simulate
from tf_rl.models import MLP

#tf.ops.reset_default_graph()
session = tf.Session()

# This little guy will let us run tensorboard
#      tensorboard --logdir [LOG_DIR]
journalist = tf.train.SummaryWriter("/tmp")

observation_size = 50;
observations_in_seq = 1;
input_size = observation_size*observations_in_seq;

# actions
num_actions = 2;

#critic = MLP([input_size, num_actions*2], [2048, 1024, 1],
#            [tf.nn.sigmoid, tf.nn.sigmoid, tf.identity], scope='critic')
#
#actor = MLP([input_size,], [2048, 1024, num_actions],
#            [tf.nn.sigmoid, tf.nn.sigmoid, tf.identity], scope='actor')

r = tf.nn.relu
t = tf.nn.tanh

critic = MLP([input_size, num_actions], [2048, 512, 256, 256, 1],
            [t, t, t, t, tf.identity], scope='critic')

actor = MLP([input_size,], [2048, 512, 256, 256, num_actions],
            [t, t, t, t, tf.identity], scope='actor')

# The optimizer to use. Here we use RMSProp as recommended
# by the publication
#optimizer = tf.train.RMSPropOptimizer(learning_rate= 0.0001, decay=0.9)
#optimizer = tf.train.RMSPropOptimizer(learning_rate= 0.0005, decay=0.9)
optimizer = tf.train.AdamOptimizer(learning_rate= 0.0001)
#optimizer = tf.train.GradientDescentOptimizer(learning_rate= 0.001)

# DiscreteDeepQ object
current_controller = ContinuousDeepQ(input_size, num_actions, actor, critic, optimizer, session, discount_rate=0.99, target_actor_u