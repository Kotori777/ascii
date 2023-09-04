#include "image_ascii.h"

int Image2Ascii::render_to_console()
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

	std::string print_buffer; 

	//For some reason x and y are mixed up????!?!?!?!?!?!??!?!?>!?!?!?! thanks opencv :(
	for (int x = 0; x != resized_image.rows; x++)
	{
		for(int y = 0; y != resized_image.cols; y++)
		{
			auto ascii_char = [pixel_intensity = resized_image.at<uchar>(x, y), &print_buffer]()
			{
				const std::string chars = " .,-+=!|$&%#08@"; 

				print_buffer += std::string(1, chars[(pixel_intensity * chars.length()) / 256]); 
			};

			ascii_char(); 
		}
		print_buffer += "\n"; 
	}

	std::cout << print_buffer;

	return 0; 
}

