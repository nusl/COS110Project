#ifndef MYRNG
#define MYRNG

#include <vector>

/** Random number generator.
 *	type() returns an unsigned int that is used to seed the RNG
 *	The type is established polymorphically by random() being called in the leaf classes of the hierarchy.
 *	This way, seeding behaviour and responsibility is self-encapsulated.
 *	If a class wants to make use of the random number generator, 
 *	the programmer needs to add that class to the list of types in the type() function.
 *	The type() function will throw a domain error if an unregistered class is attempting to use rand().
 */
class RNG
{
	public:
		RNG();
		virtual unsigned int type() const;
		int random();
	private:
		std::vector<int> numberList;
		bool seedSet;
};

#endif
