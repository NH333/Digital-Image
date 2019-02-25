#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main(){
	Mat srcImg = imread("C:/Users/NH3/Desktop/project2/1/PandD.jpg");
	Mat midImg,dstImg;
	medianBlur(srcImg,srcImg,9);
	//GaussianBlur(srcImg,srcImg,Size(9,9),2,2);
	Canny(srcImg,midImg,50,200,3);
	
	cvtColor(midImg,dstImg,CV_GRAY2BGR);
	namedWindow("canny",CV_WINDOW_NORMAL);
	namedWindow("gray", CV_WINDOW_NORMAL);
	//namedWindow("Gauss",CV_WINDOW_NORMAL);
	
	imshow("canny", midImg);
	imshow("gray",dstImg);

	//GaussianBlur(midImg, midImg, Size(9, 9), 2, 2);
	//Canny(midImg, midImg, 50, 200, 3);
	imshow("gauss", midImg);

	vector<Vec2f> lines;                              
	HoughLines(midImg, lines, 1, CV_PI / 180, 54, 0);/*把阈值设置成54就刚好还能检测出最短的那条蓝线*/
													 /*阈值为150的时候可以不通过设置斜率就可以很好的把蓝线和红线检测出来*/
	for (size_t i = 0; i < lines.size(); i++){
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		pt1.x = cvRound(x0 + 1000 * (-b));            /*对直线进行延伸*/
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 2000 * (-b));
		pt2.y = cvRound(y0 - 2000 * (a));

		/*通过a的值，可以估计出蓝线斜率的大致范围*/
		if ((a > (-0.810) && a<(-0.808) )){
			line(srcImg, pt1, pt2, Scalar(0, 255, 0), 0.5, LINE_AA);
		}
		/*else {
			line(srcImg, pt1, pt2, Scalar(255, 0, 0), 0.5, LINE_AA);
		}*/
	}


	namedWindow("dst", CV_WINDOW_NORMAL);
	imshow("dst", srcImg);

	waitKey(0);
}