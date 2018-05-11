/***************************************/
/* opencv2.2 标定camera内参和外参数
/*
/**************************************/
#include "cv.h"
#include "highgui.h"
#define	CV_IMAGES 3		// 标定图像数目NPOINTS
#define	CV_POINTS 16		// 每个图像上点数

typedef struct myPoint2Df{
	float x;
	float y;
};
typedef struct myPoint3Df{
	float x;
	float y;
	float z;
};

typedef struct myPoint2DS{
	int x;
	int y;
};

typedef struct myPoint3DS{
	int x;
	int y;
	int z;
};

CvMat* object_points = cvCreateMat(CV_IMAGES*CV_POINTS, 3, CV_32FC1);

CvMat* image_points = cvCreateMat(CV_IMAGES*CV_POINTS, 2, CV_32FC1);
CvMat* point_counts = cvCreateMat(CV_IMAGES, 1, CV_32SC1);
CvMat* intrinsic_matrix = cvCreateMat(3, 3, CV_32FC1);	// 内参
CvMat* distortion_coeffs = 	cvCreateMat(1, 4, CV_32FC1);	// Lens畸变 k1 k2 p1 p2
CvMat* rotation_vectors	= cvCreateMat(CV_IMAGES, 3, CV_32FC1);
CvMat* translation_vectors = cvCreateMat(CV_IMAGES, 3, CV_32FC1);
int corner_count = CV_POINTS;
myPoint3Df points_obj;
myPoint2Df points_pixel;
// 
// 物体(定标)设备上的点
for(int i=0; i< ; i++)
{
	;
}
cvSetData(object_points, points_obj, sizeof(CvPoint3D32f));

// 像平面上的点
for(int i=0; i< ; i++)
{
	;
}
cvSetData(image_points, points_pixel, sizeof(CvPoint2D32f));

// 指定不同视图里点的数目

cvSetData( point_counts, &corner_count, sizeof(int));

// 内参和畸变参数初始化

// camera内参|畸变|外参计算
cvCalibrateCamera2(	object_points,
					image_points,
					point_counts,
					cvSize(640, 480),
					intrinsic_matrix,
					distortion_coeffs,
					rotation_vectors,
					translation_vectors,
					0);
				   

void myUndistort2(myPoint2DS InPoints, CvMat* intrinsic, CvMat* distortion, myPoint2DS* OutPoints)
{
	float k1,k2,p1,p2;
	float fx,fy,cx,cy;
	float X0 = (float) InPoints.x;
	float Y0 = (float) InPoints.y;

	k1 = distortion->data.fl[0];
	k2 = distortion->data.fl[1];
	p1 = distortion->data.fl[2];
	p2 = distortion->data.fl[3];
	
	fx = intrinsic->data.fl[0];
	cx = intrinsic->data.fl[2];
	fy = intrinsic->data.fl[4];
	cy = intrinsic->data.fl[5];

	OutPoints->x = X0 + k1*X0(X0*X0 + Y0*Y0) + \
		p1*(3*X0*X0 + Y0*Y0)+ 2*p2*X0*Y0);
	OutPoints->y = Y0 + k2*X0(X0*X0 + Y0*Y0) + \
		p2*(X0*X0 + 3*Y0*Y0) + 2*p1*X0*Y0);


}

				 


