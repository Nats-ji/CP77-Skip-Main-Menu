local options = require("settings").Options
local loop = false

local function onInitialize()
    if options["Auto Load Last Save"] == true then
        loop = true
    end
end

-- I know it's hacky, but it works ㄟ( ▔, ▔ )ㄏ.
local function OnUpdate()
    if loop then
        if Game.GetQuestsSystem():GetFactStr("q000_started") == 0 then
            GetSingleton("inkMenuScenario"):GetSystemRequestsHandler():LoadSavedGame(0)
        else
            loop = false
        end
    end
end

return { OnInitialize = onInitialize, OnUpdate = OnUpdate }
