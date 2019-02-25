#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

int main(){
	Mat srcImg = imread("C:/Users/NH3/Desktop/project2/1/PandD.jpg");
	Mat hsvImg;
	cvtColor(srcImg,hsvImg,CV_RGB2HSV);
	
	


	medianBlur(srcImg, srcImg, 5);
	

	Mat gryImg,midImg;
	//Canny(srcImg, midImg, 50, 200, 3);
	//imshow("canny",midImg);
	namedWindow("medianBlur", CV_WINDOW_NORMAL);
	imshow("medianBlur", srcImg);

	cvtColor(srcImg, midImg, COLOR_BGR2GRAY);
	
	GaussianBlur(midImg,midImg,Size(9,9),2,2);
	namedWindow("guass", CV_WINDOW_NORMAL);
	imshow("guass", midImg);
	Canny(midImg, midImg, 10, 250, 5);
	namedWindow("canny", CV_WINDOW_NORMAL);
	imshow("canny", midImg);
	

	vector<Vec3f> circles;
	vector<Mat> H;

	split(hsvImg, H);
	//imshow("H", H[0]);
	Mat h0Img = H[0];
	
	char text[16];
	int diffValue = 100; /*用来区分硬币种类的，HSV通道H的阈值*/
	int GrayNum = 0;
	int YellowNum = 0;

	HoughCircles(midImg,circles,HOUGH_GRADIENT,1,120,100,40,10,120);

	for (size_t i = 0; i < circles.size(); i++){
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		int temp = h0Img.ptr<uchar>(center.y)[center.x];
		//sprintf_s(text,"(%d,%d)",center.x,center.y);
		if (temp < diffValue){
			GrayNum++;
			sprintf_s(text, "silver", center.x, center.y);
			putText(srcImg, text, Point(center.x, center.y), FONT_HERSHEY_PLAIN, 2, cv::Scalar(0, 0, 255), 3, 8);
		}
		else{
			YellowNum++;
			sprintf_s(text, "coppery ", center.x, center.y);
			putText(srcImg, text, Point(center.x, center.y), FONT_HERSHEY_PLAIN, 2, cv::Scalar(0, 0, 255), 3, 8);
		}
		//printf("hsv颜色通道h的值：%d\n",temp);
		//putText(srcImg, text, Point(center.x,center.y),FONT_HERSHEY_PLAIN,2, cv::Scalar(0,0,255),3,8);

		circle(srcImg,center,3,Scalar(0,255,0),-1,8,0);
		if (radius > 30){
			circle(srcImg, center, radius, Scalar(0, 255, 0), 3, 8, 0);
		}
		else{
			circle(srcImg, center, 40, Scalar(0, 255, 0), 3, 8, 0);
		}
	}
	namedWindow("xiaoguo", CV_WINDOW_NORMAL);
	imshow("xiaoguo", srcImg);
	printf("银色银币的数量为:%d枚 \n", GrayNum);
	printf("古铜色银币的数量为:%d枚 \n", YellowNum);

	waitKey(0);
}