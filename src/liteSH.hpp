#pragma once

#include <iostream>
#include <cstring>
#include <fstream>
#include <arpa/inet.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <dlfcn.h>
#include <unistd.h>

using namespace std;

int createProcess(char *procName);
int createDaemon(char *procName);

void signalHandler();
int sendSignal(pid_t pid, int signum);
int recvSignal(int signum);

int netWork_client(char * command);
void netWork_server();
void closeServer();