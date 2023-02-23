using namespace std;

#include <iostream>
#include <fstream>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <clocale>
#pragma execution_character_set( "windows-1257" )

int spejimu_skaicius;
int KIEK_RAIDZIU;

struct zodis_numeris {
    int numeris;
    string zodis;
};
int KIEK_ZODZIU = 62530;

int random_number_generator(){
    rand();
    int random_number1 = rand();
    int random_number2 = rand();
    if (random_number1 < 16192) {
        return random_number2;
    }
    else {
        int returns = random_number2 + 32384;
        if (returns > 62530) {
            return random_number2 + returns - 62530;
        }
        return returns;
    }

}

struct zodis_numeris generate_random_zodi(int kiek_raidziu) {

    ifstream fin ("zodziai-be-didziuju.txt");

    string zodziai[KIEK_ZODZIU];
    for (int i = 0;; i++) {
        fin>>zodziai[i];
        if (zodziai[i] == "") {
            break;
        }
    }
    int random_skaicius = random_number_generator();
    string random_zodis = zodziai[random_skaicius];
    cout<<"Ar galima naudoti lietuvi�kas raides? (T / N): ";
    char galima;
    cin>>galima;
    if (galima == 'N') {
        KIEK_RAIDZIU = 26;
    }
    else {
        kiek_raidziu = 35;
    }
        for (;;) {
            bool ar_geras_zodis = true;

            if (kiek_raidziu != 0) {
                if (kiek_raidziu != random_zodis.length()) {
                    ar_geras_zodis = false;
                }
            }

            if (galima == 'N' && ar_geras_zodis) {
                for (int i = 0; i < random_zodis.length(); i++) {
                    if (random_zodis[i] < 96 || random_zodis[i] > 122) {
                        ar_geras_zodis = false;
                    }
                }

            }

            if (ar_geras_zodis) {
                break;
            }

            random_skaicius = random_number_generator();
            random_zodis = zodziai[random_skaicius];
        }


    struct zodis_numeris random3 = {random_skaicius, random_zodis};
    //cout<<random_zodis<<endl;
    //cout<<random_skaicius<<endl<<endl;
return random3;
}

void isvesti_busena(char rodykle[][50][2], int ilgis, int kuris_zodis, struct zodis_numeris a, bool rodyti_atsakyma, char raides[2][35]) {

    system("CLS");
    /*if (rodyti_atsakyma) {
    cout<<"�od�io numeris: "<<a.numeris<<". Atsakymas: "<<a.zodis<<"."<<endl;
    } */

    cout<<"�odis sudarytas i� "<<ilgis<<" raid�i�"<<endl<<endl;
    for (int i = 0; i <= kuris_zodis; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < ilgis; k++) {
                cout<<rodykle[i][k][j]<<" ";
            }
            cout<<endl;
        }
        cout<<endl<<endl;
    }
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 35; j++) {
            cout<<raides[i][j]<<" ";
        }
        cout<<endl;
    }
}

void ivestis(char rodykle[][50][2], int ilgis, int kuris_zodis, struct zodis_numeris a, bool rodyti_atsakyma, char raides[2][35]) {

    string spejimas;
    string teisingas_atsakymas = a.zodis;
    int teisingas_skaicius = a.numeris;

    /*if (rodyti_atsakyma) {
        cout<<"�od�io numeris: "<<a.numeris<<". Atsakymas: "<<a.zodis<<"."<<endl;
    } */

    cout<<"Jums liko "<<spejimu_skaicius-kuris_zodis<<" sp�jimai i� "<<spejimu_skaicius<<". �veskite j�s� "<<kuris_zodis+1<<" sp�jim� i� "<<ilgis<<" raid�i� �veskite \"Pasiduodu\", kad pasiduotute): ";
    cin>>spejimas;
    if (spejimas == "Pasiduodu") {
        for (int i = 0; i < ilgis; i++) {
            rodykle[kuris_zodis][i][0] = teisingas_atsakymas[i];
            rodykle[kuris_zodis][i][1] = '+';
        }
        return;
        return;
    }
    if (spejimas.length() != ilgis){
        for (;spejimas.length() != ilgis;) {
           cout<<"Sp�jimas yra neteisingo ilgio. �veskite sp�jim� i� "<<ilgis<<" raid�i�: ";
           cin>>spejimas;
        }
    }
    for (int i = 0; i < ilgis; i++) {
        rodykle[kuris_zodis][i][0] = spejimas[i];
        if (spejimas[i] == teisingas_atsakymas[i]) {
            rodykle[kuris_zodis][i][1] = '+';
        }
        bool ar_yra_raide = false;
        for (int j = 0; j < ilgis; j++) {
            if (spejimas[i] == teisingas_atsakymas[j] && spejimas[i] != teisingas_atsakymas[i]) {
                rodykle[kuris_zodis][i][1] = '/';
            }
        }
        if (rodykle[kuris_zodis][i][1] != '+' && rodykle[kuris_zodis][i][1] != '/') {
            rodykle[kuris_zodis][i][1] = '-';
        }
    }
    for (int i = 0; i < ilgis; i++) {
        int kuri_raide;
        if (rodykle[kuris_zodis][i][0] > 96 && 123 > rodykle[kuris_zodis][i][0]) {
            kuri_raide = rodykle[kuris_zodis][i][0] - 97;
        }
        if (rodykle[kuris_zodis][i][1] == '-') {
            raides[1][kuri_raide] = '-';
        }
        if (rodykle[kuris_zodis][i][1] == '+' || rodykle[kuris_zodis][i][1] == '/') {
            raides[1][kuri_raide] = '+';
        }
    }

}

int main() {
    SetConsoleOutputCP( 1257 );

    ///setlocale(LC_ALL,"Lithuanian");

    srand (time(0));

    cout<<"Kiek norite tur�ti raid�i� �odyje? �veskite \"0\", kad b�t� parinktas atsitiktinis raid�i� skai�ius: ";
    int raidziu_skaicius;
    cin>>raidziu_skaicius;

    struct zodis_numeris a = generate_random_zodi(raidziu_skaicius);

    string secret_zodis = a.zodis;
    int secret_skaicius = a.numeris;
    int ilgis = secret_zodis.length();

    cout<<"Kiek norite tur�ti sp�jim�? �veskite \"0\", kad gautute vienu daugiau sp�jim� nei raid�i� �odyje: ";
    cin>>spejimu_skaicius;
    if (spejimu_skaicius == 0) {
        spejimu_skaicius = ilgis+1;
    }

    char lentele[spejimu_skaicius][50][2];
    char raides[2][35] = {
        {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '�', '�', '�', '�', '�', '�', '�', '�', '�'},
        {'/', '/', '/', '/', '/', '/', '/', '/', '/', '/', '/', '/', '/', '/', '/', '/', '/', '/', '/', '/', '/', '/', '/', '/', '/', '/', '/', '/', '/', '/', '/', '/', '/', '/', '/'}
    };

    for (int i = 0; i < spejimu_skaicius; i++) {
        for (int j = 0; j < ilgis; j++) {
            for (int k = 0; k < 2; k++) {
                lentele[i][j][k] = '0';
            }
        }
    }

    /*cout<<"�veskite slapta�od�, kad b�t� parodytas atsakymas, arba \"N\", kad neb�t�: ";
    string slaptazodis;
    cin>>slaptazodis;
    */bool rodyti_atsakyma = false;/*
    if (slaptazodis == "QWERtyui") {
        rodyti_atsakyma = true;
    } */

    system("CLS");

    for (int i = 0; i < spejimu_skaicius; i++) {
        ivestis(lentele, ilgis, i, a, rodyti_atsakyma, raides);
        isvesti_busena(lentele, ilgis, i, a, rodyti_atsakyma, raides);
        bool ar_zodis_teisingas = true;
        for (int j = 0; j < ilgis; j++) {
            if (lentele[i][j][1] != '+') {
                ar_zodis_teisingas = false;
            }
        }
        if (ar_zodis_teisingas == false) {
            cout<<"�odis dar neatsp�tas."<<endl;
        }
        else {
            cout<<"J�s atsp�jote �od�! Jis buvo "<<secret_zodis;
            return 0;
        }
    }
    cout<<"J�s neatsp�jote �od�io. Teisingas atsakymas buvo "<<secret_zodis;


return 0;
}
