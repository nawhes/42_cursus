FROM	debian:buster

MAINTAINER	nawhes@naver.com

RUN		apt-get update && apt-get install -y nginx mariadb-server php7.3-fpm php7.3-xml php7.3-mbstring php7.3-mysql vim

COPY	./srcs/ /tmp/

EXPOSE	80 443
CMD		["bash", "/tmp/init.sh"]
