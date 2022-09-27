#ifndef _DEBUG_UDP_H_
#define _DEBUG_UDP_H_
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>

class DEBUG_UDP {
  public:
	char UDPInput[255];
	char replyPacket[255];
	DEBUG_UDP(uint16_t port = 4210);
	void init();
	void run();
	void write(String contents);

  private:
	WiFiUDP   Udp;
	bool      En_Debug = false;
	bool      Login    = false;
	uint16_t  localUdpPort;
	uint16_t  PortRemote;
	IPAddress IPRemote;
	String    User   = "Admin";
	String    Passwd = "Admin";
	String    Data_Slist[5];
	void      slist(String contents);
};

#endif
