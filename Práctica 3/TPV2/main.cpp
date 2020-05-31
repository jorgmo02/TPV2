#include <iostream>

#include "StarWars.h"

using namespace std;

void server(int port) {
	Networking net;
	net.server(port);
}

void client(char* host, int port, char* name) {
	try {
		StarWars g(host, port, name);
		g.start();
	}
	catch (std::string& e) { // catch errors thrown as strings
		cerr << e << endl;
	}
	catch (const std::exception& e) { // catch other exceptions
		cerr << e.what();
	}
	catch (...) {
		cerr << "Caught and exception of unknown type ..";
	}
}

int main(int argc, char** argv) {

	char anon[] = "Anonymous";
	int port = 2000;
	char ip[] = "localhost";

	if (argc == 3 && strcmp(argv[1], "server") == 0) {
		server(atoi(argv[2])); // start in server mode
	}
	else if (argc == 4 && strcmp(argv[1], "client") == 0) {
		client(argv[2], atoi(argv[3]), anon); // start in client mode
	}
	else if (argc == 5 && strcmp(argv[1], "client") == 0 && std::strlen(argv[4]) < 11) {
		client(argv[2], atoi(argv[3]), argv[4]); // start in client mode
	}
	else if (true) {
		client(ip, port, anon);
	}
	else {
		cout << "Usage: " << endl;
		cout << "  " << argv[0] << " client host port " << endl;
		cout << "  " << argv[0] << " server port " << endl;
		cout << "  " << argv[0] << " server port name (max 10 chars) " << endl;
		cout << endl;
		cout << "Example:" << endl;
		cout << "  " << argv[0] << " server 2000" << endl;
		cout << "  " << argv[0] << " client localhost 2000" << endl;
		cout << "  " << argv[0] << " client localhost 2000 Pepito" << endl;
	}

	return 0;
}