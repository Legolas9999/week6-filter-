#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;

int main() {
	//-----------------------------------------��ϰ1,2,3,4-------------------------------
	Mat frame;      
	Mat median;     //��ֵ�˲�
	Mat mean;		//��ֵ�˲�
	Mat Gau;		//��˹�˲�
	Mat border_y;	//y�����Ե���
	Mat border_x;	//x�����Ե���
	
	VideoCapture cap;
	cap.open(0);
	while (1) {
			cap >> frame;
		medianBlur(frame, median, 7);								 //��ֵ�˲�
		blur(frame,mean,Size(3,3),Point(-1,-1),BORDER_DEFAULT);		//��ֵ�˲�
		GaussianBlur(frame, Gau, Size(3, 3),0,0,BORDER_DEFAULT);	//��˹�˲�
		imshow("��ֵ�˲�", median);
		imshow("��ֵ�˲�",mean);
		imshow("��˹�˲�",Gau);
		Sobel(frame,border_y, -1,1,0,3,1,1,BORDER_DEFAULT);			//y�����Ե���
		Sobel(frame, border_x, -1, 0, 1, 3,1,1,BORDER_DEFAULT);		//x�����Ե���
		imshow("��Եx",border_x);
		imshow("��Եy", border_y);
		
		//-----------------------------ĥƤ----------------------------------------------
		//HSVɫ��ģ�ͣ�Ƥ��ɫ�ʷ�Χ
		double  i_minH = 0;
		double  i_maxH = 20;

		double  i_minS = 43;
		double  i_maxS = 255;

		double  i_minV = 55;
		double  i_maxV = 255;
		Mat detMat_erzhi;		//Ƥ����ֵͼƤ��Ϊ��ɫ	
		Mat detMat_hsv;			
		Mat color_skin;			//��ȡƤ������
		Mat Gau_skin;			//����Ƥ�����ֽ��и�˹�˲�
		Mat res;
		
		cvtColor(frame, detMat_hsv, COLOR_BGR2HSV);			//������ͷת��ɫ��ģ��
		inRange(detMat_hsv, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV), detMat_erzhi);		//��ͼ���ֵ����Ƥ������Ϊ��ɫ������Ϊ��ɫ
		bitwise_and(frame,frame,color_skin,detMat_erzhi);			//��ԭͼ�������������ȡ��ɫƤ������
		GaussianBlur(color_skin, Gau_skin, Size(9, 9), 0, 0, BORDER_DEFAULT);		//����ȡ���ֽ��и�˹�˲�
		addWeighted(Gau_skin,0.7, frame,0.5, 0.0, res);			//���˲���Ĳ�ɫƤ��������ԭͼ���������ں�

		imshow("����ͷ",frame);
		imshow("��ɫƤ������",color_skin);
		imshow("Ƥ��ĥƤ",Gau_skin);
		imshow("res",res);

		waitKey(1);


	
	}

	







}
