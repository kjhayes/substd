#ifndef SUBSTD_UTIL_HPP
#define SUBSTD_UTIL_HPP

#include<iostream>
#include<stdint.h>

namespace ss {

///Read

///@fn GetNextU8
uint8_t GetNextU8(std::istream& istr, std::ostream& err = std::cerr) {
    if(istr.eof()){err<<"substd IO Error: Expected Atleast One More Byte But EOF Reached."<<std::endl; return 0;}
    else{
        return istr.get();
    }
}

//Big Endian

///@fn GetNextBEU16
uint16_t GetNextBEU16(std::istream& istr, std::ostream& err = std::cerr){
    uint16_t u = ((uint16_t)GetNextU8(istr, err)) << 8;
    u |= (uint16_t)GetNextU8(istr, err);
    return u;   
}

///@fn GetNextBEU32
uint32_t GetNextBEU32(std::istream& istr, std::ostream& err = std::cerr){
    uint32_t u = ((uint32_t)GetNextBEU16(istr, err)) << 16;
    u |= (uint32_t)GetNextBEU16(istr, err);
    return u;
}

///@fn GetNextBEU64
uint64_t GetNextBEU64(std::istream& istr, std::ostream& err = std::cerr){
    uint64_t u = ((uint64_t)GetNextBEU32(istr, err)) << 32;
    u |= (uint64_t)GetNextBEU32(istr, err);    
    return u;
}

//Little Endian

///@fn GetNextLEU16
uint16_t GetNextLEU16(std::istream& istr, std::ostream& err = std::cerr){
    uint16_t u = (uint16_t)GetNextU8(istr);
    u |= (((uint16_t)GetNextU8(istr)) << 8);
    return u;
}

///@fn GetNextLEU16
uint32_t GetNextLEU32(std::istream& istr, std::ostream& err = std::cerr){
    uint32_t u = (uint32_t)GetNextLEU16(istr);
    u |= (((uint32_t)GetNextLEU16(istr)) << 16);
    return u;
}

///@fn GetNextLEU16
uint64_t GetNextLEU64(std::istream& istr, std::ostream& err = std::cerr){
    uint64_t u = (uint64_t)GetNextLEU32(istr);
    u |= (((uint64_t)GetNextLEU32(istr)) << 32);
    return u;
}

///Write

///@fn PutU8
void PutU8(std::ostream& ostr, const uint8_t& i) {
    ostr.write((char*)(&i), 1);
}

//Big Endian

///@fn PutBEU16
void PutBEU16(std::ostream& ostr, const uint16_t& i) {
    PutU8(ostr, ((i&0xFF00)>>8));
    PutU8(ostr, (i&0x00FF)); 
}

///@fn PutBEU32
void PutBEU32(std::ostream& ostr, const uint32_t& i) {
    PutBEU16(ostr, ((i&0xFFFF0000)>>16));
    PutBEU16(ostr, (i&0x0000FFFF)); 
}

///@fn PutBEU64
void PutBEU64(std::ostream& ostr, const uint64_t& i) {
    PutBEU32(ostr, ((i&0xFFFFFFFF00000000)>>32));
    PutBEU32(ostr, (i&0x00000000FFFFFFFF)); 
}

//Little Endian

///@fn PutLEU16
void PutLEU16(std::ostream& ostr, const uint16_t& i) {
    PutU8(ostr, (i&0x00FF)); 
    PutU8(ostr, ((i&0xFF00)>>8));
}

///@fn PutLEU32
void PutLEU32(std::ostream& ostr, const uint32_t& i) {
    PutLEU16(ostr, (i&0x0000FFFF)); 
    PutLEU16(ostr, ((i&0xFFFF0000)>>16));
}

///@fn PutLEU64
void PutLEU64(std::ostream& ostr, const uint64_t& i) {
    PutLEU32(ostr, (i&0x00000000FFFFFFFF)); 
    PutLEU32(ostr, ((i&0xFFFFFFFF00000000)>>32));
}

}

#endif