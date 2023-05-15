#ifndef MOVE_COMMAND_H
#define MOVE_COMMAND_H

#include "Command.hpp"

class MoveCommand : public Command {
    public:
    virtual void execute() override;
    MoveCommand();
    ~MoveCommand();
};
#endif