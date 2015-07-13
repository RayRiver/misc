
function love.load()
    print("load...")
    require("bt.init")
end

function love.update(dt)
    if love.keyboard.isDown('escape') then
        love.event.push('quit')
    end
end

function love.draw()

end
