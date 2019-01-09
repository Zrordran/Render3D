#ifndef __MODEL_H__
#define __MODEL_H__

#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <vector>
#include <string.h> 

//#include <vector>
//#include "geometry.h"

class Model {
private:
        std::vector<std::string> tab;
public:
	Model(const char *filename);
	~Model();
        std::vector<std::string> getTab();
};

#endif //__MODEL_H__
