local settings = require("settings")
local autoload = require("autoload")

local function onInitialize()
    settings.OnInitialize()
    autoload.OnInitialize()
end

registerForEvent("onInit", onInitialize)
