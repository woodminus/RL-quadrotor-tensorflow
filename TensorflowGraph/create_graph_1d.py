import numpy as np
import tempfile
import tensorflow as tf

from tf_rl.controller import DiscreteDeepQ
#from tf_rl.simulation import KarpathyGame
from tf_rl import simulate
from tf_rl.models import MLP

#tf.ops.reset_default_graph()
session = tf.Session()

# This little guy will let us run tensorboard
#      tensorboard --logdir [LOG_DIR]
journalist = tf.train.SummaryWriter("/Users/anton/devel/unity/QuadrocopterHabr/TensorflowLog")

# Brain maps from observation to Q values for different actions.
# Here it is a done using a multi layer perceptron with 2 hidden
# layers

# observation
# double currentRotW,
# double currentRotX,
# double currentRotY,
# double currentRotZ,
#
# double targetX,
# double targetY,
# double targetZ,
#
# double motor1powerVal,
# double motor2powerVal,
# double motor3powerVal,
# double motor4powerVal
observation_size = 4;
observations_in_seq = 1;
input_size = observation_size*observations_in_seq;

# actions
num_actions = 3;

#brain = MLP([input_size,], [5, 5, 5, num_actions], 
#            [tf.tanh, tf.tanh, tf.tanh, tf.identity])
#brain = MLP([input_size,], [20, 20, 20, 20, num_actions], 
#            [tf.tanh, tf.tanh, tf.tanh, tf.tanh, tf.identity])

#brain = MLP([input_size,], [32, 32, 32, 32, 32, num_actions], 
#            [tf.nn.relu, tf.nn.relu, tf.nn.relu, tf.nn.relu, tf.nn.relu, tf.identity])
brain = MLP([input_size,], [64, 64, num_actions], 
            [tf.sigmoid, tf.sigmoid, tf.identity])

# The optimizer to use. Here we use RMSProp as recommended
# by the publication
#optimizer =