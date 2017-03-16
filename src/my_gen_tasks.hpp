#ifndef MY_GEN_TASKS_HPP_INCLUDED
#define MY_GEN_TASKS_HPP_INCLUDED

#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

#include "mystream.hpp"
#include "task.hpp"

/** \brief Merge rendezést szimuláló osztály: két rendezett vektort összefésül és egy rendezett vektort ad.
Ha ezt a taskot kaszkádosítjuk (pipeban) önmagával, akkor exponenciális mennyiségû vektort tudunk összefésülni.
A futását szakaszokra bontottuk, így szimulálva a program egymás utáni bemeneteit. Szálakat használva nincs erre szükség.
 *  \todo convert to real task, after threading.
 */
class Merger : public Task {
private:
    std::vector<int> vec1;
    std::vector<int> vec2;
    std::vector<int> target_v;
    enum Stage { wait_input1, wait_input2, calculate} current_stage;
public:
    Merger(): Task(), current_stage(wait_input1){}
protected:
    void eval(MyStream& input, MyStream& output) {
        if(current_stage == wait_input1){
            std::string line;
            if((line=input.read())!=""){
                std::stringstream ssline(line);
                int n;
                while(ssline >> n)
                    vec1.push_back(n);
            }
            else
                return;
            if(vec1.size() == 0){
                throw "Üres az 1. vektor! Rossz adatbevitel lehetett az ok.";
            }
            current_stage = wait_input2;
            return;
        }
        if(current_stage == wait_input2){
            std::string line;
            if((line=input.read())!=""){
                std::stringstream ssline(line);
                int n;
                while(ssline >> n)
                    vec2.push_back(n);
            }
            else
                return;
            if(vec2.size() == 0){
                throw "Üres a 2. vektor! Rossz adatbevitel lehetett az ok.";
            }
            current_stage = calculate;
        }
        if(current_stage == calculate){
            if(vec1.size()!=vec2.size())
                throw "Különböző méretű vektorok!";

            target_v.reserve( vec1.size() + vec2.size() ); // preallocate memory
            target_v.insert( target_v.begin(),vec1.begin(), vec1.end() );
            target_v.insert( target_v.begin(), vec2.begin(), vec2.end() );
            std::inplace_merge(target_v.begin(),target_v.begin()+target_v.size()/2,target_v.end());


            std::stringstream  ssline;
            for (unsigned int i = 0; i < target_v.size();i++)
                ssline << target_v[i] << ' ';

            ssline << std::endl;
            std::string line;
            std::getline(ssline,line);
            output.write(line);

            vec1.clear();
            vec2.clear();
            target_v.clear();
            current_stage = wait_input1;
            state = stopped;
        }
    }
};

/** \brief Bemenetkezelő osztály
 * \param std::istream&
 */
class UserInput : public Task {
private:
    std::istream& is;
public:
    UserInput(std::istream& is = std::cin): is(is){
        if(!is.good())
            throw "Hiba az input megynyitásánán";
    }
protected:
    void eval(MyStream& input, MyStream& output) {
        std::string line;
        if(std::getline(is,line)){
            output.write(line);
        }
        if(is.eof())
            state=stopped;
    }
};

/** \brief Kimenetkezelő osztály
 * \param std::ostream&
 */
class UserOutput : public Task{
private:
    std::ostream& os;
public:
    UserOutput(std::ostream& os = std::cout): os(os){
        if(!os.good())
            throw "Hiba az output megnyitásánál";
    }
protected:
    void eval(MyStream& input, MyStream& output) {
        std::string line;
        while((line=input.read())!=""){
            os << line << std::endl;
        }
    }
};

#endif // MY_GEN_TASKS_HPP_INCLUDED
