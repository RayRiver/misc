#ifndef BTDef_h__
#define BTDef_h__

#define NS_BT_BEGIN namespace BehaviorTree {
#define NS_BT_END   }
#define USING_NS_BT using namespace BehaviorTree

enum 
{
	BTInvalidChildNodeIndex = -1,
};

enum class BTRunningStatus
{
	Executing = 0,
	Finish = 1,
	Terminal = -1, // 节点在executing中transition
};

enum class BTNodeEvent
{
	enter,
	exit,
};

enum class BTControlNode
{
	PrioritySelector,
	NonePrioritySelector,
	Sequence,
	Loop,
	Parallel,
};

#endif // BTDef_h__
