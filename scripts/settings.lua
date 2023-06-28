local options = {
    ["Skip Intro Videos"] = true,
    ["Skip Breaching Screen"] = true,
    ["Auto Load Last Save"] = true,
}

local widgets = {
    ["Skip Intro Videos"] = {
        name = "SkipIntroVideos",
        label = "Skip Intro Videos",
        description = "Enable this option will skip all the logo videos and intro videos when launching the game.",
    },
    ["Skip Breaching Screen"] = {
        name = "SkipBreaching",
        label = "Skip Breaching Screen",
        description =
        "Enable this option will skip the \"Breaching\" screen where it askes you to press the spacebar to continue.",
    },
    ["Auto Load Last Save"] = {
        name = "AutoLoadLastSave",
        label = "Auto Load Last Save",
        description = "Enable this option will automatically load into your last save game when you launch the game.",
    },
}

local widgetPath = "/gameplay/misc"

---set the option to default value if it doesn't exist in the config file
local function setOption(aValue, aDefault)
    if aValue == nil then
        return aDefault
    else
        return aValue
    end
end

local function saveOptions()
    local config = {}

    config["skip_intro"] = options["Skip Intro Videos"]
    config["skip_breach"] = options["Skip Breaching Screen"]
    config["auto_load"] = options["Auto Load Last Save"]

    local file = io.open("config.json", "w")
    if file ~= nil then
        file:write(json.encode(config))
        file:close()
    end
end

local function loadOptions()
    local file = io.open("config.json", "r")
    if file ~= nil then
        local config = json.decode(file:read("*a"))
        file:close()

        options["Skip Intro Videos"] = setOption(config.skip_intro, options["Skip Intro Videos"])
        options["Skip Breaching Screen"] = setOption(config.skip_breach, options["Skip Breaching Screen"])
        options["Auto Load Last Save"] = setOption(config.auto_load, options["Auto Load Last Save"])
    end

    saveOptions()
end

---@param aSettingsMainGameController SettingsMainGameController
local function spawnWidgets(aSettingsMainGameController)
    for _, widget in pairs(widgets) do
        local boolWidget = aSettingsMainGameController:SpawnFromLocal(inkWidgetRef.Get(
            aSettingsMainGameController.settingsOptionsList), "settingsSelectorBool")
        boolWidget:SetName(widget.name)
        local currentItem = boolWidget:GetController() --[[@as SettingsSelectorControllerBool]]
        currentItem.LabelText:SetText(widget.label)
        currentItem.onState:SetVisible(options[widget.label])
        currentItem.offState:SetVisible(not options[widget.label])
        currentItem.varGroupPath = CName.new(widgetPath)
        currentItem:RegisterToCallback("OnHoverOver", aSettingsMainGameController, "OnSettingHoverOver")
        currentItem:RegisterToCallback("OnHoverOut", aSettingsMainGameController, "OnSettingHoverOut")
        table.insert(aSettingsMainGameController.settingsElements, currentItem)
    end
end

---@param aSettingsMainGameController SettingsMainGameController
---@param aOptions ConfigVar[]
local function populateWidgets(aSettingsMainGameController, aOptions)
    for _, option in ipairs(aOptions) do
        if option:GetGroupPath().value == widgetPath then
            spawnWidgets(aSettingsMainGameController)
            break
        end
    end
end

---@param aSettingsSelectorControllerBool SettingsSelectorControllerBool
local function changeValue(aSettingsSelectorControllerBool)
    local currentItemGroupPath = aSettingsSelectorControllerBool:GetGroupPath().value
    local currentItemLabel = aSettingsSelectorControllerBool.LabelText:GetText()
    if currentItemGroupPath == widgetPath and options[currentItemLabel] ~= nil then
        options[currentItemLabel] = not options[currentItemLabel]
        aSettingsSelectorControllerBool.onState:SetVisible(options[currentItemLabel])
        aSettingsSelectorControllerBool.offState:SetVisible(not options[currentItemLabel])
        saveOptions()
    end
end

---@param aSettingsMainGameController SettingsMainGameController
---@param aEvent inkPointerEvent
local function showTooltip(aSettingsMainGameController, aEvent)
    local currentItem = aEvent:GetCurrentTarget():GetController() --[[@as SettingsSelectorController]]
    local currentItemGroupPath = currentItem:GetGroupPath().value
    local currentItemLabel = currentItem.LabelText:GetText()
    if currentItemGroupPath == widgetPath and widgets[currentItemLabel] ~= nil then
        aSettingsMainGameController.descriptionText:SetText(widgets[currentItemLabel].description)
        aSettingsMainGameController.descriptionText:SetVisible(true)
    end
end

local function onInitialize()
    loadOptions()
    ObserveAfter('SettingsMainGameController', 'PopulateOptions', populateWidgets)
    Observe("SettingsSelectorControllerBool", "AcceptValue", changeValue)
    ObserveAfter("SettingsMainGameController", "OnSettingHoverOver", showTooltip)
end

return { OnInitialize = onInitialize, Options = options }
