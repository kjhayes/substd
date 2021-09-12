#include<substd/dool.hpp>

namespace ss{

dool::dool():val(false),change(false){}
dool::dool(const bool& b):val(b),change(false){}
dool::dool(const dool& d):val(d.val),change(d.change){}

void dool::Set(const bool& b){
    change = (b != val);
    val = val ^ change;
}

bool dool::GetValue(){return val;}
bool dool::IsChanged(){return change;}

}