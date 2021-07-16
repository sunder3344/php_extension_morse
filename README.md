# php_extension_morse
extension morse based on PHP8. With this extension, you can encode string into morse code and vice versa.

# compile
1. go into the PHP source file and run "./configure --with-php-config=/your_php_installed_folder/bin/php-config"
2. make
3. make install
4. add the new extension "morse.so" into your php.ini file and reload your php-fpm
5. open the demo.php in your favorite tool and use "morseEncode" and "morseDecode" to do it.