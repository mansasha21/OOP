#include "ChromaKeyer.hpp"

ChromaKeyer::ChromaKeyer() :lower(LOWERGREEN), upper(UPPERGREEN) {}

cv::Mat ChromaKeyer::apply(const cv::Mat& srcImg, const cv::Mat& backImg)
{
	cv::Mat backCopy;
	backImg.copyTo(backCopy);
	cv::resize(backCopy, backCopy, cv::Size(srcImg.cols, srcImg.rows));
	cv::Mat substractedImg = eraseBack(srcImg);
	cv::Mat result;
	backCopy.copyTo(result, mask);
	result += substractedImg;
	return result;
}

cv::Mat ChromaKeyer::eraseBack(const cv::Mat& srcImg)
{
	const int sigmaX = 1;
	cv::Mat srcHSV, result;
	cv::cvtColor(srcImg, srcHSV, cv::COLOR_BGR2HSV);
	inRange(srcHSV, lower, upper, mask);
	srcImg.copyTo(result, ~mask);
	return result;
}

cv::Mat ChromaKeyer::eraseBack()
{
	if (src.empty())
		throw std::invalid_argument("empty image");
	return eraseBack(src);
}


void ChromaKeyer::setThreshholds(const cv::Vec3i& lower_, const cv::Vec3i& upper_)
{
	lower = lower_;
	upper = upper_;
}

void ChromaKeyer::setBackgroound(const cv::Mat& back_)
{
	cv::Mat backCopy;
	back_.copyTo(backCopy);
	back = backCopy;
}

void ChromaKeyer::setSource(const cv::Mat& src_)
{
	cv::Mat srcCopy;
	src_.copyTo(srcCopy);
	src = src_;
}

cv::Mat ChromaKeyer::apply()
{
	if (src.empty() || back.empty())
		throw std::invalid_argument("empty image");
	return apply(src, back);
}






