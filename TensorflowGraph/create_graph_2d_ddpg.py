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
#actor = MLP([input_size,], [2048, 1024, num_act