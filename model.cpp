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
	std::string token;
    if (myfile.is_open()){
        while (!myfile.eof()) {
            std::getline(myfile, line);
            std::istringstream iss(line);
            std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
                                 std::istream_iterator<std::string>());
            for(int i=0; i < results.size() ;i = i+4){
                if(results[i]=="f"){
					token = results[i+1].substr(0, results[i+1].find("/"));
					tab.push_back(std::stoi(token));
					token = results[i + 2].substr(0, results[i + 2].find("/"));
					tab.push_back(std::stoi(token));
					token = results[i + 3].substr(0, results[i + 3].find("/"));
					tab.push_back(std::stoi(token));
					//tab.push_back(token);
                   //std::cout<<results[i+1]<< " "; std::cout<<results[i+2] << '\n'; 
                //std::cout<<results[i]<< '\n'; 
                }
				if (results[i] == "v") {
					tabPos.push_back(std::stod(results[i + 1]));
					tabPos.push_back(std::stod(results[i + 2]));
					tabPos.push_back(std::stod(results[i + 3]));

					//std::cout << tabPos.at(0) << "-" << tabPos.at(1) << '\n';
					//tab.push_back(token);
				   //std::cout<<results[i+1]<< " "; std::cout<<results[i+2] << '\n'; 
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

std::vector<int> Model::getTab(){
    return tab;
}

std::vector<double> Model::getTabPos() {
	return tabPos;
}