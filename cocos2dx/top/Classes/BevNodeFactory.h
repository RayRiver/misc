#ifndef BevNodeFactory_h__
#define BevNodeFactory_h__

class BevNode;
class BevNodeFactory
{
public:
	template<typename T>
	static BevNode &createTerminalNode(BevNode *parent, const char *name = nullptr)
	{
		BevNodeTerminal *node = new T(parent);
		BevNodeFactory::_createNode(node, parent, name);
		return *node; 
	}

	static BevNode &createPrioritySelectorNode(BevNode *parent, const char *name = nullptr);

private:
	static void _createNode(BevNode *me, BevNode *parent, const char *name = nullptr);
};

#endif // BevNodeFactory_h__
