#ifndef TASK_HPP_INCLUDED
#define TASK_HPP_INCLUDED

#include "mystream.hpp"
#include "shell_task.hpp"

/** \class Task task.hpp
 *  \brief Minden task oszt�lynak van egy inputja �s egy outputja, �s egy met�dusa, amit �r�kl�s sor�n defini�lunk. Absztrakt oszt�ly.
 */
class Task: public ShellTask
{
private:
    MyStream* input;
    MyStream* output;
protected:
    //Fut�s jelz�
    enum State {running, stopped} state;
    virtual void eval(MyStream& input,MyStream& output) = 0;
public:
    Task():state(running) {}
    virtual ~Task(){}

    bool isRunning() const { return state == running; }

    void set_input(MyStream* input_stream){
        input=input_stream;
    }

    void set_output(MyStream* output_stream){
        output=output_stream;
    }

    void step_task(void){
        eval(*input,*output);
    }
};


#endif // TASK_HPP_INCLUDED
