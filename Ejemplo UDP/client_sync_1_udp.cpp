#include <iostream>
#include <SDL_net.h>
#include <signal.h>

using namespace std;

inline bool sameAddress(const IPaddress &ip1, const IPaddress &ip2) {
	return (ip1.host == ip2.host && ip1.port == ip2.port);
}

/*
 *
 * Kinds of messages:
 *
 * M0: C->S : 0          // I want to connect
 * M1: C->S : 1          // I want to disconnect
 * M2: C->S : 2 int int  // I want to broadcast my state - <id,state>
 * M3: S->C : 3 int      // You're connected - <id>
 * M4: S->C : 4          // Not possible to connect
 * M5: S->C : 5          // Please broadcast your state
 * M6: S->C : 6 int      // Client disconnected
 *
 */

static const int MAX_CLIENTS = 10;
static const int MAX_PACKET_SIZE = 512;

void error() {
	cout << "Error: " << SDLNet_GetError() << endl;
	exit(1);
}

void server(int port) {

	cout << "Starting server at port " << port << endl;

	UDPsocket serverUDPSock;
	UDPpacket *p;
	char *buffer;
	SDLNet_SocketSet socketSet = nullptr;

	// open a UDP socket to listen at 'port' -- unlike TCP, this socket is used to
	// receive information from all clients
	serverUDPSock = SDLNet_UDP_Open(port);

	// We use socketSet for non-blocking communication
	socketSet = SDLNet_AllocSocketSet(1000);
	SDLNet_UDP_AddSocket(socketSet, serverUDPSock);

	// An array to store addresses of clients, unlike TCP were
	// we store the IP address and not the socket (there is not socket per client)
	struct ClientInfo {
		bool used;
		IPaddress address;
	};
	ClientInfo clients[MAX_CLIENTS];
	for (int i = 0; i < MAX_CLIENTS; i++) {
		clients[i].used = false;
	}

	// We allocate the data structure to be used for sending packets
	p = SDLNet_AllocPacket(MAX_PACKET_SIZE);

	// this is the data sent by the client, buffer and p->data now
	// point to the same address, so we will use buffer
	buffer = (char*) p->data;

	// now we process requests in an infinite loop
	while (true) {

		// check if there is activity
		if (SDLNet_CheckSockets(socketSet, SDL_MAX_UINT32) > 0) {

			// check if there is activity in the server socket
			if (SDLNet_SocketReady(serverUDPSock)) {

				// get the packet - return -1,0 or 1
				if (SDLNet_UDP_Recv(serverUDPSock, p) > 0) { // a packet received

					// this is the address of the sender (we don't have a dedicated socket like TCP)
					IPaddress senderAddress = p->address;

					// check the kind of message
					switch (buffer[0]) {

					// M0: client wants to connect
					case 0: {
						// look for a free slot
						int j = 0;
						while (j < MAX_CLIENTS && clients[j].used)
							j++;

						if (j < MAX_CLIENTS) {
							cout << "Client connected, assigned id " << j
									<< endl;

							// store the client address and mark the slot as used
							//
							clients[j].used = true;
							clients[j].address = senderAddress;

							// tells the client its id (M3)
							//
							buffer[0] = 3; // buffer points to p->data
							*((int*) (buffer + 1)) = j; // the id assigned to the client
							p->len = 1 + sizeof(int); // the size of data we send goes into the packet
							// p->address is already filled with the address of the sender, no need for p->address = senderAddress
							SDLNet_UDP_Send(serverUDPSock, -1, p);

							// tell all clients to broadcast their state (message type M5)
							//
							buffer[0] = 5;
							p->len = 1;
							for (int i = 0; i < MAX_CLIENTS; i++) {
								if (clients[i].used) {
									// we have to add the client's address to the packet because
									// unlike TCP there is no socket for every client
									p->address = clients[i].address;
									SDLNet_UDP_Send(serverUDPSock, -1, p);
								}
							}
						} else {
							// tell the client that it is not possible to connect (M4)
							//
							buffer[0] = 4;
							p->len = 1;
							// p->address is already filled with the address of the sender, no need for p->address = senderAddress
							SDLNet_UDP_Send(serverUDPSock, -1, p);
						}

					}
						break;

						// client wants to disconnect (M1)
					case 1: {
						// first we look for the client id
						int j = 0;
						while (j < MAX_CLIENTS
								&& !(clients[j].used
										&& sameAddress(senderAddress,
												clients[j].address))) //
							j++;

						// if we found the client, we delete it and tell other clients that it disconnected (M6)
						if (j < MAX_CLIENTS) {
							cout << "Client " << j << "disconnected"<< endl;
							clients[j].used = false;
							buffer[0] = 6;
							*((int*) (buffer + 1)) = j;
							p->len = 1 + sizeof(int);
							for (int i = 0; i < MAX_CLIENTS; i++) {
								if (clients[i].used) {
									p->address = clients[i].address;
									SDLNet_UDP_Send(serverUDPSock, -1, p);
								}
							}
						}
					}
						break;

						// a client is broadcasting a state so we forward it it to _other_ clients (M2)
					case 2:
						for (int i = 0; i < MAX_CLIENTS; i++) {
							if (clients[i].used
									&& !sameAddress(senderAddress,
											clients[i].address)) {
								p->address = clients[i].address;
								SDLNet_UDP_Send(serverUDPSock, -1, p);
							}
						}
						break;
					}
				}
			}
		}
	}
}

bool done = false;

void client(char *host, int port) {

	srand(time(NULL));

	UDPsocket sd;
	IPaddress srvadd;
	UDPpacket *p;

	int id = -1;
	int states[MAX_CLIENTS];
	for (int i = 0; i < MAX_CLIENTS; i++)
		states[i] = -1;

	// pick a socket at random port (locally)
	sd = SDLNet_UDP_Open(0);

	// resolve the sever name
	SDLNet_ResolveHost(&srvadd, host, port);

	// We allocate the data structure to be used for sending packets
	p = SDLNet_AllocPacket(MAX_PACKET_SIZE);

	// this is the data sent by the client, buffer and p->data now
	// point to the same address, so we will use buffer
	char *buffer = (char*) p->data;

	// tell the server you want to connect
	buffer[0] = 0;
	p->len = 1;
	p->address = srvadd;
	SDLNet_UDP_Send(sd, -1, p);

	// socket set for non-blocking communication
	SDLNet_SocketSet socketSet = SDLNet_AllocSocketSet(1);
	SDLNet_UDP_AddSocket(socketSet, sd);

	bool stateChanegd = false;
	while (!done) {
		if (SDLNet_CheckSockets(socketSet, 0) > 0) {
			if (SDLNet_SocketReady(sd)) {

				// get the packet - return -1,0 or 1
				if (SDLNet_UDP_Recv(sd, p) > 0) { // a packet received

					// check the kind of message
					switch (buffer[0]) {
					case 2: // M2 - a client has sent a new state
						states[*((int*) (buffer + 1))] = *((int*) (buffer + 1
								+ sizeof(int)));
						stateChanegd = true;
						break;
					case 3: // M3 - your are connected
						id = *((int*) (buffer + 1)); // copy the identifier to id
						states[id] = 1 + rand() % 1000; // choose and initial state
						stateChanegd = true;
						break;
					case 4: // M4 - not possible to connect
						cout << "Connection refused!" << endl;
						done = true;
						break;
					case 5: // M5 - broadcast your state, so we reply with M2
						buffer[0] = 2;
						*((int*) (buffer + 1)) = id;
						*((int*) (buffer + 1 + sizeof(int))) = states[id];
						p->len = 1 + 2 * sizeof(int);
						p->address = srvadd; // I think it is not needed since we received o from the server, so p->address has the address of the server
						SDLNet_UDP_Send(sd, -1, p);
						break;
					case 6:	// M6 - a client has disconnected
						states[*((int*) (buffer + 1))] = -1; // delete the client from the state array
						stateChanegd = true;
						break;
					}

				}
			}
		}

		// change state every now and then
		if (id != -1 && rand() % 1000000 < 10) {

			// change state
			states[id] = 1 + rand() % 1000;
			stateChanegd = true;

			// broadcast state
			buffer[0] = 2;
			*((int*) (buffer + 1)) = id;
			*((int*) (buffer + 1 + sizeof(int))) = states[id];
			p->len = 1 + 2 * sizeof(int);
			p->address = srvadd; // I think it is not needed since we received o from the server, so p->address has the address of the server
			SDLNet_UDP_Send(sd, -1, p);
		}

		if (stateChanegd) {
			system("clear"); // system("CLS");
			cout << "id=" << id << endl;
			for (int i = 0; i < MAX_CLIENTS; i++) {
				if (states[i] != -1) {
					cout << i << ":" << states[i] << " ";
				}
			}
			cout << endl;
			stateChanegd = false;
		}
	}

	if (id != -1) {
		// tell the server you are disconnecting
		buffer[0] = 1;
		p->len = 1;
		p->address = srvadd;
		SDLNet_UDP_Send(sd, -1, p);
	}
}

/* Signal Handler for SIGINT */
void sigintHandler(int sig_num) {
	cout << "Ctrl-C" << endl;
	done = true;
	signal(SIGINT, sigintHandler);
}

int main(int argc, char **argv) {

	// for capturing CTRL-C
	signal(SIGINT, sigintHandler);

	// initialize SDLNet
	if (SDLNet_Init() < 0) {
		error();
	}

	if (argc == 3 && strcmp(argv[1], "server") == 0) {
		server(atoi(argv[2])); // start in server mode
	} else if (argc == 4 && strcmp(argv[1], "client") == 0) {
		client(argv[2], atoi(argv[3])); // start in client mode
	} else {
		cout << "Usage: " << endl;
		cout << "  " << argv[0] << " client host port " << endl;
		cout << "  " << argv[0] << " server port " << endl;
		cout << endl;
		cout << "Example:" << endl;
		cout << "  " << argv[0] << " server 2000" << endl;
		cout << "  " << argv[0] << " client localhost 2000" << endl;
	}

	// finalize SDLNet
	SDLNet_Quit();

	return 0;
}
