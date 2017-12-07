/*
 * NetworkClient.h
 *
 *  Created on: Dec 07, 2017
 *      Author: avi simson & yakir pinchas
 *      Avi id: 205789100
 *      Yakir: 203200530
*/
#include "NetworkClient.h"
//constructor initialize clientSocket to 0,
// and read ip and port of server from file.
NetworkClient ::NetworkClient(char *filename) {
    clientSocket = 0;
    string portLine, ipLine;
    ifstream infoAddress;
    infoAddress.open(fileName, std :: fstream :: in); //open file.
    getline(infoAddress, ipLine); //read first line of file-the ip
    getline(infoAddress, portLine); //read second line of file-the port.
    portLine.erase(portLine.begin(), portLine.begin() + strlen("Port = "));
    ipLine.erase(ipLine.begin(), ipLine.begin() + strlen("IP = "));
    //enter to port the currect value from the file
    port = atoi(portLine.c_str());
    ip = new char[ipLine.size() + 1]; //allocate enough memory in heap to ip.
    ip = ipLine.c_str();
    infoAddress.close(); //close the file.
}
