#pragma once

struct UserCmd;

class GlobalContext {
public:
    bool createMoveHook(float inputSampleTime, UserCmd* cmd);
    void doPostScreenEffectsHook(void* param);
};

inline GlobalContext globalContext;