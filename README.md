# SAMP-LocalPlugin
Gives access to all keys. Only works for the LOCAL machine (the PC the server is running on). Only for debug purposes/Map Editors (etc).

Note: WINDOWS only!

# Natives:

	IsLocalKeyPressed(key)
		Checks if a key ID is currently pressed.

	IsSAMPFocused()
		Checks if SAMP is the foreground application.

	GetVKName(key, const name[], maxlen = sizeof name)
		Gets the complete name of a key.

	ToggleKey(key, toggle = 1)
		Toggles the given key for OnLocalKeyStateChange only. 
		All keys are off by default!

	IsKeyToggled(key)
		Checks if a key is toggled.

# Callbacks:

	OnLocalKeyStateChange(key, newstate)
		Gets called whenever a keystate has changed (newstate will be 0 or 1).
