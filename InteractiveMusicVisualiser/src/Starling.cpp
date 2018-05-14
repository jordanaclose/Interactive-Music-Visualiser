//=========================================================================
// Flock and Starling code from Daniel Shiffman's book "The Nature of Code"
// (Chapter 6 - Autonomous Agents)
//=========================================================================

#include "Starling.h"

    Starling::Starling()
    {
        acceleration.set(ofRandom(-3, 3), ofRandom(-3, 3));
        velocity.set(0, 0);
        location.set(ofRandom(ofGetWidth()/4, 3*ofGetWidth()/4), ofRandom(ofGetHeight()/4, 3*ofGetHeight()/4));
        
        r = 3.0f;
        maxspeed = Global::maxspeed;
        maxforce = Global::maxforce;
        radius = ofRandom(3, 6);
    }

    
	ofVec2f Starling::separate(std::vector<Starling> starlings)
	{
		ofVec2f sum;
		int count = 0;
		for (auto& other : starlings)
		{
            float d = location.distance(other.location);
			if ((d > 0) && (d < Global::separationDist))
			{
                ofVec2f diff = location - other.location;
				diff.normalize();
				diff = diff/d;
				sum = sum+diff;
				count++;
			}
		}
		if (count > 0)
		{
			sum = sum/count;
			sum.normalize();
			sum = sum * (maxspeed);
			ofVec2f steer = sum - velocity;
			steer.limit(maxforce);
			return steer;
		}
		else
		{
			return ofVec2f(0,0);
		}
	}

	ofVec2f Starling::align(std::vector<Starling> starlings)
	{
		ofVec2f sum(0,0);
		int count = 0;
		for (auto& other : starlings)
		{
            float d = location.distance(other.location);
			if ((d > 0) && (d < Global::alignDist))
			{
                sum = sum + other.velocity;
				count++;
			}
		}
		if (count > 0)
		{
			sum = sum/count;
			sum.normalize();
			sum = sum * maxspeed;
			ofVec2f steer = sum - velocity;
			steer.limit(maxforce);
			return steer;
		}
		else
		{
			return ofVec2f(0,0);
		}
	}

	ofVec2f Starling::cohesion(std::vector<Starling> starlings)
	{
		 ofVec2f sum(0,0);
		 int count = 0;
		 for (auto& other : starlings)
		 {
             float d = location.distance(other.location);
			 if ((d > 0) && (d < Global::cohesionDist))
			 {
                 sum = sum+other.location;
				 count++;
			 }
		 }
		 if (count > 0)
		 {
			 sum = sum/count;
			 return seek(sum);
		 }
		 else
		 {
			 return ofVec2f(0,0);
		 }
	}

	void Starling::move()
	{
        velocity = velocity+acceleration;
		velocity.limit(maxspeed);
		location = location + velocity;
        acceleration.set(0,0);
	}

	void Starling::applyForce(ofVec2f force)
	{
		acceleration = acceleration + force;
	}

	ofVec2f Starling::seek(ofVec2f target)
	{
        ofVec2f desired = target - location;
		desired.normalize();
		desired = desired * maxspeed;
		desired = desired * 0.8f;
		ofVec2f steer = desired - velocity;
		steer.limit(maxforce);
		return steer;
	}

	void Starling::flee(ofVec2f enemy)
	{
        ofVec2f avoid = enemy - location;
		avoid.normalize();
		avoid = avoid * maxspeed;
		avoid = avoid * -10.0f;
		ofVec2f steer = avoid - velocity;
		steer.limit(Global::maxFleeForce);
		applyForce(steer);
	}

	void Starling::display()
	{
        ofDrawCircle(location.x, location.y, radius);
    }

    void Starling::bass()
    {
        ofDrawCircle(location.x, location.y, radius*3);
    }

    void Starling::midrange()
    {
        ofDrawCircle(location.x, location.y, radius*2);
    }
    
    void Starling::high()
    {
        ofSetColor(255, 255, 255);
        ofFill();
        ofDrawCircle(ofRandom(Global::width), ofRandom(Global::height), 3);

    }

	void Starling::checkEdges()
	{
		if(location.x > ofGetWidth()){
			location.x = 0; 
		}
		else if(location.x < 0){
			location.x = ofGetWidth();
		}
		
		if(location.y > ofGetHeight()){
			location.y = 0; 
		}
		else if(location.y < 0){
			location.y = ofGetHeight(); 
		}
	}

	void Starling::run(std::vector<Starling> starlings)
	{
		//The three flocking rules
		ofVec2f sep = separate(starlings);
		ofVec2f ali = align(starlings);
		ofVec2f coh = cohesion(starlings);

		applyForce(sep);
		applyForce(ali);
		applyForce(coh);

		move();
        display();
		checkEdges();
	}
