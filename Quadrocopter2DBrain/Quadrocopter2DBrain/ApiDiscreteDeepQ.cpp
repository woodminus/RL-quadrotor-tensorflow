//
//  ApiDiscreteDeepQ.cpp
//  Quadrocopter2DBrain
//
//  Created by anton on 20/03/16.
//  Copyright © 2016 anton. All rights reserved.
//

#include "ApiDiscreteDeepQ.hpp"

#include <iostream>
#include <math.h>
#include <stdio.h>
#include <vector>
#include <string>

#include "Unity/IUnityGraphics.h"

#include "Main.h"
#include "QuadrocopterBrain.hpp"
#include "ExpLambdaFilter.hpp"

using namespace std;

const int numOfQuadrocopters = 50;

QuadrocopterBrain quadrocopterBrain;
vector<ObservationSeqLimited> currStateSeqs;
vector<ObservationSeqLimited> prevStateSeqs;
vector<ExpLambdaFilter> experienceFilters; //one filter for each quadrocopter;
vector<double> randomnessOfQuadrocopter;

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetQuadrocopterState(
	int quadrocopterId,
	float* stateData
) {

	std::vector<float> stateV;
	stateV.resize(QuadrocopterBrain::observationSize);
	stateV.assign(stateData, stateData + QuadrocopterBrain::observationSize);
	Observation state (stateV);

	ObservationSeqLimited& currStateSeq = currStateSeqs [quadrocopterId];
	prevStateSeqs [quadrocopterId] = currStateSeq;
	currStateSeq.push(state);
}

extern "C" long UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API QuadrocopterBrainAct(
	int quadrocopterId
) {
	return quadrocopterBrain.act (
		currStateSeqs [quadrocopterId],
		randomnessOfQuadrocopter [quadrocopterId]
	);
}
