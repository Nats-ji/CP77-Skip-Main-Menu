registerForEvent("onInit", function()
	loop = true
end)

registerForEvent("onUpdate", function(dt)
	if loop then
		if Game.GetQuestsSystem():GetFactStr("q000_started") == 0 then
			GetSingleton("inkMenuScenario"):GetSystemRequestsHandler():LoadSavedGame(0)
			print("looping")
		else
			loop = false
		end
	end
end)