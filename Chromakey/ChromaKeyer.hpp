#pragma once
#include "opencv2/opencv.hpp"

class ChromaKeyer final
{
	cv::Vec3i lower, upper;
	cv::Size kernelSize;
	cv::Mat mask;
	cv::Mat src, back;
public:
	const static inline cv::Vec3i UPPERGREEN{ 110, 255, 255 };
	const static inline cv::Vec3i LOWERGREEN{ 20, 100, 100 };
	
	ChromaKeyer();
	void setThreshholds(const cv::Vec3i& lower, const cv::Vec3i& upper);
	void setSource(const cv::Mat& src);
	void setBackgroound(const cv::Mat& back);
	cv::Mat eraseBack(const cv::Mat& srcImg);
	cv::Mat eraseBack();
	cv::Mat apply(const cv::Mat& srcImg, const cv::Mat& backImg);
	cv::Mat apply();
};
