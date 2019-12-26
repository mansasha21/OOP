#include "GUI.hpp"
#include "Application.h"

GUI::GUI()
{
	cv::namedWindow(mainWindowName, cv::WINDOW_GUI_EXPANDED);
	cv::namedWindow(tracbarName, cv::WINDOW_GUI_EXPANDED);
}

void GUI::drawImg(cv::Mat img) const
{
	if (img.empty())
		return;
	cv::imshow(mainWindowName, img);
}

void GUI::drawTrackbars(cv::Vec3i& lower, cv::Vec3i& upper, int& ready2Apply, void* userdata)
{
	cv::createTrackbar("lower Hue", tracbarName, &lower[0], 255, Application::trackBar, userdata);
	cv::createTrackbar("lower Sat", tracbarName, &lower[1], 255, Application::trackBar, userdata);
	cv::createTrackbar("lower Val", tracbarName, &lower[2], 255, Application::trackBar, userdata);
	cv::createTrackbar("Upper Hue", tracbarName, &upper[0], 255, Application::trackBar, userdata);
	cv::createTrackbar("Upper Sat", tracbarName, &upper[1], 255, Application::trackBar, userdata);
	cv::createTrackbar("Upper Val", tracbarName, &upper[2], 255, Application::trackBar, userdata);
	cv::createTrackbar("Apply", tracbarName, &ready2Apply, 1, Application::trackBar, userdata);
}
