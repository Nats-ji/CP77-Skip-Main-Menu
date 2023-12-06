local options = require("settings").Options
local autoLoaded = false

-- reference https://github.com/psiberx/cp2077-playground/blob/main/DevTools/AutoContinue.reds
---@param aSingleplayerMenuGameController SingleplayerMenuGameController
local function autoLoad(aSingleplayerMenuGameController)
    if aSingleplayerMenuGameController.savesCount > 0 and options["Auto Load Last Save"] == true and autoLoaded == false then
        aSingleplayerMenuGameController:GetSystemRequestsHandler():LoadLastCheckpoint(false)
    end
end

local function setFlag()
    if options["Auto Load Last Save"] == true then
        autoLoaded = true
    end
end

local function onInitialize()
    ObserveAfter('SingleplayerMenuGameController', 'OnSavesForLoadReady', autoLoad)
    ObserveAfter('SingleplayerMenuGameController', 'OnUninitialize', setFlag)
end

return { OnInitialize = onInitialize }
