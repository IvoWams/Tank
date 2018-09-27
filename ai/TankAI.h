// Class Tank AI
// Just a AI for kinds of tanks
// Controls tank named control:
//  -- Aims for tank "target"
//	-- Tries to stay in the donut shaped area with boundaries distance_inner and _outer
//  -- When in the boundaries, the tank mixes movement from going clockwise to counterclockwise arount the "target" tank

using namespace std;

#ifndef TANKAI_H
#define TANKAI_H

#include <game/GameHandler.h>
#include <gameobjects/tanks/Tank.h>
#include <global/Tools.h>

class GameHandler;

class TankAI {
	private:
		Tank* 			control;
		Tank* 			target;
		GameHandler*	handler;

		int		change_lane;
		double	distance_inner;
		double	distance_outer;
		double	distance;

	public:
		TankAI(GameHandler*, Tank*, Tank*, int, int);
		~TankAI();

		void	changeTarget(Tank*);
		void	setInnerDistance(float);
		void	setOuterDistance(float);

		void	think();
		void	paint();		// Debug paint
};

#endif
