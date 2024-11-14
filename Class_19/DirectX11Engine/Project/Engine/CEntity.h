#pragma once


class CEntity
{
private:
	static UINT g_NextID;

private:
	wstring		m_Name;
	UINT		m_ID;

public:
	const wstring& GetName() { return m_Name; }
	void SetName(const wstring& _Name) { m_Name = _Name; }
	UINT GetID() { return m_ID; }

	// 자기 자신을 복제한 객체를 반환
	//virtual CEntity* Clone() = 0;

public:
	CEntity();
	CEntity(const CEntity& _Origin);
	virtual ~CEntity();
};

