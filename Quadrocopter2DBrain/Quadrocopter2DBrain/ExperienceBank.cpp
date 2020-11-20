//
//  ExperienceBank.cpp
//  Quadrocopter2DBrain
//
//  Created by anton on 17/04/16.
//  Copyright © 2016 anton. All rights reserved.
//

#include "ExperienceBank.hpp"
#include "Lib.hpp"

ExperienceBank::ExperienceBank () {
	experience.resize(maxExperience);
}

//static std::mutex storeExperienceMutex;

void ExperienceBank::store (const ExperienceItem& expItem) {
//	std::lock_guard<std::mutex> lock(storeExperienceMutex);
	
	experience [experienceI] = expItem;
	experienceI++;
	experienceI %= maxExperience;
	if (size < maxExperience) size++;

//	std::cerr << "--- ExperienceBank " << name << ": " << experienceI << " / " << experience.size() << std::endl;
}

v