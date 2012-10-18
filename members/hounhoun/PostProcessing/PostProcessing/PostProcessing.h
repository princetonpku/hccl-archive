#ifndef POSTPROCESSING_H
#define POSTPROCESSING_H

#include <QtGui/QDialog>
#include "ui_PostProcessing.h"
#include "Kinect.h"
#include <vector>
#include <opencv2/opencv.hpp>

class QTimer;

class PostProcessing : public QDialog
{
	Q_OBJECT

public:
	PostProcessing(QWidget *parent = 0, Qt::WFlags flags = 0);
	~PostProcessing();

private:
	Ui::PostProcessingClass ui;

	QTimer* timer;
	void UpdateMaxFrame(int mx);

public:
	int x_res, y_res, total;

	int near_dist, far_dist;
	double mx_dist;

	Kinect kinect;
	std::vector<XnPoint3D>	pt_projected;
	std::vector<XnPoint3D>	pt_real;
	std::vector<XnPoint3D>	pt_color;

	cv::Mat							colorMap, colorMap_cut, depthMap, depthMap_cut;
	cv::Rect						roi;
	std::vector<std::vector<int>>	tri_indx[2];
	std::vector<XnPoint3D>			pt_projected2[2];
	std::vector<XnPoint3D>			pt_real2[2];
	std::vector<XnPoint3D>			pt_color2[2];
	std::vector<cv::Point>			vertex_indx[2];
	std::vector<cv::Vec3f>			vertex_normal[2];
	std::vector<cv::Vec3f>			face_normal[2];

	void SaveMesh(const char* filename, const std::vector<XnPoint3D>& real, const std::vector<std::vector<int>>& tri);
	void SaveDepthMap(const char* filename, const cv::Mat& dmap);
	void SaveIndx(const char* filename, const std::vector<cv::Point>& v_indx);
	void Triangulation( const cv::Rect& roi, const cv::Mat& depth_map, const std::vector<XnPoint3D>& real_pt, std::vector<std::vector<int>>& tri_indx);
	
	void Cut(int indx);
	void Cut_2(int indx);
	void UpdateFacetNormal(int indx);
	void UpdateVertexNormal(int indx);
	void Smooth(int indx);

public slots:

	void TimerCallback();
	void SliderCallback(int f);
	void SliderCallback_near(int f);
	void SliderCallback_far(int f);

	void Load();
	void Load(const char* filename);
	void Play();
	void Cut1();
	void Cut2();
};

#endif // POSTPROCESSING_H
