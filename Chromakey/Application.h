#pragma once
#include "GUI.hpp"
#include "Streamer.hpp"
#include "ChromaKeyer.hpp"


class Application final
{
	int ready2Apply;
	std::string output;
	GUI gui;
	Streamer streamer;
	ChromaKeyer chromaKeyer;
	cv::Vec3i lower, upper;
public:
	Application();
	bool setBackground(const std::string& backName);
	bool setBackground(const cv::Mat& back);
	void start(const std::string& srcName, const std::string& backName, const std::string& output_ = "output.jpg");
	static void trackBar(int, void*);
};

