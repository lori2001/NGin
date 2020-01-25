#include "SFML/Graphics.hpp"
#include "UIElement.h"
#include "../System/Console.h"

// This UI Element has to be inherited in order to be used properly

namespace ngin {

	class ScrollBox : public ngin::UIElement {
	public:
		ScrollBox() : ScrollBox({ 1000, 1000 }, { 500, 500 }, { 150, 30 }, { 30, 150 }){}
		ScrollBox(const sf::Vector2f& insideSize, const sf::Vector2f& outsideSize,
			const sf::Vector2f& XscrollerSize, const sf::Vector2f& YscrollerSize)
		{
			setInsideSize(insideSize);
			setOutsideSize(outsideSize);
			setXScrollerSize(XscrollerSize);
			setYScrollerSize(YscrollerSize);
			setPosition({0, 0});
		
			if (outsideSize.x > insideSize.x) {
				NG_LOG_WARN("Scrollbox nr.", getElementIndex(),
					" -- outsideSize.x should be smaller or equal to insideSize.x!");
			} 
			if (outsideSize.y > insideSize.y) {
				NG_LOG_WARN("Scrollbox nr.", getElementIndex(),
					" -- outsideSize.x should be smaller or equal to insideSize.x!");
			}
			if (outsideSize.x == insideSize.x) {
				XisUsed_ = false;  
			}
			if (outsideSize.y == insideSize.y) {
				YisUsed_ = false;
			}
		}

		void handleEvents(const sf::Event& event, const sf::Vector2f& mouse);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		// add elements to scrollbox by this
		// arg1: an sfml rectangle
		// arg2: the position relative to the inside of scrollbox
		// -- positions outside of bounds will result in warning message and false return
		// -- makes ScrollBox responsible for drawing the object passed in
		bool addElement(sf::RectangleShape& rectangle, const sf::Vector2f& relativePosition);

		void setXScrollerSize(const sf::Vector2f& size) { Xscroller_.setSize(size); }
		void setYScrollerSize(const sf::Vector2f& size) { Yscroller_.setSize(size); }
		void setInsideSize(const sf::Vector2f& insideSize) { insideSize_ = insideSize; }	
		void setOutsideSize(const sf::Vector2f& outsideSize) {
			outsideSize_ = outsideSize;
			container_.setSize(outsideSize);
		}
		// Composition:
		// background of outsideSize
		// scrollbar of Yscrollersize(next to background)
		// scrollbar of Xscrollersize(under background)
		void setTexture(const sf::Texture& texture);
		void setPosition(const sf::Vector2f& position);
		void setScrollSpeed(const float scrollSpeed) { scrollSpeed_ = scrollSpeed; }
		
		sf::Vector2f getPosition() const { return container_.getPosition(); }
		bool XisActive() const { return XisActive_; }
		bool YisActive() const { return YisActive_; }

	private:
		// outsideSize_ < insideSize_
		sf::Vector2f insideSize_; // the hidden size of container
		sf::Vector2f outsideSize_; // the size of the container seen by user

		sf::RectangleShape container_;
		
		bool isFocused_ = false; // true when mouse is on container
		
		float selectThickness_ = -2.45F; // the thickenss of the outline of selected items
		
		sf::Vector2f savedMousePosition_;
		sf::Vector2f scrollPercent; // the offset of scrolling in percentage
		float scrollSpeed_ = 0.15F; // scroll speed for mouse wheel

		sf::RectangleShape Xscroller_; // bottom scroller
		bool XisUsed_ = true;
		bool XisSelected_ = false;
		bool XisActive_ = false;
		bool XisPressed_ = false;
		
		sf::RectangleShape Yscroller_; // right scroller
		bool YisUsed_ = true;
		bool YisSelected_ = false;
		bool YisActive_ = false;
		bool YisPressed_ = false;

		bool isDisabled_ = false;

		// rectangle subscriptions
		std::vector<sf::RectangleShape*> subsRects_;
		// contains position relative to scrollbox inside
		std::vector<sf::Vector2f> subsRectPositions_;
	};
}