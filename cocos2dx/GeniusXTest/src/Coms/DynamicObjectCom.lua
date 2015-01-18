
local ComClass = class("DynamicObjectCom", function(com_name)
    return ECS.createComBase(com_name)
end)

function ComClass:ctor()
    self.m_speed_x = 0
    self.m_speed_y = 0

    self.m_direction_x = 0
    self.m_direction_y = -1

    self.m_move_direction_x = 0
    self.m_move_direction_y = 0

    self.m_speed = 10
    self.m_speed_direction = self.m_speed / math.sqrt(2)
end

function ComClass:getSpeed()
    return self.m_speed_x, self.m_speed_y
end

function ComClass:setDesiredPosition(x, y)
    self.m_desired_position_x = x
    self.m_desired_position_y = y
end

function ComClass:getDesiredPosition()
    return self.m_desired_position_x, self.m_desired_position_y
end

function ComClass:onMoveUp()
    self.m_move_direction_y = self.m_move_direction_y + 1
    self:updateSpeed()
end

function ComClass:onMoveUpStop()
    self.m_move_direction_y = self.m_move_direction_y - 1
    self:updateSpeed()
end

function ComClass:onMoveDown()
    self.m_move_direction_y = self.m_move_direction_y - 1
    self:updateSpeed()
end

function ComClass:onMoveDownStop()
    self.m_move_direction_y = self.m_move_direction_y + 1
    self:updateSpeed()
end

function ComClass:onMoveLeft()
    self.m_move_direction_x = self.m_move_direction_x - 1
    self:updateSpeed()
end

function ComClass:onMoveLeftStop()
    self.m_move_direction_x = self.m_move_direction_x + 1
    self:updateSpeed()
end

function ComClass:onMoveRight()
    self.m_move_direction_x = self.m_move_direction_x + 1
    self:updateSpeed()
end

function ComClass:onMoveRightStop()
    self.m_move_direction_x = self.m_move_direction_x - 1
    self:updateSpeed()
end

function ComClass:updateSpeed()
    if self.m_move_direction_x == 0 and self.m_move_direction_y == 0 then
        self.m_speed_x = 0
        self.m_speed_y = 0
    elseif self.m_move_direction_x ~= 0 and self.m_move_direction_y ~= 0 then
        self.m_speed_x = self.m_speed_direction * self.m_move_direction_x
        self.m_speed_y = self.m_speed_direction * self.m_move_direction_y
    else
        self.m_speed_x = self.m_speed * self.m_move_direction_x
        self.m_speed_y = self.m_speed * self.m_move_direction_y
    end
end

return ComClass

