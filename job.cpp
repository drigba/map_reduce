
#include "job.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string.h>
#include <sstream>
#include <math.h>
using namespace std;

vector<string> split (string mit,  string delim, size_t darab)
{
    vector<string> mibe;
    size_t szoszam=0;
    for(string :: iterator it = mit.begin(); it != mit.end(); ++it)                //Stringben lévő szavak megszámlálása
    {
        if(delim.find(*it) != string :: npos )
            szoszam++;
    }
    if(delim.find(mit[mit.size()-1])== string :: npos)
        szoszam++;
    if(darab == 0)
        darab = szoszam;
    if (szoszam < darab)                                                          //Ha túl sok szóra szeretnénk tördelni
        throw "Data could not be split into this many pieces";

    size_t meret = szoszam / darab;
    size_t hatar = darab - (szoszam % darab);

    size_t szamlalo = 0;
    string tmp;
    for(string :: iterator it = mit.begin(); it != mit.end(); ++it)
    {
        if(delim.find(*it) != string :: npos)
            szamlalo++;
        if(szamlalo != meret)
            tmp += *it;

        else
        {
            mibe.push_back(tmp);
            tmp.clear();
            szamlalo = 0;
            if(mibe.size() == hatar)
                meret++;
        }


    }
    if(!tmp.empty())
        mibe.push_back(tmp);
    return mibe;

}


void Job :: beolvas()
{
    string h;
    if(akt_input_konfig.where== file)
    {
        if(akt_input_konfig.filename.empty())
            throw "Missing filename" ;

        ifstream myfile(akt_input_konfig.filename.c_str());
        if(myfile)
        {
            stringstream strS;
            strS << myfile.rdbuf();
            h = strS.str();
        }
        else
            throw "File could not be opened";
    }
    else
    {
        cout << "Input data:" << endl;
        string t;
        while(getline(cin , t) && !t.empty()) {h+= t + " ";}
    }

    input =  split(h,akt_input_konfig.delim,akt_input_konfig.piece_cnt);



}

void Job:: Map()
{
    for(size_t i = 0; i< akt_map.size(); ++i)
    {
        akt_map[i].mapper();
    }
}



void Job:: distribute()
{
    for(vector<string> :: iterator it = input.begin(); it!= input.end(); ++it)
    {
        Map_Prot uj;
        uj.splitter(*it,akt_input_konfig.delim);
        akt_map.push_back(uj);
    }

}

template <typename T1, typename T2>
void Reduce_Base<T1, T2>:: shuffle(vector<Map_Prot> inp)
{
    vector< vector<pair <T1, T2> > > uj;
    for(size_t i = 0; i< inp.size(); ++i)
    {
        for(size_t j = 0; j<inp[i].get_res().size(); ++j)
        {
            size_t k =0;
            bool talalt = false;
            while (!talalt)
            {
                if(k >= uj.size() || inp[i].get_res()[j].first < uj[k][0].first)
                {
                    vector<pair < T1,T2 > > tmp;
                    tmp.push_back(inp[i].get_res()[j]);
                    uj.insert(uj.begin()+k, tmp);
                    talalt = true;
                }
                else if(inp[i].get_res()[j].first == uj[k][0].first )
                {
                    uj[k].push_back(inp[i].get_res()[j]);
                    talalt = true;
                }

                else
                    ++k;


            }
        }
    }
    shuffled = uj;
}

void Job::Shuffle(){akt_red.shuffle(akt_map);}

void Job::Reduce(){ akt_red.work();}

void Job::write ()
{
    if(akt_output_konfig.where == console)
    {
        for(size_t i = 0; i< akt_red.get_complete().size(); ++i)
            cout << akt_red.get_complete()[i].first << " - - - - " << akt_red.get_complete()[i].second<<endl;
    }
    else
    {
        if(akt_output_konfig.filename.empty())
            throw "Missing output filename";
        ofstream myfile(akt_output_konfig.filename.c_str());
        for(size_t i = 0; i< akt_red.get_complete().size(); ++i)
            myfile << akt_red.get_complete()[i].first << " - - - - " << akt_red.get_complete()[i].second<<endl;
        myfile.close();

    }
}

void Job::Work()
{
    try{Job::beolvas(); Job::distribute(); Job::Map(); Job::Shuffle(); Job::Reduce();}
    catch (char const * p)
        {cout<< p<<endl;}

}








