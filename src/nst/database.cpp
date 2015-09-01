#include "database.hpp"

namespace nst {
    void database::addCart(database::cart cart)
    {
        m_carts[cart.crc32] = cart;
    }
    
    database::cart database::getCart(string crc32)
    {
        return m_carts.at(crc32);
    }
    
    database::size_type database::getCartCount(void)
    {
        return m_carts.size();
    }
}