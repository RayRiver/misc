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
	int InputNumber;						// ��������������������;
	int OutputNumber;						// �������;
	int HiddenLayerNumber;					// ���ز�����;
	int NeuronNumberPerHiddenLayer;			// ÿ�����ز����ϸ����;

	int SweeperNumber;						// sweeper������Ⱥ��������;
	int MineNumber;							// ��������;
	int TicksPerGeneration;					// ÿһ��ticks;

	Fixed CrossoverRate;					// �ӽ���;
	Fixed MutateRate;						// ������;
};

#define CONSTANTS (*SweeperConstants::instance())

#endif // SweeperConstants_h__
