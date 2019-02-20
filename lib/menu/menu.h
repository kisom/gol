#ifndef __MENU_H
#define __MENU_H

namespace menu {


void	addItem(const char *text, void (*callback)(void));
void	clear();
void	show();


} // namespace menu
#endif // __MENU_H