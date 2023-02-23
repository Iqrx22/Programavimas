using namespace std;

#include <iostream>
#include <fstream>
#include <windows.h>
#pragma execution_character_set( "utf-8" )

int main() {
    SetConsoleOutputCP( 65001 );

    ifstream fin ("lithuanian-words-list.txt");
    ofstream fout ("zodziai-be-didziuju.txt");

    for (;;) {
        string zodis;
        fin>>zodis;
        if (zodis != "") {
            if (zodis[0] > 64 && zodis[0] < 91) {
            }
            else {
                fout<<zodis<<endl;
            }
        }
        else {
            break;
        }

    }
return 0;
}
