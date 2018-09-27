#include <collision/CollisionPair.h>

CollisionPair::CollisionPair(CollisionAlgorithm* _algorith, CollisionObject* _object_A, CollisionObject* _object_B){
	algorithm = _algorithm;
	object_A = _object_A;
	object_B = _object_B;
}

CollisionPair::~CollisionPair(){}

