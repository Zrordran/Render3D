#include "tgaimage.h"
#include <cstdlib>
#include "model.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
Model *model = NULL;
const int width  = 1600;
const int height = 1600;

void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
    bool steep = false;
    if (std::abs(x0-x1)<std::abs(y0-y1)) {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }
    if (x0>x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    int dx = x1-x0;
    int dy = y1-y0;
    int derror2 = std::abs(dy)*2;
    int error2 = 0;
    int y = y0;
    for (int x=x0; x<=x1; x++) {
        if (steep) {
            image.set(y, x, color);
        } else {
            image.set(x, y, color);
        }
        error2 += derror2;
        if (error2 > dx) {
            y += (y1>y0?1:-1);
            error2 -= dx*2;
        }
    }
}

int main(int argc, char** argv) {
    if (2==argc) {
        model = new Model(argv[1]);
    } else {
        model = new Model("african_head.obj");
    }

    TGAImage image(width, height, TGAImage::RGB);
	std::cout<< model->getTab().size() << '\n';
	std::vector<double> pos = model->getTabPos();
	int v0;
	int v1;
	int v2;
    for (int i=0; i<model->getTab().size(); i = i+3) {
        //std::cout<<model->getTab()[i]<< '\n'; 
		//image.set(model->getTab()[i], model->getTab()[i+1], white);

		v0 = (model->getTab()[i]-1)*2;
		v1 = (model->getTab()[i + 1]-1)*2;
		v2 = (model->getTab()[i + 2] - 1) * 2;
		int x0 = (pos.at(v0))*width/2 + width/2;
		int y0 = (pos.at(v0+1))*height/2 + height/2;
		int x1 = (pos.at(v1))*width/2 + width/2;
		int y1 = (pos.at(v1+1))*height/2 + height/2;
		int x2 = (pos.at(v2))*width/2 + width/2;
		int y2 = (pos.at(v2 + 1))*height/2 + height/2;

		line(x0, y0, x1, y1, image, white);
		line(x1, y1, x2, y2, image, white);
		line(x2, y2, x0, y0, image, white);
    }

    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
    delete model;
    return 0;
}