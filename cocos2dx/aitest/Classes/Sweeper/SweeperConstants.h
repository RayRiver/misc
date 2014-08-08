#ifndef SweeperConstants_h__
#define SweeperConstants_h__

#include "utils/helper.h"

class SweeperConstants
{
public:
	static SweeperConstants *SweeperConstants::instance();
	~SweeperConstants();

private:
	static SweeperConstants *s_instance;
	SweeperConstants();

public:
	int InputNumber;						// 输入数量（基因数量）;
	int OutputNumber;						// 输出数量;
	int HiddenLayerNumber;					// 隐藏层数量;
	int NeuronNumberPerHiddenLayer;			// 每个隐藏层的神经细胞数;

	int SweeperNumber;						// sweeper数量（群体数量）;
	int MineNumber;							// 地雷数量;
	int TicksPerGeneration;					// 每一代ticks;

	Fixed CrossoverRate;					// 杂交率;
	Fixed MutateRate;						// 变异率;
};

#define CONSTANTS (*SweeperConstants::instance())

#endif // SweeperConstants_h__
