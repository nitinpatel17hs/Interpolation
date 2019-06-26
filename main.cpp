#include <opencv2/core/core.hpp> 
#include <opencv2/highgui/highgui.hpp> 
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>

using namespace cv;
using namespace std;


Mat src1 = imread("apple.jpg"); 
Mat src2;
Mat src3,src4;
Point P1, P2;
int a = 1;




class Parallel_process : public cv::ParallelLoopBody
{

private:
	cv::Mat img;
	cv::Mat& retVal;
	int size;
	int diff;

public:
	Parallel_process(cv::Mat inputImgage, cv::Mat& outImage,
		int sizeVal, int diffVal)
		: img(inputImgage), retVal(outImage),
		size(sizeVal), diff(diffVal) {}

	virtual void operator()(const cv::Range& range) const
	{
		//src4 = Mat::zeros(Size(img.cols * a, img.rows * a), CV_8UC3);
		for (int i = range.start; i < range.end; i++)
		{
			/* divide image in 'diff' number
			of parts and process simultaneously */

			cv::Mat in(img, cv::Rect(0, (img.rows / diff) * i,
				img.cols, img.rows / diff));
			cv::Mat out(retVal, cv::Rect(0, (retVal.rows / diff) * i,
				retVal.cols, retVal.rows / diff));
			resize(in, out, Size(0, 0), (double)a, (double)a, INTER_LANCZOS4);

			//src4(cv::Rect(0, (retVal.rows / diff) * i,
				//retVal.cols, retVal.rows / diff)) = out.clone();
		}
	}
};


void onMouse(int event, int x, int y, int flags, void* userdata)
{
	Mat img = *((Mat*)userdata);

	if (event == EVENT_LBUTTONDOWN)
	{
		if ((a != 1))
		{
			P1 = Point(x, y);
			//cout << P1;
			P2 = Point(a * x, a * y);
			/*if((P2.x+src1.cols/2 < a*src1.cols)&&(P2.y + src1.rows / 2 < a * src1.rows)&&(P2.x-src1.cols/2>0)&&(P2.y-src1.rows/2>0))
				src3 = src2(cv::Rect(P2.x - src1.cols / 2, P2.y - src1.rows / 2, src1.cols, src1.rows));
			else*/ 

			//---------------*** if Point Chosen in Left Top corner ***-------
			if((P2.x - src1.cols / 2 < 0)&&(P2.y - src1.rows / 2 > 0)&&(P2.x + src1.cols / 2 < src2.cols)&&(P2.y + src1.rows / 2 < src2.rows))
				src3 = src2(cv::Rect(0, P2.y - src1.rows / 2 , src1.cols, src1.rows));
			else if((P2.x - src1.cols / 2 > 0)&&(P2.y - src1.rows / 2 < 0) && (P2.x + src1.cols / 2 < src2.cols) && (P2.y + src1.rows / 2 < src2.rows))
				src3 = src2(cv::Rect(P2.x - src1.cols / 2, 0, src1.cols, src1.rows));
			else if((P2.x - src1.cols / 2 > 0) && (P2.y - src1.rows / 2 > 0) && (P2.x + src1.cols / 2 < src2.cols) && (P2.y + src1.rows / 2 < src2.rows))
				src3 = src2(cv::Rect(P2.x - src1.cols / 2, P2.y - src1.rows / 2, src1.cols, src1.rows));
			else if ((P2.x - src1.cols / 2 < 0) && (P2.y - src1.rows / 2 < 0) && (P2.x + src1.cols / 2 < src2.cols) && (P2.y + src1.rows / 2 < src2.rows))
				src3 = src2(cv::Rect(0, 0 , src1.cols, src1.rows));
			//--------------------


			//---------------** if point chosen in right bottom corner **---------------
			else if((P2.x - src1.cols / 2 > 0) && (P2.y - src1.rows / 2 > 0) && (P2.x + src1.cols / 2 > src2.cols) && (P2.y + src1.rows / 2 < src2.rows))
				src3 = src2(cv::Rect(a*src1.cols-(3/2)*src1.cols, P2.y - src1.rows / 2, src1.cols , src1.rows));
			else if ((P2.x - src1.cols / 2 > 0) && (P2.y - src1.rows / 2 > 0) && (P2.x + src1.cols / 2 < a * src1.cols) && (P2.y + src1.rows / 2 > a * src1.rows))
				src3 = src2(cv::Rect(P2.x - src1.cols / 2, (a-3/2)*src1.rows , src1.cols, src1.rows));
			else if ((P2.x - src1.cols / 2 > 0) && (P2.y - src1.rows / 2 > 0) && (P2.x + src1.cols / 2 > a * src1.cols) && (P2.y + src1.rows / 2 > a * src1.rows))
				src3 = src2(cv::Rect(a * src1.cols - (3 / 2) * src1.cols, (a - 3 / 2) * src1.rows, src1.cols, src1.rows));
			else if ((P2.x - src1.cols / 2 > 0) && (P2.y - src1.rows / 2 > 0) && (P2.x + src1.cols / 2 < a * src1.cols) && (P2.y + src1.rows / 2 < a * src1.rows))
				src3 = src2(cv::Rect(P2.x - src1.cols / 2, P2.y - src1.rows / 2, src1.cols, src1.rows));
			//-----------------------
			
			//--------------------*****  Taking Care of other two corners  *****-------------
			else if ((P2.x - src1.cols / 2 < 0)&&(P2.y - src1.rows / 2 > 0)&&(P2.y + src1.rows / 2 < a * src1.rows))
				src3 = src2(cv::Rect(0 , P2.y - src1.rows / 2, src1.cols, src1.rows));
			else if ((P2.x - src1.cols / 2 < 0) && (P2.y - src1.rows / 2 > 0) && (P2.y + src1.rows / 2 > a * src1.rows))
				src3 = src2(cv::Rect(0, (a-3/2)*src1.rows , src1.cols, src1.rows));
			else if ((P2.x - src1.cols / 2 > 0) && (P2.y - src1.rows / 2 < 0) && (P2.x+src1.cols/2 > src2.cols))
				src3 = src2(cv::Rect((a-3/2)*src1.cols, 0 , src1.cols, src1.rows));
			else if ((P2.x - src1.cols / 2 > 0) && (P2.y - src1.rows / 2 < 0) && (P2.x + src1.cols / 2 < src2.cols))
				src3 = src2(cv::Rect(P2.x - src1.cols / 2, 0, src1.cols, src1.rows));
			//-------------------------	

			imshow("DST", src3);
		}

	}
}




int main()
{
	namedWindow("ORI", WINDOW_NORMAL);
	imshow("ORI", src1);
	
	namedWindow("DST", WINDOW_NORMAL);
	createTrackbar("zoom", "DST", &a, 50);



	int a_last = -1;
	while (1)
	{
		int px = 0, py = 0;
		if (a < 1)
			break;
		// INTER_NEAREST    INTER_LINEAR   INTER_AREA    INTER_CUBIC     INTER_LANCZOS4
		
		//src2 = cv::Mat::zeros(Size(src1.cols * a, src1.rows * a), CV_8UC3);

		//-----------*************
		resize(src1, src2, Size(0, 0), (double)a, (double)a, INTER_LANCZOS4);
		//***---------------------
		//imwrite("Grain.tif", src2);

		/*src2 = imread("src2.jpg");*/

		/*imshow("src2", src2);
		imshow("src4", src4);*///waitKey(0);

		//src2 = src4.clone();

		setMouseCallback("ORI", onMouse, &src1); 

		if (a_last != a)
		{
			//-----
			while (1)
			{
				char t = waitKey(33);
				if (t == 'w' && py >= 10)
				{
					py -= 10;
					src3 = src2(cv::Rect(px, py, src1.cols, src1.rows));
					imshow("DST", src3);
				}

				if (t == 's' && py <= src2.rows - src1.rows - 10)
				{
					py += 10;
					src3 = src2(cv::Rect(px, py, src1.cols, src1.rows));
					imshow("DST", src3);
				}

				if (t == 'd' && px <= src2.cols - src1.cols - 10)
				{
					px += 10;
					src3 = src2(cv::Rect(px, py, src1.cols, src1.rows));
					imshow("DST", src3);
				}

				if (t == 'a' && px >= 10)
				{
					px -= 10;
					src3 = src2(cv::Rect(px, py, src1.cols, src1.rows));
					imshow("DST", src3);
				}

				if (t == 'e')
					break;
			}

		}

		//----
		a_last = a;
		char c = waitKey(33);
		if (c == 'q')
			break;
	}


	
	
	//waitKey(0);
	return(0);
}
