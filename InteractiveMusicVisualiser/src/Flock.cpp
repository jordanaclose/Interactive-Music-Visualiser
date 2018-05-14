//=========================================================================
// Flock and Starling code from Daniel Shiffman's book "The Nature of Code"
// (Chapter 6 - Autonomous Agents)
//=========================================================================

#include "Flock.h"

    Flock::Flock()
	{

	}

	void Flock::run()
	{
		for (auto& s : starlings)
		{
            s.run(starlings);
		}
	}

	void Flock::addStarling(Starling s)
	{
		starlings.push_back(s);
	}

    std::vector<Starling> Flock::getStarling()
    {
        return starlings;
    }
