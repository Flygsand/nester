#include <boost/program_options.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/log/trivial.hpp>
#include <boost/foreach.hpp>
#include <boost/cstdint.hpp>
#include <fstream>
#include <string>
#include <vector>
#include "nst/database.hpp"
#include "nst/util.hpp"

using std::ifstream;
using std::istreambuf_iterator;
using std::string;
using std::vector;
using boost::uint32_t;
using nst::database;
namespace bpo = boost::program_options;
namespace bpt = boost::property_tree;
namespace util = nst::util;

bpo::variables_map parse_options(int argc, char *argv[]);
database parse_database_file(string file);

int main(int argc, char *argv[])
{
    bpo::variables_map vm = parse_options(argc, argv);
    
    string databaseFilePath("NstDatabase.xml");
    
    if (vm.count("database")) {
        databaseFilePath.assign(vm["database"].as<string>());
    }
    
    BOOST_LOG_TRIVIAL(debug) << "Using database file " << databaseFilePath;
    
    database db = parse_database_file(databaseFilePath);
    
    BOOST_FOREACH(char *file, argv) {
        ifstream romFile(file, ifstream::binary);
        vector<unsigned char> romBuffer(
            (istreambuf_iterator<unsigned char>(romFile)), 
            istreambuf_iterator<unsigned char>());
        romFile.close();
        
        uint32_t crc32 = util::crc32(romBuffer);
        database::cart cart = db.getCart(crc32);
        
    }
}

bpo::variables_map parse_options(int argc, char *argv[])
{
    bpo::variables_map vm;
    bpo::options_description desc("Allowed options");
    desc.add_options()
        ("database,d", bpo::value<string>(), "NEStopia database");
        
    bpo::store(bpo::parse_command_line(argc, argv, desc), vm);
    bpo::notify(vm);
    
    return vm;
}

database parse_database_file(string path)
{
    bpt::ptree pt;
    database db;
    bpt::read_xml(path, pt);
    
    BOOST_FOREACH(bpt::ptree::value_type &g, pt.get_child("database")) {
        BOOST_FOREACH(bpt::ptree::value_type &c, g.second.get_child("cartridge")) {
            database::cart cart;
            cart.crc32 = c.second.get<string>("<xmlattr>.crc32");
            cart.prgSize = c.second.get<string>("prg.<xmlattr>.size");
            cart.chrSize = c.second.get<string>("chr.<xmlattr>.size");
            
            db.addCart(cart);
        }
    }
    
    BOOST_LOG_TRIVIAL(debug) << "Read " << db.getCartCount() << " carts from database";
    
    return db;
}