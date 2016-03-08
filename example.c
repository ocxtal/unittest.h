
#include "unittest.h"

unittest()
{
	assert(0 == 0);
}

int main(int argc, char *argv[])
{
	/* argv[0] must be a valid name of the executable */
	return(unittest_main(argc, argv));
}
