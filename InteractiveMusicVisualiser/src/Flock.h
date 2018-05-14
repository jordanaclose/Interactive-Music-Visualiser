#pragma once

//=========================================================================
// Flock and Starling code from Daniel Shiffman's book "The Nature of Code"
// (Chapter 6 - Autonomous Agents)
//=========================================================================

#include <vector>
#include "ofMain.h"
#include "Starling.h"


	class Flock
	{
	public:
        Flock();
        
        std::vector<Starling> starlings;

		virtual void run();

		virtual void addStarling(Starling s);
        
        std::vector<Starling> getStarling();
	};
