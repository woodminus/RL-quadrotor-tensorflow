//
//  BrainDiscreteDeepQ.hpp
//  QuadrocopterBrain
//
//  Created by anton on 17/01/16.
//  Copyright © 2016 anton. All rights reserved.
//

#ifndef BrainDiscreteDeepQ_hpp
#define BrainDiscreteDeepQ_hpp

#include "tensorflow/core/public/session.h"
//#include "tensorflow/core/public/env.h"

#include "Observation.hpp"
#include "ExperienceItem.hpp"
#include "BrainAlgorithm.hpp"

class BrainDiscreteDeepQ : public BrainAlgorithm {

public:

	BrainDiscreteDeepQ ();
	BrainDiscreteDeepQ (const std::string& tfGraphFilename);

	std::string getTFFilename ();

	/**
		@return index of action
	*/
	long control (const ObservationSeqLimited& ob, double randomness) override;
	
	void control (const ObservationSeqLimited& ob, std::vector<float>& action, double randomness) override {}
	
	void control (
		const ObservationSeqLimited& ob,
		const std::vector<float>& lstmStateC,
		const std::vector<float>& lstmStateH,
		std::vector<float>& action,
		double randomness//,
//		std::vector<float>& outLstmStateC,
//		std::vector<float>& outLstmStateH
	) override {}
	
//	/**
//		@return prediction error on choosed minibatch
//	*/
//	float train (
//		const std::vector<ExperienceItem>& experience,
//		std::vector