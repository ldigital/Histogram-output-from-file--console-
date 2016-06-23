#include <iostream>
#include <fstream>
#include <string.h>
#include <readfile.h>
#include <iomanip>
#include <sstream>

/*Initialise two-dimensional array to start from bottom to top vertical, and left to right horizontal for the histogram */
readfile::readfile(): _maxDays(50), _numberOfEmployees(11){

    for(int i = _maxDays; i >= 0; i--){ //set vertical from bottom to top
        for(int j = 0; j < _numberOfEmployees; j++){ //set horizontal from left to right
             _hist[i][j] = ' ';
        }
    }
}

void readfile::read(){
    /*1.read all data from file
      2.search relevant information; employee name and absent days
      3.store the data-structure data to be used in histogram
    */
    std::ifstream file("staff absent days report.txt"); //file for fstream needs to be in build directory of qt... not project directory as normal

    if(! file.is_open()){
        std::cout << "could not open file -- exiting" << std::endl;
    }

    while(file >> _data){ //once file open, loop through all of its contents and copy to data variable.
        for(unsigned int i = _data.find("employee:", 0); i != std::string::npos; i = _data.find("employee:", i)){
            i++;
            getline(file, _data);
            _store.name = _data.substr(i, 8);
        }

        for(unsigned int i = _data.find("days:", 0); i != std::string::npos; i = _data.find("days:", i)){
            i++;
            _store.days = _data.substr(i+4, 3);
        }
        _vec.push_back(_store);  //store all relevant data based on what was found
    }
    /*the data in the days part of the structure at this point is currently a string. Therefore;
      1. read data from 'days' and convert it to an integer
      2. use integer variable 'stringNum' for iteration value, to create column
      3. when finished column, move to next 'days' record, to create row
     */
    int stringNum;

    for(unsigned int i = 0; i < _vec.size(); i++){
        std::istringstream(_vec[i].days) >> stringNum;
        for(unsigned int j = 0; j < stringNum; j++){
            _hist[j][i] = '*';
        }
    }

}

void readfile::display(){
    std::cout << "  Annual staff absent days histogram report:\n\n";

    for(int i = _maxDays-1; i >= 0; i--){
        std::cout << std::setw(2) << i+1 <<"|";
        for(int j = 0; j < _numberOfEmployees; j++){
            std::cout <<"         " << _hist[i][j];
        }
        std::cout << "\n";
    }

    //horizontal name display from vector
    std::cout << "  ";

    for(unsigned int i = 0; i < _vec.size(); i++){
        std::cout << "  " <<_vec[i].name;
    }
      std::cout << "\n\n\n";
}
