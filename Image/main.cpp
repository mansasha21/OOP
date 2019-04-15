#include "Image.hpp"
#include <opencv2/highgui.hpp>
#include <string>
#include <iostream>

using namespace cv;
int main(int argc, char** argv) {
	std::string filename;
	if (argc > 1) {
		 filename=argv[1];
	}
	else {
		return 2;
	}
	Image img1;
	img1.load(filename);
	Image nimg1(4500, 4100), nimg2(4500, 4100), nimg(4500, 4100);
	Mat nimg11, nimg22, nimg33;
	Mat nimg111, nimg222, nimg333;
	nimg11 = imread(filename);
	nimg33 = imread(filename);
	nimg22 = imread(filename);
	Size size(4500, 4100);
	resize(nimg11, nimg111, size, 0, 0, 1);
	resize(nimg22, nimg222, size, 0, 0, INTER_CUBIC);
	resize(nimg33, nimg333, size, 0, 0, INTER_LANCZOS4);
	img1.resize(nimg2, 2, InterpolationFuncs::Lanz);
	img1.resize(nimg1, 2, InterpolationFuncs::bicubic);
	img1.resize(nimg, 1,  InterpolationFuncs::linear);
	imwrite("ocvL.jpg", nimg111);
	imwrite("ocvB.jpg", nimg222);
	imwrite("ocvLa.jpg", nimg333);
	nimg1.save(filename+"bicubic.jpg");
	nimg.save(filename + "linear.jpg");
	nimg2.save(filename + "lanz.jpg");
	waitKey(0);
	return 0;
}