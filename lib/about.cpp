#include <iostream>
#include <fstream>

using namespace std;

extern "C" {

    void about()
    {
        cout << "\t\t**********LiteSH**********\n\n" << 
        "Using this utility you can easily create processes and daemons,\n" << 
        "receive signals from external programs and the operating system\n" << 
        "and also send signals to other processes\n" << 
        "Author: Evgeniy Sapronov" << endl;

        ifstream signals("../bin/signals.txt");
        string SigName;

        cout << "Available signal numbers\n" << 
        "---------------------------" << endl;

        for (int i = 1; getline(signals, SigName); i++) {
          cout << "\E[36m" << i << " - ";
          cout << "\E[39m";
          cout << SigName << endl;
        }

        signals.close();
    }


    void mainMenu()
    {
        cout << "Print 'createProcess' to create process\n" <<
        "Print 'createDaemon' to create daemon\n" <<
        "Print 'sendSignal' to send signal to the process\n" <<
        "Print 'recvSignal' to receive signal\n" << 
        "Print 'fm' to start FileManager\n" << 
        "Print 'about' to learn about project\n" << 
        "Print 'exit' to close program" << endl << endl;
    }

}


int main()
{
    return 0;
}