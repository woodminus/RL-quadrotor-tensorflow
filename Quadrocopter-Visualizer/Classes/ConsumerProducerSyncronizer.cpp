//
//  ConsumerProducerSyncronizer.cpp
//  Quadrocopter-Visualizer
//
//  Created by anton on 29/05/16.
//
//

#include "ConsumerProducerSyncronizer.hpp"

ConsumerProducerSyncronizer::ConsumerProducerSyncronizer (int numOfProducers) :
	numOfProducers(numOfProducers)
{
	producersDone.assign(numOfProducers, false);
	producersMayProceed.assign(numOfProducers, false);
}

void ConsumerProducerSyncronizer::reportProducerDone (int index) {
	mtxProducersDone.lock();
	producersDone [index] = true;
	mtxProducersDone.unlock();
	std::unique_lock<std::mutex> lock(mtxConsumer);
	cvConsumer.notify_one();
}

void ConsumerProducerSyncronizer::reportConsumerDone () {
	setProducersNotDone();
	setProducersMayProceed();
	std::unique_lock<std::mutex> lock(mtxProducers);
	cvProducers.notify_all();
}

void ConsumerProducerSyncronizer::waitProducers () {
	std::unique_lock<std::mutex> lock(mtxConsumer);
	while (!isProducersDone()) {
		cvConsumer.wait(lock);
	}
}

void ConsumerProducerSyncronizer::waitConsumer (int index) {
	std::unique_lock<std::mutex> lock(mtxProducers);
	whil