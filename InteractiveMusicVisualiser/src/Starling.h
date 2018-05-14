#pragma once

//=========================================================================
// Flock and Starling code from Daniel Shiffman's book "The Nature of Code"
// (Chapter 6 - Autonomous Agents)
//=========================================================================

#include <vector>
#include "ofMain.h"
#include "Global.h"


    class Starling
	{
	public:

        Starling();
        
        ofVec2f location;
        ofVec2f velocity;
        ofVec2f acceleration;

		float r;
		float maxforce;
		float maxspeed;
        float radius;

		virtual ofVec2f separate(std::vector<Starling> starlings);

		virtual ofVec2f align(std::vector<Starling> starlings);

		virtual ofVec2f cohesion(std::vector<Starling> starlings);


		virtual void move();

		virtual void applyForce(ofVec2f force);

		virtual ofVec2f seek(ofVec2f target);

		virtual void flee(ofVec2f enemy);

		  virtual void display();
        
        virtual void high();
        
        virtual void midrange();
        
        virtual void bass();

		  virtual void checkEdges();

		  virtual void run(std::vector<Starling> starlings);
	};
