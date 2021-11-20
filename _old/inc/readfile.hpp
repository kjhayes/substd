#ifndef SUBSTD_READFILE_HPP
#define SUBSTD_READFILE_HPP

#include<substd/typedef.hpp>
#include<string>
#include<vector>

namespace ss
{
	
ss_int ReadFile(const char* file_name, std::string& out);
ss_int ReadFile(const char* file_name, std::vector<unsigned char>& out);

}

#endif // READFILE_HPP
