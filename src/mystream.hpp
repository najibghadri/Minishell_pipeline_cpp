#ifndef MYSTREAM_HPP_INCLUDED
#define MYSTREAM_HPP_INCLUDED

#include <deque>
#include <string>

/** \brief Saj�t stream oszt�ly. Sz�ks�g volt r� mert az std stream-ek t�l bonyolultak voltak.
Egyszer� deque string alap� read/write met�dusok �lnak rendelkez�sre. Ez hibamentes �zenetv�lt�st enged meg.
 */
class MyStream {
private:
    std::deque<std::string> strings;
public:
    /**< Sor olvas�sa a MyStream t�rol�j�b�l */
    const std::string read() {
        if(strings.size()){
            std::string line = strings.back();
            strings.pop_back();
            return line;
        }
        return std::string("");
    }

    /**< Sor �r�sa a MyStream t�rol�j�ba */
    void write(std::string line){
        strings.push_front(line);
    }
};



#endif // MYSTREAM_HPP_INCLUDED
