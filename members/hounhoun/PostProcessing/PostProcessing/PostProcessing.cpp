#include "PostProcessing.h"
#include <QTimer>
#include <QFileDialog>
#include <fstream>

using namespace cv;
using namespace std;

PostProcessing::PostProcessing(QWidget *parent, Qt::WFlags flags)
	: QDialog(parent, flags), near_dist(600), far_dist(900), mx_dist(1000)
{
	timer = new QTimer;
	ui.setupUi(this);

	ui.graphicsView_kinect->SetParentPtr(this);
	ui.graphicsView_cut->SetParentPtr(this);

	ui.spinBox_near->setMaximum(1000);
	ui.horizontalSlider_near->setMaximum(1000);
	ui.spinBox_far->setMaximum(3000);
	ui.horizontalSlider_far->setMaximum(3000);	
	
	ui.label_rgb->setFixedSize(320, 240);
	
	connect(ui.pushButton_play, SIGNAL(clicked()), this, SLOT(Play()));
	connect(ui.pushButton_load, SIGNAL(clicked()), this, SLOT(Load()));
	connect(ui.pushButton_cut1, SIGNAL(clicked()), this, SLOT(Cut1()));
	connect(ui.pushButton_cut2, SIGNAL(clicked()), this, SLOT(Cut2()));
	connect(ui.horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(SliderCallback(int)));
	connect(ui.horizontalSlider_near, SIGNAL(valueChanged(int)), this, SLOT(SliderCallback_near(int)));
	connect(ui.horizontalSlider_far, SIGNAL(valueChanged(int)), this, SLOT(SliderCallback_far(int)));
	connect(timer, SIGNAL(timeout()), this, SLOT(TimerCallback()));

	ui.horizontalSlider_near->setValue(near_dist);
	ui.horizontalSlider_far->setValue(far_dist);

	Load("sample1.oni");
	int f = 40;
	ui.horizontalSlider->setValue(f);
	SliderCallback(f);
}

PostProcessing::~PostProcessing()
{
}

void PostProcessing::TimerCallback()
{	
	if (ui.horizontalSlider->value() == ui.horizontalSlider->maximum())
	{
		ui.horizontalSlider->setValue(0);
		SliderCallback(0);
		timer->stop();
	}
	else
	{
		ui.horizontalSlider->setValue(ui.horizontalSlider->value()+1);		
	};
}

void PostProcessing::SliderCallback( int f )
{
	if (kinect.player.IsValid())
	{
		kinect.context.WaitAndUpdateAll();
		kinect.player.SeekToFrame(kinect.depth_generator.GetName(), f, XN_PLAYER_SEEK_SET);

		// color image
		const XnRGB24Pixel* pColorMap = kinect.image_generator.GetRGB24ImageMap();
		colorMap = Mat(y_res, x_res, CV_8UC3, (uchar*)pColorMap);
		ui.label_rgb->UpdatePixmap(QPixmap::fromImage(QImage((uchar*)pColorMap, x_res, y_res ,QImage::Format_RGB888).scaled(ui.label_rgb->size())));

		// depth image	
		const XnDepthPixel* pDepthMap = kinect.depth_generator.GetDepthMap();
		
		depthMap = Mat(XN_VGA_Y_RES, XN_VGA_X_RES, CV_16UC1, (unsigned short*)pDepthMap);
		double mx;
		minMaxLoc(depthMap, NULL, &mx);

		Mat depth_display;
		depthMap.convertTo(depth_display, CV_8U, 255/mx);
		cvtColor(depth_display, depth_display, CV_GRAY2BGR);
		ui.label_depth->setPixmap(QPixmap::fromImage(QImage((uchar*)depth_display.data, x_res, y_res ,QImage::Format_RGB888).scaled(ui.label_depth->size())));

		pt_projected.clear();
		pt_color.clear();

		pt_projected.reserve(total);		
		pt_color.reserve(total);

		for (int i = 0; i<total; ++i)
		{
			int indx_a = i+1;		
			int indx_d = i+x_res;
			int indx_da = indx_d+1;

 			if (pDepthMap[i]>near_dist && pDepthMap[i]<far_dist)
			{
				int x = i%x_res;				
				int y = i/x_res;

				XnPoint3D tem;	

				// save position data
				tem.X = x; tem.Y = y; tem.Z = pDepthMap[i];
				pt_projected.push_back(tem);

				// save color data
				tem.X = pColorMap[i].nRed; tem.Y = pColorMap[i].nGreen; tem.Z = pColorMap[i].nBlue;
				pt_color.push_back(tem);
			}
		}

		pt_real.resize(pt_projected.size());
		kinect.depth_generator.ConvertProjectiveToRealWorld(pt_projected.size(), pt_projected.data(), pt_real.data());

		ui.graphicsView_kinect->updateGL();
	}
}

void PostProcessing::Load()
{
	// get file name
	QString file = QFileDialog::getOpenFileName(this,"Select one or more files to open", "", "kinect (*.oni)");
	if(file.isEmpty()) return;

	Load(file.toStdString().c_str());

	if (ui.horizontalSlider->value()!=0) ui.horizontalSlider->setValue(0);
	else SliderCallback(0);
}

void PostProcessing::Load( const char* filename )
{
	// init kinect form file
	if (kinect.InitKinect(filename))
	{
		printf("Load failed!\n");
	}

	// get max fame
	unsigned mx_frame;
	kinect.player.GetNumFrames(kinect.depth_generator.GetName(), mx_frame);
	UpdateMaxFrame(mx_frame);

	// init 3d data
	XnMapOutputMode outputmode;
	kinect.depth_generator.GetMapOutputMode(outputmode);
	x_res = outputmode.nXRes;
	y_res = outputmode.nYRes;
	total = x_res*y_res;

	ui.graphicsView_kinect->updateGL();
	ui.graphicsView_kinect->z_translate = -(near_dist+far_dist)*0.5;
	ui.graphicsView_kinect->setSceneRadius((far_dist-near_dist)*0.6);
	ui.graphicsView_kinect->showEntireScene();
}

void PostProcessing::Play()
{
	if (timer->isActive())
	{
		timer->stop();
	} 
	else
	{
		timer->start(30);
	}
}

void PostProcessing::UpdateMaxFrame( int mx )
{	
	ui.spinBox_maxframe->setMaximum(mx);
	ui.spinBox_curframe->setMaximum(mx);
	ui.horizontalSlider->setMaximum(mx);
	ui.spinBox_maxframe->setValue(mx);
}

void PostProcessing::Cut1()
{
	Cut_2(0);
	SaveMesh("cut1.off", pt_real2[0], tri_indx[0]);
	SaveIndx("indx1.txt", vertex_indx[0]);
}

void PostProcessing::Cut2()
{
	Cut_2(1);
	SaveMesh("cut2.off", pt_real2[1], tri_indx[1]);
	SaveIndx("indx2.txt", vertex_indx[1]);
}

void PostProcessing::Cut(int indx)
{
	if(ui.label_rgb->mouse_press.x()<0 || ui.label_rgb->mouse_press.y()<0) return;

	// define ROI of kinect images
	Point p1(ui.label_rgb->mouse_press.x(), ui.label_rgb->mouse_press.y());
	Point p2(ui.label_rgb->mouse_relaese.x(), ui.label_rgb->mouse_relaese.y());
	roi = Rect(p1*2, p2*2);


	ui.spinBox_x->setValue(roi.x);
	ui.spinBox_y->setValue(roi.y);
	ui.spinBox_w->setValue(roi.width);
	ui.spinBox_h->setValue(roi.height);


	// get ROI of kinect images
	colorMap_cut = Mat(colorMap, roi).clone();
	depthMap_cut = Mat(depthMap, roi).clone();

	Mat cut1, cut2, msk1, msk2, msk3, depthMap_result;

	cut1 = depthMap_cut > near_dist;
	cut2 = depthMap_cut < far_dist;	

	bitwise_and(cut1, cut2, msk1);
	bitwise_not(msk1, msk2);

	msk1.convertTo(msk1, CV_16UC1, 1.0/255.0);
	msk2.convertTo(msk3, CV_16UC1, mx_dist/255.0);

	multiply(depthMap_cut, msk1, depthMap_result);
	add(depthMap_result, msk3, depthMap_result, msk2);

	Mat depth_display;
	depthMap_result.convertTo(depth_display, CV_8U, 255.0/mx_dist);
	cvtColor(depth_display, depth_display, CV_GRAY2BGR);

	// draw ROI depth image
	ui.label_cut->setFixedSize(roi.width, roi.height);
	ui.label_cut->setPixmap(QPixmap::fromImage(QImage((uchar*)depth_display.data, depth_display.cols, depth_display.rows, QImage::Format_RGB888)));

	// initialize data vector
	int t = roi.width*roi.height;
	pt_projected2[indx].clear();
	pt_projected2[indx].reserve(t);
	pt_color2[indx].clear();
	pt_color2[indx].reserve(t);
	tri_indx[indx].clear();
	tri_indx[indx].reserve(t*2);

	int nx = 0, ny = 0;
	XnPoint3D tem;
	double up, down, left, right;
	double thr = 5;
	std::vector<int> tri(3,0);

	// check map
	Mat checkmap(roi.height, roi.width, CV_8UC1, Scalar());

	// get data
	for (int i = 0; i<roi.height; ++i)
	for (int j = 0; j<roi.width; ++j)
	{
		nx = j+roi.x;
		ny = i+roi.y;
		
		// get position data
		tem.X = nx;
		tem.Y = ny;
		tem.Z = depthMap_result.at<short>(i,j);

// 		if (tem.Z != mx_dist)
		{
			vertex_indx[indx].push_back(Point(i,j));
			pt_projected2[indx].push_back(tem);
			if (i>0 && j>0)
			{ 
				if (abs(tem.Z-depthMap_result.at<short>(i,j-1)) < thr && abs(tem.Z-depthMap_result.at<short>(i-1,j)) < thr)
				{
					tri[0] = i*roi.width+j;
					tri[2] = (i-1)*roi.width+j;
					tri[1] = i*roi.width+(j-1);
	 				tri_indx[indx].push_back(tri);
				}
			}
			
			if (i<roi.height-1 && j<roi.width-1)
			{
				if (abs(tem.Z-depthMap_result.at<short>(i,j+1)) < thr && abs(tem.Z-depthMap_result.at<short>(i+1,j)) < thr)
				{
					tri[0] = i*roi.width+j;
					tri[2] = (i+1)*roi.width+j;
					tri[1] = i*roi.width+(j+1);
					tri_indx[indx].push_back(tri);
				}
			}
		}

	}
	
	if (indx)
	{
		SaveDepthMap("target_dmap.txt", depthMap_result);
	}

	pt_real2[indx].resize(pt_projected2[indx].size());
	kinect.depth_generator.ConvertProjectiveToRealWorld(pt_projected2[indx].size(), pt_projected2[indx].data(), pt_real2[indx].data());

	ui.graphicsView_cut->z_translate = -(near_dist+mx_dist)*0.5;
	ui.graphicsView_cut->setSceneRadius((mx_dist-near_dist)*0.6);
	ui.graphicsView_cut->showEntireScene();
	ui.graphicsView_cut->updateGL();
}


void PostProcessing::Cut_2( int indx )
{
	if(ui.label_rgb->mouse_press.x()<0 || ui.label_rgb->mouse_press.y()<0) return;

	// define ROI of kinect images
	Point p1(ui.label_rgb->mouse_press.x(), ui.label_rgb->mouse_press.y());
	Point p2(ui.label_rgb->mouse_relaese.x(), ui.label_rgb->mouse_relaese.y());
	roi = Rect(p1*2, p2*2);

	ui.spinBox_x->setValue(roi.x);
	ui.spinBox_y->setValue(roi.y);
	ui.spinBox_w->setValue(roi.width);
	ui.spinBox_h->setValue(roi.height);

	// get ROI of kinect images
	colorMap_cut = Mat(colorMap, roi).clone();
	depthMap_cut = Mat(depthMap, roi).clone();

	Mat cut1, cut2, msk1, msk2, msk3, depthMap_result;

	cut1 = depthMap_cut > near_dist;
	cut2 = depthMap_cut < far_dist;	

	bitwise_and(cut1, cut2, msk1);
	bitwise_not(msk1, msk2);

	msk1.convertTo(msk1, CV_16UC1, 1.0/255.0);
	msk2.convertTo(msk3, CV_16UC1, mx_dist/255.0);

	multiply(depthMap_cut, msk1, depthMap_result);
	add(depthMap_result, msk3, depthMap_result, msk2);

	Mat depth_display;
	depthMap_result.convertTo(depth_display, CV_8U, 255.0/mx_dist);
	cvtColor(depth_display, depth_display, CV_GRAY2BGR);

	// draw ROI depth image
	ui.label_cut->setFixedSize(roi.width, roi.height);
	ui.label_cut->setPixmap(QPixmap::fromImage(QImage((uchar*)depth_display.data, depth_display.cols, depth_display.rows, QImage::Format_RGB888)));

	// initialize data vector
	int t = roi.width*roi.height;
	pt_projected2[indx].clear();
	pt_projected2[indx].reserve(t);
	pt_color2[indx].clear();
	pt_color2[indx].reserve(t);
	tri_indx[indx].clear();
	tri_indx[indx].reserve(t*2);

	int nx = 0, ny = 0;
	XnPoint3D tem;
	double up, down, left, right;
	double thr = 5;
	std::vector<int> tri(3,0);

	// check map
	Mat checkmap(depthMap_result.size(), CV_8UC1, Scalar());

	// get data
	for (int i = 0; i<roi.height; ++i)
	for (int j = 0; j<roi.width; ++j)
	{
		nx = j+roi.x;
		ny = i+roi.y;

		// get position data		
		if (depthMap_result.at<short>(i,j) != mx_dist)
		{			
			if (i>0 && j>0)
			{
				if (abs(depthMap_result.at<short>(i,j)-depthMap_result.at<short>(i,j-1)) < thr && abs(depthMap_result.at<short>(i,j)-depthMap_result.at<short>(i-1,j)) < thr)					
				{
					tem.X = nx;
					tem.Y = ny;
					tem.Z = depthMap_result.at<short>(i,j);		
					pt_projected2[indx].push_back(tem);
					if (checkmap.at<uchar>(i,j)==0) checkmap.at<uchar>(i,j) = 255;					

					tem.Y -= 1; tem.Z = depthMap_result.at<short>(i-1,j);
					pt_projected2[indx].push_back(tem);
					if (checkmap.at<uchar>(i-1,j)==0) checkmap.at<uchar>(i-1,j) = 255;

					tem.X -= 1; tem.Y += 1; tem.Z = depthMap_result.at<short>(i,j-1);
					pt_projected2[indx].push_back(tem);
					if (checkmap.at<uchar>(i,j-1)==0) checkmap.at<uchar>(i,j-1) = 255;

					tri[0] = i*roi.width+j;
					tri[2] = (i-1)*roi.width+j;
					tri[1] = i*roi.width+(j-1);
					tri_indx[indx].push_back(tri);
				}
			}

			if (i<roi.height-1 && j<roi.width-1)
			{
				if (abs(depthMap_result.at<short>(i,j)-depthMap_result.at<short>(i,j+1)) < thr && abs(depthMap_result.at<short>(i,j)-depthMap_result.at<short>(i+1,j)) < thr)
				{
					tem.X = nx;
					tem.Y = ny;
					tem.Z = depthMap_result.at<short>(i,j);		
					pt_projected2[indx].push_back(tem);
					if (checkmap.at<uchar>(i,j)==0) checkmap.at<uchar>(i,j) = 255;					

					tem.Y += 1; tem.Z = depthMap_result.at<short>(i+1,j);
					pt_projected2[indx].push_back(tem);
					if (checkmap.at<uchar>(i+1,j)==0) checkmap.at<uchar>(i+1,j) = 255;					
					
					tem.X += 1; tem.Y -= 1; tem.Z = depthMap_result.at<short>(i,j+1);
					pt_projected2[indx].push_back(tem);
					if (checkmap.at<uchar>(i,j+1)==0) checkmap.at<uchar>(i,j+1) = 255;

					tri[0] = i*roi.width+j;
					tri[2] = (i+1)*roi.width+j;
					tri[1] = i*roi.width+(j+1);
					tri_indx[indx].push_back(tri);
				}
			}
		}
	}
	
	// sorting projected points and face indx
	std::sort(pt_projected2[indx].begin(), pt_projected2[indx].end(), [&](XnPoint3D& ei, XnPoint3D& ej)->bool{
		if(ei.Y < ej.Y) return true;
		else if(ei.Y > ej.Y) return false;
		else return (ei.X < ej.X);
	});
	std::vector<XnPoint3D>::iterator it = std::unique(pt_projected2[indx].begin(), pt_projected2[indx].end(), [&](XnPoint3D& ei, XnPoint3D& ej)->bool{
		return (ei.X == ej.X && ei.Y == ej.Y);
	});
	pt_projected2[indx].erase(it, pt_projected2[indx].end());
	
	bitwise_not(checkmap, checkmap);
	checkmap.convertTo(checkmap, CV_8UC1, 1.0/255.0);

	for (int i = 0; i<tri_indx[indx].size(); ++i)
	{
		for (int j = 0 ; j<3; ++j)
		{
			int ix = tri_indx[indx][i][j]%roi.width;
			int iy = tri_indx[indx][i][j]/roi.width;
			Rect temroi(0,0,roi.width,iy);
			Rect temroi2(0,iy,ix+1,1);
			int s = sum(Mat(checkmap, temroi)).val[0]+sum(Mat(checkmap, temroi2)).val[0];

			tri_indx[indx][i][j] -= s;
		}
	}	
	
	// save indx
	vertex_indx[indx].resize(pt_projected2[indx].size());
	for (int i = 0; i<pt_projected2[indx].size(); ++i)
	{
		vertex_indx[indx][i].x = pt_projected2[indx][i].X;
		vertex_indx[indx][i].y = pt_projected2[indx][i].Y;
	}

	if (indx)
	{
		SaveDepthMap("target_dmap.txt", depthMap_result);
	}

	pt_real2[indx].resize(pt_projected2[indx].size());
	kinect.depth_generator.ConvertProjectiveToRealWorld(pt_projected2[indx].size(), pt_projected2[indx].data(), pt_real2[indx].data());

	Smooth(indx);
	UpdateFacetNormal(indx);
	UpdateVertexNormal(indx);

 	ui.graphicsView_cut->z_translate = -(near_dist+mx_dist)*0.5;
	ui.graphicsView_cut->setSceneRadius((mx_dist-near_dist)*0.6);
	ui.graphicsView_cut->showEntireScene();
	ui.graphicsView_cut->updateGL();
}


void PostProcessing::SliderCallback_near( int f )
{
	near_dist = f;
	SliderCallback(ui.horizontalSlider->value());
}

void PostProcessing::SliderCallback_far( int f )
{
	far_dist = f;
	SliderCallback(ui.horizontalSlider->value());
}

void PostProcessing::Triangulation( const cv::Rect& roi, const cv::Mat& depth_map, const std::vector<XnPoint3D>& real_pt, std::vector<std::vector<int>>& tri_indx )
{
// 	int w = depth_map.cols;
// 	int h = depth_map.rows;
// 
// 
// 	for (int i = 0; i<w-1; ++i)
// 	{
// 		for (int j = 0; j<h-1; ++j)
// 		{
// 			int indx = j*w+i;
// 			if (pDepthMap[indx]>near_dist && pDepthMap[indx]<far_dist)
// 			{
// 
// 				int indx_a = indx+1;		
// 				int indx_d = indx+w;
// 				int indx_da = indx_d+1;
// 
// 				int t1[3] = {indx, indx_d, indx_a};
// 				int t2[3] = {indx_a, indx_d, indx_da};
// 
// 				tri_indx.push_back(vector<int>(t1, t1+3));
// 				tri_indx.push_back(vector<int>(t2, t2+3));
// 			}
// 		}
// 		cout<<i<<endl;
// 	}

	std::cout<< "complete" <<std::endl;
}

void PostProcessing::SaveMesh( const char* filename, const std::vector<XnPoint3D>& real, const std::vector<std::vector<int>>& tri )
{
	ofstream fout(filename);
	fout << "OFF" << endl;
	fout << real.size() << " " << tri.size() << " " << 0 << endl;
	
	for (int i = 0; i<real.size(); ++i)
	{
		fout << real[i].X << " " << real[i].Y << " " << real[i].Z << endl;
	}
	for (int i = 0; i<tri.size(); ++i)
	{
		fout << 3 << " " << tri[i][0] << " " << tri[i][1] << " " << tri[i][2] << endl;
	}
	fout.close();
}

void PostProcessing::SaveDepthMap( const char* filename, const cv::Mat& dmap )
{
	ofstream fout(filename);
	fout << roi.x<< " " << roi.y<< " " << roi.width << " " << roi.height << endl;
	for (int i = 0; i<dmap.rows; ++i)
	{
		for (int j = 0; j<dmap.cols; ++j)
		{
			fout<< dmap.at<short>(i, j) << " ";
		}
		fout << endl;
	}	
}

void PostProcessing::SaveIndx( const char* filename, const std::vector<cv::Point>& v_indx )
{
	ofstream fout(filename);
	for (int i = 0; i<v_indx.size(); ++i)
	{
		fout << v_indx[i].x << " " << v_indx[i].y << endl;
	}
}

void PostProcessing::UpdateFacetNormal( int indx )
{
	cv::Vec3f pts[3];
	face_normal[indx].resize(tri_indx[indx].size());
	for (int i = 0; i<tri_indx[indx].size(); ++i)
	{				
		for (int j = 0; j<3; ++j)
		{
			int ii = tri_indx[indx][i][j];
			pts[j] = cv::Vec3f(pt_real2[indx][ii].X, pt_real2[indx][ii].Y, pt_real2[indx][ii].Z);
		}		
		face_normal[indx][i] = normalize((pts[1]-pts[0]).cross(pts[2]-pts[0]));
	}
}

void PostProcessing::UpdateVertexNormal( int indx )
{
	vertex_normal[indx].resize(pt_real2[indx].size(), Vec3f(0,0,0));
	for(int i = 0; i < tri_indx[indx].size(); i++)
	{
		int n0 = tri_indx[indx][i][0];
		int n1 = tri_indx[indx][i][1];
		int n2 = tri_indx[indx][i][2];

		vertex_normal[indx][n0] += face_normal[indx][i];
		vertex_normal[indx][n1] += face_normal[indx][i];
		vertex_normal[indx][n2] += face_normal[indx][i];
	}	
	for(int i = 0; i < vertex_normal[indx].size(); i++)
		vertex_normal[indx][i] = normalize(vertex_normal[indx][i]);

}

void PostProcessing::Smooth( int indx )
{
	std::vector<Vec3f> temp(pt_real2[indx].size(), Vec3f(0,0,0));
	std::vector<int> cnt(pt_real2[indx].size(), 0);
	
	for (int i = 0; i<tri_indx[indx].size(); ++i)
	{
		Vec3f face_center;
		int ii[3];
		for (int j = 0; j<3; ++j)
		{
			ii[j] = tri_indx[indx][i][j];
			face_center += cv::Vec3f(pt_real2[indx][ii[j]].X, pt_real2[indx][ii[j]].Y, pt_real2[indx][ii[j]].Z);
		}		
		face_center /= 3.0;
		
		for (int j = 0; j<3; ++j)
		{
			temp[ii[j]] += face_center;
			cnt[ii[j]] += 1;
		}			
	}

	for(int i = 0; i < pt_real2[indx].size(); i++)
	{
		if(cnt[i] > 0)
		{
			Vec3f dx = temp[i];
			dx /= cnt[i];
			pt_real2[indx][i].X = dx[0];
			pt_real2[indx][i].Y = dx[1];
			pt_real2[indx][i].Z = dx[2];
		}
	}
}
