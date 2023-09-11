# Reinforcement Learning Quadrotor 2D

This project is a bit dated and uses older technologies.

This is a 2D quadrotor simulator that employs reinforcement learning to master flight maneuvers and achieve its objectives. There's a brief video demonstration available.

[![RL Quadrotor 2D video](http://img.youtube.com/vi/acQJfkgeiZc/0.jpg)](https://www.youtube.com/watch?v=acQJfkgeiZc)

Bear in mind, building and running it could be a bit complex, as it requires tensorflow compiled in dynamic library libtensorflow.so for reinforcement learning, and cocos2-x for building the simulator. There's a plan to separate the code into two repositories, one for the reinforcement learning server, and another for the quadrotor simulator.