#include "TankShell.h"

// Moves the shell one step in its current direction
void TankShell::movePos() {
	pos.move(direction);
}