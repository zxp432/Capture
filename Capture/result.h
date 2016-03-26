#pragma once
using namespace System;
ref struct Result
{
	int x1;
	int y1;
	int x2;
	int y2;
	System::String ^score;
	System::String ^cls;  /*'aeroplane', 'bicycle', 'bird', 'boat',
						  'bottle', 'bus', 'car', 'cat', 'chair',
						  'cow', 'diningtable', 'dog', 'horse',
						  'motorbike', 'person', 'pottedplant',
						  'sheep', 'sofa', 'train', 'tvmonitor'*/
};  //最后有一个分号