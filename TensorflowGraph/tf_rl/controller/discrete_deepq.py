# -*- coding: utf-8 -*-

# DQN taken from
# https://github.com/nivwusquorum/tensorflow-deepq
# thank you Szymon Sidor ;)

import numpy as np
import random
import tensorflow as tf

from collections import deque

class DiscreteDeepQ(object):
    # Описание параметров ниже
    def __init__(self, observation_size,
                       num_actions,
                       observation_to_actions,
                       optimizer,
                       session,
                       random_action_probability=0.05,
                       exploration_period=1000,
                       store_every_nth=5,
                       train_every_nth=5,
                       minibatch_size=32,
                       discount_rate=0.95,
                       max_experience=30000,
                       target_network_update_rate=0.01,
                       summary_writer=None):
        # Этот большой комментарий я просто переведу ниже
        """Initialized the Deepq object.

        Based on:
            https://www.cs.toronto.edu/~vmnih/docs/dqn.pdf

        Parameters
        -------
        observation_size : int
            length of the vector passed as observation
        num_actions : int
            number of actions that the model can execute
        observation_to_actions: dali model
            model that implements activate function
            that can take in observation vector or a batch
            and returns scores (of unbounded values) for each
            action for each observation.
            input shape:  [batch_size, observation_size]
            output shape: [batch_size, num_ac