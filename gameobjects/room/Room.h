// Room
// A nice tiled box

using namespace std;

#include <global/Vector.h>
#include <global/RootObject.h>

class Room : public RootObject{
	private:
		Vector*		dimensions;

	public:
		Room(double, double, double);
		~Room();

		Vector*		getDimensions(){ return dimensions; }

		void		paint();
};
