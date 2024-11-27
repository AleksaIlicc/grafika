#pragma once
class Item
{
public:
	float min;
	float max;
	float v25;
	float v75;
	CString label;

public:
	void set(float min, float v25, float v75 , float max, CString label) {
		this->min = min;
		this->max = max;
		this->v25 = v25;
		this->v75 = v75;
		this->label = label;
	}
};

