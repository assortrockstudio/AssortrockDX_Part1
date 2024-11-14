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

public:
	CEntity();
	CEntity(const CEntity& _Origin);
	~CEntity();
};

