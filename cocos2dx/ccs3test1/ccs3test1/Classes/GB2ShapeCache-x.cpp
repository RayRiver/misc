//
//  GB2ShapeCache-x.cpp
//  
//  Loads physics sprites created with http://www.PhysicsEditor.de
//  To be used with cocos2d-x
//
//  Generic Shape Cache for box2d
//
//  Created by Thomas Broquist
//
//      http://www.PhysicsEditor.de
//      http://texturepacker.com
//      http://www.code-and-web.de
//  
//  All rights reserved.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//  
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//  
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//

#include "GB2ShapeCache-x.h"
#include "box2d/Box2D.h"
#include "CCNS.h"

using namespace cocos2d;

/**
 * Internal class to hold the fixtures
 */
class FixtureDef {
public:
    FixtureDef()
    : next(NULL) {}
    
    ~FixtureDef() {
        delete next;
        delete fixture.shape;
    }
    
    FixtureDef *next;
    b2FixtureDef fixture;
    int callbackData;
};

class BodyDef {
public:
	BodyDef()
	: fixtures(NULL) {}
	
	~BodyDef() {
		if (fixtures)
			delete fixtures;
	}
	
	FixtureDef *fixtures;
	Point anchorPoint;
};

static GB2ShapeCache *_sharedGB2ShapeCache = NULL;

GB2ShapeCache* GB2ShapeCache::sharedGB2ShapeCache(void) {
	if (!_sharedGB2ShapeCache) {
		_sharedGB2ShapeCache = new GB2ShapeCache();
        _sharedGB2ShapeCache->init();
	}
	
	return _sharedGB2ShapeCache;
}

bool GB2ShapeCache::init() {
	return true;
}

void GB2ShapeCache::reset() {
	std::map<std::string, BodyDef *>::iterator iter;
	for (iter = shapeObjects.begin() ; iter != shapeObjects.end() ; ++iter) {
		delete iter->second;
	}
	shapeObjects.clear();
}

void GB2ShapeCache::addFixturesToBody(b2Body *body, const std::string &shape) {
	std::map<std::string, BodyDef *>::iterator pos = shapeObjects.find(shape);
	assert(pos != shapeObjects.end());
	
	BodyDef *so = (*pos).second;

	FixtureDef *fix = so->fixtures;
    while (fix) {
        body->CreateFixture(&fix->fixture);
        fix = fix->next;
    }
}

cocos2d::Point GB2ShapeCache::anchorPointForShape(const std::string &shape) {
	std::map<std::string, BodyDef *>::iterator pos = shapeObjects.find(shape);
	assert(pos != shapeObjects.end());
	
	BodyDef *bd = (*pos).second;
	return bd->anchorPoint;
}

//typedef CCDictionary<std::string, CCObject*> ObjectDict;
typedef cocos2d::ValueMap ObjectDict;
typedef cocos2d::ValueVector ObjectList;

void GB2ShapeCache::addShapesWithFile(const std::string &plist) 
{
	//const char *fullName = CCFileUtils::fullPathFromRelativePath(plist.c_str());
	//ObjectDict *dict = CCFileUtils::dictionaryWithContentsOfFile(fullName);

	ObjectDict dict = FileUtils::getInstance()->getValueMapFromFile(plist);

	//CCAssert(dict != nullptr, "Shape-file not found"); // not triggered - cocos2dx delivers empty dict if non was found
    //CCAssert(dict->size() != 0, "plist file empty or not existing");
	
	//ObjectDict *metadataDict = (ObjectDict *)dict->objectForKey("metadata");
    //int format = static_cast<CCString *>(metadataDict->objectForKey("format"))->toInt();
    //ptmRatio = static_cast<CCString *>(metadataDict->objectForKey("ptm_ratio"))->toFloat();
	//CCAssert(format == 1, "Format not supported");

	ObjectDict &metadataDict = dict["metadata"].asValueMap();
	int format = metadataDict["format"].asInt();
	ptmRatio = metadataDict["ptm_ratio"].asFloat();
	CCAssert(format == 1, "Format not supported");

	//ObjectDict *bodyDict = (ObjectDict *)dict->objectForKey("bodies");
	ObjectDict &bodyDict = dict["bodies"].asValueMap();

    b2Vec2 vertices[b2_maxPolygonVertices];

	//ObjectDict::CCObjectMapIter iter;
	
	//bodyDict->begin();
	//std::string bodyName;
	//ObjectDict *bodyData;
	//while ((bodyData = (ObjectDict *)bodyDict->next(&bodyName))) {
	for (ObjectDict::iterator iter=bodyDict.begin(); iter!=bodyDict.end(); ++iter)
	{
		std::string bodyName = iter->first;
		ObjectDict &bodyData = iter->second.asValueMap();

		BodyDef *bodyDef = new BodyDef();
		//bodyDef->anchorPoint = CCPointFromString(static_cast<CCString *>(bodyData->objectForKey("anchorpoint"))->toStdString().c_str());
		bodyDef->anchorPoint = PointFromString(bodyData["anchorpoint"].asString());
		
		//CCMutableArray<ObjectDict *> *fixtureList = (CCMutableArray<ObjectDict *> *)(bodyData->objectForKey("fixtures"));
		ObjectList &fixtureList = bodyData["fixtures"].asValueVector();

        FixtureDef **nextFixtureDef = &(bodyDef->fixtures);

		//CCMutableArray<ObjectDict *>::CCMutableArrayIterator iter;
		//for (iter = fixtureList->begin(); iter != fixtureList->end(); ++iter) {
		for (ObjectList::iterator it=fixtureList.begin(); it!=fixtureList.end(); ++it)
		{
            b2FixtureDef basicData;
            //ObjectDict *fixtureData = *iter;
			ObjectDict &fixtureData = it->asValueMap();
			
            //basicData.filter.categoryBits = static_cast<CCString *>(fixtureData->objectForKey("filter_categoryBits"))->toInt();
            //basicData.filter.maskBits = static_cast<CCString *>(fixtureData->objectForKey("filter_maskBits"))->toInt();
            //basicData.filter.groupIndex = static_cast<CCString *>(fixtureData->objectForKey("filter_groupIndex"))->toInt();
            //basicData.friction = static_cast<CCString *>(fixtureData->objectForKey("friction"))->toFloat();
            //basicData.density = static_cast<CCString *>(fixtureData->objectForKey("density"))->toFloat();
            //basicData.restitution = static_cast<CCString *>(fixtureData->objectForKey("restitution"))->toFloat();
            //basicData.isSensor = (bool)static_cast<CCString *>(fixtureData->objectForKey("isSensor"))->toInt();

			basicData.filter.categoryBits = fixtureData["filter_categoryBits"].asInt();
			basicData.filter.maskBits = fixtureData["filter_maskBits"].asInt();
			basicData.filter.groupIndex = fixtureData["filter_groupIndex"].asInt();
			basicData.friction = fixtureData["friction"].asInt();
			basicData.density = fixtureData["density"].asInt();
			basicData.restitution = fixtureData["restitution"].asInt();
			basicData.isSensor = (bool)(fixtureData["isSensor"].asInt());

			//CCString *cb = static_cast<CCString *>(fixtureData->objectForKey("userdataCbValue"));
			std::string cb = fixtureData["userdataCbValue"].asString();
			
            int callbackData = 0;
			
			//if (cb)
			//	callbackData = cb->toInt();
			callbackData = atoi(cb.c_str());
            
			//std::string fixtureType = static_cast<CCString *>(fixtureData->objectForKey("fixture_type"))->toStdString();
			std::string fixtureType = fixtureData["fixture_type"].asString();
			
			if (fixtureType == "POLYGON") 
			{
				//CCMutableArray<ObjectDict *> *polygonsArray = (CCMutableArray<ObjectDict *> *)(fixtureData->objectForKey("polygons"));
				//CCMutableArray<ObjectDict *>::CCMutableArrayIterator iter;

				ObjectList &polygonsArray = fixtureData["polygons"].asValueVector();

				//for (iter = polygonsArray->begin(); iter != polygonsArray->end(); ++iter) {
				for (ObjectList::iterator it=polygonsArray.begin(); it!=polygonsArray.end(); ++it)
				{
                    FixtureDef *fix = new FixtureDef();
                    fix->fixture = basicData; // copy basic data
                    fix->callbackData = callbackData;
					
                    b2PolygonShape *polyshape = new b2PolygonShape();
                    int vindex = 0;
                    
					//CCMutableArray<CCString *> *polygonArray = (CCMutableArray<CCString *> *)(*iter);
					ObjectList &polygonArray = it->asValueVector();

                    //assert(polygonArray->count() <= b2_maxPolygonVertices);
                    assert(polygonArray.size() <= b2_maxPolygonVertices);

					//CCMutableArray<CCString *>::CCMutableArrayIterator piter;
					
					//for (piter = polygonArray->begin(); piter != polygonArray->end(); ++piter) {
					for (ObjectList::iterator piter=polygonArray.begin(); piter!=polygonArray.end(); ++piter)
					{
                        //CCPoint offset = CCPointFromString((*piter)->toStdString().c_str());

						Point offset = PointFromString(piter->asString());
                        vertices[vindex].x = (offset.x / ptmRatio) ; 
                        vertices[vindex].y = (offset.y / ptmRatio) ; 
                        vindex++;
                    }
                    
                    polyshape->Set(vertices, vindex);
                    fix->fixture.shape = polyshape;
                    
                    // create a list
                    *nextFixtureDef = fix;
                    nextFixtureDef = &(fix->next);
				}
				
			} else if (fixtureType == "CIRCLE") {
				FixtureDef *fix = new FixtureDef();
                fix->fixture = basicData; // copy basic data
                fix->callbackData = callbackData;
                
                //ObjectDict *circleData = (ObjectDict *)fixtureData->objectForKey("circle");
                ObjectDict &circleData = fixtureData["circle"].asValueMap();
                
                b2CircleShape *circleShape = new b2CircleShape();
				
                //circleShape->m_radius = static_cast<CCString *>(circleData->objectForKey("radius"))->toFloat() / ptmRatio;
				//CCPoint p = CCPointFromString(static_cast<CCString *>(circleData->objectForKey("position"))->toStdString().c_str());
                circleShape->m_radius = circleData["radius"].asFloat() / ptmRatio;
				Point p = PointFromString(circleData["position"].asString());
                circleShape->m_p = b2Vec2(p.x / ptmRatio, p.y / ptmRatio);
                fix->fixture.shape = circleShape;
				

                // create a list
                *nextFixtureDef = fix;
                nextFixtureDef = &(fix->next);

			} else {
				CCAssert(0, "Unknown fixtureType");
			}
			
			// add the body element to the hash
			shapeObjects[bodyName] = bodyDef;
		}
	}
}