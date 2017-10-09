#ifndef __CONSTANTS_H_INCLUDED__
#define __CONSTANTS_H_INCLUDED__
#include<string>
namespace cfg
{
	namespace xml
	{

		namespace paths
		{
			const std::string XML_ELEM_ROOT = "Graphics";
			const std::string XML_ELEM_SHAPES = "Shapes";
			const std::string XML_ELEM_SHAPE = "Shape";
			const std::string XML_ELEM_DATAPOINT = "DataPoint";
			const std::string XML_ELEM_POSITION = "Position";
		}
	}
}

#define XML_PATH_ROOT cfg::xml::paths::XML_ELEM_ROOT
#define XML_PATH_SHAPES XML_PATH_ROOT + "." + cfg::xml::paths::XML_ELEM_SHAPES
#define XML_PATH_SHAPE XML_PATH_SHAPES + "." + cfg::xml::paths::XML_ELEM_SHAPE
#define XML_PATH_DATAPOINT XML_PATH_SHAPE + "." + cfg::xml::paths::XML_ELEM_DATAPOINT
#define XML_PATH_POSITION XML_PATH_DATAPOINT + "." + cfg::xml::paths::XML_ELEM_POSITION
#endif