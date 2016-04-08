#pragma once
#include <math.h>
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "client.cpp"
#include <windows.h>
#include <queue>
#include "utils.h"
#include "utilCLass.h"
#include "FeatureTracker.cpp"
CvCapture* capture;
IplImage *frame;
IplImage *frameSend;//用于发送的帧
int timeCount;
double fps;
int fpsCount;
int now_frame_no = 0;
int fame_continue = 6;
std::queue<IplImage> imageQueue;
FeatureTracker tracker;// = new FeatureTracker();
struct MyRGB
{
	int R;
	int G;
	int B;
};
std::map<std::string, MyRGB> colorMap;
std::map<std::string, MyRGB>::iterator it;

namespace Capture1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;
	using namespace System::Threading;
	using namespace SocketCommu;
	using namespace System::Collections::Generic;
	//using namespace System::Runtime::InteropServices;
	using namespace System::Media;

	public ref class Form1 : public System::Windows::Forms::Form
	{
	private:Client ^client = gcnew Client();
			List<UtilSpace::Result ^> ^boxes = gcnew List<UtilSpace::Result ^>();
			List<Thread ^> ^threadList = gcnew List<Thread ^>();//将所有线程放入线程池中
			System::String ^result = "";// "12-12-15-115-0.98-person,12-12-15-115-0.98-person,";

			List<UtilSpace::Rectangle ^> ^regions;
			HANDLE frameMutex = CreateMutex(NULL, FALSE, NULL);//用于frame多线程读写时的互斥变量
			HANDLE boxMutex = CreateMutex(NULL, FALSE, NULL);
			HANDLE timer1Handle = CreateMutex(NULL, FALSE, NULL);
			HANDLE socketHandle = CreateMutex(NULL, FALSE, NULL);
			int frameWidth = 640;
	private: System::Windows::Forms::Timer^  beepTime;

			 int frameHeight = 480;
	public:
		Form1(void)
		{
			//定义颜色map
			colorMap["person"] = { 247, 186, 64 };
			colorMap["tvmonitor"] = { 65, 105, 225 };
			colorMap["chair"] = { 135, 38, 87 };
			colorMap["aeroplane"] = { 160, 82, 45 };
			colorMap["bottle"] = { 227, 23, 13 };
			colorMap["bicycle"] = { 218, 112, 214 };
			colorMap["bird"] = { 25, 25, 112 };
			colorMap["boat"] = { 255, 69, 0 };
			colorMap["bus"] = { 41, 36, 33 };
			colorMap["car"] = { 237, 145, 33 };
			colorMap["cat"] = { 127, 255, 0 };
			colorMap["cow"] = { 64, 224, 208 };
			colorMap["diningtable"] = { 128,42,42 };
			colorMap["dog"] = { 255, 125, 64 };
			colorMap["horse"] = { 255, 69, 0 };
			colorMap["motorbike"] = { 51, 161, 201 };
			colorMap["pottedplant"] = { 163, 148, 128 };
			colorMap["sheep"] = { 250, 235, 215 };
			colorMap["sofa"] = { 138, 43, 226 };
			colorMap["train"] = { 48, 128, 20 };
			colorMap[""] = { 0, 0, 0 };
			regions = gcnew List<UtilSpace::Rectangle^>();

			InitializeComponent();
		}

	protected:
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}

#pragma region Window_control
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::TrackBar^  trackBar1;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::ComponentModel::IContainer^  components;
	private: System::Windows::Forms::ComboBox^  detectInterval;


	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Timer^  timer3;
	private: System::Windows::Forms::Button^  buttonClean;
	private: System::Windows::Forms::Button^  buttonPaint;
	private: System::Windows::Forms::Label^  labelWarning;
#pragma endregion

	protected:

	private:

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->labelWarning = (gcnew System::Windows::Forms::Label());
			this->buttonClean = (gcnew System::Windows::Forms::Button());
			this->buttonPaint = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->detectInterval = (gcnew System::Windows::Forms::ComboBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->timer3 = (gcnew System::Windows::Forms::Timer(this->components));
			this->beepTime = (gcnew System::Windows::Forms::Timer(this->components));
			this->panel1->SuspendLayout();
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->groupBox3->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel1->Controls->Add(this->labelWarning);
			this->panel1->Controls->Add(this->buttonClean);
			this->panel1->Controls->Add(this->buttonPaint);
			this->panel1->Controls->Add(this->label2);
			this->panel1->Controls->Add(this->label1);
			this->panel1->Controls->Add(this->groupBox1);
			this->panel1->Controls->Add(this->groupBox3);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel1->Location = System::Drawing::Point(3, 3);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(676, 730);
			this->panel1->TabIndex = 0;
			// 
			// labelWarning
			// 
			this->labelWarning->AutoSize = true;
			this->labelWarning->ForeColor = System::Drawing::Color::Red;
			this->labelWarning->Location = System::Drawing::Point(280, 638);
			this->labelWarning->Name = L"labelWarning";
			this->labelWarning->Size = System::Drawing::Size(0, 23);
			this->labelWarning->TabIndex = 15;
			// 
			// buttonClean
			// 
			this->buttonClean->Enabled = false;
			this->buttonClean->Location = System::Drawing::Point(126, 633);
			this->buttonClean->Name = L"buttonClean";
			this->buttonClean->Size = System::Drawing::Size(102, 33);
			this->buttonClean->TabIndex = 14;
			this->buttonClean->Text = L"清除区域";
			this->buttonClean->UseVisualStyleBackColor = true;
			this->buttonClean->Click += gcnew System::EventHandler(this, &Form1::buttonClean_Click);
			// 
			// buttonPaint
			// 
			this->buttonPaint->Enabled = false;
			this->buttonPaint->Location = System::Drawing::Point(18, 633);
			this->buttonPaint->Name = L"buttonPaint";
			this->buttonPaint->Size = System::Drawing::Size(102, 33);
			this->buttonPaint->TabIndex = 13;
			this->buttonPaint->Text = L"新建区域";
			this->buttonPaint->UseVisualStyleBackColor = true;
			this->buttonPaint->Click += gcnew System::EventHandler(this, &Form1::buttonPaint_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(280, 688);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(135, 23);
			this->label2->TabIndex = 12;
			this->label2->Text = L"平均接收帧率:";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(25, 688);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(95, 23);
			this->label1->TabIndex = 11;
			this->label1->Text = L"视频帧率:";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->trackBar1);
			this->groupBox1->Controls->Add(this->pictureBox1);
			this->groupBox1->Font = (gcnew System::Drawing::Font(L"Calibri", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->groupBox1->Location = System::Drawing::Point(5, 61);
			this->groupBox1->Margin = System::Windows::Forms::Padding(5);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Padding = System::Windows::Forms::Padding(5);
			this->groupBox1->Size = System::Drawing::Size(664, 559);
			this->groupBox1->TabIndex = 9;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"视频";
			// 
			// trackBar1
			// 
			this->trackBar1->AutoSize = false;
			this->trackBar1->Location = System::Drawing::Point(13, 534);
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Size = System::Drawing::Size(639, 26);
			this->trackBar1->TabIndex = 1;
			this->trackBar1->Visible = false;
			this->trackBar1->Scroll += gcnew System::EventHandler(this, &Form1::trackBar1_Scroll);
			// 
			// pictureBox1
			// 
			this->pictureBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pictureBox1->Location = System::Drawing::Point(12, 38);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(640, 480);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::pictureBox1_MouseDown);
			this->pictureBox1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::pictureBox1_MouseMove);
			this->pictureBox1->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::pictureBox1_MouseUp);
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->detectInterval);
			this->groupBox3->Controls->Add(this->button2);
			this->groupBox3->Controls->Add(this->comboBox1);
			this->groupBox3->Font = (gcnew System::Drawing::Font(L"Calibri", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->groupBox3->Location = System::Drawing::Point(3, 3);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(666, 62);
			this->groupBox3->TabIndex = 10;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"检测源";
			// 
			// detectInterval
			// 
			this->detectInterval->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->detectInterval->FormattingEnabled = true;
			this->detectInterval->Items->AddRange(gcnew cli::array< System::Object^  >(31) {
				L"1", L"2", L"3", L"4", L"5", L"6", L"7",
					L"8", L"9", L"10", L"11", L"12", L"13", L"14", L"15", L"16", L"17", L"18", L"19", L"20", L"21", L"22", L"23", L"24", L"25", L"26",
					L"27", L"28", L"29", L"30", L"检测帧间隔"
			});
			this->detectInterval->Location = System::Drawing::Point(336, 23);
			this->detectInterval->Name = L"detectInterval";
			this->detectInterval->Size = System::Drawing::Size(93, 27);
			this->detectInterval->TabIndex = 2;
			this->detectInterval->Text = "4";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(435, 23);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(79, 27);
			this->button2->TabIndex = 1;
			this->button2->Text = L"开始";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// comboBox1
			// 
			this->comboBox1->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"打开摄像头进行检测", L"选择视频进行检测", L"请选择检测种类" });
			this->comboBox1->Location = System::Drawing::Point(13, 23);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(317, 27);
			this->comboBox1->TabIndex = 0;
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// timer1
			// 
			this->timer1->Interval = 30;
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// timer3
			// 
			this->timer3->Interval = 1000;
			this->timer3->Tick += gcnew System::EventHandler(this, &Form1::timer3_Tick);
			// 
			// beepTime
			// 
			this->beepTime->Interval = 1000;
			this->beepTime->Tick += gcnew System::EventHandler(this, &Form1::BeepTime_Tick);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(10, 23);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(682, 736);
			this->Controls->Add(this->panel1);
			this->Font = (gcnew System::Drawing::Font(L"Calibri", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Margin = System::Windows::Forms::Padding(5);
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"Form1";
			this->Padding = System::Windows::Forms::Padding(3);
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"实时物体检测";
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->groupBox3->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion

	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (comboBox1->Text == "请选择检测种类" || detectInterval->Text == "检测帧率")
		{
			MessageBox::Show(this, "请选择检测种类或帧率", "错误!!!");
		}
		if (button2->Text == "开始")
		{
			if (comboBox1->Text == "打开摄像头进行检测")
			{
				capture = cvCaptureFromCAM(0);
				//fps = cvGetCaptureProperty(capture, CV_CAP_PROP_FPS); //视频帧率
				fame_continue = int::Parse(detectInterval->Text);
				trackBar1->Visible = false;
				trackBar1->Minimum = 0;
				trackBar1->Maximum = 0;
				button2->Text = "停止";
				timeCount = 0;
				fpsCount = 0;
				timer1->Start();
				timer3->Start();
				pictureBox1->Location = System::Drawing::Point(12, 38);
				label1->Text = "视频帧率:";
				frameWidth = 640;
				frameHeight = 480;
				buttonPaint->Enabled = true;
				buttonClean->Enabled = true;
			}
			else if (comboBox1->Text == "选择视频进行检测")
			{
				openFileDialog1->Filter = "AVI files (*.avi)|*.txt|All files (*.*)|*.*";
				openFileDialog1->FilterIndex = 2;
				openFileDialog1->RestoreDirectory = true;
				openFileDialog1->FileName = "";
				trackBar1->Visible = true;
				trackBar1->Value = 0;
				pictureBox1->Location = System::Drawing::Point(12, 28);
				if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				{
					char *fileName = (char*)Marshal::StringToHGlobalAnsi(openFileDialog1->FileName).ToPointer();
					capture = cvCaptureFromFile(fileName);
					fps = cvGetCaptureProperty(capture, CV_CAP_PROP_FPS); //视频帧率
					fame_continue = int::Parse(detectInterval->Text);
					trackBar1->Minimum = 0;
					timeCount = 0;
					fpsCount = 0;
					timer3->Start();
					//label1->Text = "视频帧率: " + double(int(fps * 100)) / 100 + "fps";
					trackBar1->Maximum = (int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_COUNT);
					button2->Text = "停止";
					timer1->Start();
					buttonPaint->Enabled = false;
					buttonClean->Enabled = false;
					//buttonPaint->Enabled = true;
					//buttonClean->Enabled = true;
				}
			}
		}
		else if (button2->Text == "停止")
		{
			timer1->Stop();
			timer3->Stop();
			for each(Thread ^t in threadList)
			{
				t->Join();
			}
			cvReleaseCapture(&capture);
			button2->Text = "开始";
			now_frame_no = 0;
			startPoint = nullptr;
			endPoint = nullptr;
			//pictureBox1->Enabled = false;
			drawing = false;
			newDraw = false;
			boxes->Clear();
			regions->Clear();
			ReleaseMutex(frameMutex);
			ReleaseMutex(boxMutex);
			ReleaseMutex(timer1Handle);
			ReleaseMutex(socketHandle);
			int frameWidth = 640;
			int frameHeight = 480;
			/*while (!imageQueue.empty()) {
				imageQueue.pop();
			}*/
		}
	}

	private: System::Void trackBar1_Scroll(System::Object^  sender, System::EventArgs^  e)
	{
		cvSetCaptureProperty(capture, CV_CAP_PROP_POS_FRAMES, trackBar1->Value);
	}

	private: System::Void cvText(IplImage* img, const char* cls, int x, int y, const char* score)//写字的
	{
		CvFont font;

		double hscale = 1.0;
		double vscale = 1.0;
		int linewidth = 2;
		cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX | CV_FONT_ITALIC, hscale, vscale, 0, linewidth);
		it = colorMap.find(cls);
		CvScalar textColor = CV_RGB((*it).second.R, (*it).second.G, (*it).second.B);
		CvPoint textPos = cvPoint(x, y);
		char temp[60];
		strcpy(temp, cls);
		strcat(temp, ":");
		strcat(temp, score);
		cvPutText(img, temp, textPos, &font, textColor);
	}

	private: System::Void cvFrame(IplImage* img, int x1, int y1, int x2, int y2, const char* cls)//画框的
	{
		it = colorMap.find(cls);
		cvRectangle(img, cvPoint(x1, y1), cvPoint(x2, y2), CV_RGB((*it).second.R, (*it).second.G, (*it).second.B), 2);
	}
	private:Thread ^thread;
			//循环画帧
	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e)
	{
		try
		{
			frame = cvQueryFrame(capture);
			if (frame != NULL)
			{
				/*cv::Mat output;
				cv::Mat *temp = new Mat(frame);
				tracker.process(*temp, output);
				pictureBox1->Image = client->ConvertMatToBitmap(output);
				pictureBox1->Refresh();*/
				/*IplImage *temp = cvCreateImage(cvGetSize(frame), frame->depth, frame->nChannels);
				cvCopy(frame, temp);*/
				//imageQueue.push(*frame);
				if (now_frame_no % fame_continue == 0)//发送帧，改变检测结果.
				{
					WaitForSingleObject(frameMutex, INFINITE);
					cvReleaseImage(&frameSend);//先释放内存，不然随着程序的运行内存会不断增加
					frameSend = cvCreateImage(cvGetSize(frame), frame->depth, frame->nChannels);
					cvCopy(frame, frameSend);
					//frame = NULL;
					ReleaseMutex(frameMutex);
					Thread ^thread = gcnew Thread(gcnew ThreadStart(this, &Form1::SendFrame));
					thread->IsBackground = true;
					if (threadList->Count > 0)
						threadList->RemoveAt(0);
					threadList->Add(thread);
					thread->Start();
				}
				labelWarning->Text = "";//初始化警告框
				IplImage frameToShow = *frame;

				WaitForSingleObject(boxMutex, INFINITE);
				//画出检测结果
				for each (UtilSpace::Result ^box in boxes)
				{
					char *cls = StringToCharArray(box->cls);
					char *score = StringToCharArray(box->score);
					//写字
					cvText(&frameToShow, cls, box->x1, box->y1, score);
					//画框子
					cvFrame(&frameToShow, box->x1, box->y1, box->x2, box->y2, cls);
				}
				//画出警告区域
				for each(UtilSpace::Rectangle ^region in regions) {

					bool call_110 = false;
					//检测有没有是人的框子踏入了警告区域
					for each (UtilSpace::Result ^box in boxes)
					{
						if (box->cls->Equals("person") && UtilSpace::Rectangle::areTwoRectsOverlapped(region, box))//如果有人的区域与警告区域重叠，跳出循环，警告
						{
							call_110 = true;
							break;
						}
					}
					if (!call_110)
						cvRectangle(&frameToShow, cvPoint(region->x1, region->y1), cvPoint(region->x2, region->y2), CV_RGB(0, 0, 255), 2);
					else
					{
						cvRectangle(&frameToShow, cvPoint(region->x1, region->y1), cvPoint(region->x2, region->y2), CV_RGB(255, 0, 0), CV_FILLED);
						labelWarning->Text = "警告！！！";
						beepTime->Start();
					}
				}
				ReleaseMutex(boxMutex);
				pictureBox1->Image = gcnew System::Drawing::Bitmap(frameToShow.width, frameToShow.height, frameToShow.widthStep, System::Drawing::Imaging::PixelFormat::Format24bppRgb, (System::IntPtr) frameToShow.imageData);
				WaitForSingleObject(timer1Handle, INFINITE);
				now_frame_no++;
				ReleaseMutex(timer1Handle);
			}
			else
			{
				ReleaseMutex(frameMutex);
			}
		}
		catch (System::Exception ^g) {
		}
	}
			 int save = 1;//测试所用，注意删除
	//发送需要被检测的帧到服务器并返回结果
	private:void SendFrame() {
		WaitForSingleObject(frameMutex, INFINITE);
		client->connect();
		//测试所用
		//Bitmap ^temp = gcnew System::Drawing::Bitmap(frameSend->width, frameSend->height, frameSend->widthStep, System::Drawing::Imaging::PixelFormat::Format24bppRgb, (System::IntPtr) frameSend->imageData);
		//temp->Save(save + ".jpg", System::Drawing::Imaging::ImageFormat::Jpeg);
		//save++;
		//if (save == 30)
		//	save = 1;
		//测试end
		client->sendImg(frameSend);
		result = client->receive();
		client->closeSocket();
		ReleaseMutex(frameMutex);
		List<UtilSpace::Result ^> ^boxesTemp = gcnew List<UtilSpace::Result ^>();
		if (!result->Equals(""))
		{
			array<System::String ^> ^boxString = result->Split(',');
			for (int i = 0; i < boxString->Length - 1; i++)
			{
				UtilSpace::Result ^temp = gcnew UtilSpace::Result();
				array<System::String ^> ^box = boxString[i]->Split('-');
				temp->x1 = int::Parse(box[0]);
				temp->y1 = int::Parse(box[1]);
				temp->x2 = int::Parse(box[2]);
				temp->y2 = int::Parse(box[3]);
				temp->score = box[4];
				temp->cls = box[5];
				boxesTemp->Add(temp);
			}
		}
		WaitForSingleObject(boxMutex, INFINITE);
		boxes = boxesTemp;
		fpsCount++;
		ReleaseMutex(boxMutex);
	}


			//显示数据用的线程
	private: System::Void timer3_Tick(System::Object^  sender, System::EventArgs^  e) {
		timeCount++;
		label1->Text = "视频帧率: " + (double)((int)(((double)now_frame_no / timeCount) * 100)) / 100 + "fps";
		label2->Text = "平均接收帧率: " +(double)((int)(((double)fpsCount / timeCount) * 100)) / 100 + "fps";
	}

			 //警告区域相关的函数
	private:System::Drawing::Point ^startPoint = nullptr, ^endPoint = nullptr;//鼠标下落点和离开店
			bool drawing = false;
			bool newDraw = false;

	private: System::Void pictureBox1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		if (newDraw) {
			startPoint = gcnew System::Drawing::Point(e->X, e->Y);
			endPoint = nullptr;
			drawing = true;
		}
	}
	private: System::Void pictureBox1_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		if (newDraw) {
			drawing = false;
			endPoint = gcnew System::Drawing::Point(e->X, e->Y);
			newDraw = false;
			//计算当前picturebox上的点的位置
			int topleftX = startPoint->X < endPoint->X ? startPoint->X : endPoint->X;
			int topleftY = startPoint->Y < endPoint->Y ? startPoint->Y : endPoint->Y;
			int bootomRightX = startPoint->X > endPoint->X ? startPoint->X : endPoint->X;
			int bootomRightY = startPoint->Y > endPoint->Y ? startPoint->Y : endPoint->Y;
			//映射回frame
			int x1 = frameWidth * topleftX / pictureBox1->Width;
			int y1 = frameHeight * topleftY / pictureBox1->Height;
			int x2 = frameWidth * bootomRightX / pictureBox1->Width;
			int y2 = frameHeight * bootomRightY / pictureBox1->Height;

			regions->Add(gcnew UtilSpace::Rectangle(x1, y1, x2, y2));
		}
	}
	private: System::Void pictureBox1_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		Graphics ^g = pictureBox1->CreateGraphics();
		if (e->Button == System::Windows::Forms::MouseButtons::Left) {
			if (drawing)
			{
				g->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;//消除锯齿  
				pictureBox1->Refresh();
				//找出矩形的最左上角
				int leftTopX = startPoint->X < e->X ? startPoint->X : e->X;
				int leftTopY = startPoint->Y < e->Y ? startPoint->Y : e->Y;

				g->DrawRectangle(gcnew Pen(Color::Blue, 2), leftTopX, leftTopY, Math::Abs(e->X - startPoint->X), Math::Abs(e->Y - startPoint->Y));
			}
		}
	}
	private: System::Void buttonPaint_Click(System::Object^  sender, System::EventArgs^  e) {
		newDraw = true;
	}
	private: System::Void buttonClean_Click(System::Object^  sender, System::EventArgs^  e) {
		regions->Clear();
	}
			 //警告区域相关的函数结束
	private: System::Void BeepTime_Tick(System::Object^  sender, System::EventArgs^  e) {

		System::Media::SoundPlayer ^sp = gcnew SoundPlayer();
		sp->SoundLocation = "BLEEP1_S.WAV";
		sp->Play();
		beepTime->Stop();
	}
	};
}

