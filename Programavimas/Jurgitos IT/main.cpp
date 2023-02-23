#include <iostream>
#include <fstream>

using namespace std;

struct pirmas
{
    int num;
    int sm;
    int sd;
    int fm;
    int fd;
};

void ieskoti(int B[], int L[], int R[], int M[], int &k, int &m1, int &d1);

int main()
{
    int n;

    ifstream fin ("U1.txt");
    fin>>n;
    pirmas Gele[30];

    for(int i=0; i<n; i++)
    {
        fin>>Gele[i].num>>Gele[i].sm>>Gele[i].sd>>Gele[i].fm>>Gele[i].fd;
    }

    int M[92]={0};
    int B[30]={0};
    int L[31]={0};
    int R[31]={0};

    ///---------------------------------

    for (int i=0; i<n; i++)
    {
            ///Birzelis
            if(Gele[i].sm==6)
            {
                if(Gele[i].sm==Gele[i].fm)
                    {
                        for(int j=Gele[i].sd-1; j<Gele[i].fd; j++)
                            B[j]++;
                    }
                else if(Gele[i].fm==8)
                {
                    for(int j=0; j<31; j++)
                    {
                        L[j]++;
                    }
                    for (int j=0; j<Gele[i].fd; j++)
                        R[j]++;
                    for (int j=Gele[i].sd-1; j<30; j++)
                    {
                        B[j]++;
                    }
                }
                else if(Gele[i].fm==7)
                {
                    for(int j=0; j<Gele[i].fd; j++)
                        L[j]++;
                    for (int j=Gele[i].sd-1; j<30; j++)
                    {
                        B[j]++;
                    }
                }
            }
            ///Liepa
            if(Gele[i].sm==7)
            {
                if(Gele[i].sm==Gele[i].fm)
                    {
                        for(int j=Gele[i].sd-1; j<Gele[i].fd; j++)
                            L[j]++;
                    }
                else if(Gele[i].fm==8)
                {
                    for(int j=0; j<Gele[i].fd; j++)
                        R[j]++;
                    for (int j=Gele[i].sd-1; j<31; j++)
                    {
                        L[j]++;
                    }
                }
            }
            ///Rugpjutis
            if(Gele[i].sm==8)
            {
                if(Gele[i].sm==Gele[i].fm)
                    {
                        for(int j=Gele[i].sd-1; j<Gele[i].fd; j++)
                            R[j]++;
                    }
            }

    }

    int k=0, m1=0, d1=0;
    ieskoti(B,L,R,M,k,m1,d1);
    cout<<k<<" "<<d1<<" "<<m1<<endl;

    for(int i=0; i<92; i++)
    {
        cout<<i<<" "<<M[i]<<endl;
    }

    ofstream fout("U1rez.txt");
    fout<<k<<endl;
    if(d1<30)
    fout<<"6 "<<d1+1;
    if(d1>29&&d1<61)
    fout<<"7 "<<(d1-30)+1;
    if(d1>60)
    fout<<"8 "<<d1-60;
    fout<<endl;
    if(m1<30)
    fout<<"6 "<<m1+1;
    if(m1>29&&m1<61)
    fout<<"7 "<<(m1-30)+1;
    if(m1>60)
    fout<<"8 "<<m1-60;


    return 0;
}

void ieskoti(int B[], int L[], int R[], int M[], int &k, int &m1, int &d1)
{
    int d=0;

    for (int i=0; i<30; i++)
    {
        M[i]=B[i];
    }
    for (int i=30; i<61; i++)
    {
        M[i]=L[i-30];
    }
    for (int i=61; i<92; i++)
    {
        M[i]=R[i-61];
    }

    for(int i=0; i<92; i++)
    {
        if(M[i]>d)
        {
            d=M[i];
            d1=i;
        }
    }
    k=d;
    int a=92;
    for(int i=d1; i<a; i++)
    {
        if(M[i]==d) m1=i;
        else a=i;
    }
}

