#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

int main(int argc, char** argv)
{
    Mat image = imread("apples.jpg"); //Загрузить изображение с диска
    /*
    Mat image2 = 0.3 * image; //image2 попиксельно равен 0.3 * image
    //imshow( "image", image); //Показать изображение
    imshow( "image2", image2);
    */
    //Разделение исходной картинки на три канала - channels[0], channels[1], channels[2]
    std::vector<Mat> channels;
    split( image , channels );
    //Показываем каналы в отдельных окнах
    //Обратите внимание, что красный канал - 2, а не 0
    imshow( "Red", channels[2] );
    imshow( "Green", channels[1] );
    imshow( "Blue", channels[0] );
    waitKey( 0 ); //Ждем нажатия клавиши
}
