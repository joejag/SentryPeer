/* SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only */
/* Copyright (c) 2021 Gavin Henry <ghenry@sentrypeer.org> */

// Bring in getaddrinfo and others as -std=c18 bins them off
#define _GNU_SOURCE

#include "sip_daemon.h"
#include "sentrypeer.h"

/*
 * Hands-On Network Programming with C, page 117
 * UDP Server (move to libevent and/or 0MQ Routers/zproto/zproject/Zyre:
 *
 * getaddrinfo();
 * socket();
 * bind();
 * select();
 *
 * Has socket() input? Yes, move on. No, go back to select().
 *
 * recvfrom();
 * sip_parse_request(); etc
 * send();
 *
 */

/*
 * sip_daemon_init
 *
 * TODO: Implement proper logging
 */

int sip_daemon_init(struct sentrypeer_config *config)
{
	// TODO: Do a macro for these later
	if (config->debug_mode || config->verbose_mode) {
		fprintf(stderr, "Configuring local address...\n");
	}
	struct addrinfo gai_hints;
	memset(&gai_hints, 0, sizeof(gai_hints));
	gai_hints.ai_family = AF_INET;
	gai_hints.ai_socktype = SOCK_DGRAM; // UDP
	gai_hints.ai_flags = AI_PASSIVE;

	struct addrinfo *bind_address;
	int gai = getaddrinfo(0, "5060", &gai_hints, &bind_address);
	if (gai != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(gai));
		// TODO: wrap these
		freeaddrinfo(bind_address);
		return (EXIT_FAILURE);
	}

	if (config->debug_mode || config->verbose_mode) {
		fprintf(stderr, "Creating socket...\n");
	}
	SOCKET socket_listen;
	socket_listen =
		socket(bind_address->ai_family, bind_address->ai_socktype,
		       bind_address->ai_protocol);
	if (!ISVALIDSOCKET(socket_listen)) {
		perror("socket() failed.");
		freeaddrinfo(bind_address);
		return (EXIT_FAILURE);
	}

	/* The failure of the bind() call can be prevented by setting
	 * the SO_REUSEADDR flag on the server socket before calling bind().
	 *
	 * Eliminates "ERROR on binding: Address already in use" error.
	 * See Hands-On Network Programming with C, page 374 of PDF.
	 */
	int yes = 1;
	if (setsockopt(socket_listen, SOL_SOCKET, SO_REUSEADDR, (void *)&yes,
		       sizeof(yes)) < 0) {
		fprintf(stderr, "setsockopt() failed. (%d)\n",
			GETSOCKETERRNO());
		perror("setsockopt() failed.");
	}

	if (config->debug_mode || config->verbose_mode) {
		fprintf(stderr, "Binding socket to local address...\n");
	}
	if (bind(socket_listen, bind_address->ai_addr,
		 bind_address->ai_addrlen)) {
		fprintf(stderr, "bind() failed. (%d)\n", GETSOCKETERRNO());
		perror("bind() failed.");
		freeaddrinfo(bind_address);
		return (EXIT_FAILURE);
	}
	freeaddrinfo(bind_address); // Not needed anymore

	fd_set master;
	FD_ZERO(&master);
	FD_SET(socket_listen, &master);
	SOCKET max_socket = socket_listen;

	if (config->debug_mode || config->verbose_mode) {
		fprintf(stderr, "Listening for incoming connections...\n");
	}

	// TODO: Switch to libevent/0MQ/epoll etc. later
	while (1) {
		fd_set reads;
		reads = master;
		if (select(max_socket + 1, &reads, 0, 0, 0) < 0) {
			fprintf(stderr, "select() failed. (%d)\n",
				GETSOCKETERRNO());
			perror("select() failed.");
			return EXIT_FAILURE;
		}

		if (FD_ISSET(socket_listen, &reads)) {
			struct sockaddr_storage client_address;
			socklen_t client_len = sizeof(client_address);

			char read[1024];
			int bytes_received =
				recvfrom(socket_listen, read, 1024, 0,
					 (struct sockaddr *)&client_address,
					 &client_len);
			if (bytes_received < 1) {
				if (config->debug_mode ||
				    config->verbose_mode) {
					fprintf(stderr,
						"connection closed. (%d)\n",
						GETSOCKETERRNO());
					perror("recvfrom() failed.");
				}
				return (EXIT_FAILURE);
			}

			if (config->debug_mode || config->verbose_mode) {
				fprintf(stderr, "Received (%d bytes): %.*s\n",
					bytes_received, bytes_received, read);
			}

			char client_ip_address_buffer[100];
			char client_send_port_buffer[100];
			if (getnameinfo(((struct sockaddr *)&client_address),
					client_len, client_ip_address_buffer,
					sizeof(client_ip_address_buffer),
					client_send_port_buffer,
					sizeof(client_send_port_buffer),
					NI_NUMERICHOST | NI_NUMERICSERV) != 0) {
				perror("getnameinfo() failed.");
				return (EXIT_FAILURE);
			}

			if (config->debug_mode || config->verbose_mode) {
				fprintf(stderr,
					"Client IP address: %s, Client send port: %s\n",
					client_ip_address_buffer,
					client_send_port_buffer);
			}
		}
	}
	// TODO: Implement proper cleanup
	CLOSESOCKET(socket_listen);
	//
	//	if (config->debug_mode || config->verbose_mode) {
	//		fprintf(stderr, "Finished.\n");
	//	}
	//	return (EXIT_SUCCESS);
}
