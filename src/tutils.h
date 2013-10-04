/*
    tutils - a library of functions with some use.
    Copyright (C) 2013  Frank Allenby

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see http://www.gnu.org/licenses/.
*/

#ifndef TUTILS_H
#define TUTILS_H

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

#include <dirent.h>

namespace tutils
{

    /** Function to split a string into a vector of its substrings by a predefined delimeter.
     *
     *  e.g. "Hello world!" split with the delimeter of a space would give the vector result of
     *       {"Hello", "world!"}.
     */
    inline void split(std::vector<std::string>& _out, const std::string& _toSplit, const std::string& _delimeter)
    {
        std::string temp;

        unsigned pos = _toSplit.find(_delimeter.c_str());

        if (pos > _toSplit.length())
        {
            _out.push_back(_toSplit);
            return;
        }

        unsigned lastPos = 0;

        while (pos < _toSplit.length())
        {
            for (unsigned i = lastPos; i < pos; ++i)
            {
                temp += _toSplit[i];
            }

            _out.push_back(temp);
            temp = "";

            lastPos = pos + _delimeter.length();
            pos = _toSplit.find(_delimeter.c_str(), pos + 1);
        }

        if (lastPos == _toSplit.length())
        {
            return;
        }

        for (unsigned i = lastPos; i < _toSplit.length(); ++i)
        {
            temp += _toSplit[i];
        }
        _out.push_back(temp);
    }

    /** Function to convert from any type to any other type.
     *
     *  Convert works provided that the correct operators are overloaded.
     *  A compiler error should be thrown if an invalid conversion is attempted.
     */
    template <class FROM, class TO>
    inline void convert(const FROM& _f, TO& _out)
    {
        std::stringstream stream;

        stream << _f;
        stream >> _out;
    }

    /** Get an unsorted list of all of the files in the provided root directory with the provided extension recursively.
     *
     *  Searches all child directories for files with the provided extension within the provided root directory.
     */
    inline void getFilesInDirRecursive(std::vector<std::string>& outList, const std::string& rootPath, const std::string& ext)
    {
        DIR *dir = opendir(rootPath.c_str());
        struct dirent *file = 0;

        if (dir != NULL){
            while ((file = readdir(dir))){
                std::string fName(file->d_name);

                if (file->d_type == DT_REG)
                {
                    if (fName.length() > ext.length())
                    {
                        if (fName.substr(fName.length() - ext.length(), ext.length()) == ext)
                        {
                            if (rootPath == ".")
                            {
                                outList.push_back(fName);
                            } else {
                                outList.push_back(rootPath + ((rootPath.find_last_of("/") == rootPath.length() - 1) ? "" : "/") + fName);
                            }
                        }
                    }
                }

                std::string dName = fName;
                if (file->d_type == DT_DIR)
                {
                    if (dName != "." && dName != "..")
                    {
                        dName = "/" + dName + "/";
                        dName = rootPath + dName;
                        getFilesInDirRecursive(outList, dName.c_str(), ext);
                    }
                }
            }
        }

        closedir(dir);
    }

    /** Sanitize a string.
     *
     *  Removes all characters in the given string from the original string.
     *
     *  @param str a std::string reference
     *  @param list a constant std::string reference
     */
    inline void sanitize(std::string& str, const std::string& list)
    {
        std::string temp;
        for (unsigned i = 0; i < str.length(); ++i)
        {
            if (list.find(str[i]) == std::string::npos)
            {
                temp += str[i];
            }
        }
        str = temp;
    }

} // namespace tutils

#endif
