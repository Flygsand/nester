#ifndef __NST__DATABASE_HPP__
#define __NST__DATABASE_HPP__

#include <boost/unordered_map.hpp>
#include <string>

using boost::unordered_map;
using std::string;

namespace nst
{
    class database
    {
    public:
        struct cart
        {
            string crc32;
            string prgSize;
            string chrSize;
        };
        
        typedef unordered_map<string, cart>::size_type size_type;
        
        void addCart(cart c);
        cart getCart(string crc32);
        size_type getCartCount(void);
    
    private:
        unordered_map<string, cart> m_carts;
    };
}

#endif /* __NST__DATABASE_HPP__ */