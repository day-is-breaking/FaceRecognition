#pragma once
#ifndef MOL_TRA_H
#define MOL_TRA_H


#include "opencv_head.h"
class Mol_Tra
{
public:
	void modul_train();
	void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, char separator = ' ');
};

#endif // !
