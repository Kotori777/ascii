#include "opencv4/opencv2/opencv.hpp"	

#include <iostream> 
#include <thread> 
#include <string> 

std::string pixel_to_ascii(int pixel_intensity)
{
	const std::string chars = " .,-+=!|$&%#08@"; 
 
	return std::string(1, chars[(pixel_intensity * chars.length()) / 256]); 
}

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cerr << "err: no input path" << std::endl; 
		return 1; 
	}
	
	cv::Mat image = cv::imread(argv[1]);

	if (image.empty())
	{	
		std::cerr << "err: invalid path" << std::endl; 
		return 1; 
	}
	
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

	cv::Size target_res(720, 460); // example size for testing, can be changed later. Maybe should be a thing that you can choose at command line. 				       
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
			std::string v = pixel_to_ascii(resized_image.at<uchar>(x, y)); // okay?  
			std::cout << v; 
		}
		std::cout << std::endl; 
	}

	return 0; 
}


