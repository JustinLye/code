#ifndef TYPEDEFS_H_INCLUDED
#define TYPEDEFS_H_INCLUDED

#include<map>
#include<boost/property_tree/ptree.hpp>
#include<boost/property_tree/xml_parser.hpp>
#include<boost/optional.hpp>

typedef unsigned int comp_id;
typedef boost::optional<comp_id> opt_uint;
typedef boost::optional<std::string> opt_str;
typedef boost::optional<double> opt_dbl;


#endif