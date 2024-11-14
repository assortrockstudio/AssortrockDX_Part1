#pragma once
#include "singleton.h"


class CTimeMgr :
    public CSingleton<CTimeMgr>
{
    SINGLE(CTimeMgr)
private:
    LARGE_INTEGER   m_llFrequency;  // 초당 카운트 수
    LARGE_INTEGER   m_llCurCount;   // 현재 카운트 수
    LARGE_INTEGER   m_llPrevCount;  // 이전 프레임 카운트 수

    float           m_DT;           // Delta Time : 1프레임 동작하는데 걸린 시간
    float           m_Time;         // 프로세스 실행 이후의 누적 시간
    float           m_AccTime;      // 1초를 체크하기 위한 시간 누적변수

    UINT            m_FrmCount;

public:
    void init();
    void tick();

public:
    float GetDeltaTime()
    {
        return m_DT;
    }
};

