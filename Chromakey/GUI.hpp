#pragma once

#include <string>
#include <opencv2//opencv.hpp>


class GUI final
{
	const std::string tracbarName{ "TrackBars" };
	const std::string mainWindowName{ "Chromakey" };
public:
	GUI();
	void drawTrackbars(cv::Vec3i& lower, cv::Vec3i& upper, int& ready2Apply, void* userdata);
	void drawImg(cv::Mat img) const;
};
