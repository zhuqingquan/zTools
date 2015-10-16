#include "queue_sync.h"
#include <assert.h>

using namespace zTools;

int test_queue_sync(int argc, char* argv[])
{
	queue_sync q;
	q.push(0);
	q.push(3);
	q.push(2);
	q.push(5);
	q.push(53);

	assert(q.size() == 5);
	assert(q.front() == 0);
	q.pop();

	assert(q.size() == 4);
	assert(q.front() == 3);
	q.pop();

	assert(q.size() == 3);
	assert(q.front() == 2);
	q.pop();
	
	assert(q.size() == 2);
	assert(q.front() == 5);
	q.pop();
	
	assert(q.size() == 1);
	assert(q.front() == 53);
	q.pop();

	return 0;
}