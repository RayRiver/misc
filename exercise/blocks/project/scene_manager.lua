
local Utils = require("utils")

local SceneManager = Utils.Class("SceneManager")

function SceneManager:instance()
    if not SceneManager.s_instance then
        SceneManager.s_instance = SceneManager:new()
    end
    return SceneManager.s_instance
end

function SceneManager:initialize()
    self.m_scene_index = 0
    self.m_scenes = {}
end

function SceneManager:enterScene(scene)
    self.m_scene_index = self.m_scene_index + 1
    self.m_scenes[self.m_scene_index] = scene
end

function SceneManager:exitScene()
    if self.m_scene_index > 0 then
        self.m_scenes[self.m_scene_index] = nil
        self.m_scene_index = self.m_scene_index - 1
    end
end

function SceneManager:replaceScene(scene)
    self:exitScene()
    self:enterScene(scene)
end

function SceneManager:getRunningScene()
    return self.m_scenes[self.m_scene_index]
end

return SceneManager
