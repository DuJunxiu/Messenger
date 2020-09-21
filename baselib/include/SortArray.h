
#ifndef __SORT_ARRAY_H__
#define __SORT_ARRAY_H__

#include <string.h>

namespace MyMessenger
{
	// 数组模板类
	template<class T, int iCount>
	class CArray
	{
	public:
		CArray() { m_iUsedCount = 0; }
		~CArray() {}

	public:
		// 已用大小
		int size()
		{
			return m_iUsedCount;
		}
		
		// 容量
		int capacity()
		{
			return iCount;
		}
		
		// 清空
		void clear()
		{
			m_iUsedCount = 0;
		}
		
		// 是否为空
		bool empty()
		{
			return 0 == m_iUsedCount;
		}
		
		// 是否已满
		bool full()
		{
			return m_iUsedCount >= iCount;
		}
		
		// 尾插
		int push(const T& stData)
		{
			if (m_iUsedCount >= iCount)
			{
				return -1;
			}
			
			m_astData[m_iUsedCount] = stData;
			++m_iUsedCount;
			
			return 0;
		}
		
		int insert(int iIndex, const T& stData)
		{
			if (iIndex < 0 || iIndex >= iCount)
			{
				return -1;
			}
			
			if (m_iUsedCount >= iCount)
			{
				return -2;
			}
			
			if (iIndex == m_iUsedCount + 1)
			{
				m_astData[m_iUsedCount] = stData;
				++m_iUsedCount;
			}
			else
			{
				for (int i = m_iUsedCount; i > iIndex; --i)
				{
					m_astData[i] = m_astData[i - 1];
				}
				
				m_astData[iIndex] = stData;
				++m_iUsedCount;
			}
			
			return 0;
		}
		
		// 尾删
		int pop()
		{
			if (m_iUsedCount <= 0)
			{
				return -1;
			}
			
			--m_iUsedCount;
		}
		
		int erase(int iIndex)
		{
			if (iIndex > m_iUsedCount)
			{
				return -1;
			}
			
			if (iIndex == m_iUsedCount)
			{
				--m_iUsedCount;
			}
			else
			{
				for (int i = iIndex; i < m_iUsedCount - 1; ++i)
				{
					m_astData[i] = m_astData[i + 1];
				}
				
				--m_iUsedCount;
			}
			
			return 0;
		}
		
		// 返回对应下标的数据
		const T& operator[](int iIndex) const
		{
			int iRet = checkIndex(iIndex);
			
			return m_astData[iRet];
		}

		T& operator[](int iIndex)
		{
			int iRet = checkIndex(iIndex);
			
			return m_astData[iRet];
		}
		
	private:
		// 容错处理
		int checkIndex(int iIndex)
		{
			if (iIndex < 0)
			{
				iIndex = 0;
			}
			else if (iIndex > m_iUsedCount)
			{
				iIndex = m_iUsedCount - 1;
			}
			
			return iIndex;
		}

	private:
		int m_iUsedCount;
		T m_astData[iCount];
	};
}

#endif