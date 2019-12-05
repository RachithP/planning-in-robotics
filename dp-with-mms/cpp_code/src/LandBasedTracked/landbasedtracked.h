//! \file landbasedtracked.h

#pragma once
#include <iostream>
//!Includes basic Land Based Robot header file needed to create derived classes.
#include "../LandBasedRobot/landbasedrobot.h" 

/** @brief Defines common fp namespace */
namespace fp
{

/** @brief Creates LandBasedTracked class by deriving from basic LandBasedRobot class */
class LandBasedTracked : public LandBasedRobot
{
	public:
		/** @brief Constructor for LandBasedTracked robot using LandBasedRobot as derived object */
		LandBasedTracked(std::string, int, int, std::string track_type="");

		/** @brief Getter for track type pointer */
        /** @return track_type_: track type characteristic of robot. Refers to steer method of platform. */
		std::string get_track_type() const{
			return track_type_;
		}
		
		/** @brief Setter for track type pointer */
        /** @details Function set_track_type sets class attribute to functional track type parameter. */
		void set_track_type(std::string track_type){
			track_type_ = track_type;
		}
        
		/** @brief Function Prototyping */
        /** @details function prototypes for MoveForward, TurnLeft, TurnRight */
		virtual void MoveForward() override;       		//! Move the robot forward in the maze.
		virtual void TurnLeft() override;   			//! Turn Robot 90 deg counter-clockwise direction.
		virtual void TurnRight() override;  			//! Turn Robot 90 deg clockwise direction.
		
        /** @brief Destructor.for LandBasedTracked */
		virtual ~LandBasedTracked(){}
		
    /** @brief Land Based Tracked robot attributes included in protected class section */
    /** @param track_type_: Defines track type of robot under protected attributes */	
    protected:
		std::string track_type_;
        
};//End of the LandBasedTracked class.
}//End of namespace fp.