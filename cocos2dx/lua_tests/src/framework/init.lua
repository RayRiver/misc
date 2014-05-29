local FRAMEWORK_PACKAGE_NAME = "src.framework"

cc = cc or {}
cc.PACKAGE_NAME = FRAMEWORK_PACKAGE_NAME
cc.VERSION = "3.0.0"

require(cc.PACKAGE_NAME .. ".debug")
require(cc.PACKAGE_NAME .. ".functions")
require(cc.PACKAGE_NAME .. ".cocos2dx")

display = require(cc.PACKAGE_NAME .. ".display")
scheduler = require(cc.PACKAGE_NAME .. ".scheduler")
ui = require(cc.PACKAGE_NAME .. ".ui")
transition = require(cc.PACKAGE_NAME .. ".transition")
device = require(cc.PACKAGE_NAME .. ".transition")

require(cc.PACKAGE_NAME .. ".network")

DEBUG_FPS = DEBUG_FPS and true or false
cc.Director:getInstance():setDisplayStats(DEBUG_FPS)
