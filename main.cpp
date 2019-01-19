#include "tgaimage.h"
#include <cstdlib>
#include "model.h"
#include "point.h"
#include "math.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
Model *model = NULL;
const int width  = 1600;
const int height = 1600;
Point* light = new Point(0,0,1);

void line(Point* p0,Point* p1, TGAImage &image, TGAColor color) {
    int x0 = p0->getX();
	int y0 = p0->getY();
	int x1 = p1->getX();
	int y1 = p1->getY();
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
	double derror2 = std::abs(dy)*2;
    int error2 = 0;
	double y = y0;
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

void triangle(Point* p0,Point* p1,Point* p2, TGAImage &image, TGAColor color) {
    
    if (p0->getY() >p1->getY()) std::swap(p0, p1); 
    if (p0->getY() >p2->getY()) std::swap(p0, p2); 
    if (p1->getY() >p2->getY()) std::swap(p1, p2); 

    int total_height = p2->getY()-p0->getY(); 
    if(total_height != 0){
        for (int y=p0->getY(); y< p2->getY(); y++) {
            bool moitie = y < p1->getY() ;
			int segment_height;
            if(moitie){
                segment_height = p1->getY()-p0->getY();
            }else{
                segment_height = p2->getY()-p1->getY();
            } 
			double a = (double)(y-p0->getY())/total_height;
			double b;
			int aBis = p0->getX() + (p2->getX()-p0->getX())*a;
			int bBis;
            if(moitie){
                b = (double)(y-p0->getY())/segment_height;
                bBis = p0->getX() + (p1->getX()-p0->getX())*b;
            }else{
                b = (double)(y-p1->getY())/segment_height;
                bBis = p1->getX() + (p2->getX()-p1->getX())*b; 
            } 
            if (aBis>bBis) std::swap(aBis, bBis); 
            for (int i=aBis; i<=bBis; i++) {
                image.set(i, y, color);
            } 
        }
    }else{
        line(p0,p1,image,color);
        line(p1,p2,image,color);
        line(p0,p2,image,color);
    } 
}

int main(int argc, char** argv) {
    if (2==argc) {
        model = new Model(argv[1]);
    } else {
        model = new Model("african_head.obj");
    }

    TGAImage image(width, height, TGAImage::RGB);
	std::vector<double> pos = model->getTabPos();
	int v0;
	int v1;
	int v2;
        Point* v;
        Point* w;
        Point* n;
		Point* p0;
		Point* p1;
		Point* p2;
        double intensite;
        for (int i=0; i<model->getTab().size(); i = i+3) {
				v0 = (model->getTab()[i]-1)*3;
				v1 = (model->getTab()[i + 1]-1)*3;
				v2 = (model->getTab()[i + 2]-1) * 3;
				p0 = new Point((pos.at(v0)),(pos.at(v0+1)),pos.at(v0+2));
                p1 = new Point((pos.at(v1)),(pos.at(v1+1)),pos.at(v1+2));
                p2 = new Point((pos.at(v2)),(pos.at(v2+1)),pos.at(v2+2));
                
                v = new Point(p1->getX()-p0->getX(),p1->getY()-p0->getY(),p1->getZ()-p0->getZ());
                w = new Point(p2->getX()-p1->getX(),p2->getY()-p1->getY(),p2->getZ()-p1->getZ());

				//Cross product
				double surfaceNormale[3];
				surfaceNormale[0] = (v->getY()*w->getZ())-(v->getZ()*w->getY());
				surfaceNormale[1] = (v->getZ()*w->getX())-(v->getX()*w->getZ());
				surfaceNormale[2] = (v->getX()*w->getY())-(v->getY()*w->getX());

				//Calculate norme :
				double norme = sqrtl(surfaceNormale[0] * surfaceNormale[0] + surfaceNormale[1] * surfaceNormale[1] + surfaceNormale[2] * surfaceNormale[2]);
				surfaceNormale[0] = surfaceNormale[0] / norme;
				surfaceNormale[1] = surfaceNormale[1] / norme;
				surfaceNormale[2] = surfaceNormale[2] / norme;

                intensite = surfaceNormale[0]*light->getX() + surfaceNormale[1]*light->getY()+ surfaceNormale[2]*light->getZ();

                if(intensite >0) triangle(p0->toRatio(width,height), p1->toRatio(width, height),p2->toRatio(width, height), image,  TGAColor(intensite*255, intensite*255, intensite*255, 255));
    }

    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
    delete model;
    return 0;
}