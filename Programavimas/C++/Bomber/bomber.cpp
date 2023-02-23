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

const static int LENTOS_DYDIS = 1000;
int TIKRAS_DYDIS = 10;

const static int KOKIA_TIKIMYBE_KAD_PATEKS = 90;
const static int PO_KIEK_MAZINT_TIKIMYBE = 0.5;

struct koordinates {
    int x;
    int y;
};

bool ar_pateks(int mazint) {
    rand();
    if ((rand() % 100) < KOKIA_TIKIMYBE_KAD_PATEKS - mazint) {
        return true;
    }
    else {
        return false;
    }
}

int kiek_yra_kaimynu(int kaimynu_skaicius, char lenta[LENTOS_DYDIS][LENTOS_DYDIS], struct koordinates taskas) {
    int kiek_kaimynu = 0;
    for (int i = 0; i < kaimynu_skaicius; i++) {
        struct koordinates kaimynas;
        if (i == 0) {
            if (taskas.x+1 == TIKRAS_DYDIS) {
                continue;
            }
            kaimynas.x = taskas.x+1;
            kaimynas.y = taskas.y;
        }
        if (i == 1) {
            if (taskas.y+1 == TIKRAS_DYDIS) {
                continue;
            }
            kaimynas.x = taskas.x;
            kaimynas.y = taskas.y+1;
        }
        if (i == 2) {
            if (taskas.x-1 == -1) {
                continue;
            }
            kaimynas.x = taskas.x-1;
            kaimynas.y = taskas.y;
        }
        if (i == 3) {
            if (taskas.y-1 == -1) {
                continue;
            }
            kaimynas.x = taskas.x;
            kaimynas.y = taskas.y-1;
        }
        if (i == 4) {
            if (taskas.x+1 == TIKRAS_DYDIS || taskas.y-1 == -1) {
                continue;
            }
            kaimynas.x = taskas.x+1;
            kaimynas.y = taskas.y-1;
        }
        if (i == 5) {
            if (taskas.x+1 == TIKRAS_DYDIS || taskas.y+1 == TIKRAS_DYDIS) {
                continue;
            }
            kaimynas.x = taskas.x+1;
            kaimynas.y = taskas.y+1;
        }
        if (i == 6) {
            if (taskas.x-1 == -1 || taskas.y+1 == TIKRAS_DYDIS) {
                continue;
            }
            kaimynas.x = taskas.x-1;
            kaimynas.y = taskas.y+1;
        }
        if (i == 7) {
            if (taskas.x-1 == -1 || taskas.y-1 == -1) {
                continue;
            }
            kaimynas.x = taskas.x-1;
            kaimynas.y = taskas.y-1;
        }

        if (lenta[kaimynas.x][kaimynas.y] != 0) {
            kiek_kaimynu++;
        }
    }
    return kiek_kaimynu;
}

struct koordinates sugeneruoti_random_siena(char lentele[LENTOS_DYDIS][LENTOS_DYDIS]) {
    rand();
    for (;;) {
        int random_skaicius2 = rand();
        int random_skaicius = random_skaicius2 % (int)pow(TIKRAS_DYDIS, 2);
        if (lentele[random_skaicius/TIKRAS_DYDIS][random_skaicius%TIKRAS_DYDIS] == 0) {
            if (random_skaicius/TIKRAS_DYDIS == 0 || random_skaicius/TIKRAS_DYDIS == 9 || random_skaicius%TIKRAS_DYDIS == 0 || random_skaicius%TIKRAS_DYDIS == 9) {
                continue;
            }
            struct koordinates sekla= {random_skaicius/TIKRAS_DYDIS, random_skaicius%TIKRAS_DYDIS};
            return sekla;
        }
    }


}

void sugeneruoti_sienas(char lenta[LENTOS_DYDIS][LENTOS_DYDIS]) { //
    ofstream fout ("bomber_isvestis.out");

    //for (int i = 0; i < 3; i++) {

        int kiek_mazint_procentu_tikimybe = 0;
        struct koordinates masyvas[TIKRAS_DYDIS*TIKRAS_DYDIS+1];
        masyvas[0] = sugeneruoti_random_siena(lenta); //seed'as idedamas i masyva
        struct koordinates *paimti = &masyvas[0];
        struct koordinates *ideti = &masyvas[1];
        for (int kelintas = 0;;kelintas++) {
            struct koordinates kandidatas  = *paimti;//
            int kaimynu_skaicius = kiek_yra_kaimynu(8, lenta, kandidatas);

            if (kaimynu_skaicius > 2) {
                paimti++;
                fout<<endl<<kelintas<<". x: "<<paimti->x<<", y: "<<paimti->y<<", jis nepateko, nes per daug kaimynu";
                if (paimti == ideti) {
                    break;
                }
                continue;
            }
            if (kelintas == 0) {
                kiek_mazint_procentu_tikimybe = kiek_mazint_procentu_tikimybe+PO_KIEK_MAZINT_TIKIMYBE;
                lenta[paimti->x][paimti->y] = '#';
                fout<<kelintas<<". x: "<<paimti->x<<", y: "<<paimti->y<<", jis pateko, nes yra seed'as";
            }
            else if (ar_pateks(kiek_mazint_procentu_tikimybe)) {
                kiek_mazint_procentu_tikimybe = kiek_mazint_procentu_tikimybe+PO_KIEK_MAZINT_TIKIMYBE;
                lenta[paimti->x][paimti->y] = '#';
                fout<<endl<<kelintas<<". x: "<<paimti->x<<", y: "<<paimti->y<<", jis pateko";
            }
            else {
                paimti++;
                fout<<endl<<kelintas<<". x: "<<paimti->x<<", y: "<<paimti->y<<", jis nepateko, nes generatorius";
                if (paimti == ideti) {
                    break;
                }
                continue;
            }
            int kiek_kaimynu_pateko = 0;
            for (int i = 0; i < 4; i++) {
                struct koordinates kaimynas;
                if (i == 1) {
                    kaimynas.x = (paimti->x)+1;
                    kaimynas.y = paimti->y;
                }
                if (i == 0) {
                    kaimynas.x = paimti->x;
                    kaimynas.y = (paimti->y)+1;
                }
                if (i == 3) {
                    kaimynas.x = (paimti->x)-1;
                    kaimynas.y = paimti->y;
                }
                if (i == 2) {
                    kaimynas.x = paimti->x;
                    kaimynas.y = (paimti->y)-1;
                }
                fout<<endl<<"kaimynas: "<<kaimynas.x<<", "<<kaimynas.y<<" ";
                if (kaimynas.x == -1 || kaimynas.x == TIKRAS_DYDIS || kaimynas.y == -1 || kaimynas.y == TIKRAS_DYDIS) {
                    fout<<"Nepateko, nes uz ribu";
                    continue;
                }
                bool labai_blogai = false;
                for (int i = 0; i < ideti - &masyvas[0]; i++) {
                    if (kaimynas.x == masyvas[i].x && kaimynas.y == masyvas[i].y) {
                        labai_blogai = true;
                        fout<<"Nepateko, nes buvo sarase, "<<i<<"-ntas numeris";
                        break;
                    }
                }
                if (labai_blogai) {
                    continue;
                }
                if (lenta[kaimynas.x][kaimynas.y] != 0) {
                    fout<<"Nepateko, nes jau yra siena";
                    continue;
                }
                *ideti = kaimynas;
                ideti++;
                fout<<"Jis pateko";
            }
            paimti++;
            if (paimti >= ideti) {
                break;
            }
        }

    //}
}

void isvesti_busena(char lenta[LENTOS_DYDIS][LENTOS_DYDIS]) {
    system ( "CLS" );
    ofstream f2 ("bomber_lentele.out");

    //cout<<endl;
    for (int i = -1; i < TIKRAS_DYDIS+1; i++) {
        for (int j = -1; j< TIKRAS_DYDIS+1; j++) {
            if (i == -1 || i == TIKRAS_DYDIS) {
                cout<<"π";
            }
            else {
                if (j == -1 || j == TIKRAS_DYDIS) {
                    cout<<"π";
                }
                else {
                    if (lenta[i][j] == 0) {
                        cout<<" ";
                    }
                    else {
                        cout<<lenta[i][j];
                    }
                }
            }
        }
        cout<<endl;
    }
}

void nenugriaunamos_sienos (char lenta[LENTOS_DYDIS][LENTOS_DYDIS]) {
    for (int i = 0; i < TIKRAS_DYDIS; i++) {
        for (int j = 0; j < TIKRAS_DYDIS; j++) {
            if (lenta[i][j] == 0) {
                continue;
            }
            struct koordinates taskas = {i, j};
            if (kiek_yra_kaimynu(4, lenta, taskas) > 2) {
                lenta[i][j] = '+';
            }
        }
    }
}

int main() {
    SetConsoleOutputCP( 65001 );

    srand (time(0));

    //cout<<"Kokios norite lentos?:"<<endl<<"1. Maža"<<endl<<"2. Normali"<<endl<<"3. Didelė"<<endl<<"Įveskite skaičių tos lentos, kurios norite: ";
    //int kuri_lenta;
    //cin>>kuri_lenta;
    //TIKRAS_DYDIS = kuri_lenta*2 + 6;

    char lenta[LENTOS_DYDIS][LENTOS_DYDIS] = {0};

    sugeneruoti_sienas(lenta);
    nenugriaunamos_sienos(lenta);
    struct koordinates veikejas = sugeneruoti_random_siena(lenta);
    isvesti_busena(lenta);

return 0;
}
