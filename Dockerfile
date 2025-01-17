# syntax=docker/dockerfile:1
# SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only  */
# Copyright (c) 2021 - 2022 Gavin Henry <ghenry@sentrypeer.org> */
#
#   _____            _              _____
#  / ____|          | |            |  __ \
# | (___   ___ _ __ | |_ _ __ _   _| |__) |__  ___ _ __
#  \___ \ / _ \ '_ \| __| '__| | | |  ___/ _ \/ _ \ '__|
#  ____) |  __/ | | | |_| |  | |_| | |  |  __/  __/ |
# |_____/ \___|_| |_|\__|_|   \__, |_|   \___|\___|_|
#                              __/ |
#                             |___/
#
FROM alpine:3.15 AS build

LABEL maintainer="Gavin Henry, ghenry@sentrypeer.org"

RUN apk add --no-cache autoconf automake autoconf-archive \
	git sqlite-dev cmocka-dev util-linux-dev curl-dev \
	pcre2-dev jansson-dev libmicrohttpd-dev build-base

RUN apk add --no-cache -X http://dl-cdn.alpinelinux.org/alpine/edge/testing \
    libosip2-dev

RUN git clone https://github.com/SentryPeer/SentryPeer.git

WORKDIR /SentryPeer

RUN ./bootstrap.sh
RUN ./configure
RUN make
RUN make check
RUN make install


# SIP Port 5060 and RESTful API
EXPOSE 5060 8082

# ENV SENTRYPEER_DB_FILE=/my/location/sentrypeer.db
# ENV SENTRYPEER_SYSLOG=1
# ENV SENTRYPEER_VERBOSE=1
# ENV SENTRYPEER_DEBUG=1

CMD ["./sentrypeer", "-d", "-s"]
