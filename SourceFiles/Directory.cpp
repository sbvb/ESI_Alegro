#include "Allegro_esi.h"
using namespace std;

void Search_Dir::load_files(string direct)
{
    /*
        *Look what's on the directory
        *Adds on the container objects of type string, which are the directory files
        *The directory is passed as an argument. (using an string)
    */
    DIR *dir = NULL;

    struct dirent *input = NULL;

    dir = opendir(direct.c_str()); //starts reading the directory

    if(dir == 0) //error treating
    {
        cerr << "Failed to open the directory!" << endl;
        exit(1);
    }

    while ((input = readdir(dir)))
    {
        if(!strcmp(input->d_name, ".") || !strcmp(input->d_name, "..")) continue;
        container.push_back(direct + input->d_name); //direct is the directory's name

    }
    closedir(dir); //stops reading the directory
}

void Search_Dir::debug_container() //no comment needed
{
    for(it = container.begin(); it != container.end(); it++)
    {
        cout << *it << endl;
    }
}

void Search_Dir::destroy() //no comment needed
{
    container.clear();
}

