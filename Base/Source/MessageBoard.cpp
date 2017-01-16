#include "MessageBoard.h"
#include "GraphicsManager.h"
#include "MeshBuilder.h"
#include "RenderHelper.h"
#include "MouseController.h"
#include <sstream>
MessageBoard* MessageBoard::m_instance = 0;

MessageBoard::MessageBoard()
: fontSize(25)
, ScrollOffsetY(0)
{

}


MessageBoard::~MessageBoard()
{

}


MessageBoard* MessageBoard::GetInstance()
{
	if (!m_instance)
	{
		m_instance = new MessageBoard();
	}
	return m_instance;
}

void MessageBoard::SetFontSize(int _size)
{
	fontSize = _size;
}

void MessageBoard::Update()
{
	if (MouseController::GetInstance()->GetMouseScrollStatus(MouseController::SCROLL_TYPE_YOFFSET) != 0.0)
	{
		ScrollOffsetY += MouseController::GetInstance()->GetMouseScrollStatus(MouseController::SCROLL_TYPE_YOFFSET);
		//std::cout << "SCROLL " << MouseController::GetInstance()->GetMouseScrollStatus(MouseController::SCROLL_TYPE_YOFFSET) << std::endl;
	}

	if (ScrollOffsetY < 0)
		ScrollOffsetY = 0;

	//int temp = ScrollOffsetY * fontSize + (mb.size() * fontSize) - fontSize;

	//if (ScrollOffsetY * fontSize + (mb.size() * fontSize) - fontSize > mb.size() * fontSize)
	//{
	//	ScrollOffsetY = (mb.size() * fontSize - 600 + fontSize) / fontSize;
	//}
}

void MessageBoard::Add(CCharacter* source, const std::string& _message)
{
	std::ostringstream ss;
	if (source)
	{
		ss << "<Team " << source->GetTeamID() << " " << source->GetType() << "> " << _message;
	}
	else
	{
		ss << "<" << "NULL" << " " << "NULLTYPE" << "> " << _message;
	}

	mb.push_back(ss.str());

	if (ScrollOffsetY * fontSize + 600 - fontSize < mb.size() * fontSize)
	{
		ScrollOffsetY = (mb.size() * fontSize - 600 + fontSize) / fontSize;
	}
}

void MessageBoard::Render()
{
	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();
	modelStack.Translate(400, 0, 0);
	modelStack.Scale(1100, 600, 0);
	RenderHelper::RenderMesh(MeshBuilder::GetInstance()->GetMesh("BlackQuad"));
	modelStack.PopMatrix();

	for (int i = 0; i < mb.size(); i++)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-150, i*-fontSize + (300 - fontSize) + (ScrollOffsetY * fontSize), 1);
		modelStack.Scale(fontSize, fontSize, fontSize);
		RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), mb[i], Color(1, 1, 1));
		modelStack.PopMatrix();
	}
}