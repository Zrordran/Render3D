#include "tgaimage.h"
#include <cstdlib>
#include "model.h"
#include "point.h"
#include "math.h"
#include "geometry.h"
#include <algorithm>
#include <time.h>

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
	double derror2 = (double)std::abs(dy)*2;
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

Vec3f barycentre(Point* vectors[], Vec3f p) {
	Vec3f s[2];
	Vec3f tmp(vectors[2]->getX() - vectors[0]->getX(), vectors[1]->getX() - vectors[0]->getX(), vectors[0]->getX() - p.x);
	s[0] = tmp;
	Vec3f tmp2(vectors[2]->getY() - vectors[0]->getY(), vectors[1]->getY() - vectors[0]->getY(), vectors[0]->getY() - p.y);
	s[1] = tmp2;

	float u[3]; //cross product entre s[0] et s[1]
	u[0] = s[0][1] * s[1][2] - s[0][2] * s[1][1];
	u[1] = s[0][2] * s[1][0] - s[0][0] * s[1][2];
	u[2] = s[0][0] * s[1][1] - s[0][1] * s[1][0];

	if (std::abs(u[2]) > 1e-2) { // dont forget that u[2] is integer. If it is zero then triangle ABC is degenerate
		Vec3f barycentre = { 1.f - (u[0] + u[1]) / u[2] ,u[1] / u[2],u[0] / u[2] };
		return barycentre;
	}
	else {
		Vec3f barycentre = { -1,1,1 };
		return barycentre;
	}
}

void triangleV2(Point* p0, Point* p1, Point* p2, float *zbuffer, TGAImage &image, TGAColor color) {

	Vec2f bboxmin(std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
	Vec2f bboxmax(-std::numeric_limits<float>::max(), -std::numeric_limits<float>::max());
	Vec2f clamp(width - 1, height - 1);
	Point *vectors[3];
	vectors[0] = p0; vectors[1] = p1; vectors[2] = p2;

	for (int i = 0; i < 3; i++) {
		bboxmin[0] = std::max(0.f, std::min(bboxmin[0], (float)vectors[i]->getX()));
		bboxmax[0] = std::min(clamp[0], std::max(bboxmax[0], (float)vectors[i]->getX()));
		bboxmin[1] = std::max(0.f, std::min(bboxmin[1], (float)vectors[i]->getY()));
		bboxmax[1] = std::min(clamp[1], std::max(bboxmax[1], (float)vectors[i]->getY()));
	}

	Vec3f p;
	Vec3f barycen;
	for (p.x = bboxmin[0]; p.x <= bboxmax[0]; p[0]++) {
		for (p.y = bboxmin[1]; p.y <= bboxmax[1]; p[1]++) {
			barycen = barycentre(vectors, p);
			if (barycen.x < 0 || barycen.y < 0 || barycen.z < 0) {
				continue;
			}
			p.z = 0;
			for (int i = 0; i < 3; i++) {
				p.z += vectors[i]->getZ() * barycen[i];
			}
			if (zbuffer[int(p.x + p.y * width)] < p.z) {
				zbuffer[int(p.x + p.y * width)] = p.z;
				image.set(p.x, p.y, color);
			}
		}
	}
}

int main(int argc, char** argv) {
	if (2 == argc) {
		model = new Model(argv[1]);
	}
	else {
		model = new Model("african_head.obj");
	}
	TGAImage image(width, height, TGAImage::RGB);

	float *zbuffer = new float[width*height];
	for (int i = 0; i < width*height; i++) {
		zbuffer[i] = -std::numeric_limits<float>::max();
	}

	std::vector<float> pos = model->getTabPos();
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
	for (int i = 0; i < model->getTab().size(); i = i + 3) {
		v0 = (model->getTab()[i] - 1) * 3;
		v1 = (model->getTab()[i + 1] - 1) * 3;
		v2 = (model->getTab()[i + 2] - 1) * 3;
		p0 = new Point((pos.at(v0)), (pos.at(v0 + 1)), pos.at(v0 + 2));
		p1 = new Point((pos.at(v1)), (pos.at(v1 + 1)), pos.at(v1 + 2));
		p2 = new Point((pos.at(v2)), (pos.at(v2 + 1)), pos.at(v2 + 2));

		v = new Point(p1->getX() - p0->getX(), p1->getY() - p0->getY(), p1->getZ() - p0->getZ());
		w = new Point(p2->getX() - p1->getX(), p2->getY() - p1->getY(), p2->getZ() - p1->getZ());

		//Cross product
		double surfaceNormale[3];
		surfaceNormale[0] = (v->getY()*w->getZ()) - (v->getZ()*w->getY());
		surfaceNormale[1] = (v->getZ()*w->getX()) - (v->getX()*w->getZ());
		surfaceNormale[2] = (v->getX()*w->getY()) - (v->getY()*w->getX());

		//Calculate norme :
		double norme = sqrtl(surfaceNormale[0] * surfaceNormale[0] + surfaceNormale[1] * surfaceNormale[1] + surfaceNormale[2] * surfaceNormale[2]);
		surfaceNormale[0] = surfaceNormale[0] / norme;
		surfaceNormale[1] = surfaceNormale[1] / norme;
		surfaceNormale[2] = surfaceNormale[2] / norme;

		intensite = surfaceNormale[0] * light->getX() + surfaceNormale[1] * light->getY() + surfaceNormale[2] * light->getZ();

		if (intensite > 0) triangleV2(p0->toRatio(width, height), p1->toRatio(width, height), p2->toRatio(width, height), zbuffer, image, TGAColor(intensite * 255, intensite * 255, intensite * 255, 255));
	}
	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");
	delete model;
	return 0;
}