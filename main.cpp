#include <iostream>
#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"

using namespace cv;
using namespace std;
static const char ASCIIARRAY[] = { '@', '#', '%', '&', '+', '*', ';', ':', ',', '.', '\`', ' ' };

char getASCIIbyRGB(uchar* rgb)
{
	return ASCIIARRAY[(int)((rgb[0] + rgb[1] + rgb[2]) / 67)];
}

int main(int argc, const char** argv)
{
	VideoCapture capture(0);

	if (!capture.isOpened())
		return -1;

	while (true)
	{
		Mat originFrame;

		if (!capture.read(originFrame))
			return -1;

		Mat imgHSV = originFrame.clone();
		imgHSV.setTo(Scalar::all(255));

		std::string txt = "";

		float xpad = originFrame.cols / 45;
		float ypad = originFrame.rows / 32;
		float xsize = cv::getTextSize("@", 1, 1, 1, 0).width;

		for (int y = 0; y < originFrame.rows - ypad; y += ypad)
		{
			for (int x = 0; x < originFrame.cols - xpad; x += xpad)
			{
				txt += getASCIIbyRGB(originFrame.ptr(y, x));
			}
			for (int i = 0; i < txt.size(); i++)
			{
				cv::putText(imgHSV, string(1, txt.at(i)), Point(i * xsize, 10 + (y * 1)), 1, 1, Scalar::all(0));
			}
			txt.clear();
		}

		imshow("ASCII ART", imgHSV);
		imshow("Original", originFrame);

		if (waitKey(30) == 27)
			break;
	}

	return 0;
}