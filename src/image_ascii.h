#pragma once

#include "opencv2/opencv.hpp"

class Image2Ascii
{
	public: 
		Image2Ascii(cv::Mat& cv_image) 
			: image(cv_image)
		{}

		~Image2Ascii()
		{}

		int render_to_console(); 
	private: 
		cv::Mat image; 
};


