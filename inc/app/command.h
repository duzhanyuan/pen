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

#ifndef APP_COMMAND_H_
#define APP_COMMAND_H_

#include <iostream>
#include <vector>
#include <string>
#include <sys/func.h>
#include <sys/type.h>
#include <app/command/input.h>
#include <app/command/output.h>

using std::string;
using std::vector;
using namespace app::command;

#define ArgumentList vector<InputArgument*>
#define OptionList vector<InputOption*>

namespace app
{
	class Command
	{
		private:
			string name;
			string description;
			ArgumentList arguments;
			OptionList options;
		public:
			Command();
			~Command();
			// Name
			Command *setName(string);
			string getName();
			// Description
			Command *setDescription(string);
			string getDescription();
			// Argument
			Command *addArgument(string name, string description = "");
			ArgumentList getArguments();
			// Option
			Command *addOption(string name, string description = "", int inputFlag = InputOption::REQUIRED, string defaultValue = "");
			OptionList getOptions();
	};
}

#endif