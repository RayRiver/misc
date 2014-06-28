#ifndef BevNodeFactory_h__
#define BevNodeFactory_h__

class BevNode;
class BevNodeFactory
{
public:
	template<typename T>
	static BevNode &createActionNode(BevNode *parent, const char *name = nullptr)
	{
		BevNodeAction *node = new T(parent);
		BevNodeFactory::_createNode(node, parent, name);
		return *node; 
	}

	static BevNode &createPrioritySelectorNode(BevNode *parent, const char *name = nullptr);
	static BevNode &createNonePrioritySelectorNode(BevNode *parent, const char *name = nullptr);
	static BevNode &createSequenceNode(BevNode *parent, const char *name = nullptr);
	static BevNode &createLoopNode(BevNode *parent, const char *name = nullptr);
	static BevNode &createParallelNode(BevNode *parent, const char *name = nullptr);

private:
	static void _createNode(BevNode *me, BevNode *parent, const char *name = nullptr);
};

#endif // BevNodeFactory_h__
