/**
 *	@author		zhuqingquan
 *	@date		2015/10/09
 *	@brief		completement of a simply queue with synchronization
 **/

#pragma once
#ifndef _ZTOOLS_QUEUE_SYNC_H_
#define _ZTOOLS_QUEUE_SYNC_H_

#include <Windows.h>

namespace zTools
{
	class queue_sync_spsc
	{
	public:
		queue_sync_spsc();
		~queue_sync_spsc();

		void push(int val);
		void pop();
		int& front() const;
		size_t size() const;

	private:
		queue_sync_spsc(const queue_sync_spsc&);
		queue_sync_spsc& operator=(const queue_sync_spsc&);

		void clear();

		struct queue_sync_node
		{
			queue_sync_node* next;
			int val;

			queue_sync_node() : next(0) {}
		};
	private:
		typedef UINT32 size_type;

		struct head_size
		{
			union
			{
				size_type iVal;
				queue_sync_node* pt;
			} head;
			size_type size;
		};

		struct size_tail
		{
			size_type size;
			union
			{
				size_type iVal;
				queue_sync_node* pt;
			} tail;
		};

		union { size_type i; queue_sync_node* pt; } m_head;
		size_type m_size;
		union { size_type i; queue_sync_node* pt; } m_tail;
		//queue_sync_node* m_head;
		//queue_sync_node* m_tail;
	};

	queue_sync_spsc::queue_sync_spsc()
		: m_size(0)
	{
		m_tail.pt = new queue_sync_node;
		m_head.pt = m_tail.pt;
	}

	queue_sync_spsc::~queue_sync_spsc()
	{
		clear();
		delete m_tail.pt;
		m_tail.pt = m_head.pt = 0;
	}

	void queue_sync_spsc::push(int val)
	{
		queue_sync_node* newnode = new queue_sync_node;
		m_tail.pt->val = val;
		m_tail.pt->next = newnode;

		size_tail oldst;
		size_tail newst;

		while (true)
		{
			oldst.size = m_size;
			oldst.tail.pt = m_tail.pt;

			newst.size = oldst.size + 1;
			newst.tail.pt = newnode;

			LONG64 oldval = *(LONG64*)(&oldst);
			if (oldval == InterlockedCompareExchange64((LONG64*)(struct size_tail*)(&m_size), *(LONG64*)(&newst), oldval))
				break;
		}
		
		//InterlockedExchange(reinterpret_cast<long*>(&m_tail), reinterpret_cast<long>(newnode));
	}

	void queue_sync_spsc::pop()
	{
		while (m_head != m_tail)
		{
			queue_sync_node* pPoped = m_head;
			queue_sync_node* next = m_head->next;
			InterlockedExchange(reinterpret_cast<long*>(&m_head), reinterpret_cast<long>(next));
			delete pPoped;
			break;
		}
	}

	int& queue_sync_spsc::front() const
	{
		if (m_head == m_tail)
			throw "queue_sync is empty";
		return m_head->val;
	}

	size_t queue_sync_spsc::size() const
	{
		return m_size;
	}

	void queue_sync_spsc::clear()
	{
		while (m_size>0)
		{
			pop();
		}
	}
}//namespace zTools

#endif //_ZTOOLS_QUEUE_SYNC_H_