#include "Fac_Rec.h"
Fac_Rec::Fac_Rec() {
	cascade.load("haarcascade_frontalface_alt2.xml");
	/*model = LBPHFaceRecognizer::create();
	model->read("MyFaceLBPHModel.xml");*/

	model = EigenFaceRecognizer::create();
	model->read("C:\\Users\\TianXu\\Desktop\\FaceRecognition\\QtGuiFaceRecognition\\MyFacePCAModel.xml");
}

int Fac_Rec::fac_pre(Mat image) {
	Mat face_test;
	int predict = 0;
	//截取的ROI人脸尺寸调整
	if (image.rows >= 120)
	{
		//改变图像大小，使用双线性差值
		resize(image, face_test, Size(92, 112));
	}
	//判断是否正确检测ROI
	if (!face_test.empty())
	{
		//测试图像应该是灰度图  
		predict = model->predict(face_test);
	}
	cout << predict << endl;
	return predict;
}

int Fac_Rec::fac_rec(Mat image) {
	Mat gray;

	vector<Rect> faces(0);//建立用于存放人脸的向量容器

	cvtColor(image, gray, COLOR_RGB2GRAY);//测试图像必须为灰度图

	equalizeHist(gray, gray); //变换后的图像进行直方图均值化处理  
	//检测人脸
	cascade.detectMultiScale(gray, faces, 1.1, 4,  CASCADE_DO_ROUGH_SEARCH, Size(30, 30), Size(500, 500));
	Mat* pImage_roi = new Mat[faces.size()];    //定以数组
	Mat face;
	//框出人脸
	string str;
	int predict = 0;
	for (int i = 0; i < faces.size(); i++)
	{
		pImage_roi[i] = gray(faces[i]); //将所有的脸部保存起来
		if (pImage_roi[i].empty())
			continue;
		if (predict == 0)
		{
			predict = fac_pre(pImage_roi[i]);
		}
	}
	return predict;
}