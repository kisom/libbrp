/*
 * Copyright (c) 2013 Kyle Isom <kyle@tyrfingr.is>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "brp.h"

/*
 * a test_case consists of three things: the value to be tested, the bit
 * length the number should have, and the expected output of tau.
 */
struct test_case {
	unsigned int	value;
	unsigned int	bitlen;
	int		expected;
};

static struct test_case	test_cases[4];

/*
 * setup_tests populates the test case array with a series of tests.
 */
static void
setup_tests(void)
{
	struct test_case	tc;

	tc.value = 0x1;
	tc.bitlen = 0;
	tc.expected = 0x1;
	test_cases[0] = tc;

	tc.value = 0x10;
	tc.bitlen = 4;
	tc.expected = 0x1;
	test_cases[1] = tc;

	tc.value = 0x100;
	tc.bitlen = 8;
	tc.expected = 0x1;
	test_cases[2] = tc;

	tc.value = 0xab;
	tc.bitlen = 7;
	tc.expected = 0xd5;
	test_cases[3] = tc;
}


/*
 * brp_test is a small test program to validate the brp library.
 * It iterates over an array of test cases, checking the output of
 * both * the bit length and tau functions to ensure they match our
 * expectations.
 */
int
main(int argc, char *argv[])
{
	unsigned int	i, bitlen;
	int		x;
	int		ch;
	int		runs = 1;

	setup_tests();

	while ((ch = getopt(argc, argv, "n:")) != -1) {
		switch (ch) {
		case 'n':
			runs = atoi(optarg);
			break;
		default: /* NOT REACHED */
			abort();
		}
	}

	while (runs-- >= 0) {
		for (i = 0; i < 4; i++) {
			bitlen = brp_bit_length(test_cases[i].value);
			if (bitlen != test_cases[i].bitlen) {
				fprintf(stderr, "expected bit length %u, saw %u\n",
				    test_cases[i].bitlen, bitlen);
				return EXIT_FAILURE;
			}
			x = brp_tau(test_cases[i].value);
			if (x != test_cases[i].expected) {
				fprintf(stderr, "expected tau(%x) -> %x, saw %x\n",
				    test_cases[i].value, test_cases[i].expected, x);
				return EXIT_FAILURE;
			}
		}
	}

	printf("ok\n");
	return EXIT_SUCCESS;
}
