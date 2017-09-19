#include<iostream>
#include<string>
#include<string.h>
#include<fstream>
#include<sstream>

#define Max 10000000;

using namespace std;

class Hash
{
private:
    int hindex[100000];
    string htable[100000];
public:
    void Insert(int key,string &value,int index);
    void Search(int key,string &value);
    void Delete(int key,string &value);
    ~Hash(){};
};

int l,fp,total,arr[100];

void Hash::Insert(int key,string &value,int index)
{
    int i=0;
    while(htable[key]!="" && htable[key]!="*" && i!=l)
    {
        key++;
        key=key%l;
        i++;
    }
    htable[key]=value;
    hindex[key]=index;
}

void Hash::Search(int key,string &value)
{
    int i=0,j=0;
    fp=0;total=0;
    while(htable[key]!="" && i!=l)
    {
        if(htable[key]==value)
        {
            arr[j]=hindex[key];
            j++;
        }
        else
            fp++;
        total++;
        key++;
        key=key%l;
        i++;
    }
}

void Hash::Delete(int key,string &value)
{
    Hash *pt=new Hash;
    int i=0;
    while(pt->htable[key]!=""||pt->htable[key]!=value||i!=l)
    {
        key++;
        key=key%l;
        i++;
    }
    if(pt->htable[key]==value)
        pt->htable[key]="*";
    else
        cout<<"The value is not in hash table\n";
}

/* ..... INTEGER CASTING.... */

unsigned int intcast(int i,int f,string &te)
{
    int j=i,m;
    unsigned int v=0;
    m=(int)te[j];
    while(j<f && j<(i+3))
    {
        m=(int)te[j];
        v= v|m;
        v = v<<8;
        v= v%Max;
        j++;
    }
    v=v | m;
    //v=v%Max;
    return v;
}

/* ..... COMPONENT SUM ..... */

int composum(int i,int f,string &te)
{
    int j,v=0;
    for(j=i;j<=f;j++)
    {
        v=v+(int)te[j];
        //v=v%Max;
    }
    return v;
}

/* .... POLYNOMIAL SUM .... */

int polysum(int i,int f,string &te)
{
    int j,v=0;
    for(j=i;j<f;j++)
    {
        v=v+(int)te[j];
        v=v*33;
        v=v%Max;
    }
    v=v+(int)te[j];
    v=v%Max;
    return v;
}

/* ..... CYCLIC SHIFT ..... */

unsigned int cyclsum(int i,int f,string &te)
{
    unsigned int v=0;
    int j;
    for(j=i;j<=f;j++)
    {
        v=v+(unsigned int)te[j];
        v=(v<<5)|(v>>27);
        v=v%Max;
    }
    return v;
}

int main()
{
    int i,lt,lp,v,j,m,a,b,u,fpm[5][4],tcm[5][4],arrl;
    float mn=0.618033;
    char buf[10000];
    string t,p,temp;
    ifstream myfile;
    ifstream pfile;
    ofstream outfile;

    outfile.open("2015csb1014-output1.txt");
    myfile.open("T.txt");
    pfile.open("P.txt");
    getline(myfile,t);
    lt=t.length();
    pfile>>p;

    lp=p.length();
    l=2*(lt-lp)+1;
    Hash* icastd=new Hash;              // CREATING 12 HASH TABLES
    Hash* icastmad=new Hash;
    Hash* icastm=new Hash;
    Hash* compsd=new Hash;
    Hash* compsmad=new Hash;
    Hash* compsm=new Hash;
    Hash* polysd=new Hash;
    Hash* polysmad=new Hash;
    Hash* polysm=new Hash;
    Hash* cyclsd=new Hash;
    Hash* cyclsmad=new Hash;
    Hash* cyclsm=new Hash;
    if(l>2)
    {
        a=2;                              // SELECTING a AND b for multiplication and divison scheme
        b=3;
    }
    else if(l==2)
    {
        a=1;
        b=1;
    }
    else
    {
        a=0;
        b=0;
    }
    for(i=0;i<=(lt-lp);i++)
    {
        for(j=0;j<lp;j++)
        {
            buf[j]=t[i+j];
        }
        temp=string(buf);

        v=intcast(i,i+lp-1,t);
        m=v%l;                                      // DIVISON METHOD
        icastd->Insert(m,temp,i);
        m=(a*v+b)%l;                                // MAD METHOD
        icastmad->Insert(m,temp,i);
        u=v*mn;                                     // MULTIPLICATION METHOD
        m=l*(v*mn-u);
        icastm->Insert(m,temp,i);

        v=composum(i,i+lp-1,t);
        m=v%l;
        compsd->Insert(m,temp,i);
        m=(a*v+b)%l;
        compsmad->Insert(m,temp,i);
        u=v*mn;
        m=l*(v*mn-u);
        compsm->Insert(m,temp,i);

        v=polysum(i,i+lp-1,t);
        m=v%l;
        polysd->Insert(m,temp,i);
        m=(a*v+b)%l;
        polysmad->Insert(m,temp,i);
        u=v*mn;
        m=l*(v*mn-u);
        polysm->Insert(m,temp,i);

        v=cyclsum(i,i+lp-1,t);
        m=v%l;
        cyclsd->Insert(m,temp,i);
        m=(a*v+b)%l;
        cyclsmad->Insert(m,temp,i);
        u=v*mn;
        m=l*(v*mn-u);
        cyclsm->Insert(m,temp,i);
    }
    v=cyclsum(0,lp-1,p);                                      // SEARCHING FOR THE FIRST VALUE OF P.
    u=v*mn;
    m=l*(v*mn-u);
    cyclsm->Search(m,p);

    if(total==fp)
        outfile<<"Pattern not found\n";
    else
    {
        outfile<<"Pattern found at indexes :- \n";
        for(i=0;i<total-fp;i++)
            outfile<<arr[i]<<"\n";
    }

    v=intcast(0,lp-1,p);
    m=v%l;
    icastd->Search(m,p);
    fpm[0][0]=fp;
    tcm[0][0]=total;
    m=(a*v+b)%l;
    icastmad->Search(m,p);
    fpm[0][1]=fp;
    tcm[0][1]=total;
    u=v*mn;
    m=l*(v*mn-u);
    icastm->Search(m,p);
    fpm[0][2]=fp;
    tcm[0][2]=total;

    v=composum(0,lp-1,p);
    m=v%l;
    compsd->Search(m,p);
    fpm[1][0]=fp;
    tcm[1][0]=total;
    m=(a*v+b)%l;
    compsmad->Search(m,p);
    fpm[1][1]=fp;
    tcm[1][1]=total;
    u=v*mn;
    m=l*(v*mn-u);
    compsm->Search(m,p);
    fpm[1][2]=fp;
    tcm[1][2]=total;

    v=polysum(0,lp-1,p);
    m=v%l;
    polysd->Search(m,p);
    fpm[2][0]=fp;
    tcm[2][0]=total;
    m=(a*v+b)%l;
    polysmad->Search(m,p);
    fpm[2][1]=fp;
    tcm[2][1]=total;
    u=v*mn;
    m=l*(v*mn-u);
    polysm->Search(m,p);
    fpm[2][2]=fp;
    tcm[2][2]=total;

    v=cyclsum(0,lp-1,p);
    m=v%l;
    cyclsd->Search(m,p);
    fpm[3][0]=fp;
    tcm[3][0]=total;
    m=(a*v+b)%l;
    cyclsmad->Search(m,p);
    fpm[3][1]=fp;
    tcm[3][1]=total;
    u=v*mn;
    m=l*(v*mn-u);
    cyclsm->Search(m,p);
    fpm[3][2]=fp;
    tcm[3][2]=total;

    outfile<<"False Positive \n";
    for(i=0;i<4;i++)
    {
        for(j=0;j<3;j++)
            outfile<<fpm[i][j]<<" ";
        outfile<<endl;
    }
    outfile<<"Total Comparison \n";
    for(i=0;i<4;i++)
    {
        for(j=0;j<3;j++)
            outfile<<tcm[i][j]<<" ";
        outfile<<endl;
    }
    outfile<<endl;

    while(pfile>>p)                                            // SEARCHING FOR THE REST VALUE OF P.
    {
    v=cyclsum(0,lp-1,p);
    u=v*mn;
    m=l*(v*mn-u);
    cyclsm->Search(m,p);

    if(total==fp)
        outfile<<"Pattern not found\n";
    else
    {
        outfile<<"Pattern found at indexes :- \n";
        for(i=0;i<total-fp;i++)
            outfile<<arr[i]<<"\n";
    }

    v=intcast(0,lp-1,p);
    m=v%l;
    icastd->Search(m,p);
    fpm[0][0]=fp;
    tcm[0][0]=total;
    m=(a*v+b)%l;
    icastmad->Search(m,p);
    fpm[0][1]=fp;
    tcm[0][1]=total;
    u=v*mn;
    m=l*(v*mn-u);
    icastm->Search(m,p);
    fpm[0][2]=fp;
    tcm[0][2]=total;

    v=composum(0,lp-1,p);
    m=v%l;
    compsd->Search(m,p);
    fpm[1][0]=fp;
    tcm[1][0]=total;
    m=(a*v+b)%l;
    compsmad->Search(m,p);
    fpm[1][1]=fp;
    tcm[1][1]=total;
    u=v*mn;
    m=l*(v*mn-u);
    compsm->Search(m,p);
    fpm[1][2]=fp;
    tcm[1][2]=total;

    v=polysum(0,lp-1,p);
    m=v%l;
    polysd->Search(m,p);
    fpm[2][0]=fp;
    tcm[2][0]=total;
    m=(a*v+b)%l;
    polysmad->Search(m,p);
    fpm[2][1]=fp;
    tcm[2][1]=total;
    u=v*mn;
    m=l*(v*mn-u);
    polysm->Search(m,p);
    fpm[2][2]=fp;
    tcm[2][2]=total;

    v=cyclsum(0,lp-1,p);
    m=v%l;
    cyclsd->Search(m,p);
    fpm[3][0]=fp;
    tcm[3][0]=total;
    m=(a*v+b)%l;
    cyclsmad->Search(m,p);
    fpm[3][1]=fp;
    tcm[3][1]=total;
    u=v*mn;
    m=l*(v*mn-u);
    cyclsm->Search(m,p);
    fpm[3][2]=fp;
    tcm[3][2]=total;

    outfile<<"False Positive \n";
    for(i=0;i<4;i++)
    {
        for(j=0;j<3;j++)
            outfile<<fpm[i][j]<<" ";
        outfile<<endl;
    }
    outfile<<"Total Comparison \n";
    for(i=0;i<4;i++)
    {
        for(j=0;j<3;j++)
            outfile<<tcm[i][j]<<" ";
        outfile<<endl;
    }
    outfile<<endl;

    }

    pfile.close();
    myfile.close();
    delete icastd;
    delete icastmad;
    delete icastm;
    delete compsd;
    delete compsmad;
    delete compsm;
    delete polysd;
    delete polysmad;
    delete polysm;
    delete cyclsd;
    delete cyclsmad;
    delete cyclsm;
    return 0;
}
