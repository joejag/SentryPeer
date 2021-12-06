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

#include "test_http_api.h"
#include "../../src/http_daemon.h"
#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <string.h>
#include <jansson.h>
#include <config.h>

size_t curl_to_jansson_to_version(void *buffer, size_t size, size_t nmemb,
				  void *userp)
{
	json_t *json = json_loadb(buffer, size * nmemb, 0, NULL);
	assert_non_null(json);

	json_t *sentrypeer_version_json = json_object_get(json, "version");
	assert_non_null(sentrypeer_version_json);
	fprintf(stderr, "SentryPeer version from RESTful API: %s\n",
		json_string_value(sentrypeer_version_json));
	assert_string_equal(json_string_value(sentrypeer_version_json),
			    PACKAGE_VERSION);

	*((json_t **)userp) = json;
	return size * nmemb;
}

void test_http_api_get(void **state)
{
	(void)state; /* unused */

	struct sentrypeer_config config;
	config.debug_mode = true;
	fprintf(stderr, "Debug mode set to true at line number %d in file %s\n",
		__LINE__ - 1, __FILE__);

	assert_int_equal(http_daemon_init(&config), EXIT_SUCCESS);
	fprintf(stderr, "http_daemon started at line number %d in file %s\n",
		__LINE__ - 1, __FILE__);

	curl_global_init(CURL_GLOBAL_ALL);
	CURL *easyhandle = curl_easy_init();
	assert_non_null(easyhandle);
	if (easyhandle) {
		curl_easy_setopt(easyhandle, CURLOPT_URL,
				 "http://127.0.0.1:8082");
		struct curl_slist *headers = NULL;
		headers = curl_slist_append(headers,
					    "Content-Type: application/json");
		curl_easy_setopt(easyhandle, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(easyhandle, CURLOPT_WRITEFUNCTION,
				 curl_to_jansson_to_version);
		assert_int_equal(curl_easy_perform(easyhandle), CURLE_OK);

		curl_slist_free_all(headers);
		curl_easy_cleanup(easyhandle);
		curl_global_cleanup();
	}
}