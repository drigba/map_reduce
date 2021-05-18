#ifndef JOB_H_INCLUDED
#define JOB_H_INCLUDED
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string.h>
#include <sstream>
using namespace std;

enum honnanhova {console, file};
vector<string> split (string mit,  string delim, size_t darab=0);

template <typename T>
class Map_Base
{
//protected:
    vector<string> splitted;
    vector<T> result;

public:

    virtual T key_val(string data)=0;
    void splitter (string data, string delim = " \n")
    {
        splitted =  split(data,delim);
    }
    void mapper()
    {
        for(typename vector<string> :: iterator it = splitted.begin(); it!= splitted.end(); ++it )
            result.push_back(key_val(*it));
    }
    vector <T> get_res()
    {
        return result;
    }
    vector<string> get_split()
    {
        return splitted;
    }

};

class Map_Prot : public Map_Base<pair<int,int> >
{
public:
    pair<int,int> key_val(string data)
    {
        int first = data.size();
        if(first != 0)
        {
            if(!isalnum(data[data.size()-1]))
                first--;
            if(!isalnum(data[0]))
                first--;
        }

        return make_pair(first,1);
    }
};

/*class Map_Prot : public Map_Base<pair<int,int> >
{
public:
    pair<int,int> key_val(string data)
    {
        int first=0;
        if(data.size() == 2)
            first = 2;
        if(data.size() == 3 && (!isalnum(data[data.size()-1]) || !isalnum(data[0])))
            first =2;
        if(data.size() == 4 && !isalnum(data[data.size()-1]) && !isalnum(data[0]))
            first =2;


        return make_pair(first,1);
    }
};*/

/*class Map_Prot : public Map_Base<pair<string,int> >
{
public:
    pair<string,int> key_val(string data)
    {
        return make_pair(data,1);
    }
};*/



template <typename T1, typename T2>
class Reduce_Base
{
protected:
    vector<vector<pair<T1,T2> > > shuffled;
    vector<pair<T1, T2> > complete;
public:
    void shuffle (vector<Map_Prot> inp);                                                    //ELVILEG KÉSZ

    virtual pair<T1, T2> reduce (const vector<pair<T1,T2> >  input)=0;
    void work()
    {
        for(typename vector<vector<pair<T1,T2> > > :: iterator it = shuffled.begin(); it!= shuffled.end(); ++it )
            complete.push_back(reduce(*it));
    }
    vector<pair<T1, T2> > get_complete()
    {
        return complete;
    }

};


class Reduce_Prot: public Reduce_Base<int, int>
{
    pair<int, int> reduce (const vector <pair<int, int> > input)
    {
        return make_pair(input[0].first, (input.end()-input.begin()));
    }
};

/*class Reduce_Prot: public Reduce_Base<string, int>
{
    pair<string, int> reduce (const vector <pair<string, int> > input) {return make_pair(input[0].first, (input.end()-input.begin()));}
};*/



class InputKonfig
{
public:
    honnanhova where;
    string filename;
    size_t piece_cnt;
    string delim;
};

class OutputKonfig
{
public:
    honnanhova where;
    string filename;
};


class Job
{
    vector<Map_Prot > akt_map;
    Reduce_Prot akt_red;
    vector<string> input;
public:
    InputKonfig akt_input_konfig;
    OutputKonfig akt_output_konfig;
    void beolvas();                         // KÉSZ    ELLENŐRIZVE
    void distribute();                      // KÉSZ    ELLENŐRIZVE
    void write();                           // KÉSZ    ELLENŐRIZVE
    void Map();                             // KÉSZ    ELLENŐRIZVE
    void Shuffle();                         // KÉSZ    NEGATÍV EREDMÉNYEK
    void Reduce();                          // KÉSZ    ELLENŐRIZVE
    void Work();                            // KÉSZ
    vector<string> get_input (){return input;}


};




#endif // JOB_H_INCLUDED
