#include<opencv2/opencv.hpp>
#include<iostream>
#include<stdio.h>


using namespace cv;
using namespace std;

Mat HistogramEqual(Mat Img);  //ֱ��ͼ���⻯
Mat ZhongZhi(Mat Img);        //��ֵ�˲�

Mat JunZhi(Mat Img);          //��ֵ�˲�
Mat LaShi(Mat Img);

void DrawHist(Mat Img);

double Mask(int x, int y, Mat Img);

int main(){
	Mat Img = imread("C:/Users/NH3/Desktop/����ͼ����/image1-1.jpg",1);
	Mat Img2 = imread("C:/Users/NH3/Desktop/����ͼ����/image4.jpg",1);
	Mat Img3 = imread("C:/Users/NH3/Desktop/����ͼ����/image2-2.gif", 1);
	Mat test;
	Mat test1;
	
	Mat test_zhong = ZhongZhi(Img2);
	imshow("zhong", test_zhong);

	test = JunZhi(Img2);
	namedWindow("��ֵ�˲�", CV_WINDOW_AUTOSIZE);
	imshow("��ֵ�˲�", test);


	Mat Out;
	Mat Out_ = Img; 
	cvtColor(Out_, Out_, CV_BGR2GRAY);
	Out = HistogramEqual(Img);
	equalizeHist(Out_, Out_);
	
	DrawHist(Out_);
	//equalizeHist(Out, Out);

	
	namedWindow("�仯ǰ",CV_WINDOW_NORMAL);
	namedWindow("�仯��_OpenCV�Դ�������ֱ��ͼ����", CV_WINDOW_NORMAL);
	namedWindow("�仯��_�ҵ�ֱ��ͼ����", CV_WINDOW_NORMAL);
	imshow("�仯ǰ",Img);
	imshow("�仯��_�ҵ�ֱ��ͼ����", Out);
	imshow("�仯��_OpenCV�Դ�������ֱ��ͼ����", Out_);
	
	waitKey(0);
	return 0;

	//cvEqualizeHist(Img, Out);
}


Mat HistogramEqual(Mat Img){
	Mat Out = Img;
	int ImgSize = Img.cols * Img.rows;  
	double Gray_Level_New[256];         //����µĻҶȼ�
	int GrayVal_Add[256];				//��Ÿ����Ҷ�ֵ�ĸ���
	double P[256];						//��Ÿ����Ҷ�ֵ��ռ�ı��� Ҳ���Ǹ���


	cvtColor(Out, Out, CV_BGR2GRAY);     

	/*��ʼ��������*/
	int idx = 0;
	for (int i = 0; i < 256; i++){
		GrayVal_Add[i] = 0;
		P[i] = 0;
		Gray_Level_New[i] = 0;

	}


	/*ͳ��ÿ���Ҷ�ֵ�ĸ���*/
	for (int i = 0; i < Img.rows; i++)
		for (int j = 0; j < Img.cols; j++){
			GrayVal_Add[Out.ptr<uchar>(i)[j]] += 1;
		}

	for (int i = 0; i < 256; i++){
		P[i] = (double)GrayVal_Add[i] / ImgSize;
	}


	/*�����µĻҶȼ��������*/
	double sum = 0;
	for (int i = 0; i < 256; i++){

		sum += P[i];
		Gray_Level_New[i] = sum * 255;
	}

	/*���*/
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
	copyMakeBorder(Img, Img2_Border, 1, 1, 1, 1, BORDER_CONSTANT, cv::Scalar(0, 0, 0)); //��ͼ��������䣬��ͼ���Ե����һȦ�Ҷ�Ϊ0�����ص�

	for (int i = 1; i < Img2_Border.rows - 1; i++)
		for (int j = 1; j < Img2_Border.cols - 1; j++){
			/* ����3*3����ģ   ����д�û��Ǻܳ� */
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
	copyMakeBorder(Img, Img2_Border, 1, 1, 1, 1, BORDER_CONSTANT, cv::Scalar(0, 0, 0)); //��ͼ��������䣬��ͼ���Ե����һȦ�Ҷ�Ϊ0�����ص�
	int A[9];
	int temp = 0;
	//namedWindow("1");
	//imshow("1", Img2_Border);
	for (int i = 1; i < Img2_Border.rows - 1; i++){
		for (int j = 1; j < Img2_Border.cols - 1; j++){

			/* ����3*3����ģ ������A[]���洢��ģ�ĻҶ�ֵ */ 
			/* ����д���е�� ���Ӷȸ� */
			A[0] = Img2_Border.ptr<uchar>(i - 1)[j - 1];
			A[1] = Img2_Border.ptr<uchar>(i - 1)[j];
			A[2] = Img2_Border.ptr<uchar>(i - 1)[j + 1];
			A[3] = Img2_Border.ptr<uchar>(i)[j - 1];
			A[4] = Img2_Border.ptr<uchar>(i)[j];
			A[5] = Img2_Border.ptr<uchar>(i)[j + 1];
			A[6] = Img2_Border.ptr<uchar>(i + 1)[j - 1];
			A[7] = Img2_Border.ptr<uchar>(i + 1)[j];
			A[8] = Img2_Border.ptr<uchar>(i + 1)[j + 1];

			/**************  ��������  ***************/
			for (int m = 0; m<9; m++)
				for (int n = m; (j>0 && A[n]<=A[n - 1]); n--){
					temp = A[n - 1];
					A[n - 1] = A[n];
					A[n] = temp;
				}
			Img2_Border.ptr<uchar>(i)[j] = A[4]; //ѡ����ֵ
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


/*******�ο����˵�***************/
void DrawHist(Mat Img){
	Mat Out;
	//���庯����Ҫ��һЩ����
	//ͼƬ����nimages
	int nimages = 1;
	
	int channels[1] = { 0 };
	//���ֱ��ͼ
	cv::Mat outputHist;
	//ά��
	int dims = 1;
	//���ÿ��ά��ֱ��ͼ�ߴ磨bin������������histSize
	int histSize[1] = { 256 };
	//ÿһά��ֵ��ȡֵ��Χranges
	float hranges[2] = { 0, 255 };
	//ֵ��Χ��ָ��
	const float *ranges[1] = { hranges };
	//�Ƿ����
	bool uni = true;
	//�Ƿ��ۻ�
	bool accum = false;

	calcHist(&Img, nimages, channels, Mat(), Out, dims, histSize, ranges, uni, accum);

	//����ֱ��ͼ
	int scale = 1;
	//ֱ��ͼ��ͼƬ
	cv::Mat histPic(histSize[0] * scale, histSize[0], CV_8U, cv::Scalar(255)); \
		//�ҵ����ֵ����Сֵ
		double maxValue = 0;
	double minValue = 0;
	cv::minMaxLoc(Out, &minValue, &maxValue, NULL, NULL);
	double rate = (histSize[0] / maxValue)*0.9;

	for (int i = 0; i < histSize[0]; i++)
	{
		//�õ�ÿ��i�����ӵ�ֵ
		float value = Out.at<float>(i);
		//��ֱ��
		cv::line(histPic, cv::Point(i*scale, histSize[0]), cv::Point(i*scale, histSize[0] - value*rate), cv::Scalar(0));
	}
	cv::imshow("histgram", histPic);

	return ;
}