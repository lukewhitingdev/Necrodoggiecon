//#include "Cerberus\Core\Engine.h"
#include "Cerberus\Game\CPlayer.h"

/*

TODO:
Move all Cerberus/Game code into this app
Parse WndProc and WinMain in here and give it to the engine
Make Engine::start or whatver to get the device working
Re-create test bed using this application project

*/

int main() 
{

	CPlayer* player = Engine::CreateEntity<CPlayer>();

	player->visible = false;

	return 0;
}