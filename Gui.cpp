#include "Gui.h"

gui::Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text, unsigned character_size,
	sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
	sf::Color idle_color, sf::Color hover_color, sf::Color active_color)
{
	this->buttonState = BTN_IDLE;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(idle_color);

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(text_idle_color);
	this->text.setCharacterSize(character_size);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
	);

	this->textIdleColor = text_idle_color;
	this->textHoverColor = text_hover_color;
	this->textActiveColor = text_active_color;

	this->idleColor = idle_color;
	this->hoverColor = hover_color;
	this->activeColor = active_color;

}

gui::Button::~Button()
{

}

//Accessors
const bool gui::Button::isPressed() const
{
	if (this->buttonState == BTN_ACTIVE)
		return true;
	return false;
}

const std::string gui::Button::getText() const
{
	return this->text.getString();
}

//Modifiers
void gui::Button::setText(const std::string text)
{
	this->text.setString(text);
}

//Functions

void gui::Button::update(const sf::Vector2f& mousePos)
{
	/*Update the booleans for hover and pressed*/

	//Idle
	this->buttonState = BTN_IDLE;

	//Hover 
	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		this->buttonState = BTN_HOVER;

		//Pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BTN_ACTIVE;
		}
	}

	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		this->text.setFillColor(this->textIdleColor);
		break;

	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		this->text.setFillColor(this->textHoverColor);
		break;

	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		this->text.setFillColor(this->textActiveColor);
		break;
	default:
		this->shape.setFillColor(sf::Color::Red);
		this->shape.setFillColor(sf::Color::Blue);
		break;
	}
}

void gui::Button::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);
}

//Drop down list----------------------------------

gui::DropDownList::DropDownList(float x, float y, float width, float height,
	sf::Font& font, std::string list[],
	unsigned nrofElements, unsigned default_index)
	: font(font), showList(false), keytimeMax(1.f),keytime(0.f)
{
	//unsigned nrofElements = sizeof(list) / sizeof(std::string);

	this->activeElement = new gui::Button(
		x, y, width, height,
		&this->font, list[default_index], 14,
		sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 250), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));

	for (size_t i = 0; i < nrofElements; i++)
	{
		this->list.push_back (
			new gui::Button(
				x, y + ((i+1) * height), width, height,
				&this->font, list[i], 14,
				sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
				sf::Color(70, 70, 70, 250), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200)
			)
		);
	}
}

gui::DropDownList::~DropDownList()
{
	delete this->activeElement;
	for (size_t i = 0; i < this->list.size(); i++)
	{
		delete this->list[i];
	}
}

//Accessors
const bool gui::DropDownList::getKeytime()
{
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}

	return false;
}

//Functions
void gui::DropDownList::updateKeytime(const float& dt)
{
	if (this->keytime < this->keytimeMax)
		this->keytime += 10.f * dt;
}

void gui::DropDownList::update(const sf::Vector2f& mousePos, const float& dt)
{
	this->updateKeytime(dt);

	this->activeElement->update(mousePos);

	//Show and hide the list
	if (this->activeElement->isPressed() && this->getKeytime())
	{
		if(this->showList)
			this->showList = false;
		else
			this->showList = true;
	}

	if (this->showList)
	{
		for (auto& i : this->list)
		{
			i->update(mousePos);

			if (i->isPressed() && this->getKeytime())
			{
				this->showList = false;
				this->activeElement->setText(i->getText());
			}
		}
	}
}

void gui::DropDownList::render(sf::RenderTarget& target)
{
	this->activeElement->render(target);

	if (this->showList)
	{
		for (auto& i : this->list)
		{
			i->render(target);
		}
	}
}