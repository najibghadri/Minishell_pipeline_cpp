#ifndef SHELL_TASK_HPP_INCLUDED
#define SHELL_TASK_HPP_INCLUDED

#include <stdlib.h>

/** \class ShellTask shell_task.hpp
 *  \brief Bázis osztály az összes shell-ben futó taszkhoz.
 */
class ShellTask
{
public:
    virtual void step_task()
    {
        system ("cls");
    }
};

#endif // SHELL_TASK_HPP_INCLUDED
