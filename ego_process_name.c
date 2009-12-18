//
//  ego_process_name.c
//  enormego
//
//  Created by Shaun Harrison on 12/17/09.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>
#include <string.h>
#include <sys/prctl.h>

#include "php_ego_process_name.h"

static void ego_set_process_name(char* name, int name_length) {
	// Need to use name_length here to make sure it's not too long
	// But I don't know how to get a substring right now.
	prctl(PR_SET_NAME, name, 0, 0, 0);
}

PHP_FUNCTION(set_process_name) {
	char    *new_name;
	long    name_length;

	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &new_name, &name_length) == FAILURE) {
		RETURN_NULL();
	}

	ego_set_process_name(new_name, name_length);
}

static function_entry egoprocessname_functions[] = {
	PHP_FE(set_process_name, NULL) {NULL, NULL, NULL}
};

PHP_MINFO_FUNCTION(egoprocessname) {
	php_info_print_table_start();
	php_info_print_table_header(2, "set_process_name", "enabled");
	php_info_print_table_row(2, "Build Date", __DATE__);
	php_info_print_table_row(2, "Build Time", __TIME__);
	php_info_print_table_row(2, "Version", EGO_PROCESS_NAME_V);
	php_info_print_table_end();
}

zend_module_entry egoprocessname_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"EGOProcessName",
	egoprocessname_functions,
	NULL,
	NULL,
	NULL,
	NULL,
	PHP_MINFO(egoprocessname),
#if ZEND_MODULE_API_NO >= 20010901
	"0.1",
#endif
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_EGOPROCESSNAME
ZEND_GET_MODULE(egoprocessname)
#endif

