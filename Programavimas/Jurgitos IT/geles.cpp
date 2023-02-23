using namespace std;

#include <bits/stdc++.h>

struct formatas {
    int numeris;
    int m1;
    int d1;
    int m2;
    int d2;
};

struct data {
    int m;
    int d;
};

int paversti_i_diena(int m, int d) {
    //cout<<"m = "<<m<<", d = "<<d<<".\n";
    int diena = 0;
    if (m == 7) {
        diena += 30;
    } else if (m == 8) {
        diena += 61;
    }
    diena += d;
return diena;
}

data paversti_i_data(int diena) {
    data isvestis = {6, diena+1};
    if (diena > 29) {
        isvestis.m++;
        isvestis.d -= 29;
    }
    if (diena > 60) {
        isvestis.m++;
        isvestis.d -= 30;
    }
return isvestis;
}

int main() {
    ifstream fin ("U1.txt");
    ofstream fout ("U1rez.txt");

    int M[92];
    for (int i = 0; i < 92; i++) M[i] = 0;

    int N; fin>>N;
    formatas geles[N];
    for (int i = 0; i < N; i++) {
        fin>>geles[i].numeris>>geles[i].m1>>geles[i].d1>>geles[i].m2>>geles[i].d2;
        int pradzia = paversti_i_diena(geles[i].m1, geles[i].d1);
        int pabaiga = paversti_i_diena(geles[i].m2, geles[i].d2);
        //cout<<"Kai i = "<<i<<", tai pradzia = "<<pradzia<<", pabaiga = "<<pabaiga/*<<", m1 = "<<geles[i].m1<<", m2 = "<<geles[i].m2<<", d1 = "<<geles[i].d1<<", d2 = "<<geles[i].d2*/<<".\n";
        for (int j = pradzia; j <= pabaiga; j++) {

            M[j] = 1;
        }
    }

    int didziausias = 0;
    int pradzios_diena = 0, pabaigos_diena = 91;
    bool galima_keisti = false;
    for (int i = 0; i < 92; i++) {
        //cout<<M[i]<<endl;
        if (M[i] > didziausias) {
            didziausias = M[i];
            pradzios_diena = i;
            galima_keisti = true;
        } else if (M[i] < didziausias && galima_keisti) {
            //cout<<"pabaigos diena";
            pabaigos_diena = i-1;
            galima_keisti = false;
        }
    }
    fout<<didziausias<<endl;
    /*cout<<pradzios_diena<<endl;
    cout<<pabaigos_diena; */
    data isvestis = paversti_i_data(pradzios_diena-1);
    fout<<isvestis.m<<" "<<isvestis.d<<endl;
    isvestis = paversti_i_data(pabaigos_diena-1);
    fout<<isvestis.m<<" "<<isvestis.d;
}
