#ifndef READFILE_H
#define READFILE_H

#include <fstream>
#include <vector>

struct info{
    std::string name;
    std::string days;
};

class readfile{

public:
    readfile();
    ~readfile(){}

    void read();
    void display();

private:
    //this variable contains streamed data from ifstream
    std::string _data;
    //this stores the data found in search to be sent to the vector
    info _store;
    //this store's the all information that has been collected
    std::vector<info> _vec;
    const int _maxDays; //50
    const int _numberOfEmployees; //11
    char _hist[50][11];
};

#endif
