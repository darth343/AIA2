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
	}

	if (ScrollOffsetY < 0)
		ScrollOffsetY = 0;

	//int temp = ScrollOffsetY * fontSize + (mb.size() * fontSize) - fontSize;

	//if (ScrollOffsetY * fontSize + (mb.size() * (2*fontSize)) - fontSize > 300)
	//{
	//	ScrollOffsetY = (mb.size() * fontSize - 600 + fontSize) / fontSize;
	//}
}

void MessageBoard::Add(CCharacter* source, const std::string& recipient, const std::string& _message)
{
	std::ostringstream ss;
	if (source)
	{
		ss << "<Team " << source->GetTeamID() << " Fr: " << source->GetType() << "To: " << recipient << ">";
	}
	else
	{
		ss << "<APPLICATION>";
	}



	//if (mb.size() - 1> 600 / fontSize)
	//{
	//	for (int i = 0; i < mb.size(); i++)
	//	{
	//		if (i + 1 < mb.size())
	//		{
	//			mb[i] = mb[i+1];
	//		}
	//		else
	//		{
	//			mb.push_back(ss.str());
	//			break;
	//		}
	//	}
	//}
	//else
	//{
	Message temp;
	temp.header = ss.str();
	temp.msg = _message;
	mb.push_back(temp);
	//}

	//if (ScrollOffsetY * fontSize + 600 - fontSize < mb.size() * fontSize && ScrollOffsetY + 600 / fontSize == (int)(mb.size()))
	//{
	//	ScrollOffsetY = (mb.size() * fontSize - 600 + fontSize) / fontSize;
	//}

	if (( ((int)(mb.size()) - 1) * (2*fontSize)) + ScrollOffsetY * fontSize - (150 + fontSize) > 75)
	{
		ScrollOffsetY = ((((int)(mb.size()) - 1) * (2 * fontSize)) + ScrollOffsetY * fontSize - (150 + fontSize)) / 50;
	}

	//std::cout << ScrollOffsetY << std::endl;

}

void MessageBoard::Render()
{
	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();
	modelStack.Translate(0, -300, 0);
	modelStack.Scale(1200, 300, 0);
	RenderHelper::RenderMesh(MeshBuilder::GetInstance()->GetMesh("BlackQuad"));
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-600, ScrollOffsetY * fontSize - (150 + fontSize), 0);

	for (int i = 0; i < mb.size(); i++)
	{

		float ypos = i * (-fontSize * 2);
		//std::cout << ypos + ScrollOffsetY * fontSize - (150 + fontSize) << std::endl;
		if (ypos + ScrollOffsetY * fontSize - (150 + fontSize) > -150 - fontSize)
			continue;

		modelStack.PushMatrix();
		modelStack.Translate(0, ypos, 1);

		modelStack.PushMatrix();
		modelStack.Scale(fontSize, fontSize, fontSize);
		RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), mb[i].header, Color(1, 1, 1));
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0, -fontSize, 0);
		modelStack.Scale(fontSize, fontSize, fontSize);
		RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), mb[i].msg, Color(1, 1, 1));
		modelStack.PopMatrix();

		modelStack.PopMatrix();
	}
	modelStack.PopMatrix();
}