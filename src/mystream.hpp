#ifndef MYSTREAM_HPP_INCLUDED
#define MYSTREAM_HPP_INCLUDED

#include <deque>
#include <string>

/** \brief Saját stream osztály.A streameknél sokkal egyszerûb deque string alapú 
read/write metódusok álnak rendelkezésre. Ez hibamentes üzenetváltást valósít meg.
 */
class MyStream {
private:
    std::deque<std::string> strings;
public:
    /**< Sor olvasása a MyStream tárolójából */
    const std::string read() {
        if(strings.size()){
            std::string line = strings.back();
            strings.pop_back();
            return line;
        }
        return std::string("");
    }

    /**< Sor írása a MyStream tárolójába */
    void write(std::string line){
        strings.push_front(line);
    }
};



#endif // MYSTREAM_HPP_INCLUDED
