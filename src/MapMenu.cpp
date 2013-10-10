#include "MapMenu.h"

#include "MapMenuItem.h"
#include "tutils.h"

#include <fstream>
#include <sstream>
#include <algorithm>

MapMenu::MapMenu()
{
    //unsigned lastSortLoc = 0;

    std::vector<std::string> fileNames;

    std::string files[3] = {"easy", "medium", "hard"};
	std::string end = ".txt";
	
	std::ifstream in;
	
	for(int i = 0; i < 3; i++)
	{
		int j = 1;
		while(true)
		{
			std::stringstream ss;
			ss << files[i];
			ss << j;
			ss << end;
			std::string map = ss.str();
			
			in.open(map.c_str());
			if(in.good())
			{
				in.close();
				fileNames.push_back(map);
			}
			else
				break;
			
			j++;
		}
	}

    for (unsigned i = 0; i < fileNames.size(); ++i)
    {
        addItem(new MapMenuItem(fileNames[i]));
    }
}

void MapMenu::printPrompt(std::ostream &outStream)
{
    outStream << "Please select a map to play.\n";
}
