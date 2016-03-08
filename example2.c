
#include "unittest.h"

/*
 * global (per-file) configuration can be added with `unittest_config` macro.
 */
unittest_config(
	.name = "foo",					/* groupname */
	.depends_on = {"bar"}			/* depends on the other groups */
);

/*
 * per-test configurations can be added passing arguments to the `unittest` macro.
 */
unittest(
	.name = "first test",			/* name of the test */
	.depends_on = {}				/* depends on nothing */
) {
	assert(0 == 0);
}

/*
 * variables can be dumped in the `printf` style.
 */
unittest(
	.name = "second test",
	.depends_on = {"first test"}	/* depends on the first test */
) {
	int i = 0;
	assert(i == 0);
	assert(i == 1, "%d", i);		/* prints the content of `i` */
}

/*
 * binary dump is also available
 */
unittest(
	.name = "third test",
	.depends_on = {"second test"}
) {
	char const *hello = "hello world";
	assert(hello == NULL, "%s, %s", hello, dump(hello, 16));
}

/*
 * main
 */
int main(int argc, char *argv[])
{
	return(unittest_main(argc, argv));
}
