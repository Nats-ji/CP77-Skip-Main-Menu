---@meta

---@param self_ inkTextWidgetReference
---@param displayText string
---@param textParams? textTextParameterSet
function inkTextWidgetReference.SetText(self_, displayText, textParams) end

---@param typeName string
---@param funcName string
---@param callback fun(...): void
---@return string
function Observe(typeName, funcName, callback) end

---@param typeName string
---@param funcName string
---@param callback fun(...): void
---@return string
function ObserveAfter(typeName, funcName, callback) end
