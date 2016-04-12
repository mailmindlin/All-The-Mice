
namespace Peripherals {
namespace Display {
class Terminal {
	void writeText(char* text, size_t length);
	void setColor(TScreenColor color);
	void setCursorPosition(uint32_t x, uint32_t y);
	void setCursorX(uint32_t x);
	size_t getWidth() const;
	size_t getHeight() const;
	void setCursorY(uint32_t y);
	void clearLine();
}