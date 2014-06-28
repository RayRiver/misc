#ifndef BevDef_h__
#define BevDef_h__

#define BevInvalidChildNodeIndex -1

enum class BevRunningStatus
{
	Executing = 0,
	Finish = 1,
	Terminal = -1, // �ڵ���executing��transition
};

enum class BevControlNode
{
	PrioritySelector,
	NonePrioritySelector,
	Sequence,
	Loop,
	Parallel,
};

#endif // BevDef_h__
