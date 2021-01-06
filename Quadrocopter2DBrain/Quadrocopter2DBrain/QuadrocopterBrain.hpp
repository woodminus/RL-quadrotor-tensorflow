//
//  QuadrocopterBrain.hpp
//  QuadrocopterBrain
//
//  Created by anton on 19/01/16.
//  Copyright © 2016 anton. All rights reserved.
//

#ifndef QuadrocopterBrain_hpp
#define QuadrocopterBrain_hpp

#include <deque>
#include <list>

#include "BrainDiscreteDeepQ.hpp"
#include "ExperienceItem.hpp"
#include "ExperienceBank.hpp"
#include "BrainAlgorithm.hpp"

class QuadrocopterBrain {

public:
	
	static const int observationsInSeq = 1;

	//2d
	static const int observationSize = 50;
	static const int lstmStepsCount = 6;
	static const int lstmStateSize = 128;
	static const int numActions = 9;
	static const int contActionSize = 2;
	static const int mlpSeqSize = 4;
	
//	static const bool useObsSeq = true;
	static const bool useObsSeq = false;

	static const int minibatchSize = 128;

	//1d
//	static const int observationSize = 4;
//	static const int numActions = 3;
//	static const int contActionSize = 1;

	QuadrocopterBrain ();
	QuadrocopterBrain (std::shared_ptr<BrainAlgorithm> algorithm);
	
	long act (const ObservationSeqLimited& state, double randomness);
	void actCont (const ObservationSeqLimited& state, std::vector<float>& action, double randomness);
	void actContLSTMWeak (
		const ObservationSeqLimited& state,
		const std::vector<fl