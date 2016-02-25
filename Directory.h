#ifndef DIRECTORY_H_INCLUDED
#define DIRECTORY_H_INCLUDED


class Search_Dir //A class to treat directories
{
public:
    std::deque<std::string> container; //an deque that contains the name of the files on the directory
    std::deque<std::string>::iterator it;

    void load_files(std::string direct); //"writes" on the container the content of the directory (string).
                                    //it's argument is the directory's name.
    void debug_container(); //list the container's content (only used for debugging)
    void destroy(); //clear the container, releasing memory.
};

#endif // DIRECTORY_H_INCLUDED
