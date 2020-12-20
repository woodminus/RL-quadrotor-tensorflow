//
//  Quadrocopter2DBrain.cpp
//  Quadrocopter2DBrain
//
//  Created by anton on 29/04/16.
//  Copyright © 2016 anton. All rights reserved.
//

#include "Quadrocopter2DBrain.hpp"

#include <iostream>
#include <math.h>
#include <stdio.h>
#include <vector>
#include <string>

#include "QuadrocopterBrain.hpp"
#include "ExpLambdaFilter.hpp"
#include "DDPG.hpp"
#include "DDPG_LSTM.hpp"
#include "DDPG_LSTM_Weak.hpp"

using namespace std;

namespace Quadrocopter2DBrain {

	const int numOfQuadrocopters = 64;

  QuadrocopterBrain quadrocopterBrain (std::shared_ptr<BrainAlgorithm> (new DDPG ()));
//	QuadrocopterBrain quadrocopterBrain (std::shared_ptr<BrainAlgorithm> (new DDPG_LSTM ()));
//	QuadrocopterBrain quadrocopterBrain (std::shared_ptr<BrainAlgorithm> (new DDPG_LSTM_Weak ()));
	
	const bool useLstmWeak = false;
//	const bool useLstmWeak = true;
	
	//lstm
	vector<ObservationSeqLimited> prevObsSeq;
	vector<ObservationSeqLimited> nextObsSeq;
	vector<ObservationSeqLimited> lstmActions;
	vector<ObservationSeqLimited> lstmRewards;
	
	vector<ExpLambdaFilter> experienceFilters; //one filter for each quadrocopter;
	vector<double> randomnessOfQuadrocopter;
	
	vector<ExperienceItem> lstmWeakExperience; // by copter
	vector<ExperienceItem*> lstmWeakExperienceMinibatch;

	vector<ObservationSeqLimited> prevObsMLPSeq;
	vector<ObservationSeqLimited> nextObsMLPSeq;


//	void setQuadrocopterState(
//		int quadrocopterId,
//		const std::vector<float>& stateV
//	) {
//
//	//	std::vector<float> stateV;
//	//	stateV.resize(QuadrocopterBrain::observationSize);
//	//	s