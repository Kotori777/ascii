#include "opencv4/opencv2/opencv.hpp"	

#include <chrono>
#include <iostream> 
#include <opencv2/videoio.hpp>
#include <thread> 
#include <string> 

std::string fn_pixel_to_ascii(int pixel_intensity)
{
	const std::string chars = " .,-+=!|$&%#08@"; 
 
	return std::string(1, chars[(pixel_intensity * chars.length()) / 256]); 
}

int fn_image_2_ascii(cv::Mat& image)
{
	/* MAKING NEW IMAGE TO GRAYSCALE*/

	cv::Mat grayscale_image;

	if (image.channels() == 3)
	{
		try 
		{
			cv::cvtColor(image, grayscale_image, cv::COLOR_RGB2GRAY); 	
		}
		catch (cv::Exception e)
		{
			std::cerr << "err: " << e.what() << std::endl; 
			return 1; 
		}
	}
	else
	{
		grayscale_image = image.clone();
	}

	/* MAKE NEW IMAGE TO TARGET RES*/

	cv::Size target_res(1440, 1080); // example size for testing, can be changed later. Maybe should be a thing that you can choose at command line. 				       
	cv::Mat resized_image; 

	if (grayscale_image.size() != target_res)
	{
		try
		{
			cv::resize(grayscale_image, resized_image, target_res);
		}
		catch (cv::Exception e)
		{
			std::cerr << "err: " << e.what() << std::endl;
			return 1; 
		}
	}
	else // should have error handling here but oh well I guess :)
	{
		resized_image = grayscale_image.clone(); 
	}

	/* PRINT ASCII ART TO SCREEN */ 

	//For some reason x and y are mixed up????!?!?!?!?!?!??!?!?>!?!?!?! thanks opencv :(
	for (int x = 0; x != resized_image.rows; x++)
	{
		for(int y = 0; y != resized_image.cols; y++)
		{
			std::string v = fn_pixel_to_ascii(resized_image.at<uchar>(x, y)); // okay?  
			std::cout << v; 
		}
		std::cout << std::endl; 
	}

	return 0; 
}

int fn_video_2_ascii(cv::VideoCapture& video)
{
	cv::Mat frame; 

	if (!video.isOpened())
	{
		std::cerr << "err: video could not be opened" << std::endl; 
		return 1; 
	}

	while (video.read(frame))
	{
		cv::Mat grayscale_frame;

		if (frame.channels() == 3)
		{
			try 
			{
				cv::cvtColor(frame, grayscale_frame, cv::COLOR_RGB2GRAY); 	
			}
			catch (cv::Exception e)
			{
				std::cerr << "err: " << e.what() << std::endl; 
				return 1; 
			}
		}
		else
		{
			grayscale_frame = frame.clone();
		}

		/* MAKE NEW FRAME TO TARGET RES*/

		cv::Size target_res(720, 460); 			       
		
		cv::Mat resized_frame; 

		if (grayscale_frame.size() != target_res)
		{
			try
			{
				cv::resize(grayscale_frame, resized_frame, target_res);
			}
			catch (cv::Exception e)
			{
				std::cerr << "err: " << e.what() << std::endl;
				return 1; 
			}
		}
		else		{
			resized_frame = grayscale_frame.clone(); 
		}

		/* PRINT ASCII FRAME TO SCREEN */ 

		for (int x = 0; x != resized_frame.rows; x++)
		{
			for(int y = 0; y != resized_frame.cols; y++)
			{
				std::string v = fn_pixel_to_ascii(resized_frame.at<uchar>(x, y)); 				 
			}
			std::cout << std::endl; 
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(133)); 

		system("clear"); 
	}

	return 1; 
}

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

		if (fn_video_2_ascii(cv_video) == 1)
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

		if (fn_image_2_ascii(cv_image) == 1)
		{
			std::cerr << "err: image conversion failed" << std::endl; 
			return 1; 
		}
	}
	
	return 0; 
}



