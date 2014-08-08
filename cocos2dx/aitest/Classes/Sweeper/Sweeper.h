#ifndef Sweeper_h__
#define Sweeper_h__

#include <vector>

#include "cocos2d.h"

#include "utils/Fixed.h"
#include "NeuralNet.h"

class Sweeper : public cocos2d::Node
{
public:
	CREATE_FUNC(Sweeper);
	bool update(const FixedVec2 &closestPos);

	bool checkCollision(const FixedVec2& mine);

	const FixedVec2 &getFixedPosition() const { return m_fixedPosition; }
	void setFixedPosition(const FixedPoint &p) { m_fixedPosition = p; setPosition((float)p.x, (float)p.y); }

	void resetFitness();
	void increaseFitness();

	// 设置基因;
	void setGenome(const Genome &chromo) { m_brain.setGenome(chromo); }


private:
	bool init();

private:
	cocos2d::DrawNode *m_drawnode;
	cocos2d::Label *m_label;

	NeuralNet m_brain;						// 神经网络;
	Fixed m_speed;							// 速度;

	FixedSize m_size;

	FixedVec2 m_fixedPosition;
	FixedVec2 m_lookat;
	Fixed m_rotation;
	
	Fixed m_lTrack, m_rTrack;
};

#endif // Sweeper_h__
