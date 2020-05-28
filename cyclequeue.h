#ifndef CYCLEQUEUE_H
#define CYCLEQUEUE_H


template <class T>
class CycleQueue
{
    private:
        unsigned int m_size;
        int m_front;
        int m_rear;
        T*  m_data;
    public:
        CycleQueue(unsigned size)
            :m_size(size),
            m_front(0),
            m_rear(0)
        {
            m_data = new T[size];
        }

        ~CycleQueue()
        {
            delete [] m_data;
        }

        bool isEmpty()
        {
            return m_front == m_rear;
        }

        bool isFull()
        {
            return m_front == (m_rear + 1)%m_size;
        }

        void push(const T& ele)
        {
            memcpy(&m_data[m_rear],&ele,sizeof(T));
            m_rear = (m_rear + 1)%m_size;
        }

        void pop(T& out)
        {
            memcpy(&out,&m_data[m_front],sizeof(T));
            m_front = (m_front + 1)%m_size;
        }
};

#endif // CYCLEQUEUE_H
