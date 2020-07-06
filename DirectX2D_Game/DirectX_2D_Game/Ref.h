#pragma once
#include "helper.h"
class CRef
{
protected:
	CRef();
	virtual ~CRef() {};
protected:
	int m_iRef;
	
	bool m_bLife;
	wstring m_strTag;
public:
	bool m_bEnable;
	wstring GetTag()const& noexcept {
		return m_strTag;
	}
	void SetTag(wstring Tag) noexcept{
		m_strTag = std::move(Tag); 
	}
	void AddRef(); 
	int Release() {
		--m_iRef;
		if (m_iRef == 0) {
			delete this;
			return 0; 
		}
		return m_iRef; 
	}
	
	void SetEnable(bool bEnable) {
		m_bEnable = bEnable; 
	}
	void SetLife(bool bLife) {
		m_bLife = bLife; 
	}
	bool GetEnable() const {
		return m_bEnable; 
	}
	bool GetLife() const {
		return  m_bLife;
	}
	virtual void Die()
	{
		m_bLife = false; 
	}
};

