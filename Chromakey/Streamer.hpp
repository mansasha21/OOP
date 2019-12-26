#pragma once
#include "opencv2/opencv.hpp"
#include <vector>
#include <string>

class Streamer final
{
public:
	Streamer();
	cv::Mat read(const std::string& name) const;
	std::vector<cv::Mat> read(const std::vector<std::string>& names) const;
	void write(const std::string& filename, const cv::Mat& img) const;
	void write(const std::vector<std::string>& fileNames, const std::vector<cv::Mat>& imgs) const;
};

