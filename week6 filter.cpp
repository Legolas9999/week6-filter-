#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;

int main() {
	//-----------------------------------------练习1,2,3,4-------------------------------
	Mat frame;      
	Mat median;     //中值滤波
	Mat mean;		//均值滤波
	Mat Gau;		//高斯滤波
	Mat border_y;	//y方向边缘检测
	Mat border_x;	//x方向边缘检测
	
	VideoCapture cap;
	cap.open(0);
	while (1) {
			cap >> frame;
		medianBlur(frame, median, 7);								 //中值滤波
		blur(frame,mean,Size(3,3),Point(-1,-1),BORDER_DEFAULT);		//均值滤波
		GaussianBlur(frame, Gau, Size(3, 3),0,0,BORDER_DEFAULT);	//高斯滤波
		imshow("中值滤波", median);
		imshow("均值滤波",mean);
		imshow("高斯滤波",Gau);
		Sobel(frame,border_y, -1,1,0,3,1,1,BORDER_DEFAULT);			//y方向边缘检测
		Sobel(frame, border_x, -1, 0, 1, 3,1,1,BORDER_DEFAULT);		//x方向边缘检测
		imshow("边缘x",border_x);
		imshow("边缘y", border_y);
		
		//-----------------------------磨皮----------------------------------------------
		//HSV色彩模型：皮肤色彩范围
		double  i_minH = 0;
		double  i_maxH = 20;

		double  i_minS = 43;
		double  i_maxS = 255;

		double  i_minV = 55;
		double  i_maxV = 255;
		Mat detMat_erzhi;		//皮肤二值图皮肤为白色	
		Mat detMat_hsv;			
		Mat color_skin;			//提取皮肤部分
		Mat Gau_skin;			//仅对皮肤部分进行高斯滤波
		Mat res;
		
		cvtColor(frame, detMat_hsv, COLOR_BGR2HSV);			//将摄像头转换色彩模型
		inRange(detMat_hsv, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV), detMat_erzhi);		//将图像二值化，皮肤部分为白色，其余为黑色
		bitwise_and(frame,frame,color_skin,detMat_erzhi);			//与原图进行与操作，提取彩色皮肤部分
		GaussianBlur(color_skin, Gau_skin, Size(9, 9), 0, 0, BORDER_DEFAULT);		//对提取部分进行高斯滤波
		addWeighted(Gau_skin,0.7, frame,0.5, 0.0, res);			//将滤波后的彩色皮肤部分与原图进行线性融合

		imshow("摄像头",frame);
		imshow("彩色皮肤部分",color_skin);
		imshow("皮肤磨皮",Gau_skin);
		imshow("res",res);

		waitKey(1);


	
	}

	







}
