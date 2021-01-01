#include "Utilities.h"

#pragma warning( push )
#pragma warning( disable : 4706)
// String hashing function
// Taken from http://www.cse.yorku.ca/~oz/hash.html (public domain)
ullong Engine::StringHash(const std::string& a_String)
{
    ullong hash = 0;
    int c;
    const char* cstr = a_String.c_str();

    while (c = *cstr++)
    {
        hash = c + (hash << 6) + (hash << 16) - hash;
    }

    return hash;
}

bool Engine::Replace(std::string& str, const std::string& from, const std::string& to)
{
    size_t start_pos = str.find(from);
    if (start_pos == std::string::npos)
    {
        return false;
    }
    str.replace(start_pos, from.length(), to);
    return true;
}
