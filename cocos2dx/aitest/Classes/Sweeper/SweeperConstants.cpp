#include "SweeperConstants.h"

#include "utils/helper.h"

SweeperConstants *SweeperConstants::s_instance;

SweeperConstants * SweeperConstants::instance()
{
	if (!s_instance)
	{
		s_instance = new SweeperConstants;
	}
	return s_instance;
}

SweeperConstants::SweeperConstants()
{
	InputNumber = helper::getIntSetting("sweeper_inputs");
	OutputNumber = helper::getIntSetting("sweeper_outputs");
	HiddenLayerNumber = helper::getIntSetting("sweeper_hidden_layers");
	NeuronNumberPerHiddenLayer = helper::getIntSetting("sweeper_neurons_per_hidden_layer");

	SweeperNumber = helper::getIntSetting("sweeper_number");
	MineNumber = helper::getIntSetting("sweeper_mine_number");
	TicksPerGeneration = helper::getIntSetting("sweeper_ticks_per_generation");

	CrossoverRate = helper::getFloatSetting("sweeper_crossover_rate");
	MutateRate = helper::getFloatSetting("sweeper_mutate_rate");
}

SweeperConstants::~SweeperConstants()
{

}
