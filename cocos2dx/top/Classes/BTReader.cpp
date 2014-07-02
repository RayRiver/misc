#include "BTReader.h"

#include <assert.h>

#include "BehaviorTree.h"

#include "cocos2d.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "cocostudio/DictionaryHelper.h"

USING_NS_CC;
using namespace cocostudio;

BTReader *BTReader::s_instance = nullptr;

BTReader * BTReader::getInstance()
{
	if (!s_instance)
	{
		s_instance = new BTReader;
	}
	return s_instance;
}

BTReader::BTReader()
{
	m_defaultActionNodeHandler = [](BTNode *, const char *) -> BTNode * {
		return nullptr;
	};
	m_defaultPreconditionHandler = []() -> BTPrecondition * {
		return nullptr;
	};
}

BTReader::~BTReader()
{
	for (auto &it : m_docMap)
	{
		auto pDoc = it.second;
		if (pDoc)
		{
			delete pDoc;
		}
	}
	m_docMap.clear();
}

bool BTReader::registerActionNodeHandler( const char *actionNodeName, ActionNodeHandler handler )
{
	auto it = m_actionNodeHandlerMap.find(actionNodeName);
	if (it == m_actionNodeHandlerMap.end())
	{
		m_actionNodeHandlerMap.insert(ActionNodeHandlerMapPair(actionNodeName, handler));
		return true;
	}
	else
	{
		assert(false);
		return false;
	}
}

bool BTReader::registerPreconditionHandler( const char *preconditionName, PreconditionHandler handler )
{
	auto it = m_preconditionHandlerMap.find(preconditionName);
	if (it == m_preconditionHandlerMap.end())
	{
		m_preconditionHandlerMap.insert(PreconditionHandlerMapPair(preconditionName, handler));
		return true;
	}
	else
	{
		assert(false);
		return false;
	}
}

BTNode * BTReader::readFromFile( const char *filename )
{
	std::string fullPath = FileUtils::getInstance()->fullPathForFilename(filename);
	auto it = m_docMap.find(fullPath);
	if (it != m_docMap.end())
	{
		auto pDoc = it->second;
		return _parseDoc(*pDoc);
	}

	std::string fileContent = FileUtils::getInstance()->getStringFromFile(fullPath);

	auto pDoc = new rapidjson::Document;
	if (!pDoc)
	{
		return nullptr;
	}

	pDoc->Parse<0>(fileContent.c_str());
	if (pDoc->HasParseError()) {
		CCLOG("GetParseError %s\n", pDoc->GetParseError());
		delete pDoc;
		return false;
	}

	auto node = _parseDoc(*pDoc);
	if (node)
	{
		m_docMap.insert(DocMapPair(fullPath, pDoc));
	}
	else
	{
		delete pDoc;
	}
	return node;
}

BTNode * BTReader::_parseDoc( const rapidjson::Document &doc )
{
	const auto &nodeVal = DICTOOL->getSubDictionary_json(doc, 0);
	return _parseNode(nodeVal, nullptr);
}

BTNode * BTReader::_parseNode( const rapidjson::Value &nodeVal, BTNode *parent )
{
	BTNode *node = nullptr;

	// parse node
	const char *desc = DICTOOL->getStringValue_json(nodeVal, "desc", "");
	const char *classname = DICTOOL->getStringValue_json(nodeVal, "class");
	if (strcmp(classname, "BTNodePrioritySelector") == 0)
	{
		node = BTNodeFactory::createPrioritySelectorNode(parent, desc);
	}
	else if (strcmp(classname, "BTNodeNonePrioritySelector") == 0)
	{
		node = BTNodeFactory::createNonePrioritySelectorNode(parent, desc);
	}
	else if (strcmp(classname, "BTNodeSequence") == 0)
	{
		node = BTNodeFactory::createSequenceNode(parent, desc);
	}
	else if (strcmp(classname, "BTNodeLoop") == 0)
	{
		int count = DICTOOL->getIntValue_json(nodeVal, "count", -1);
		node = BTNodeFactory::createLoopNode(parent, desc, count);
	}
	else if (strcmp(classname, "BTNodeParallel") == 0)
	{
		node = BTNodeFactory::createParallelNode(parent, desc);
	}
	else if (strcmp(classname, "BTNodeAction") == 0)
	{
		const char *imp = DICTOOL->getStringValue_json(nodeVal, "imp");
		auto handler = _findActionNodeHandler(imp);
		if (!handler)
		{
			assert(false);
			return nullptr;
		}
		node = handler(parent, desc);
	}
	else
	{
		assert(false);
		return nullptr;
	}

	// parse precondition
	bool bExistPrecondition = DICTOOL->checkObjectExist_json(nodeVal, "precondition");
	if (bExistPrecondition)
	{
		const auto &precondition = DICTOOL->getSubDictionary_json(nodeVal, "precondition");
		const char *precondition_desc = DICTOOL->getStringValue_json(nodeVal, "precondition_desc", "");
		BTPrecondition *btPrecondition = _parsePrecondition(precondition);
		if (btPrecondition)
		{
			node->setPrecondition(btPrecondition, precondition_desc);
		}
		else
		{
			assert(false);
		}
	}

	// parse children
	int children_count = DICTOOL->getArrayCount_json(nodeVal, "children");
	for (int i=0; i<children_count; ++i)
	{
		const auto &childVal = DICTOOL->getSubDictionary_json(nodeVal, "children", i);
		_parseNode(childVal, node);
	}

	return node;
}

BTPrecondition * BTReader::_parsePrecondition( const rapidjson::Value &preconditionVal )
{
	BTPrecondition *precondition = nullptr;

	const char *classname = DICTOOL->getStringValue_json(preconditionVal, "class");
	if (strcmp(classname, "BTPreconditionTRUE") == 0)
	{
		precondition = new BTPreconditionTRUE();
	}
	else if (strcmp(classname, "BTPreconditionFALSE") == 0)
	{
		precondition = new BTPreconditionFALSE();
	}
	else if (strcmp(classname, "BTPreconditionNOT") == 0)
	{
		if (DICTOOL->checkObjectExist_json(preconditionVal, "lhs"))
		{
			const auto &lhs = DICTOOL->getSubDictionary_json(preconditionVal, "lhs");	
			auto lhsPrecondition = _parsePrecondition(lhs);
			if (lhsPrecondition)
			{
				precondition = new BTPreconditionNOT(lhsPrecondition);				
			}
			else
			{
				assert(false);
			}
		}
	}
	else if (strcmp(classname, "BTPreconditionOR") == 0)
	{
		if (DICTOOL->checkObjectExist_json(preconditionVal, "lhs") && DICTOOL->checkObjectExist_json(preconditionVal, "rhs"))
		{
			const auto &lhs = DICTOOL->getSubDictionary_json(preconditionVal, "lhs");	
			const auto &rhs = DICTOOL->getSubDictionary_json(preconditionVal, "rhs");	
			auto lhsPrecondition = _parsePrecondition(lhs);
			auto rhsPrecondition = _parsePrecondition(rhs);
			if (lhsPrecondition && rhsPrecondition)
			{
				precondition = new BTPreconditionOR(lhsPrecondition, rhsPrecondition);				
			}
			else
			{
				assert(false);
				if (lhsPrecondition) delete rhsPrecondition;
				if (rhsPrecondition) delete lhsPrecondition;
			}
		}
	}
	else if (strcmp(classname, "BTPreconditionAND") == 0)
	{
		if (DICTOOL->checkObjectExist_json(preconditionVal, "lhs") && DICTOOL->checkObjectExist_json(preconditionVal, "rhs"))
		{
			const auto &lhs = DICTOOL->getSubDictionary_json(preconditionVal, "lhs");	
			const auto &rhs = DICTOOL->getSubDictionary_json(preconditionVal, "rhs");	
			auto lhsPrecondition = _parsePrecondition(lhs);
			auto rhsPrecondition = _parsePrecondition(rhs);
			if (lhsPrecondition && rhsPrecondition)
			{
				precondition = new BTPreconditionAND(lhsPrecondition, rhsPrecondition);				
			}
			else
			{
				assert(false);
				if (lhsPrecondition) delete rhsPrecondition;
				if (rhsPrecondition) delete lhsPrecondition;
			}
		}
	}
	else if (strcmp(classname, "BTPreconditionXOR") == 0)
	{
		if (DICTOOL->checkObjectExist_json(preconditionVal, "lhs") && DICTOOL->checkObjectExist_json(preconditionVal, "rhs"))
		{
			const auto &lhs = DICTOOL->getSubDictionary_json(preconditionVal, "lhs");	
			const auto &rhs = DICTOOL->getSubDictionary_json(preconditionVal, "rhs");	
			auto lhsPrecondition = _parsePrecondition(lhs);
			auto rhsPrecondition = _parsePrecondition(rhs);
			if (lhsPrecondition && rhsPrecondition)
			{
				precondition = new BTPreconditionXOR(lhsPrecondition, rhsPrecondition);				
			}
			else
			{
				assert(false);
				if (lhsPrecondition) delete rhsPrecondition;
				if (rhsPrecondition) delete lhsPrecondition;
			}
		}
	}
	else if (strcmp(classname, "BTPrecondition") == 0)
	{
		const char *imp = DICTOOL->getStringValue_json(preconditionVal, "imp");
		auto handler = _findPreconditionHandler(imp);
		if (!handler)
		{
			assert(false);
			return nullptr;
		}
		precondition = handler();
	}
	else
	{
		assert(false);
		return nullptr;
	}

	return precondition;
}

const BTReader::ActionNodeHandler & BTReader::_findActionNodeHandler( const char *classname )
{
	auto it = m_actionNodeHandlerMap.find(classname);
	if (it == m_actionNodeHandlerMap.end())
	{
		return m_defaultActionNodeHandler;
	}
	else
	{
		const auto &handler = it->second;
		return handler;
	}
}

const BTReader::PreconditionHandler & BTReader::_findPreconditionHandler( const char *classname )
{
	auto it = m_preconditionHandlerMap.find(classname);
	if (it == m_preconditionHandlerMap.end())
	{
		return m_defaultPreconditionHandler;
	}
	else
	{
		const auto &handler = it->second;
		return handler;
	}
}

