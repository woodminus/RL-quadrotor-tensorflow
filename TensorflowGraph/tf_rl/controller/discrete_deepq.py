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
            output shape: [batch_size, num_actions]
        optimizer: tf.solver.*
            optimizer for prediction error
        session: tf.Session
            session on which to execute the computation
        random_action_probability: float (0 to 1)
        exploration_period: int
            probability of choosing a random
            action (epsilon form paper) annealed linearly
            from 1 to random_action_probability over
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
        target_network_update_rate: float
            how much to update target network after each
            iteration. Let's call target_network_update_rate
            alpha, target network T, and network N. Every
            time N gets updated we execute:
                T = (1-alpha)*T + alpha*N
        summary_writer: tf.train.SummaryWriter
            writer to log metrics
        """

        """Инициализация Deepq

        Основано на:
            https://www.cs.toronto.edu/~vmnih/docs/dqn.pdf

        Параметры
        -------
        observation_size : int
            длина вектора входных данных (этот вектор
            будем называть наблюдением или состоянием)
            
        num_actions : int
            количество возможных действий или же
            длина вектора выходных данных нейросети
            
        observation_to_actions: dali model
            модель (в нашем случае нейросеть),
            которая принимает наблюдение или набор наблюдений
            и возвращает оценку очками каждого действия или
            набор оценок для каждого действия каждого из наблюдений
            входной размер: матрица [batch_size, observation_size]
            выходной размер: матрица [batch_size, num_actions]
            
        optimizer: tf.solver.*
            алгоритм рассчета обратого распространения ошибки
            в нашем случае будет использоваться RMSProp
            
        session: tf.Session
            сессия TensorFlow в которой будут производится вычисления
            
        random_action_probability: float (0 to 1)
            вероятность случайного действия,
            для обогощения опыта нейросети и улучшения качесва управления
            с определенной вероятностью выполняется случайное действие, а не
            действие выданное нейросетью
            
        exploration_period: int
            период поискового поведения в итерациях,
            в течении которого вероятность выполнения случайного
            действия падает от 1 до random_action_probability
            
        store_every_nth: int
            параметр нужен чтобы сохранять не все обучающие примеры
            а только определенную часть из них.
            Сохранение происходит один раз в указаное в параметре
            количество обучающих примеров
            
        train_every_nth: int
            обычно training_step (шаг обучения)
            запускается после каждого действия.
            Иногда получается так, что это слишком часто.
            Эта переменная указывает сколько шагов
            пропустить перед тем как запускать шаг обучения
            
        minibatch_size: int
            размер набора обучающих примеров который
            используется на одном шаге обучения
            алгоритмом RMSProp.
            Обучающий пример включает в себя
            состояние, предпринятое действие, награду и
            новое состояние
            
        dicount_rate: float (0 to 1)
            параметр Q-learning
            насколько сильно влияет будущая награда при
            расчете поль