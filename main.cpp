#include <iostream>
#include "job.h"



using namespace std;

void test1 ()
{
    cout << "test1:  Adatok beolvasasa fajlbol, eredmenyek kiirasa console-ra" << endl<<endl;
    Job proba;
    proba.akt_input_konfig.filename="example1.txt";
    proba.akt_input_konfig.piece_cnt = 2;
    proba.akt_input_konfig.where = file;
    proba.akt_input_konfig.delim = " \n";
    proba.akt_output_konfig.where = console;

    try
    {
        proba.beolvas();
    }
    catch(char const * p)
    {
        cout << p;
    }
    proba.distribute();
    proba.Map();
    proba.Shuffle();
    proba.Reduce();
    proba.write();

}

void test2()
{
    cout << "Adatok beolvasasa parancssorbol, eredmenyek kiirasa fajlba"<<endl;
    Job proba;
    std:: streambuf *backup = std::cin.rdbuf();
    std::ifstream in("example3.txt");
    std::cin.rdbuf(in.rdbuf());

    proba.akt_input_konfig.delim =" \n";
    proba.akt_input_konfig.piece_cnt= 4;
    proba.akt_input_konfig.where = console;
    proba.akt_output_konfig.where= file;
    proba.akt_output_konfig.filename= "test1.txt";
    proba.Work();
    proba.write();
    std::cin.rdbuf(backup);

}


void test3()
{

    cout << "test3: Hibas bemeneti fajlnev" << endl<<endl;
    Job proba;
    proba.akt_input_konfig.filename="example8.txt";
    proba.akt_input_konfig.piece_cnt = 2;
    proba.akt_input_konfig.where = file;
    proba.akt_input_konfig.delim = " \n";
    proba.akt_output_konfig.where = console;
    proba.Work();
    try
    {
        proba.write();
    }
    catch (char const *p)
    {
        cout<<p<<endl;
    }
}

void test4()
{
    cout << "test4: Tulsagosan nagymerteku tordeles" << endl<<endl;
    Job proba;
    proba.akt_input_konfig.filename="example1.txt";
    proba.akt_input_konfig.piece_cnt = 2000000000;
    proba.akt_input_konfig.where = file;
    proba.akt_input_konfig.delim = " \n";
    proba.akt_output_konfig.where = file;
    proba.akt_output_konfig.filename = "test4.txt";

    proba.Work();
    proba.write();
}


void test5()
{
    cout << "test5: Hianyzo kimeneti fajlnev" << endl<<endl;
    Job proba;
    proba.akt_input_konfig.filename="example1.txt";
    proba.akt_input_konfig.piece_cnt = 12;
    proba.akt_input_konfig.where = file;
    proba.akt_input_konfig.delim = " \n";
    proba.akt_output_konfig.where = file;
    proba.Work();
    try
    {
        proba.write();
    }
    catch (char const *p)
    {
        cout<<p<<endl;
    }
}




int main()
{
    cout <<endl<< "Map-Reduce objektummodell mukodeset demonstralo peldaprogram"<<endl<<endl;
    int nr;
//    std:: streambuf *backup = std::cin.rdbuf();
    std::ifstream in("standard_input.txt");
        std::cin.rdbuf(in.rdbuf());

    cout<< "Teszteset szama:";
    while (cin >> nr && nr > 0)
    {
        cout<<endl;
        switch (nr)
        {
        case 4:
            test4();
            break;

        case 1:
            test1();
            break;

        case 2:
            test2();
            break;

        case 3:
            test3();
            break;
        case 5:
            test5();
            break;

        default:
            cout << "Ilyen teszteset nem letezik" << endl;

        }
        cout << endl;
    }

    return 0;
}
