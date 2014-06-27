#ifndef BevDef_h__
#define BevDef_h__

enum class BevRunningStatus
{
	Executing = 0,
	Finish = 1,
	Terminal = -1, // 节点在executing中transition
};

#define BevInvalidChildNodeIndex -1

#endif // BevDef_h__
