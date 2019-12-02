//! \file landbasedtracked.h

#pragma once
#include <iostream>
//!Includes basic Land Based Robot header file needed to create derived classes.
#include "../LandBasedRobot/landbasedrobot.h" 

namespace fp //!Defines common fp namespace.
{
//!Creates LandBasedTracked class by deriving from basic LandBasedRobot class.
class LandBasedTracked : public LandBasedRobot
{
	public:
		//!Constructor for LandBasedTracked robot using LandBasedRobot as derived object.
		LandBasedTracked(std::string, int, int, std::string track_type="");

		//!Getter for track type pointer.
		std::string get_track_type() const{
			return track_type_; //!Returns track type
		}
		
		//!Setter for track type pointer.
		void set_track_type(std::string track_type){
			track_type_ = track_type;
		}
        
		//!Function Prototyping.
		virtual void MoveForward() override;       		//! Move the robot forward in the maze.
		virtual void TurnLeft() override;   			//! Turn Robot 90 deg counter-clockwise direction.
		virtual void TurnRight() override;  			//! Turn Robot 90 deg clockwise direction.
		
        //!Destructor.
		virtual ~LandBasedTracked(){} //!Destructor of LandBasedTracked class.
		
	protected:
		std::string track_type_; //! Defining type of track mounted on the robot under protected attributes.
        
};//End of the LandBasedTracked class.
}//End of namespace fp.