#ifndef BTNodeFactory_h__
#define BTNodeFactory_h__

class BTNode;
class BTNodeFactory
{
public:
	template<typename T>
	static BTNode &createActionNode(BTNode *parent, const char *name = nullptr)
	{
		BTNodeAction *node = new T(parent);
		BTNodeFactory::_createNode(node, parent, name);
		return *node; 
	}

	static BTNode &createPrioritySelectorNode(BTNode *parent, const char *name = nullptr);
	static BTNode &createNonePrioritySelectorNode(BTNode *parent, const char *name = nullptr);
	static BTNode &createSequenceNode(BTNode *parent, const char *name = nullptr);
	static BTNode &createLoopNode(BTNode *parent, const char *name = nullptr);
	static BTNode &createParallelNode(BTNode *parent, const char *name = nullptr);

private:
	static void _createNode(BTNode *me, BTNode *parent, const char *name = nullptr);
};

#endif // BTNodeFactory_h__
