/*
 * Код для проекта "Шарики"
 */
#include <opencv2/opencv.hpp>


using namespace cv;
using namespace std;

const double OPT_FACTOR = 10;

struct Circle {
	Point speed;
	Point center;
	Scalar color;
	int radius;
};

const int MAX_RADIUS = 40;
const int MIN_RADIUS = 20;
const int CIRCLES_NUM = 70;
int camH;
int camW;


int main( int argc, char** argv )
{

	VideoCapture cap(0); // open the default camera
	if(!cap.isOpened())  // check if we succeeded
		return -1;

	Mat flow, curr, prev, prevBG, currBG, result;
	const char window[] = "Optical flow";
	namedWindow( window, CV_WINDOW_AUTOSIZE );
	cap >> prev;

	camH = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
	camW = cap.get(CV_CAP_PROP_FRAME_WIDTH);

	vector<Circle> circles;
	//initCircles(circles);

//	VideoWriter outputVideo;
//	int ex = static_cast<int>(cap.get(CV_CAP_PROP_FOURCC));     // Get Codec Type- Int form
//    outputVideo.open("output.avi", ex, cap.get(CV_CAP_PROP_FPS), Size(camW, camH), true);


	for(;;)
	{

		cap >> curr; // get a new frame from camera
		cvtColor(curr, currBG, COLOR_BGR2GRAY);
		cvtColor(prev, prevBG, COLOR_BGR2GRAY);
		calcOpticalFlowFarneback(prevBG, currBG, flow, 0.5, 5, 5, 3, 7, 1.5, OPTFLOW_FARNEBACK_GAUSSIAN);
		curr.copyTo(result);

		//moveCircles(circles, flow);
		//drawCircles(circles, result);

		// outputVideo << result;
		//imshow(window, result);
		imshow(window,curr);
		if(waitKey(30) >= 0) break;
		swap(prev, curr);
	}
	return 0;
}



