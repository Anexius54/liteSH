#include "liteSH.hpp"

int main(int argc, char * argv[])
{
    if (argc == 2) {
        if (strcmp(argv[1], "-silent") == 0) {
            setsid();
            chdir("/");
            fclose(stdout);
            fclose(stderr);
        }
    }

    void * handle = dlopen("../lib/about.so", RTLD_LAZY);
    if (!handle) {
        fputs(dlerror(), stderr);
        return 1; 
    }

    typedef void (*p_mainMenu)();
    typedef void (*p_about)();
    p_mainMenu  mainMenu = (p_mainMenu)dlsym(handle, "mainMenu");
    p_about about = (p_about)dlsym(handle, "about");

    char *error;
    if ((error = dlerror()) != NULL) {
        fprintf (stderr, "%s\n", error);
        return 1;
    }

    mainMenu();

    bool f_exit = false;

    while (f_exit == false)
    {

        int selection = 0;
        char *command = new char[100];

        cout << endl << endl;
        cout << "command to server: ";
        cin >> command;
        cout << endl << endl;

        cout << "--------------------------" << endl;
        selection = netWork_client(command);
        cout << "--------------------------" << endl << endl;

        switch (selection) {
            case 1: {
                char *ProcName = new char[100];
                cout << "process name: ";
                cin >> ProcName;

                if (createProcess(ProcName) == 1)
                    cout << "failed to create process" << endl;

                delete [] ProcName;
                break;
            }

            case 2: {
                char *ProcName = new char[100];
                cout << "process name: ";
                cin >> ProcName;

                if (createDaemon(ProcName) == 1)
                    cout << "failed to create daemon" << endl;

                delete [] ProcName;
                break;
            }

            case 3: {
                pid_t pid, signum;
                cout << "pid: ";
                cin >> pid;
                cout << "signal to send: ";
                cin >> signum;

                if (sendSignal(pid, signum) == 1)
                  cout << "failed to send signal";

                break;
            }

            case 4: {
                int signum;
                cout << "signal to receive: ";
                cin >> signum;

                if (recvSignal(signum) == 1)
                  cout << "failed to receive signal";

                break;
            }

            case 5:
                createProcess("/home/evn/study/OS/lab2/fm");
                break;

            case 6:
                about();
                break;

            case 7:
                f_exit = true;
            break;
        }
    }

    dlclose(handle);
    return 0;
}