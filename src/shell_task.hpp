#ifndef SHELL_TASK_HPP_INCLUDED
#define SHELL_TASK_HPP_INCLUDED

#include <stdlib.h>

/** \class ShellTask shell_task.hpp
 *  \brief B�zis oszt�ly az �sszes shell-ben fut� taszkhoz.
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
