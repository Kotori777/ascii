#pragma once

#include "opencv2/opencv.hpp"
#include <thread>
#include <chrono>

class Video2Ascii
{
	public:
		Video2Ascii(cv::VideoCapture& cv_video) 
			: video(cv_video) 
		{} 

		~Video2Ascii(){};

		int render_to_console();
	private:
		cv::VideoCapture video; 
}; 
