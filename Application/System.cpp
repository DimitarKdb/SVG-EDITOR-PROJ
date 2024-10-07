#include "System.h"
#include "ShapeFactory.h"
#include <iostream>
#include <stdexcept>

using std::cout;
using std::cin;
using std::endl;
using std::ofstream;
using std::ifstream;

System& System::theSystem()
{
	static System theSystem;

	return theSystem;
}

void System::startSystem()
{
	this->loadCommands();
	this->introduction();

	do
	{
		cout << "Enter a command:" << endl;

		readCommandFromInput();
		executeCommand();

		cout << "-----------------------------" << endl;

	} while (currentCommand != "exit");

	saveBeforeClosing();

	cout << "Application is closing.." << endl;

}

void System::introduction()
{
	cout << "----------SVG-parser---------" << endl;
	cout << "Application is running, you can procceed by typing one of the following commands: " << endl;
	
	this->help();

	cout << "-----------------------------" << endl;
}

void System::loadCommands()
{
	commands.push_back("open");
	commands.push_back("print");
	commands.push_back("create");
	commands.push_back("group");
	commands.push_back("ungroup");
	commands.push_back("insert");
	commands.push_back("extract");
	commands.push_back("hide");
	commands.push_back("show");
	commands.push_back("translate");
	commands.push_back("scale");
	commands.push_back("save");
	commands.push_back("saveas");
	commands.push_back("stroke");
	commands.push_back("fill");
	commands.push_back("help");
	commands.push_back("exit");
}

void System::readCommandFromInput()
{
	std::getline(std::cin, currentInput);

	if (currentInput.empty())
		return;

	size_t commandPos = currentInput.find_first_not_of(' ');

	currentInput = currentInput.substr(commandPos);

	size_t size = currentInput.size();

	for (size_t i = 0; currentInput[i] != ' ' && i < size; i++)
	{
		currentCommand.push_back(currentInput[i]);
	}

	currentCommandToLower();
	
	setCurrentSystemParameters();
}

void System::executeCommand()
{
	if (currentCommand == "open" && getParamsCount() == 1)
	{
		open();
	}
	else if (currentCommand == "print" && getParamsCount() == 0)
	{
		print();
	}
	else if (currentCommand == "create" && getParamsCount() != 0 && getParamsCount() != 1)
	{
		create();
	}
	else if (currentCommand == "group" && getParamsCount() == 4)
	{
		group();
	}
	else if (currentCommand == "ungroup" && getParamsCount() == 1)
	{
		ungroup();
	}
	else if (currentCommand == "insert" && getParamsCount() == 2)
	{
		insert();
	}
	else if (currentCommand == "extract" && getParamsCount() == 2)
	{
		extract();
	}
	else if (currentCommand == "hide" && getParamsCount() == 1)
	{
		hide();
	}
	else if (currentCommand == "show" && getParamsCount() == 1)
	{
		show();
	}
	else if (currentCommand == "translate" && (getParamsCount() == 2 || getParamsCount() == 3))
	{
		translate();
	}
	else if (currentCommand == "scale" && (getParamsCount() == 2 || getParamsCount() == 3))
	{
		scale();
	}
	else if (currentCommand == "help" && getParamsCount() == 0)
	{
		help();
	}
	else if (currentCommand == "save" && getParamsCount() == 0)
	{
		save();
	}
	else if (currentCommand == "saveas" && getParamsCount() == 1)
	{
		saveAs();
	}
	else if (currentCommand == "stroke" && getParamsCount() == 2)
	{
		stroke();
	}
	else if (currentCommand == "fill" && getParamsCount() == 2)
	{
		fill();
	}
	else if (currentCommand == "exit" && getParamsCount() == 0)
	{
		return;
	}
	else {
		cout << "Command is not supported or used correctly, please try again." << endl;
	}

	currentCommand.clear();
	currentInput.clear();
	currentParameters.clear();
}

void System::setCurrentSystemParameters()
{
	bool isEmpty = true;

	if (currentInput.size() == currentCommand.size()) {
		currentParameters = "";
	}
	else {
		currentParameters = currentInput.substr(currentCommand.size() + 1);

		for (size_t i = 0; i < currentParameters.size(); i++)
		{
			if (currentParameters[i] != ' ') {
				isEmpty = false;
				break;
			}

		}
	}

	if (isEmpty) {
		currentParameters.clear();
	}
	else {
		int firtParamPos = currentParameters.find_first_not_of(" ");
		int lastParamPos = currentParameters.find_last_not_of(" ");

		currentParameters = currentParameters.substr(firtParamPos, lastParamPos + 1);
	}
		
}

void System::currentCommandToLower()
{
	for (size_t i = 0; i < currentCommand.size(); i++)
	{
		if (currentCommand[i] >= 'A' && currentCommand[i] <= 'Z')
			currentCommand[i] += ' ';
	}
}

size_t System::getParamsCount()
{
	size_t count = 0;

	if (currentParameters.empty())
		return count;

	count = 1;

	for (size_t i = 0; i < currentParameters.size(); i++)
	{
		if (currentParameters[i] != ' ')
			continue;

		count++;

		while (currentParameters[i] == ' ')
		{
			i++;
		}
	}


	return count;
}

vector<string> System::getParameters()
{
	vector<string> parameters;

	string parameter;

	if (currentCommand == "translate") {
		
		parameters = getTranslateParams();

	}
	else {
		for (size_t i = 0; i < currentParameters.size(); i++)
		{
			if (currentParameters[i] == ' ') {
				continue;
			}
			else {
				while (currentParameters[i] != ' ' && i < currentParameters.size())
				{
					parameter.push_back(currentParameters[i]);
					i++;
				}

				parameters.push_back(parameter);
				parameter.clear();
			}

		}
	}


	return parameters;



}

vector<string> System::getTranslateParams()
{
	vector<string> parameters;
	int verticalPos = currentParameters.find("vertical=");
	int horizontalPos = currentParameters.find("horizontal=");

	if (verticalPos == string::npos || horizontalPos == string::npos)
		return parameters;

	string parameter;


	if (verticalPos == 0) {

		parameters = getTranslateNoId();
		return parameters;

	}
	else {
		for (size_t i = 0; i < verticalPos - 1; i++)
		{
			if (currentParameters[i] == ' ')
				continue;
			else
				parameter.push_back(currentParameters[i]);
		}
		string parametersSaved = currentParameters;

		currentParameters = currentParameters.substr(verticalPos);
		parameters = getTranslateNoId();
		parameters.push_back(parameter);

		currentParameters = parametersSaved;

		return parameters;
	}

	
}

vector<string> System::getTranslateNoId()
{
	vector<string> parameters;
	int verticalPos = currentParameters.find("vertical=");
	int horizontalPos = currentParameters.find("horizontal=");
	const int verticalLength = 9;
	const int horizontalLength = 11;
	string parameter;

	if (verticalPos == string::npos || horizontalPos == string::npos)
		throw std::runtime_error("Translate arguments are not correct");

	for (size_t i = verticalLength; i < currentParameters.size(); i++)
	{
		if (currentParameters[i] == ' ')
			continue;
		else if(currentParameters[i] >= '0' && currentParameters[i] <= '9' || currentParameters[i] == '-')
			parameter.push_back(currentParameters[i]);

		if (i == horizontalPos) {
			i += horizontalLength - 1;
			parameters.push_back(parameter);
			parameter.clear();
		}

	}

	parameters.push_back(parameter);

	return parameters;
}

vector<string> System::getShapeParameters()
{
	string parameter;
	vector<string> parameters;

	for (size_t i = 0; i < currentParameters.size(); i++)
	{
		if (currentParameters[i] == ' ')
			continue;
		else {
			while (currentParameters[i] != ' ' && i < currentParameters.size())
			{
				parameter.push_back(currentParameters[i]);
				i++;
			}

			parameters.push_back(parameter);
			parameter.clear();
		}

	}

	return parameters;
}

void System::open()
{
	fileName = extractFilename();

	if (fileName == "") {
		cout << "Invalid file name." << endl;
		return;
	}

	if (ObjectManager::getInstance().readShapes(fileName)) {
		cout << "File: " << fileName << " was sucessfully opened!" << endl;
	}
	else {
		cout << "File: " << fileName << " was not sucessfully opened! Try another one!" << endl;
	}

	return;
}

void System::print()
{
	ObjectManager::getInstance().print();
}

void System::create()
{
	string shapeType;

	for (size_t i = 0; currentParameters[i] != ' '; i++)
	{
		shapeType.push_back(currentParameters[i]);
	}

	currentParameters = currentParameters.substr(shapeType.size() + 1);

	vector<string> parameters = getShapeParameters();

	if (ObjectManager::getInstance().createShape(shapeType, parameters)) {
		cout << "Shape " << shapeType << " was sucessfully created!" << endl;
	}
	else {
		cout << "Shape " << shapeType << " was not created, try again!" << endl;
	}
	
}

void System::group()
{

	vector<string> parameters = getShapeParameters();

	Point TL{ stod(parameters[0]), stod(parameters[1]) };
	Point BR{ stod(parameters[2]), stod(parameters[3]) };

	if (ObjectManager::getInstance().group(TL, BR)) {
		cout << "A group was sucessfully created!" << endl;
	}
	else {
		cout << "Grouping was not possible, no shapes in this region!" << endl;
	}
}

void System::ungroup()
{
	vector<string> parameters = getShapeParameters();

	size_t grId = stoi(parameters[0]);

	if (ObjectManager::getInstance().ungroup(grId)) {
		cout << "The group with id: " << grId << " was sucessfully removed!" << endl;
	}
	else {
		cout << "Ungrouping was not possible!" << endl;
	}
}

void System::insert()
{
	vector<string> parameters = getShapeParameters();

	size_t grId = stoi(parameters[0]);
	size_t elId = stoi(parameters[1]);

	if (ObjectManager::getInstance().insert(grId, elId)) {
		cout << "The element was sucessfully added to the group!" << endl;
	}
	else {
		cout << "Inserting was not possible!" << endl;
	}
}

void System::extract()
{
	vector<string> parameters = getShapeParameters();

	size_t grId = stoi(parameters[0]);
	size_t elId = stoi(parameters[1]);

	if (ObjectManager::getInstance().extract(grId, elId)) {
		cout << "The element was sucessfully extracted from the group!" << endl;
	}
	else {
		cout << "Extracting was not possible!" << endl;
	}
}

void System::hide()
{
	int id = stoi(currentParameters);

	if (!ObjectManager::getInstance().hideFigure(id)) {
		cout << "Hiding the figure was not possible!" << endl;
		return;
	}

	cout << "Figure with id: " << id << " was hidden!" << endl;
}

void System::show()
{
	int id = stoi(currentParameters);

	if (!ObjectManager::getInstance().showFigure(id)) {
		cout << "Showing the figure was not possible!" << endl;
		return;
	}

	cout << "Figure with id: " << id << " was shown!" << endl;
}

void System::translate()
{
	vector<string> parameters;

	parameters = getParameters();

	if (parameters.size() == 0) {
		cout << "Wrong translate parameters!" << endl;
		return;
	}

	double xCoord = stod(parameters[1]);
	double yCoord = stod(parameters[0]);

	bool outcome = false;

	if (parameters.size() == 2) {

		outcome = ObjectManager::getInstance().translateAll(Point(xCoord, yCoord));

	}
	else if (parameters.size() == 3) {

		int id = stoi(parameters[2]);

		outcome = ObjectManager::getInstance().translateShape(id ,Point(xCoord, yCoord));
	}

	if (outcome) {
		cout << "Translation was sucessful!" << endl;
	}
	else {
		cout << "Translation was not sucessful!" << endl;
	}
}

void System::scale()
{
	vector<string> parameters = getParameters();

	bool outcome = false;

	if (getParamsCount() == 2) {
		double wCoeff = stod(parameters[0]);
		double hCoeff = stod(parameters[1]);

		outcome = ObjectManager::getInstance().scaleAll(wCoeff, hCoeff);
	}
	else
	{
		int id = stoi(parameters[0]);
		double wCoeff = stod(parameters[1]);
		double hCoeff = stod(parameters[2]);

		outcome = ObjectManager::getInstance().scaleShape(id, wCoeff, hCoeff);
	}

	if (outcome) {
		cout << "Scaling was sucessful!" << endl;
	}
	else {
		cout << "Scaling was not sucessful!" << endl;
	}
}

void System::save()
{
	if (ObjectManager::getInstance().saveAs(fileName))
		cout << "Figures were sucessfully saved!" << endl;
}

void System::saveAs()
{
	string tempFileName = extractFilename();

	if (ObjectManager::getInstance().saveAs(tempFileName))
		cout << "Figures were sucessfully saved in file: " << tempFileName << endl;
}

void System::stroke()
{
	vector<string> parameters = getParameters();

	size_t shapeId = stoi(parameters[0]);
	string strokeColor = parameters[1];

	if (ObjectManager::getInstance().stroke(shapeId, strokeColor)) {
		cout << "Shape's stroke color has been sucessfully updated!" << endl;
	}
	else {
		cout << "It was not possible to modifiy the shape's stroke color!" << endl;
	}
}

void System::fill()
{
	vector<string> parameters = getParameters();

	size_t shapeId = stoi(parameters[0]);
	string fillColor = parameters[1];

	if (ObjectManager::getInstance().fill(shapeId, fillColor)) {
		cout << "Shape's fill color has been sucessfully updated!" << endl;
	}
	else {
		cout << "It was not possible to modifiy the shape's fill color!" << endl;
	}
}

void System::saveBeforeClosing()
{
	if (fileName.empty())
		return;

	cout << "Do you want the changes to be saved in: " << fileName << " before closing the application?" << endl;
	cout << "\'Y\' for yes, 'N' for no" << endl;

	char answer;

	cin >> answer;

	if (answer == 'Y' || answer == 'y')
	{
		save();
		return;
	}
	else if(answer == 'N' || answer == 'n') 
	{
		return;
	}
	else 
	{
		cout << "Invalid answer!" << endl;
		saveBeforeClosing();
	}
		
}

void System::help()
{
	for (size_t i = 0; i < commands.size(); i++)
	{
		cout << commands[i];

		if (i % 5 == 0 && i != 0)
			cout << endl;
		else if (i != commands.size() - 1)
			cout << ", ";
	}

	cout << endl;
}

string System::extractFilename()
{
	string fileName = currentParameters;


	if (fileName.find(".txt") == string::npos && fileName.find(".svg") == string::npos)
		fileName += ".svg";

	return fileName;
}


