FROM alpine:3.3

RUN apk add --update \
    build-base \
    libevent-dev \
    libxml2-dev \
    openssl-dev \
    pcre-dev \
    zlib-dev \
  && rm -rf /var/cache/apk/*

WORKDIR /tmp
RUN wget http://nginx.org/download/nginx-1.8.1.tar.gz \
  && tar xzf nginx-1.8.1.tar.gz \
  && wget -O php-5.6.18.tar.gz http://jp2.php.net/get/php-5.6.18.tar.gz/from/this/mirror \
  && tar xzf php-5.6.18.tar.gz

WORKDIR /tmp/nginx-1.8.1
RUN ./configure \
    --conf-path=/etc/nginx/nginx.conf \
    --with-http_gzip_static_module \
    --with-http_realip_module \
    --with-http_ssl_module \
  && make \
  && make install

WORKDIR /tmp/php-5.6.18
RUN ./configure \
    --enable-fpm \
  && make \
  && make install \
  && cp /usr/local/etc/php-fpm.conf.default /usr/local/etc/php-fpm.conf

COPY nginx.conf /etc/nginx/nginx.conf
COPY nginx /etc/init.d/

RUN mkdir /var/www \
  && echo "<?php phpinfo();" > /var/www/index.php

EXPOSE 80
