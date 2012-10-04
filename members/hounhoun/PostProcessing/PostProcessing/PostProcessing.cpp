#include "PostProcessing.h"
#include <QTimer>
#include <QFileDialog>

using namespace cv;
using namespace std;

PostProcessing::PostProcessing(QWidget *parent, Qt::WFlags flags)
	: QDialog(parent, flags), near_dist(600), far_dist(900), mx_dist(3000)
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
		tri_indx.clear();
		tri_indx.reserve(total);

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
	Cut(0);
}

void PostProcessing::Cut2()
{
	Cut(1);
}

void PostProcessing::Cut(int indx)
{
	if(ui.label_rgb->mouse_press.x()<0 || ui.label_rgb->mouse_press.y()<0) return;

	Point p1(ui.label_rgb->mouse_press.x(), ui.label_rgb->mouse_press.y());
	Point p2(ui.label_rgb->mouse_relaese.x(), ui.label_rgb->mouse_relaese.y());
	Rect roi(p1*2, p2*2);

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

	ui.label_cut->setFixedSize(roi.width, roi.height);
	ui.label_cut->setPixmap(QPixmap::fromImage(QImage((uchar*)depth_display.data, depth_display.cols, depth_display.rows, QImage::Format_RGB888)));

	int t = roi.width*roi.height;
	pt_projected2[indx].clear();
	pt_projected2[indx].reserve(t);
	pt_color2[indx].clear();
	pt_color2[indx].reserve(t);

	// get 3D position
	for (int i = 0; i<roi.height; ++i)
		for (int j = 0; j<roi.width; ++j)
		{
			int nx = j+roi.x;
			int ny = i+roi.y;
			XnPoint3D tem;

			// save position data
			tem.X = nx;
			tem.Y = ny;
			tem.Z = depthMap_result.at<short>(i,j);
			pt_projected2[indx].push_back(tem);

			// save color data
			if (tem.Z != mx_dist)
			{
				tem.X = colorMap_cut.at<uchar>(i, 3*j);
				tem.Y = colorMap_cut.at<uchar>(i, 3*j+1);
				tem.Z = colorMap_cut.at<uchar>(i, 3*j+2);

				if (indx==0) tem.X += 50;
				else tem.Y += 50;
			} 
			else
			{
				tem.X = 100;
				tem.Y = 100;
				tem.Z = 100;
			}
			pt_color2[indx].push_back(tem);
		}

		pt_real2[indx].resize(pt_projected2[indx].size());
		kinect.depth_generator.ConvertProjectiveToRealWorld(pt_projected2[indx].size(), pt_projected2[indx].data(), pt_real2[indx].data());

		ui.graphicsView_cut->z_translate = -(near_dist+far_dist)*0.5;
		ui.graphicsView_cut->setSceneRadius((far_dist-near_dist)*0.6);
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
