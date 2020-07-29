
//
//  QuadrocopterSimulator.hpp
//  Quadrocopter-Visualizer
//
//  Created by anton on 07/05/16.
//
//

#ifndef QuadrocopterSimulator_hpp
#define QuadrocopterSimulator_hpp

#include <functional>
#include <vector>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
//#include "unistd.h"

#include "Simulation.hpp"
#include "QuadrocopterCtrl.hpp"
#include "QuadrocopterDiscreteCtrl.hpp"
#include "main.h"
#include "Quadrocopter2DBrain.hpp"
#include "Quadrocopter2DCtrl.hpp"
#include "QuadrocopterDiscrete2DCtrl.hpp"
#include "ConsumerProducerSyncronizer.hpp"
#include "WorldDiscrete.hpp"
#include "QuadrocopterDiscrete2D.hpp"
#include "QuadrocopterContActionCtrl.hpp"
#include "Quadrocopter2DContActionCtrl.hpp"
#include "Lib.h"
#include "Quadrocopter2DContActionPIDCtrl.hpp"
#include "Quadrocopter2DContActionPIDLSTMCtrl.hpp"
#include "Quadrocopter2DContActionLSTMWeakCtrl.hpp"
#include "Quadrocopter2DContActionMLPSeqCtrl.hpp"
#include "Quadrocopter2DContActionLSTMCtrl.hpp"

template <
	typename WorldType,
	typename QuadrocopterCtrlType,
	typename QuadrocopterType,
	typename ObstacleType
	>
class QuadrocopterSimulatorTmpl {
public:

	QuadrocopterSimulatorTmpl ();
	void init ();
	void reset ();
	void startActWorkers ();
	void startTrainWorkers ();
	void stop ();
	void setSimulationUpdateCallback (std::function<void ()> callback);
	void join ();
	
	QuadrocopterCtrlType& getQuadrocopterCtrl (int index);
	ObstacleType& getObstacle (int index) {
		return simulation.getWorld().getObstacle (index);
	}
	
	WorldType& getWorld () {
		return simulation.getWorld();
	}
	
	void setCollideListener (typename WorldType::CollideListener listener) {
		collideListener = listener;
	}

private:

	int trainStepIndex = 1;
	std::mutex mtxChangeQCopterParams;
	std::mutex mtxBox2DQCopterWorkers;

	SimulationTmpl<WorldType, QuadrocopterType> simulation;
	std::atomic<int> stepIndex;
	std::vector<QuadrocopterCtrlType> qcopterCtrls;
	
	typedef std::function<void ()> QCopterWorker;
	typedef std::function<void ()> QCopterTrainWorker;
	QCopterWorker qcopterMainWorker;
	std::vector<QCopterWorker> qcopterWorkers;
	QCopterTrainWorker trainWorker;
	
	std::atomic<bool> allowThreadsWork;
	std::thread qcopterMainWorkerThread;
	std::vector<std::thread> qcopterWorkersThreads;
	std::vector<std::thread> trainWorkerThreads;