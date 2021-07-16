/* morse extension for PHP */

#ifndef PHP_MORSE_H
# define PHP_MORSE_H

extern zend_module_entry morse_module_entry;
# define phpext_morse_ptr &morse_module_entry

# define PHP_MORSE_VERSION "0.1.0"

# if defined(ZTS) && defined(COMPILE_DL_MORSE)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

#endif	/* PHP_MORSE_H */
