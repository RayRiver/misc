
local BT = bt

local handleCond
local handleNode

local function handleCond0(cond_config)
    return BT.Factory:createCond(cond_config.class)
end

local function handleCond1(cond_config)
    return BT.Factory:createCond(
        cond_config.class,
        handleCond(cond_config.lhs)
    )
end

local function handleCond2(cond_config)
    return BT.Factory:createCond(
        cond_config.class,
        handleCond(cond_config.lhs),
        handleCond(cond_config.rhs)
    )
end

local function handleCondCUSTOM(cond_config)
    -- todo
end

local COND_CLASSES = {
    PreconditionTRUE = handleCond0,
    PreconditionFALSE = handleCond0,
    PreconditionNOT = handleCond1,
    PreconditionAND = handleCond2,
    PreconditionOR = handleCond2,
    PreconditionXOR = handleCond2,
    PreconditionCUSTOM = handleCondCUSTOM,
}
handleCond = function(cond_config)
    if not cond_config then
        return nil
    end

    local cond_class = cond_config.class
    local handler = COND_CLASSES[cond_class]

    if handler then
        return handler(cond_config)
    else
        assert(false)
    end
end

local function handleNode0(node_config)
    return BT.Factory:createNode(node_config.class, node_config.name)
end

local function handleLoopNode(node_config)
    return BT.Factory:createNode(node_config.class, node_config.name, node_config.loop_count)
end

local function handleParallelNode(node_config)
    return BT.Factory:createNode(node_config.class, node_config.name, node_config.finish_condition)
end

local function handleActionNode(node_config)
    return BT.Factory:createNode(node_config.class, node_config.name, node_config.config)
end

local NODE_CLASSES = {
    PrioritySelectorNode = handleNode0,
    NonPrioritySelectorNode = handleNode0,
    SequenceNode = handleNode0,
    LoopNode = handleLoopNode,
    ParallelNode = handleParallelNode,
}
handleNode = function(node_config)
    if not node_config then
        assert(false)
        return
    end

    local node_class = node_config.class
    local handler = NODE_CLASSES[node_class]

    local node
    if handler then
        node = handler(node_config)
    else
        node = handleActionNode(node_config)
    end

    local cond = handleCond(node_config.precondition)
    if cond then
        node:setPrecondition(cond)
    end

    if node_config.children then
        for _, child_config in ipairs(node_config.children) do
            local child = handleNode(child_config)
            if child then
                node:addChild(child)
            end
        end
    end

    return node
end

local function load_table(t)
    return handleNode(t)
end

local _M = {}

function _M.loadString(str)
    local chunk = loadstring(str)
    if chunk then
        local t = chunk()
        if t then
            return load_table(t)
        end
    end
end

function _M.loadFile(file)
    local t = require(file)
    if t then
        package.loaded[file] = nil
        return load_table(t)
    end
end

return _M
