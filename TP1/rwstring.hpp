#ifndef RWSTRING_HPP_INCLUDED
#define RWSTRING_HPP_INCLUDED

#include <fstream>
#include <string>

using namespace std;

// Funciones auxiliares para serializar struct que contengan strings

void writestring(fstream &fs, string str, int largo)
{
    str.resize(largo);
    fs.write(str.data(), largo);
}

string readstring(fstream &fs, int largo)
{
    char *buffer = new char[largo + 1];
    buffer[largo] = '\0';
    fs.read(buffer, largo);
    string str(buffer);
    delete[] buffer;
    return str;
}

#endif // RWSTRING_HPP_INCLUDED
