#include<opencv2/opencv.hpp>
#include<iostream>
#include<stdio.h>


using namespace cv;
using namespace std;

Mat HistogramEqual(Mat Img);  //直方图均衡化
Mat ZhongZhi(Mat Img);        //中值滤波

Mat JunZhi(Mat Img);          //均值滤波
Mat LaShi(Mat Img);

void DrawHist(Mat Img);

double Mask(int x, int y, Mat Img);

int main(){
	Mat Img = imread("C:/Users/NH3/Desktop/数字图像处理/image1-1.jpg",1);
	Mat Img2 = imread("C:/Users/NH3/Desktop/数字图像处理/image4.jpg",1);
	Mat Img3 = imread("C:/Users/NH3/Desktop/数字图像处理/image2-2.gif", 1);
	Mat test;
	Mat test1;
	
	Mat test_zhong = ZhongZhi(Img2);
	imshow("zhong", test_zhong);

	test = JunZhi(Img2);
	namedWindow("均值滤波", CV_WINDOW_AUTOSIZE);
	imshow("均值滤波", test);


	Mat Out;
	Mat Out_ = Img; 
	cvtColor(Out_, Out_, CV_BGR2GRAY);
	Out = HistogramEqual(Img);
	equalizeHist(Out_, Out_);
	
	DrawHist(Out_);
	//equalizeHist(Out, Out);

	
	namedWindow("变化前",CV_WINDOW_NORMAL);
	namedWindow("变化后_OpenCV自带函数的直方图均衡", CV_WINDOW_NORMAL);
	namedWindow("变化后_我的直方图均衡", CV_WINDOW_NORMAL);
	imshow("变化前",Img);
	imshow("变化后_我的直方图均衡", Out);
	imshow("变化后_OpenCV自带函数的直方图均衡", Out_);
	
	waitKey(0);
	return 0;

	//cvEqualizeHist(Img, Out);
}


Mat HistogramEqual(Mat Img){
	Mat Out = Img;
	int ImgSize = Img.cols * Img.rows;  
	double Gray_Level_New[256];         //存放新的灰度级
	int GrayVal_Add[256];				//存放各个灰度值的个数
	double P[256];						//存放各级灰度值所占的比列 也就是概率


	cvtColor(Out, Out, CV_BGR2GRAY);     

	/*初始化各参数*/
	int idx = 0;
	for (int i = 0; i < 256; i++){
		GrayVal_Add[i] = 0;
		P[i] = 0;
		Gray_Level_New[i] = 0;

	}


	/*统计每个灰度值的个数*/
	for (int i = 0; i < Img.rows; i++)
		for (int j = 0; j < Img.cols; j++){
			GrayVal_Add[Out.ptr<uchar>(i)[j]] += 1;
		}

	for (int i = 0; i < 256; i++){
		P[i] = (double)GrayVal_Add[i] / ImgSize;
	}


	/*建立新的灰度级别的数组*/
	double sum = 0;
	for (int i = 0; i < 256; i++){

		sum += P[i];
		Gray_Level_New[i] = sum * 255;
	}

	/*结果*/
	for (int i = 0; i < Out.rows; i++){
		for (int j = 0; j < Out.cols; j++){
			Out.ptr<uchar>(i)[j] = (int)Gray_Level_New[(int)Out.ptr<uchar>(i)[j]];
		}
	}

	return Out;

}

Mat JunZhi(Mat Img){
	Mat Img2_Border;
	cvtColor(Img, Img, CV_BGR2GRAY);
	copyMakeBorder(Img, Img2_Border, 1, 1, 1, 1, BORDER_CONSTANT, cv::Scalar(0, 0, 0)); //对图像进行扩充，对图像边缘增加一圈灰度为0的像素点

	for (int i = 1; i < Img2_Border.rows - 1; i++)
		for (int j = 1; j < Img2_Border.cols - 1; j++){
			/* 这是3*3的掩模   代码写得还是很臭 */
			Img2_Border.ptr<uchar>(i)[j] = (Img2_Border.ptr<uchar>(i-1)[j-1] + \
				                            Img2_Border.ptr<uchar>(i-1)[j] + \
										    Img2_Border.ptr<uchar>(i-1)[j+1] + \
										    Img2_Border.ptr<uchar>(i)[j-1] + \
										    Img2_Border.ptr<uchar>(i)[j] + \
										    Img2_Border.ptr<uchar>(i)[j+1] + \
										    Img2_Border.ptr<uchar>(i+1)[j-1] + \
										    Img2_Border.ptr<uchar>(i+1)[j] + \
										    Img2_Border.ptr<uchar>(i+1)[j+1])/(9.0);
		}
	return Img2_Border;
}

Mat ZhongZhi(Mat Img){
	Mat Img2_Border;
	cvtColor(Img, Img, CV_BGR2GRAY);
	copyMakeBorder(Img, Img2_Border, 1, 1, 1, 1, BORDER_CONSTANT, cv::Scalar(0, 0, 0)); //对图像进行扩充，对图像边缘增加一圈灰度为0的像素点
	int A[9];
	int temp = 0;
	//namedWindow("1");
	//imshow("1", Img2_Border);
	for (int i = 1; i < Img2_Border.rows - 1; i++){
		for (int j = 1; j < Img2_Border.cols - 1; j++){

			/* 这是3*3的掩模 用数组A[]来存储掩模的灰度值 */ 
			/* 代码写得有点臭 复杂度高 */
			A[0] = Img2_Border.ptr<uchar>(i - 1)[j - 1];
			A[1] = Img2_Border.ptr<uchar>(i - 1)[j];
			A[2] = Img2_Border.ptr<uchar>(i - 1)[j + 1];
			A[3] = Img2_Border.ptr<uchar>(i)[j - 1];
			A[4] = Img2_Border.ptr<uchar>(i)[j];
			A[5] = Img2_Border.ptr<uchar>(i)[j + 1];
			A[6] = Img2_Border.ptr<uchar>(i + 1)[j - 1];
			A[7] = Img2_Border.ptr<uchar>(i + 1)[j];
			A[8] = Img2_Border.ptr<uchar>(i + 1)[j + 1];

			/**************  插入排序  ***************/
			for (int m = 0; m<9; m++)
				for (int n = m; (j>0 && A[n]<=A[n - 1]); n--){
					temp = A[n - 1];
					A[n - 1] = A[n];
					A[n] = temp;
				}
			Img2_Border.ptr<uchar>(i)[j] = A[4]; //选择中值
		}
		
	}
	return Img2_Border;
}




/*
double Mask(int x, int y,Mat Img){
	double temp;
	temp = Img.ptr<uchar>(x)[y];
	for (int i = x - 1; i < x + 2; i++)
		for (int j = y - 1; j < y + 2; j++){
			
			Img.ptr<uchar>(x)[y] += (double)Img.ptr<uchar>(i)[j] ;
		}
	Img.ptr<uchar>(x)[y] = ((double)Img.ptr<uchar>(x)[y] - temp ) / 9.0;

	return Img.ptr<uchar>(x)[y];
}*/


/*******参考别人的***************/
void DrawHist(Mat Img){
	Mat Out;
	//定义函数需要的一些变量
	//图片数量nimages
	int nimages = 1;
	
	int channels[1] = { 0 };
	//输出直方图
	cv::Mat outputHist;
	//维数
	int dims = 1;
	//存放每个维度直方图尺寸（bin数量）的数组histSize
	int histSize[1] = { 256 };
	//每一维数值的取值范围ranges
	float hranges[2] = { 0, 255 };
	//值范围的指针
	const float *ranges[1] = { hranges };
	//是否均匀
	bool uni = true;
	//是否累积
	bool accum = false;

	calcHist(&Img, nimages, channels, Mat(), Out, dims, histSize, ranges, uni, accum);

	//画出直方图
	int scale = 1;
	//直方图的图片
	cv::Mat histPic(histSize[0] * scale, histSize[0], CV_8U, cv::Scalar(255)); \
		//找到最大值和最小值
		double maxValue = 0;
	double minValue = 0;
	cv::minMaxLoc(Out, &minValue, &maxValue, NULL, NULL);
	double rate = (histSize[0] / maxValue)*0.9;

	for (int i = 0; i < histSize[0]; i++)
	{
		//得到每个i和箱子的值
		float value = Out.at<float>(i);
		//画直线
		cv::line(histPic, cv::Point(i*scale, histSize[0]), cv::Point(i*scale, histSize[0] - value*rate), cv::Scalar(0));
	}
	cv::imshow("histgram", histPic);

	return ;
}