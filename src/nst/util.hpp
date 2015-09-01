#ifndef __NST__UTIL_HPP__
#define __NST__UTIL_HPP__

#include <boost/crc.hpp>
#include <boost/cstdint.hpp>
#include <istream>
#include <vector>

namespace nst { 
    namespace util {
        
        using std::istream;
        using std::string;
        using std::vector;
        using boost::uint32_t;
        using boost::crc_32_type;
        
        template<Target>
        struct FromHex {
            Target value;
            operator Value() const {
                return value;
            }
            
            friend istream& operator>>(istream& in, From& out) {
        }
        
        uint32_t crc32(vector<unsigned char> buffer) {
            crc_32_type crc32;
            crc32.process_bytes(buffer.data(), buffer.size());
            return crc32.checksum();
        }
    }
}    


#endif /* __NST__UTIL_HPP__ */