
#ifndef __SINGLETON_H__
#define __SINGLETON_H__

namespace MyMessenger
{
    // 饿汉单例模板类
    template<class T>
    class CSingleton
    {
    public:
        static T* GetInstance()
        {
            if (nullptr == m_pInstance)
            {
                m_pInstance = new CSingleton;
            }

            return &m_pInstance->m_iInstance;
        }

    protected:
        CSingleton()
        {}

    public:
        virtual ~CSingleton() {}
        CSingleton(CSingleton&) = delete;
        CSingleton& operator=(const CSingleton) = delete;

    private:
        T m_iInstance;
        static CSingleton<T>* m_pInstance;
    };

    template<class T>
    CSingleton<T>* CSingleton<T>::m_pInstance = nullptr;
}

#endif
