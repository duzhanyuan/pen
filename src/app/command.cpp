/**
 * Pengo Project
 *
 * Copyright (c) 2015 Penlook Development Team
 *
 * --------------------------------------------------------------------
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License
 * as published by the Free Software Foundation, either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public
 * License along with this program.
 * If not, see <http://www.gnu.org/licenses/>.
 *
 * --------------------------------------------------------------------
 *
 * Author:
 *     Loi Nguyen       <loint@penlook.com>
 */

#include <app/command.h>
#include <app/command/parser.h>

namespace app
{
	Command::Command()
	{
		options   = new InputOptionList();
		arguments = new InputArgumentList();
		this->addOption((new InputOption())
			->setName("env")
			->setAlias('e')
			->setDescription("Environment type")
			->setDefault("dev")
			->setRequired(false)
		);
	}

	Command::~Command()
	{
		clear(options);
		clear(arguments);
	}
	
	Command *Command::setName(string name)
	{
		this->name = name;
		return this;
	}
	
	string Command::getName()
	{
		return this->name;
	}

	Command *Command::setDescription(string description = "")
	{
		this->description = description;
		return this;
	}
	
	string Command::getDescription()
	{
		return description;
	}
	
	Command *Command::addArgument(InputArgument *argument)
	{
		this->arguments->push_back(argument);
		return this;
	}

	InputArgumentList *Command::getArgumentList()
	{
		return arguments;
	}

	Command *Command::addOption(InputOption *option)
	{
		(*this->options)[option->getName()] = option;
		return this;
	}
	
	InputOption *Command::getOption(string name)
	{
		return (*this->options)[name];
	}

	InputOptionList *Command::getOptionList()
	{
		return this->options;
	}

	Cli::Cli()
	{
		parser = new Parser();
		cmds   = new CommandList();
		cmd    = nullptr;
		input  = nullptr;
		output = nullptr;
	}
	
	Cli::~Cli()
	{
		clear(parser);
		clear(cmds);
		free(input);
		free(output);
	}

	Cli *Cli::setInput(Input *input)
	{
		this->input = input;
		return this;
	}
	
	Input *Cli::getInput()
	{
		return this->input;
	}
	
	Cli *Cli::setOutput(Output *output)
	{
		this->output = output;
		return this;
	}
	
	Output *Cli::getOutput()
	{
		return output;
	}
	
	Cli *Cli::addCommand(Command *command)
	{
		command->configure();
		(*this->cmds)[command->getName()] = command;
		return this;
	}
	
	Command *Cli::getCommand(string name)
	{
		return (*cmds)[name];
	}
	
	Command *Cli::getCurrentCommand()
	{
		return this->cmd;
	}

	CommandList *Cli::getCommandList()
	{
		return cmds;
	}
	
	Cli *Cli::parse(int argc, char* argv[])
	{
		// Ignore first argument
		args = seg(argv, 1, argc);

		// Could not find suitable command
		if (cmds->find(args[0]) == cmds->end()) {
			cout << "Error: command not found !" << endl;
			return this;
		}

		// Retreive input option from command configuration
		cmd = (*cmds)[args[0]];
		InputOptionList *options = cmd->getOptionList();

		// Register options of current command with parser
		InputOption *option;
		for (auto it : *options) {
			option = it.second;
			parser->add<string>(
				option->getName(),
				option->getAlias(),
				option->getDescription(),
				option->getRequired()
			);
		}

		// Parse command
		parser->parse_check(argc, argv);
		return this;
	}

	char **Cli::getArguments()
	{
		return args;
	}

	Parser *Cli::getParser()
	{
		return parser;
	}

	Cli *Cli::execute()
	{
		// Retrieve current options and arguments
		InputOptionList *options = cmd->getOptionList();
		InputArgumentList *arguments = cmd->getArgumentList();

		// Transfer arguments from parser to input
		InputArgument *argument;
		InputOption *option;

		// Number of registered arguments should be equivalent with input arguments
		int argc = arguments->size();
		int cmdArgc = (int) parser->rest().size();

		if (argc > cmdArgc) {
			cout << "Missing arguments :" << endl;
			for (int i=cmdArgc; i<argc; i++) {
				cout << "$ " << (*arguments)[i]->getName() << " is required." << endl;
			}
			cout.flush();
			return this;
		}

		argc = min(argc, cmdArgc);
		for (int i=0; i<argc; i++) {
			argument = (*arguments)[i];
			argument->setValue(parser->rest()[i + 1]);
			input->addArgument(argument);
		}

		// Add default options
		input->addOption((*options)["env"]);
		
		// Transfer options from parser to input
		for (auto it : *options) {
			option = it.second;
			option->setValue(parser->get<string>(it.first));
			input->addOption(option);
		}

		// Command execution
		cmd->execute(input, output);
		return this;
	}
}