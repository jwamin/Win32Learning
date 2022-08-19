#include <Windows.h>
#include "Helpers.h"

POINT getCenter(LPRECT rect) {

	POINT pt = { rect->right / 2, rect->bottom / 2 };
	return pt;

}