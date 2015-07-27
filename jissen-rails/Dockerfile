FROM ubuntu:latest

RUN apt-get -y update && apt-get -y install \
            build-essential \
            postgresql-9.3 \
            postgresql-server-dev-9.3 \
            software-properties-common
RUN add-apt-repository -y ppa:brightbox/ruby-ng && apt-get -y update \
    && apt-get -y install ruby2.1 ruby2.1-dev
RUN gem install rails --version=4.1.0 --no-document

RUN locale-gen ja_JP.UTF-8

COPY encoding-utf8.sql baukis/Gemfile* /tmp/
WORKDIR /tmp
RUN bundle install
RUN service postgresql restart \
    && su - postgres -c ' \
          psql -f /tmp/encoding-utf8.sql; \
          createuser -d -S -r root; \
'
