#pragma once
#include "singleton.h"

enum class KEY
{
    W,
    S,
    A,
    D,

    _0,
    _1,
    _2,
    _3,
    _4,
    _5,
    _6,
    _7,
    _8,
    _9, 

    LEFT,
    RIGHT,
    UP,
    DOWN,

    ENTER,
    ESC,
    SPACE,
    LSHILFT,
    ALT,
    CTRL,

    KEY_END,
};


enum class KEY_STATE
{
    TAP,
    PRESSED,
    RELEASED,
    NONE,
};

struct tKeyInfo
{
    KEY_STATE   State;
    bool        PrevPressed;
};

class CKeyMgr :
    public CSingleton<CKeyMgr>
{
    SINGLE(CKeyMgr)
private:
    vector<tKeyInfo>   m_vecKey;

public:
    void init();
    void tick();

public:
    KEY_STATE GetKeyState(KEY _Key) { return m_vecKey[(UINT)_Key].State; }
};

