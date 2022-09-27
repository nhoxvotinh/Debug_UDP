#ifndef _DEBUG_UDP_CPP_
#define _DEBUG_UDP_CPP_
#include "Debug_UDP.h"

DEBUG_UDP::DEBUG_UDP(uint16_t port) { localUdpPort = port; }

void DEBUG_UDP::init() { Udp.begin(localUdpPort); }

void DEBUG_UDP::run() {
	int packetSize = Udp.parsePacket();
	if (packetSize) {
		int len = Udp.read(UDPInput, 255);
		if (len > 0) { UDPInput[len] = 0; }

		if (IPRemote != Udp.remoteIP()) {
			IPRemote   = Udp.remoteIP();
			PortRemote = Udp.remotePort();
			Login      = false;
			En_Debug   = false;
		}

		if (!Login) {
			slist(String(UDPInput));
			if (Data_Slist[0].equals("login")) {
				if (Data_Slist[1].equals(User) && Data_Slist[2].equals(Passwd)) {
					Login    = true;
					En_Debug = true;
					write("Login successful\r\n");
					write("Welcome to Smart Debug\r\n");
				}
				else {
					//
					write("Login failed\r\n");
				}
			}
			else {
				En_Debug = true;
				write("Please login to Use Debug. \"login Username Password\"\r\n");
				En_Debug = false;
			}
		}
	}
}

void DEBUG_UDP::write(String contents) {
	if (!En_Debug) return;
	Udp.beginPacket(IPRemote, PortRemote);
	Udp.write(contents.c_str());
	Udp.endPacket();
}

void DEBUG_UDP::slist(String contents) {
	uint8_t a = 0;
	int8_t  b = contents.indexOf(' ');
	if (b == -1) {
		Data_Slist[0] = contents;
		Data_Slist[1] = "\0";
		Data_Slist[2] = "\0";
		Data_Slist[3] = "\0";
		Data_Slist[4] = "\0";
		return;
	}
	for (uint8_t i = 0; i < 5; i++) {
		Data_Slist[i] = contents.substring(a, b);
		a             = b + 1;
		b             = contents.indexOf(' ', a);
		if (b == -1) {
			Data_Slist[i + 1] = contents.substring(a, contents.length());
			break;
		}
	}
}
#endif
