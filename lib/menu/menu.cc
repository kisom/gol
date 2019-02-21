// The menu builds on the OLED featherwing and assumes the three
// buttons and three lines of text available there. It supports a
// maximum of 254 menu items.
//
// This library requires delay() from the Arduino library,
// which also defines a max and min macro that conflict with
// the STL.
#include <Arduino.h>
#undef max
#undef min
#include <Streaming.h>

#include <stdint.h>
#include <string.h>
#include <vector>

#include <menu.h>
#include <hal/buttons.h>
#include <hal/graphics.h>


namespace menu {


static hal::Button	A(hal::BUTTON_A);
static hal::Button	B(hal::BUTTON_B);
static hal::Button	C(hal::BUTTON_C);


static void
clearCallbacks()
{
	A.registerCallback(nullptr);	
	B.registerCallback(nullptr);	
	C.registerCallback(nullptr);	
}


typedef struct {
	char	text[hal::OLED::MAX_TEXT+1];
	bool	selected;
	void	(*callback)(void);
} menuItem;
std::vector<menuItem>	menu;
uint8_t			currentItem = 0;
uint8_t			nMenuItems = 0;
uint8_t			start = 0;
uint8_t			end = 0;


static void
setPage()
{
	start = (currentItem / 3) * 3;
	end = start + 2;
	while (nMenuItems <= end) {
		end--;	
	}
}


void	
addItem(const char *text, void (*callback)(void))
{
	menuItem	item;

	if (nMenuItems == 254) {
		return;
	}

	strncpy(item.text, text, hal::OLED::MAX_TEXT);
	item.selected = false;
	item.callback = callback;
	menu.push_back(item);
	nMenuItems++;
	if (end < 2) {
		setPage();
	}
}


void
clear()
{
	menu.clear();
}


static void
display()
{
	uint8_t	line = 0;
	hal::OLED::clearLines();
	for (uint8_t i = start; i <= end; i++) {
		if (menu[i].selected) {
			hal::OLED::iprint(line++, menu[i].text);
		}
		else {
			hal::OLED::print(line++, menu[i].text);
		}
	}

	hal::OLED::show();
}


static inline uint8_t
wrap(uint8_t n)
{
	// Handle the rollover.
	if (n == 255) {
		return nMenuItems - 1;
	}
	return n % nMenuItems;
}


static void
prevItem()
{
	menu[currentItem].selected = false;
	currentItem = wrap(currentItem - 1);
	menu[currentItem].selected = true;
	setPage();
	display();
}


static void
nextItem()
{
	menu[currentItem].selected = false;
	currentItem = wrap(currentItem + 1);
	menu[currentItem].selected = true;
	setPage();
	display();
}


static void
selectItem()
{
	hal::OLED::clear();
	hal::OLED::clearLines();
	menu[currentItem].callback();
}


void
show()
{
	clearCallbacks();
	A.registerCallback(prevItem);
	B.registerCallback(selectItem);
	C.registerCallback(nextItem);

	if (menu.size() == 0) {
		return;
	}
	menu[0].selected = true;
	currentItem = 0;

	display();

	while (true) {
		A.sample();
		B.sample();
		C.sample();
		delay(25);
	}
}


} // namespace menu
