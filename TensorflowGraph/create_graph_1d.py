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
# double currentRot