//#include "Cerberus\Core\Engine.h"
#include "Cerberus\Game\CPlayer.h"

int main() 
{

	CPlayer* player = Engine::CreateEntity<CPlayer>();

	player->visible = false;

	return 0;
}