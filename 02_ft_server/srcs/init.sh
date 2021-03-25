#!bin/bash

mv /tmp/default /etc/nginx/sites-available/default
mv /tmp/wordpress /var/www/html/wordpress
mv /tmp/phpmyadmin /var/www/html/phpmyadmin
chown www-data.www-data /var/www/html/phpmyadmin/* -R

service mysql start
mysql < /tmp/init_wordpress_mysql.sql
service php7.3-fpm start

mkdir /etc/nginx/ssl
chmod 700 /etc/nginx/ssl
mv /tmp/example.key /etc/nginx/ssl/example.key
mv /tmp/example.crt /etc/nginx/ssl/example.crt

nginx -g 'daemon off;'
