#include "Streamer.hpp"
#include "Logger.hpp"

Streamer::Streamer()
{
	Logger::getInstance();
}


cv::Mat Streamer::read(const std::string& name) const
{
	return cv::imread(name);
}

std::vector<cv::Mat> Streamer::read(const std::vector<std::string>& names) const
{
	std::vector<cv::Mat> res;
	for (auto i : names)
		res.emplace_back(cv::imread(i));
	return res;
}

void Streamer::write(const std::string& filename, const cv::Mat& img) const
{
	if (!cv::imwrite(filename, img))
		Logger::getInstance() << filename + " wasn`t written\n";
	Logger::getInstance() << filename + " was written\n";
}

void Streamer::write(const std::vector<std::string>& fileNames, const std::vector<cv::Mat>& imgs) const
{
	for (auto i = 0; i < imgs.size(); ++i) {
		if(i >= fileNames.size())
			write(fileNames.back(), imgs[i]);
		else
			write(fileNames[i], imgs[i]);
	}
}



