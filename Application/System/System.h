#pragma once
#include "ObjectManager.h"
#include <string>
#include <vector>
#include <fstream>

using std::string;
using std::vector;

class System
{
public:

	static System& theSystem();

	void startSystem();

private:

	string fileName;
	string currentInput;
	string currentParameters;
	string currentCommand;
	vector<string> commands;

private:

	void introduction();
	void loadCommands();
	void readCommandFromInput();
	void executeCommand();
	void saveBeforeClosing();
	void setCurrentSystemParameters();
	void currentCommandToLower();

	size_t getParamsCount();
	vector<string> getParameters();

	vector<string> getTranslateParams();
	vector<string> getTranslateNoId();

	vector<string> getShapeParameters();

private:

	void open();
	void print();
	void create();
	void group();
	void ungroup();
	void insert();
	void extract();
	void hide();
	void show();
	void translate();
	void scale();
	void save();
	void saveAs();
	void stroke();
	void fill();
	void help();

private:

	string extractFilename();

	System() = default;
	
};

