#include "video_ascii.h"

int Video2Ascii::render_to_console()
{
	cv::Mat frame; 
	
	if (!video.isOpened())
	{
		std::cerr << "err: video could not be opened" << std::endl; 
		return 1; 
	}
	
	const long frame_dur = 1000/140;; 

	std::cout << "ms" << frame_dur; 

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

		const int WIDTH = 760; 
		const int HEIGHT = 180; 

		const cv::Size target_res(WIDTH, HEIGHT); 			       
		
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
		else		
		{
			resized_frame = grayscale_frame.clone(); 
		} 

		/* create buffer */ 

		std::string print_buffer; 

		for (int x = 0; x != resized_frame.rows; x++)
		{
			for(int y = 0; y != resized_frame.cols; y++)
			{
				auto ascii_char = [pixel_intensity = resized_frame.at<uchar>(x, y), &print_buffer]()
				{
					const std::string chars = " .,-+=!|$&%#08@"; 
 
					print_buffer += std::string(1, chars[(pixel_intensity * chars.length()) / 256]); 
				};

				ascii_char(); 
			}
			print_buffer += "\n";
		}
		
		// hide cursor find a better solution
		system("printf \"\\e[?25l\" ");
		
		system("clear"); 

		std::cout << print_buffer;

		std::this_thread::sleep_for(std::chrono::milliseconds(frame_dur));
	}
	
	system("printf \"\\e[?25h\" ");

	return 0; 
}
