
# DDPG taken from
# https://github.com/nivwusquorum/tensorflow-deepq

import numpy as np
import random
import tensorflow as tf

from collections import deque

class ContinuousDeepQ(object):
    def __init__(self, observation_size,
                       action_size,
                       actor,
                       critic,
                       optimizer,
                       session,
                       exploration_sigma=0.05,
                       exploration_period=1000,
                       store_every_nth=5,
                       train_every_nth=5,
                       minibatch_size=32,
                       discount_rate=0.95,
                       max_experience=30000,
                       target_actor_update_rate=0.01,
                       target_critic_update_rate=0.01,
                       summary_writer=None,
                       rewards = None,
                       given_action = None,
                       observation_for_act = None,
                       observation = None,
                       next_observation = None,
                       next_observation_mask = None
                       ):
        """Initialized the Deepq object.
        Based on:
            https://www.cs.toronto.edu/~vmnih/docs/dqn.pdf
        Parameters
        -------
        observation_size : int
            length of the vector passed as observation
        action_size : int
            length of the vector representing an action
        observation_to_actions: dali model
            model that implements activate function
            that can take in observation vector or a batch
            and returns scores (of unbounded values) for each
            action for each observation.
            input shape:  [batch_size, observation_size]
            output shape: [batch_size, action_size]
        optimizer: tf.solver.*
            optimizer for prediction error
        session: tf.Session
            session on which to execute the computation
        exploration_sigma: float (0 to 1)
        exploration_period: int
            probability of choosing a random
            action (epsilon form paper) annealed linearly
            from 1 to exploration_sigma over
            exploration_period
        store_every_nth: int
            to further decorrelate samples do not all
            transitions, but rather every nth transition.
            For example if store_every_nth is 5, then
            only 20% of all the transitions is stored.
        train_every_nth: int
            normally training_step is invoked every
            time action is executed. Depending on the
            setup that might be too often. When this
            variable is set set to n, then only every
            n-th time training_step is called will
            the training procedure actually be executed.
        minibatch_size: int
            number of state,action,reward,newstate
            tuples considered during experience reply
        dicount_rate: float (0 to 1)
            how much we care about future rewards.
        max_experience: int
            maximum size of the reply buffer
        target_actor_update_rate: float
            how much to update target critci after each
            iteration. Let's call target_critic_update_rate
            alpha, target network T, and network N. Every
            time N gets updated we execute:
                T = (1-alpha)*T + alpha*N
        target_critic_update_rate: float
            analogous to target_actor_update_rate, but for
            target_critic
        summary_writer: tf.train.SummaryWriter
            writer to log metrics
        """
        # memorize arguments
        self.observation_size          = observation_size
        self.action_size               = action_size

        self.actor                     = actor
        self.critic                    = critic
        self.optimizer                 = optimizer
        self.s                         = session

        self.exploration_sigma         = exploration_sigma
        self.exploration_period        = exploration_period
        self.store_every_nth           = store_every_nth
        self.train_every_nth           = train_every_nth
        self.minibatch_size            = minibatch_size
        self.discount_rate             = tf.constant(discount_rate)
        self.max_experience            = max_experience

        self.target_actor_update_rate = \
                tf.constant(target_actor_update_rate)
        self.target_critic_update_rate = \
                tf.constant(target_critic_update_rate)

        # deepq state
        self.actions_executed_so_far = 0
        self.experience = deque()

        self.iteration = 0
        self.summary_writer = summary_writer

        self.number_of_times_store_called = 0
        self.number_of_times_train_called = 0

        self.rewards = tf.placeholder(tf.float32, (None,), name="rewards") if (rewards is None) else rewards
        self.given_action = tf.placeholder(tf.float32, (None, action_size), name="given_action") if given_action is None else given_action
        self.observation_for_act = tf.placeholder(tf.float32, (None, self.observation_size), name="observation_for_act") if observation_for_act is None else observation_for_act
        self.observation = tf.placeholder(tf.float32, (None, self.observation_size), name="observation") if observation is None else observation
        self.next_observation = tf.placeholder(tf.float32, (None, self.observation_size), name="next_observation") if next_observation is None else next_observation
        self.next_observation_mask = tf.placeholder(tf.float32, (None,), name="next_observation_mask") if next_observation_mask is None else next_observation_mask

        self.create_variables()

    @staticmethod
    def linear_annealing(n, total, p_initial, p_final):
        """Linear annealing between p_initial and p_final
        over total steps - computes value at step n"""
        if n >= total:
            return p_final
        else:
            return p_initial - (n * (p_initial - p_final)) / (total)

    @staticmethod
    def update_target_network(source_network, target_network, update_rate):
        target_network_update = []
        for v in source_network.variables():
            # this is equivalent to target = (1-alpha) * target + alpha * source
            # print ("source: " + v.name + " : " + str(v.get_shape()))
            pass
        for v in target_network.variables():
            # this is equivalent to target = (1-alpha) * target + alpha * source
            # print ("target: " + v.name + " : " + str(v.get_shape()))
            pass
        for v_source, v_target in zip(source_network.variables(), target_network.variables()):
            # this is equivalent to target = (1-alpha) * target + alpha * source
            update_op = v_target.assign_sub(update_rate * (v_target - v_source))
            target_network_update.append(update_op)