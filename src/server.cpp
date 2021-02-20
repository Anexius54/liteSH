#include "liteSH.hpp"


void netWork_server()
{
    struct sockaddr_in server, client;
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    
    server.sin_family = AF_INET;  // ipv4
    server.sin_addr.s_addr = INADDR_ANY; // 0.0.0.0
    server.sin_port = htons(2020); // port

    bind(sock, (struct sockaddr*)&server, sizeof(server));  
    listen(sock, 5);  // queue 5

    while (1) {
        char buf[100] = "";
        int newsock, size;
        socklen_t clnlen;

        newsock = accept(sock, (struct sockaddr*)&client, &clnlen);
        cout << "new client: " << inet_ntoa(client.sin_addr) << endl;

        while ((size = recv(newsock, buf, sizeof(buf), 0)) != 0) {
            if (strcmp(buf, "createProcess") == 0) {
                strcpy(buf, "1");
                send(newsock, buf, sizeof(buf), 0);
            } else if (strcmp(buf, "createDaemon") == 0) {
                strcpy(buf, "2");
                send(newsock, buf, sizeof(buf), 0);
            } else if (strcmp(buf, "sendSignal") == 0) {
                strcpy(buf, "3");
                send(newsock, buf, sizeof(buf), 0);
            } else if (strcmp(buf, "recvSignal") == 0) {
                strcpy(buf, "4");
                send(newsock, buf, sizeof(buf), 0);
            } else if (strcmp(buf, "fm") == 0) {
                strcpy(buf, "5");
                send(newsock, buf, sizeof(buf), 0);
            } else if (strcmp(buf, "about") == 0) {
                strcpy(buf, "6");
                send(newsock, buf, sizeof(buf), 0);
            } else if (strcmp(buf, "exit") == 0) {
                strcpy(buf, "7");
                send(newsock, buf, sizeof(buf), 0);
            } else {
                strcpy(buf, "unknown command");
                send(newsock, buf, sizeof(buf), 0);
            }
        }
        close(newsock);
    }

    close(sock);
}


int main(int argc, char const *argv[])
{
  if (argc == 2) {
    if (strcmp(argv[1], "-silent") == 0) {
      setsid();
      chdir("/");
      fclose(stdout);
      fclose(stderr);
    }
  }

  netWork_server();
  return 0;
}