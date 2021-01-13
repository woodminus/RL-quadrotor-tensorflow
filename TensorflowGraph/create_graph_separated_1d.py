import numpy as np
import tempfile
import tensorflow as tf

from tf_rl.controller import DiscreteDeepQ
#from tf_rl.simulation import KarpathyGame
from tf_rl import simulate
from tf_rl.models import MLP
from tf_rl.models import Sep