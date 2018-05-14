#pragma once

//=========================================================================
// Flock and Starling code from Daniel Shiffman's book "The Nature of Code"
// (Chapter 6 - Autonomous Agents)
//=========================================================================

	class Global
	{
	public:
		static int width;
		static int height;

		static int populationSize;

		static float separationDist;
		static float alignDist;
		static float cohesionDist;

		static float maxspeed;
		static float maxforce;
		static float maxFleeForce;
	};
