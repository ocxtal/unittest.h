# unittest.h

Unittest.h is a simple, single-header unittesting framework for pure C99 codes on Unix-like environments. The simplest example looks like:

```example.c
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

```

It yields following results:


```
$ gcc -std=c99 example.c
$ ./a.out
Group (no name): 1 succeeded, 0 failed in total 1 tests.
Total: 1 succeeded, 0 failed in total 1 tests.
$ 
```

## Some other features

* Dependencies between tests
* Dependencies between files
* printf-style variable dump
* binary dump of the memory

```example2.c
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
```

The above example yields:

```
$ gcc -std=C99 example2.c
$ ./a.out
assertion failed: [foo] example2.c:31 ([second test] unittest_body_0_28) `i == 1', 0
assertion failed: [foo] example2.c:42 ([third test] unittest_body_0_40) `hello == NULL', hello world, 
`hello' len: 16
                    00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f
0x0000000101d89878: 68 65 6c 6c 6f 20 77 6f 72 6c 64 00 68 65 6c 6c  hello world hell

Group foo: 2 succeeded, 2 failed in total 4 tests.
Total: 2 succeeded, 2 failed in total 4 tests.
$
```

## Dependencies

The external command `nm` is required. (Used to dump the symbol in the executable.)

## License

MIT