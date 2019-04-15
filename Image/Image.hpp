#pragma once
#include <opencv2/imgproc.hpp>

class Image final{
public:
	typedef double(*PFN_INTERPOLATE) (double);

	Image(void) = default;
	Image(size_t w, size_t h);
	bool load(const std::string& path);
	bool save(const std::string& name)const;
	const cv::Mat& image() const;
	void  resize(
		Image & output,
		size_t w,
		PFN_INTERPOLATE f
	) const;
private:
	cv::Mat _image;
};

namespace InterpolationFuncs {
	double linear(double x);
	double bicubic(double x);
	double Lanz(double x);
}
