#include <opencv2/highgui.hpp>
#include <iostream>
#include "Image.hpp"
#define _USE_MATH_DEFINES
#include<math.h>
using namespace std;
using namespace cv;

Image::Image(size_t w, size_t h):_image(h,w, CV_8UC3, Scalar(0, 0, 0)){}
bool Image::load(const string &path) {
	_image = imread(path);
	if (_image.empty())
		return false;
	return true;
}
bool Image::save(const string &name)const {
	if (_image.empty())
		return false;
	imwrite(name, _image);
	return true;
}
const Mat& Image::image() const {
	return _image;
}

void  Image::resize(Image & output, size_t w, PFN_INTERPOLATE f) const {
	if (output._image.empty()) {
		return ;
	}
	const double h_rate = static_cast<double> (output._image.rows) / static_cast<double>(_image.rows);
	const double w_rate = static_cast<double> (output._image.cols) / static_cast<double> (_image.cols);
	for (int newy = 0; newy < output._image.rows; newy++) {
		for (int  newx = 0;  newx < output._image.cols;  newx++) {
			int oldx =  newx / w_rate;
			int oldy = newy / h_rate;
			Vec3b fxy=(0,0,0);
			for (int i = 0; i < w * 2; i++) {
				for (int j = 0; j < w * 2; j++) {
					if (oldx+i > _image.cols-1  || oldy+j > _image.rows-1)
						break;
					const Vec3b p = _image.at<Vec3b>(oldy+j, oldx+i);
					fxy += p * f(static_cast<double>(oldx + i) - static_cast<double>( newx) / w_rate)*f(static_cast<double>(oldy + j) - static_cast<double>(newy) / h_rate);
				}
			}
			output._image.at<Vec3b>(newy,  newx) = fxy;
		}
	}
}
namespace InterpolationFuncs {
	double linear(double x) {
		return fabs(x) < 1.0 ? 1.0 - fabs(x) : 0.0;
	}
	double bicubic(double x) {
		double xf = fabs(x);
		if (xf < 1)
			return (0.5 * (xf*xf - 1)*(xf - 2));
		else if (1 < xf && xf < 2) {
			return ((-1 / 6)*(xf - 1)*(xf - 2)*(xf - 3));
		}
		else
			return 0.0;
	}
	double Lanz(double x) {
		if (x == 0)
			return 1.0;
		else if (fabs(x) < 2)
			return 2 * sin(M_PI*x)*sin(M_PI*x / 2) / (M_PI*M_PI*x*x);
		else
			return 0.0;
	}
}
