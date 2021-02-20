#include "liteSH.hpp"


int createProcess(char *ProcName)
{
    int rv;
    char *arg[] = {ProcName, 0};

    switch (fork()) {
        case -1:
            perror("fork");
            return 1;
        case 0:
            cout << "pid: " << getpid() << endl;
            cout << "ppid: " << getppid() << endl;
            execv(arg[0], arg);
        default:
            wait(&rv);
    }

    return 0;
}


int createDaemon(char *ProcName)
{
    int rv;
    char *arg[] = {ProcName, 0};

    switch (fork()) {
        case -1:
            perror("fork");
            return 1;
        case 0:
            setsid();
            cout << "pid: " << getpid() << endl;
            cout << "ppid: " << getppid() << endl;
            chdir("/");
            fclose(stdin);
            fclose(stdout);
            fclose(stderr);
            execv(arg[0], arg);
            //exit(0);
        default:
            wait(&rv);
    }

    return 0;
}

void signalHandler(int signo)
{
    cout << "Signal received successfully" << endl;
}


int sendSignal(pid_t pid, int signum)
{
    if (kill(pid, signum) == -1)
        return 1;

    return 0;
}


int recvSignal(int signum)
{
    if (signal(signum, signalHandler) == SIG_ERR)
        return 1;

    return 0;
}


int netWork_client(char *command)
{
    // структура для сокета
    struct sockaddr_in server;
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(2020);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0) {
        cout << "connection failed" << endl;
        return -1;
    }

    char buf[100] = "";
    send(sock, command, sizeof(buf), 0);
    recv(sock, buf, sizeof(buf), 0);
    cout << "received from server: " << buf << endl;

    close(sock);

    int selection = atoi(buf);
    return selection;
}