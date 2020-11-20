//
//  DDPG_LSTM.hpp
//  Quadrocopter2DBrain
//
//  Created by anton on 06/10/16.
//  Copyright © 2016 anton. All rights reserved.
//

#ifndef DDPG_LSTM_hpp
#define DDPG_LSTM_hpp

#include <random>

#include "BrainDiscreteDeepQ.hpp"

class DDPG_LSTM : public BrainDiscreteDeepQ {
public:

	DDPG_LSTM ();

	void control (const ObservationSeqLimited& ob, std::vector<float>& action, double randomness) override;

	/**
		@return prediction error on choosed miniba