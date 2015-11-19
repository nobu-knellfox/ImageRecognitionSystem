// これは メイン DLL ファイルです。

#include "stdafx.h"
#include "ImageRecognitionSystemCpp.h"
#include <opencv2/core/core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\opencv.hpp>
#include <string>


cv::Mat Algorithm1(cv::Mat screen, cv::Mat temp,int index);
std::string MarshalString(String ^ s);

void DrawRectangle(cv::Mat& img, std::vector<cv::Rect>& maxpt, cv::Scalar color);
void TemplateMatch(cv::Mat screen, cv::Mat t_img, cv::Mat& result);
void SearchMatch(const cv::Mat& result, float threshold, std::vector<cv::Rect>& maxpt, cv::Mat t_img);

void ImageRecognitionSystemCpp::ImageRecognition::Recognition(String ^ screen_file, String ^ template_file,int index)
{
	cv::Mat a = cv::imread(MarshalString(screen_file));
	cv::Mat b = cv::imread(MarshalString(template_file));

	cv::imshow("result",Algorithm1(a,b,index));
}

cv::Mat Algorithm1(cv::Mat screen,cv::Mat temp,int index)
{
	std::vector<cv::Mat> s_plane;
	std::vector<cv::Mat> t_plane;

	cv::split(screen,s_plane);
	cv::split(temp, t_plane);

	cv::Mat result;

	cv::Mat show = screen.clone();

	TemplateMatch(s_plane[index], t_plane[index], result);

	cv::imshow("s_plane", s_plane[index]);
	cv::imshow("t_plane", t_plane[index]);
		
	std::vector<cv::Rect> maxpt;
	maxpt.clear();

	SearchMatch(result, 0.95f, maxpt, temp);
	DrawRectangle(show, maxpt, cv::Scalar(0, 0, 255));
	
	cv::imshow("result_t", result);

	return show;
}

std::string MarshalString(String ^ s) {
	using namespace Runtime::InteropServices;
	std::string os;

	const char* chars =
		(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));

	return os;
}


void DrawRectangle(cv::Mat& img, std::vector<cv::Rect>& maxpt, cv::Scalar color)
{
	for (auto x : maxpt) {
		cv::rectangle(img, cv::Point(x.x, x.y), cv::Point(x.x + x.width, x.y + x.height), color, 2, 8, 0);
	}
}

void TemplateMatch(cv::Mat screen, cv::Mat t_img, cv::Mat& result)
{
	cv::matchTemplate(screen, t_img, result, cv::TM_CCOEFF_NORMED);
}

void SearchMatch(const cv::Mat& result, float threshold, std::vector<cv::Rect>& maxpt, cv::Mat t_img)
{
	for (int y = 0; y < result.rows; ++y) {
		for (int x = 0; x < result.cols; ++x) {
			if (result.at<float>(y, x) > threshold) {
				maxpt.push_back(cv::Rect(x, y, t_img.cols, t_img.rows));
			}
		}
	}
}