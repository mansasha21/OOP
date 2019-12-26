#include "Application.h"
#include "Logger.hpp"

Application::Application(){}

bool Application::setBackground(const std::string& backName)
{
	return setBackground(streamer.read(backName));
}

bool Application::setBackground(const cv::Mat& background)
{
	if (background.empty())
	{
		Logger::getInstance() << "Back wasnt set";
		return false;
	}
	chromaKeyer.setBackgroound(background);
	return true;
}

void Application::trackBar(int, void* obj)
{
	auto app = static_cast<Application*> (obj);
	app->chromaKeyer.setThreshholds(app->lower, app->upper);
	app->gui.drawImg(app->chromaKeyer.eraseBack());
	if(app->ready2Apply)
	{
		cv::Mat res = app->chromaKeyer.apply();
		app->gui.drawImg(res);
		app->streamer.write(app->output, res);
	}
}

void Application::start(const std::string& srcName, const std::string& backName, const std::string& output_)
{
	lower = ChromaKeyer::LOWERGREEN, upper = ChromaKeyer::UPPERGREEN;
	output = output_;
	cv::Mat src = streamer.read(srcName);
	cv::Mat back = streamer.read(backName);
	if(src.empty() || back.empty())
	{
		return;
	}
	gui.drawTrackbars(lower, upper, ready2Apply, this);
	chromaKeyer.setBackgroound(back);
	chromaKeyer.setSource(src);
	chromaKeyer.setThreshholds(lower, upper);
	trackBar(0, this);
	cv::waitKey();
	if(ready2Apply)
	{
		return;
	}
	streamer.write(output,chromaKeyer.apply());
}

