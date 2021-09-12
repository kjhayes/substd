#include<substd/readfile.hpp>

#include<iostream>
#include<fstream>

namespace ss{

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