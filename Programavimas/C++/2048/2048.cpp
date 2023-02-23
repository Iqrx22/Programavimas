using namespace std;

#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma execution_character_set( "utf-8" )

void naujas_skaicius(int lentele[4][4]) {
    rand();
    for (;;) {
        //cout<<rand()<<endl;
        //<<random_skaicius<<endl<<endl;
        int random_skaicius2 = rand();
        int random_skaicius = random_skaicius2 % 16;
        if (lentele[random_skaicius/4][random_skaicius%4] == 0) {
            if (rand() % 10 == 0) {
                lentele[random_skaicius/4][random_skaicius%4] = 4;
                cout<<endl;
                return;
            }
            else {
                lentele[random_skaicius/4][random_skaicius%4] = 2;
                cout<<endl;
                return;
            }
        }
    }


}

void sutraukti_i_puse(char puse, int lentele[4][4]) {
    for (int eilute = 0; eilute < 4; eilute++) {
        for (int stulpelis = 0; stulpelis < 4; stulpelis++) {
            if (puse == 'A') {
                if (lentele[eilute][stulpelis] == 0) {
                    for (int stulpelis2 = stulpelis+1; stulpelis2 < 4; stulpelis2++) {
                        if (lentele[eilute][stulpelis2] != 0) {
                            lentele[eilute][stulpelis] = lentele[eilute][stulpelis2];
                            lentele[eilute][stulpelis2] = 0;
                            break;
                        }
                    }
                }
                if (lentele[eilute][stulpelis] == lentele[eilute][stulpelis+1]) {
                    lentele[eilute][stulpelis] = 2*lentele[eilute][stulpelis];
                    lentele[eilute][stulpelis+1] = 0;
                }
            }
            if (puse == 'D') {
                if (lentele[eilute][3-stulpelis] == 0) {
                    for (int stulpelis2 = 2-stulpelis; stulpelis2 >= 0; stulpelis2--) {
                        if (lentele[eilute][stulpelis2] != 0) {
                            lentele[eilute][3-stulpelis] = lentele[eilute][stulpelis2];
                            lentele[eilute][stulpelis2] = 0;
                            break;
                        }
                    }
                }
                if (lentele[eilute][stulpelis] == lentele[eilute][stulpelis-1]) {
                    lentele[eilute][stulpelis] = 2*lentele[eilute][stulpelis];
                    lentele[eilute][stulpelis-1] = 0;
                }
            }
        }
    }

    for (int stulpelis = 0; stulpelis < 4; stulpelis++) {
        for (int eilute = 0; eilute < 4; eilute++) {
            if (puse == 'W') {
                if (lentele[eilute][stulpelis] == 0) {
                    for (int eilute2 = eilute+1; eilute2 < 4; eilute2++) {
                        if (lentele[eilute2][stulpelis] != 0) {
                            lentele[eilute][stulpelis] = lentele[eilute2][stulpelis];
                            lentele[eilute2][stulpelis] = 0;
                            break;
                        }
                    }
                }
                if (lentele[eilute][stulpelis] == lentele[eilute+1][stulpelis]) {
                    lentele[eilute][stulpelis] = 2*lentele[eilute][stulpelis];
                    lentele[eilute+1][stulpelis] = 0;
                }
            }
            if (puse == 'S') {
                if (lentele[3-eilute][stulpelis] == 0) {
                    for (int eilute2 = 2-eilute; eilute2 >= 0; eilute2--) {
                        if (lentele[eilute2][stulpelis] != 0) {
                            lentele[3-eilute][stulpelis] = lentele[eilute2][stulpelis];
                            lentele[eilute2][stulpelis] = 0;
                            break;
                        }
                    }
                }
                if (lentele[eilute][stulpelis] == lentele[eilute-1][stulpelis]) {
                    lentele[eilute][stulpelis] = 2*lentele[eilute][stulpelis];
                    lentele[eilute-1][stulpelis] = 0;
                }
            }
        }
    }
}

void isvesti_busena(int lentele[4][4]) {
    system ( "CLS" );
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout<<setw(4)<<lentele[i][j];
            cout<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

int main() {
    SetConsoleOutputCP( 1257 );

     srand (time(0));

    int lentele[4][4] = {0};
    //int lentele[4][4] = {{8, 4, 2, 2}, 0};

    naujas_skaicius(lentele); naujas_skaicius(lentele);

    for (;;) {
        isvesti_busena(lentele);

        cout<<"Áveskite W,A,S,D, kad lentelë bûtø pajudinta á atitinkamà pusæ: ";
        char ivestis;
        cin>>ivestis;

        sutraukti_i_puse(ivestis, lentele);
        sutraukti_i_puse(ivestis, lentele);
        sutraukti_i_puse(ivestis, lentele);
        sutraukti_i_puse(ivestis, lentele);

        ///Pabaigos salygos
        bool Lentele_nepilna = false;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (lentele[i][j] >= 2048) {
                    cout<<"Sveikinu! Jûs laimëjote ðá þaidimà! Kà nors áveskite, kad þaidimas baigtøsi: ";
                    string kazkas;
                    cin>>kazkas;
                    return 0;
                }
                if (lentele[i][j] == 0) {
                    Lentele_nepilna = true;
                }
            }
        }
        if (Lentele_nepilna == false) {
            cout<<"Lentelë pilna. Jûs pralaimëjote ðá þaidimà. Kà nors áveskite, kad þaidimas baigtøsi: ";
            string kazkas;
            cin>>kazkas;
            return 0;
        }

        naujas_skaicius(lentele);

    }
return 0;
}
