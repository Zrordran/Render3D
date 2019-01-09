#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <vector>
#include <string.h> 
#include "model.h"



Model::Model(const char *file){
    std::ifstream myfile (file);
    std::string line;
    if (myfile.is_open()){
        while (!myfile.eof()) {
            std::getline(myfile, line);
            std::istringstream iss(line);
            std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
                                 std::istream_iterator<std::string>());
            for(int i=0;i<results.size();i++){
                if(i==0 && results[i]=="v"){
                //std::string token = results[i].substr(0, results[i].find("/"));
                //std::cout<<token<< '\n'; 
                //tab.push_back(token);
                    std::cout<<results[i+1]<< " "; std::cout<<results[i+2] << " "; std::cout<<results[i+3]<< '\n'; 
                   DRLUYTRE tab.push_back(results[i]);
                //std::cout<<results[i]<< '\n'; 
                }
            }
        }
    myfile.close();
    }else{
        std::cout<<"probleme lecture";
    }
    //return tab;
}

Model::~Model() {
}

std::vector<std::string> Model::getTab(){
    return tab;
}