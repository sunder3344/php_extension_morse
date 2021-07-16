/* morse extension for PHP */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_morse.h"
#include "morse_arginfo.h"
#include "morse.h"

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE() \
	ZEND_PARSE_PARAMETERS_START(0, 0) \
	ZEND_PARSE_PARAMETERS_END()
#endif

/* {{{ void test1() */
PHP_FUNCTION(test1)
{
	ZEND_PARSE_PARAMETERS_NONE();

	php_printf("The extension %s is loaded and working!\r\n", "morse");
}
/* }}} */

/* {{{ string test2( [ string $var ] ) */
PHP_FUNCTION(test2)
{
	char *var = "World";
	size_t var_len = sizeof("World") - 1;
	zend_string *retval;

	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_STRING(var, var_len)
	ZEND_PARSE_PARAMETERS_END();

	retval = strpprintf(0, "Hello %s", var);

	RETURN_STR(retval);
}
/* }}}*/

int strchar(char *str, char ch) {
    int i;
    int count = -1;
    int length = strlen(str);
    for (i = 0; i < length; i++) {
        if (str[i] == ch) {
            count = i;
            break;
        }
    }
    return count;
}

/**explode function**/
void explode(char str[], char seperator, char *data[]) {
    int len = strlen(str);
    int i;
    int pre_flag = 0;
    int count = 0;

    for(i = 0; i < len; i++) {
        if (str[i] == seperator) {
            str[i] = '\0';
            char * temp;
            temp = (char *)malloc(sizeof(char) * (i - pre_flag));
            strncpy(temp, str + pre_flag, i - pre_flag + 1);
            data[count] = temp;
            pre_flag = i + 1;
            count++;
        }
    }
    if (pre_flag < len) {
        data[count] = str + pre_flag;
    }
}

int getCharNum(char *str, char p) {
    int i = 0;
    unsigned int count = 0;
    while (*str) {
        if (*str == p)
            count++;
        str++;
    }
    return count;
}

PHP_FUNCTION(morseEncode) {
    char *str = NULL;
    size_t len = 0;
    ZEND_PARSE_PARAMETERS_START(1, 1);
        Z_PARAM_STRING(str, len)
    ZEND_PARSE_PARAMETERS_END();
    //php_printf("%s---%d\n", str, len);

    int i, count = 0;
    //php_printf("len = %d\n", sizeof(char) * len * 6);
    char *segment = (char *)malloc(sizeof(char) * len * 6);
    segment[0] = '\0';
    int charlen = 0;
    for (i = 0; i < strlen(str); i++) {
        int flag = strchar(chartStr, toupper(str[i]));
        char *tmp = dot[flag];
        charlen = strlen(tmp);
        count += (charlen + 1 + 1);
        segment = (char *)realloc(segment, sizeof(char) * count);
        strcat(segment, tmp);
        strcat(segment, "/");
    }
    //php_printf("count = %d\n", count);
    zend_string *s = zend_string_init(segment, strlen(segment), 0);
    free(segment);
    RETURN_STR(s);
}

PHP_FUNCTION(morseDecode) {
    char *str = NULL;
    size_t len = 0;
    ZEND_PARSE_PARAMETERS_START(1, 1);
        Z_PARAM_STRING(str, len)
    ZEND_PARSE_PARAMETERS_END();
    int count = getCharNum(str, op);
    char **data = (char **)malloc(sizeof(char *) * count);
    char *result = (char *)malloc(sizeof(char *) * count);
    *result = '\0';
    explode(str, '/', data);
    int i, j = 0;
    for (i = 0; i < count; i++) {
        for (j = 0; j < passNum; j++) {
            if (strcmp(*(data + i), *(dot + j)) == 0) {
                strncat(result, *(chartMap + j), 1);
            }
        }
    }
    free(data);
    zend_string *s = zend_string_init(result, strlen(result), 0);
    free(result);
    RETURN_STR(s);
}

/* {{{ PHP_RINIT_FUNCTION */
PHP_RINIT_FUNCTION(morse)
{
#if defined(ZTS) && defined(COMPILE_DL_MORSE)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION(morse)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "morse support", "enabled");
	php_info_print_table_end();
}
/* }}} */

/* {{{ morse_module_entry */
zend_module_entry morse_module_entry = {
	STANDARD_MODULE_HEADER,
	"morse",					/* Extension name */
	ext_functions,					/* zend_function_entry */
	NULL,							/* PHP_MINIT - Module initialization */
	NULL,							/* PHP_MSHUTDOWN - Module shutdown */
	PHP_RINIT(morse),			/* PHP_RINIT - Request initialization */
	NULL,							/* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(morse),			/* PHP_MINFO - Module info */
	PHP_MORSE_VERSION,		/* Version */
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_MORSE
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(morse)
#endif
