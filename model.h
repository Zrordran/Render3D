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
        std::vector<int> tab;
	std::vector<float> tabPos;
public:
	Model(const char *filename);
	~Model();
    std::vector<int> getTab();
	std::vector<float> getTabPos();
};

#endif //__MODEL_H__
