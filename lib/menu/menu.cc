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


void	
addItem(const char *text, void (*callback)(void))
{
	menuItem	item;

	strncpy(item.text, text, hal::OLED::MAX_TEXT);
	item.selected = false;
	item.callback = callback;
	menu.push_back(item);
	nMenuItems++;
	if (end < 2) {
		end++;
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
	Serial << "showing items " << start << " - " << end << endl;

	uint8_t	line = 0;
	Serial << "clearing display" << endl;
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
	return n % (nMenuItems);
}


static void
prevItem()
{
	menu[currentItem].selected = false;
	currentItem = wrap(currentItem - 1);
	if ((currentItem % 3) == 2) {
		Serial << "paging back: " << start << " - " << end << endl;
		start = currentItem - 2;
		end = currentItem;
	}

	menu[currentItem].selected = true;
	display();
	
	Serial << "current item: " << currentItem << " / " << nMenuItems <<
		   " (" << menu[currentItem].text << ") " << 
		   (menu[currentItem].selected ? "*" : "-") << endl;
}


static void
nextItem()
{
	menu[currentItem].selected = false;
	currentItem = wrap(currentItem + 1);
	if ((currentItem % 3) == 0) {
		Serial << "paging forward: " << start << " - " << end << endl;
		start = currentItem;
		if ((nMenuItems - 1) < (currentItem + 2)) {
			end = nMenuItems - 1;
		}
		else {
			end = currentItem + 2;
		}
	}

	menu[currentItem].selected = true;
	display();

	Serial << "current item: " << currentItem << " / " << nMenuItems <<
		   " (" << menu[currentItem].text << ") " << 
		   (menu[currentItem].selected ? "*" : "-") << endl;
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
	hal::Button	A(hal::BUTTON_A);
	hal::Button	B(hal::BUTTON_B);
	hal::Button	C(hal::BUTTON_C);

	A.registerCallback(prevItem);
	B.registerCallback(selectItem);
	C.registerCallback(nextItem);

	if (menu.size() == 0) {
		return;
	}
	menu[0].selected = true;
	currentItem = 0;

	Serial << "showing menu" << endl;

	display();

	while (true) {
		A.sample();
		B.sample();
		C.sample();
		delay(25);
	}
}


} // namespace menu