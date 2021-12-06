/* SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only  */
/* Copyright (c) 2021 Gavin Henry <ghenry@sentrypeer.org> */
/*
   _____            _              _____
  / ____|          | |            |  __ \
 | (___   ___ _ __ | |_ _ __ _   _| |__) |__  ___ _ __
  \___ \ / _ \ '_ \| __| '__| | | |  ___/ _ \/ _ \ '__|
  ____) |  __/ | | | |_| |  | |_| | |  |  __/  __/ |
 |_____/ \___|_| |_|\__|_|   \__, |_|   \___|\___|_|
                              __/ |
                             |___/
*/

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>

#include "test_utils.h"
#include "../../src/utils.h"
#include <stdlib.h>
#include <stdio.h>

void test_utils(void **state)
{
	(void)state; /* unused */

	// String utils
	char string_to_copy[] = "I'm a string that will be copied!";
	assert_non_null(string_to_copy);

	char *string_copied = util_duplicate_string(string_to_copy);
	assert_non_null(string_copied);
	assert_string_equal(string_to_copy, string_copied);
	free(string_copied);
	fprintf(stderr,
		"Freed string_copied successfully at line number %d in file %s\n",
		__LINE__ - 1, __FILE__);

	// Modern C by Manning, Takeaway 6.19
	// "6.19 Initialization or assignment with 0 makes a pointer null."
	string_copied = 0;
	assert_null(string_copied);

	// uuid utils
	char uuid_string[UTILS_UUID_STRING_LEN];
	util_uuid_generate_string(uuid_string);
	assert_non_null(uuid_string);
	assert_string_not_equal(uuid_string, "");
	assert_string_not_equal(uuid_string,
				"00000000-0000-0000-0000-000000000000");
}