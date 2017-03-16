#ifndef PIPELINE_HPP_INCLUDED
#define PIPELINE_HPP_INCLUDED

#include <vector>


#include "task.hpp"
#include "mystream.hpp"

#include "shell_task.hpp"

/** \class PipeLine pipeline.hpp
 *  \brief Létrehoz egy task-ok ból álló csövet. Segítségével kaszkádosíthatunk bármilyen metódust, ami a taskban van benne.
 * \param A köztes taszkok, és az input output leírók a pipe elején és végén.
 */
class PipeLine : public ShellTask
{
private:
    std::vector<Task*> tasks_p;
    std::vector<MyStream*> pipe_streams;

public:
    /** \brief Pipeline constructor. Az első taszk megadásával jön létre.
     *  \todo Should init input and output here.
     */
    PipeLine(Task* new_task_p) {
        tasks_p.push_back(new_task_p);
    }

    /** \brief Pipeline destructor. Felszabadítja a lefoglalt MyStream-eket és a Task-okat.
     *  \todo Change vector pointers to std::unique_ptr, hence avid delete loops here
     */
    ~PipeLine(){
        std::vector<Task*>::iterator iter;
        for(iter = tasks_p.begin();iter!=tasks_p.end(); iter++ ){
            delete *iter;
        }
        std::vector<MyStream*>::iterator itert;
        for(itert = pipe_streams.begin();itert!=pipe_streams.end(); itert++ ){
            delete *itert;
        }
    }

    /** \brief Egy létrehozott task pointerével a sorba tesszük a taszkot.
     *  \param Task*
     */
    void add_task(Task* new_task_p){
        /* Elõször az utolsó task outputját változtatjuk az új outputra.*/
        pipe_streams.push_back(new MyStream());
        tasks_p.back()->set_output(pipe_streams.back());

        /* Majd az új task inputját az elõzõ task outputjára.*/
        tasks_p.push_back(new_task_p);
        tasks_p.back()->set_input(pipe_streams.back());
    }

    /** \brief Tipikus call függvény, segítségével elindítjuk a már inicializált pipelinet.
        Mikozben fut nem használhatjuk a többi függvényt.
        \todo Should set std::mutex to lock pipeline change during eval.
     */
    void step_task(){
        while(tasks_p.front()->isRunning()){
        std::vector<Task*>::iterator iter;
            for(iter = tasks_p.begin();iter!=tasks_p.end(); iter++ ){
                (*(*iter)).step_task();
            }
        }
    }
};
#endif // PIPELINE_HPP_INCLUDED
