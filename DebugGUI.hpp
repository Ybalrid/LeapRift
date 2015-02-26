#ifndef DEBUG_GUI_HPP
#define DEBUG_GUI_HPP


#include <Ogre.h>
#include <Gorilla.h>

#include <string>

class DebugGUI
{
public:
	DebugGUI()
	{
		camera = NULL;
		GUI_root = NULL;
		baseLayer = NULL;
		background = NULL;
		text = NULL;
	}

	void init(Ogre::SceneNode* rootNode)
	{
		if(!rootNode) return;

		camera = rootNode;
		GUI_root = camera->createChildSceneNode();				
		GUI_root->translate(-0.6f, 0.0f, -2.0f);
		svbk = new Gorilla::Silverback();
		svbk->loadAtlas("dejavu");

		screen = svbk->createScreenRenderable(Ogre::Vector2(2.0f,1.0f),"dejavu");
		GUI_root->attachObject(screen);

		baseLayer = screen->createLayer(0);
		background = baseLayer->createRectangle(0,0,300,200);
		background->background_colour(Gorilla::rgb(255,0,0,50));
    
		createCaption();
	}

	void setText(std::string text)
	{
		textContent = text;
	}

	void update()
	{
		
		if(!baseLayer) return;

		text->text(textContent.c_str());
	}

	Ogre::SceneNode* getGUI_rootNode()
	{
		return GUI_root;
	}

private: //Methods

	void createCaption()
	{
		if(!baseLayer) return; 

		text = baseLayer->createCaption(9,20,20, textContent.c_str());
		text->colour(Ogre::ColourValue::Black);
		text->height(5);
		text->_redraw();
	}

private:
	Ogre::SceneNode* camera;
	Ogre::SceneNode* GUI_root;
	Gorilla::Silverback* svbk;
	Gorilla::ScreenRenderable* screen;
	Gorilla::Layer* baseLayer;
	Gorilla::Rectangle* background;
	Gorilla::Caption* text;

	std::string textContent;
};

#endif //DEBUG_GUI