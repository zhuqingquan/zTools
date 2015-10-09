/**
 *	@author		zhuqingquan
 *	@date		2015/10/09
 *	@brief		completement of a simply queue with synchronization
 **/

#pragma once
#ifndef _ZTOOLS_QUEUE_SYNC_H_
#define _ZTOOLS_QUEUE_SYNC_H_

namespace zTools
{
	class queue_sync
	{
	public:
		queue_sync();
		~queue_sync();

		void push(int val);
		void pop();
		int& front() const;

	private:
		queue_sync(const queue_sync&);
		queue_sync& operator=(const queue_sync&);

	private:

	};

	queue_sync::queue_sync()
	{

	}

	queue_sync::~queue_sync()
	{

	}

	void queue_sync::push(int val)
	{

	}

	void queue_sync::pop()
	{

	}

	int& queue_sync::front() const
	{

	}
}//namespace zTools

#endif //_ZTOOLS_QUEUE_SYNC_H_