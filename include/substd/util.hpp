#ifndef SUBSTD_UTIL_HPP
#define SUBSTD_UTIL_HPP

#include<list>
#include<iostream>
#include<fstream>

#include<substd/vec.hpp>

namespace ss {
    //List Functions

    /**
     * @fn PointsBetween
     * @return std::list<vec<T,dim>> List of n points in a line between a and b, inclusive.
     */
    template<typename T, size_t dim>
    std::list<vec<T,dim>> PointsBetween(const vec<T,dim>& a, const vec<T,dim>& b, const int& n){
        vec<T,dim> jump = (b-a) * (1/((T)(num-1)));
	    std::list<vec<T,dim>> list;
	    for(int i = 0; i<num; i++)
	    {
		    list.push_back(a+(jump*i));
	    }
	    return list;
    }

    //File Utilities

    int ReadFile(const char* file_name, std::string& out){
    std::ifstream file;
    file.open(file_name);
    std::string line;
    if(file.is_open())
        {
            while(std::getline(file,line))
                {out.append(line+"\n");}
            file.close();
        }
    else{std::cout<<"File: "<<file_name<<" Failed To Open"<<std::endl;return 1;}
    return 0;
}

    int ReadFile(const char* file_name, std::vector<unsigned char>& out){
        std::ifstream file;
        file.open(file_name);
        if(!file.is_open()){std::cout<<"File: "<<file_name<<" Failed To Open"<<std::endl; return 1;}
        char b;
        file.get(b);
        out.push_back(*reinterpret_cast<unsigned char*>(&b));
        while(file.get(b)){
            out.push_back(*reinterpret_cast<unsigned char*>(&b));    
        }
        file.close();
        return 0;
    }
}

#endif