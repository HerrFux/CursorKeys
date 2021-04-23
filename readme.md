# CursorKeys

The "Ease of Access" function for controlling the mouse with the keyboard in Windows does not allow the custom binding of keys and instead uses the numeric keypad. This program offers a simple yet customizable approach, which also includes custom velocities and accelerations. In order to close the program an interrupt signal needs to be send (e.g. `ctrl` + `c`).

## Customization

To customize the values for the velocity and the acceleration you'll need to change the constants at the beginning of the main function. The values are hardcoded, which avoids the usage of config files or the registry. The same goes for the keys. The order of the array `keys` is clockwise, so it is important to start with a key for the upwards movement as the first index and then keep going from there, so the order would be: up, right, down, left.