#include<substd/util.hpp>

#include<substd/vec.hpp>
#include<substd/constants.hpp>

#include<functional>
#include<cmath>

namespace ss
{

std::list<vec2<ss_float>> PointsBetween(const vec2<ss_float>& a, const vec2<ss_float>& b, const int& num)
{
	vec2<ss_float> jump = (b-a) * (1.0f/((float)(num-1)));
	std::list<vec2<ss_float>> list;
	for(int i = 0; i<num; i++)
	{
		list.push_back(a+(jump*i));
	}
	return list;
}	

float DegToRad(const float& deg)
{
	return deg * SS_PI_DIV_180;
}

float RadToDeg(const float& rad)
{
	return rad * SS_180_DIV_PI;
}

}