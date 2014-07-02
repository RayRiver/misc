#ifndef BTReader_h__
#define BTReader_h__

#include <string>
#include <map>
#include <functional>

#include "json/rapidjson.h"
#include "json/document.h"

#include "BehaviorTree.h"

class BTReader
{
public:
	typedef std::function<BTNode *(BTNode *parent, const char *name)> ActionNodeHandler;
	typedef std::function<BTPrecondition *()> PreconditionHandler;

public:
	static BTReader *getInstance();

	bool registerActionNodeHandler(const char *actionNodeName, ActionNodeHandler handler);
	bool registerPreconditionHandler(const char *preconditionName, PreconditionHandler handler);

	BTNode *readFromFile(const char *filename); 

private:
	BTNode *_parseDoc(const rapidjson::Document &doc);
	BTNode *_parseNode(const rapidjson::Value &nodeVal, BTNode *parent);
	BTPrecondition *_parsePrecondition(const rapidjson::Value &preconditionVal);
	const ActionNodeHandler &_findActionNodeHandler(const char *classname);
	const PreconditionHandler &_findPreconditionHandler(const char *classname);

public:
	~BTReader();

private:
	BTReader();
	static BTReader *s_instance;

	typedef std::map<std::string, rapidjson::Document *> DocMap;
	typedef std::pair<std::string, rapidjson::Document *> DocMapPair;
	DocMap m_docMap;

	typedef std::map<std::string, ActionNodeHandler> ActionNodeHandlerMap;
	typedef std::pair<std::string, ActionNodeHandler> ActionNodeHandlerMapPair;
	ActionNodeHandlerMap m_actionNodeHandlerMap;

	typedef std::map<std::string, PreconditionHandler> PreconditionHandlerMap;
	typedef std::pair<std::string, PreconditionHandler> PreconditionHandlerMapPair;
	PreconditionHandlerMap m_preconditionHandlerMap;

	ActionNodeHandler m_defaultActionNodeHandler;
	PreconditionHandler m_defaultPreconditionHandler;
};

#define BT_REGISTER_ACTION_NODE(classname) \
	bool __unused_register_return_##classname = BTReader::getInstance()->registerActionNodeHandler(#classname, [](BTNode *parent, const char *name) -> BTNode * { \
		return BTNodeFactory::createActionNode<classname>(parent, name); \
	});
#define BT_REGISTER_PRECONDITION(classname) \
	bool __unused_register_return_##classname = BTReader::getInstance()->registerPreconditionHandler(#classname, []() -> BTPrecondition * { \
		return (BTPrecondition *)(new classname()); \
	});

#endif // BTReader_h__
