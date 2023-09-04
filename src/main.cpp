#include "opencv4/opencv2/opencv.hpp"	

#include <chrono>
#include <iostream> 
#include <opencv2/videoio.hpp>
#include <thread> 
#include <string> 

#include "video_ascii.h"
#include "image_ascii.h"

int main(int argc, char* argv[])
{
	// TODO: move these away from main
	if (argc < 2)
	{
		std::cerr << "err: no input path" << std::endl; 
		return 1; 
	}

	if (argc != 3)
	{
		std::cerr << "err: missing file format specifier" << std::endl; 
		std::cerr << "-v for video formats" << std::endl; 
		std::cerr << "-i for image formats" << std::endl; 
		return 1;
	}

	if (strcmp(("-v"),argv[2]) == 0)
	{
		cv::VideoCapture cv_video = cv::VideoCapture(argv[1]);
		
		if (!cv_video.isOpened())
		{
			std::cerr << "err: invalid video path" << std::endl; 
			return 1;
		}

		Video2Ascii Renderer = Video2Ascii(cv_video);

		//TODO: either find a library to do this for me, or figure out how to add the correct path to the output/create a file for the output
		system("ffplay -loglevel quiet -autoexit -window_title \"ASCII Video Player\" ~/Downloads/output.wav &"); 

		if (Renderer.render_to_console() == 1)
		{
			std::cerr << "err: video conversion failed" << std::endl; 
			return 1; 
		}
	}

	if (strcmp(("-i"),argv[2]) == 0)
	{
		cv::Mat cv_image = cv::imread(argv[1]);

		if (cv_image.empty())
		{	
			std::cerr << "err: invalid image path" << std::endl; 
			return 1; 
		}

		Image2Ascii Renderer = Image2Ascii(cv_image);

		if (Renderer.render_to_console() == 1)
		{
			std::cerr << "err: image conversion failed" << std::endl; 
			return 1; 
		}
	}
	
	return 0; 
}



