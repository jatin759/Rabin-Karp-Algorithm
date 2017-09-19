#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<string.h>

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

int l,qarr[100000],arr[100000],total,fp,lqarr;

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
    int i=0;
    while(htable[key]!=""||htable[key]!=value||i!=l)
    {
        key++;
        key=key%l;
        i++;
    }
    if(htable[key]==value)
        htable[key]="*";
    else
        cout<<"The value is not in hash table\n";
}

unsigned int cyclsum(int i,int f,string &te)
{
    unsigned int v=0;
    int j,k=0;
    for(j=i;j<=f;j++)
    {
        if(k<lqarr && qarr[k]==j-i)
        {
            v=v+63;
            k++;
        }
        else
        {
            v=v+(unsigned int)te[j];
        }
        v=(v<<5)|(v>>27);
        v=v%Max;
    }
    return v;
}


int main()
{
    int i,j,lt,lp,m,v,k,u;
    float mn=0.618033;
    char buf[100000];
    ifstream myfile;
    myfile.open("T.txt");

    string t,p,temp;
    getline(myfile,t);
    getline(cin,p);
    lt=t.length();
    lp=p.length();
    l=2*(lt-lp)+1;

    Hash* cyclsm=new Hash;
    j=0;
    for(i=0;i<lp;i++)
    {
        if(p[i]=='?')
        {
            qarr[j]=i;
            j++;
        }
    }
    lqarr=j;
    for(i=0;i<=(lt-lp);i++)
    {
        k=0;
        for(j=0;j<lp;j++)
        {
            if(k<lqarr && qarr[k]==j)
            {
                buf[j]='?';
                k++;
            }
            else
                buf[j]=t[i+j];
        }
        temp=string(buf);

        v=cyclsum(i,i+lp-1,t);
        u=v*mn;
        m=l*(v*mn-u);
        cyclsm->Insert(m,temp,i);

    }

    v=cyclsum(0,lp-1,p);
    u=v*mn;
    m=l*(v*mn-u);
    cyclsm->Search(m,p);

    if(total==fp)
        cout<<"Not found\n";
    else
    {
    for(i=0;i<total-fp;i++)
    {
        for(j=0;j<lp;j++)
        {
            cout<<t[arr[i]+j];
        }
        cout<<endl;
    }
    }
    cout<<"No. of patterns "<<total-fp<<endl;
    myfile.close();
    delete cyclsm;

    return 0;
}
