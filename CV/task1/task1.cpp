#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cv.h>
//using namespace cv;
//using namespace std;

/*
int main(int argc, char** argv)
{
    Mat src_image = imread("1.jpg"); //Загрузить изображение с диска
    Mat Ai = src_image;
    Mat Ti;
    Mat AiTidiff;
    while(!Ai.empty())
    {
        
    }
    imshow( "Skeleton", AiTidiff);
    waitKey( 0 ); //Ждем нажатия клавиши
}
*/
double alpha = 3; /**< Simple contrast control */
int beta = 0;  /**< Simple brightness control */

int main()
{
    cv::Mat image = cv::imread("1.jpg"); //загрузка входного изображения
    /*
    //imshow( "Input image", image );
    std::vector<cv::Mat> planes;
    cv::split( image, planes );
    cv::Mat gray;
    */
    //cv::Mat gray = /*0.299*/0.741*planes[2] + /*0.587*/0.756*planes[1] + /*0.114*/0.752*planes[0];
    /*    
    double thresh = 10.0; //Порог, подбирается опытным путем
    cv::threshold( planes[0], gray, thresh, 255.0, CV_THRESH_BINARY | CV_THRESH_OTSU);
    cv::namedWindow("Threshold", cv::WINDOW_NORMAL);
    cv::resizeWindow("Threshold", 1920, 1080);
    cv::imshow( "Threshold", gray );
    */
    cv::Mat new_image = cv::Mat::zeros( image.size(), image.type() );

    /// Do the operation new_image(i,j) = alpha*image(i,j) + beta
    for( int y = 0; y < image.rows; y++ )
    { 
        for( int x = 0; x < image.cols; x++ )
        { 
            for( int c = 0; c < 3; c++ )
            {
                new_image.at<cv::Vec3b>(y,x)[c] =
                    cv::saturate_cast<uchar>( alpha*( image.at<cv::Vec3b>(y,x)[c] ) + beta );
            }
        }
    }

    /// Create Windows
    cv::namedWindow("Original Image", cv::WINDOW_NORMAL);
    cv::resizeWindow("Original Image", 1920, 1080);
    cv::namedWindow("New Image", cv::WINDOW_NORMAL);
    cv::resizeWindow("New Image", 1920, 1080);

    /// Show stuff
    cv::imshow("Original Image", image);
    cv::imshow("New Image", new_image);

    cv::waitKey( 0 ); //Ждем нажатия клавиши
}


