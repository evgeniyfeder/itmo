#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>


int main(int argc, char* argv[], char* envp[]) {
	std::cout << "> ";                                  

	std::string line;	
	while (std::getline(std::cin, line)) {
		if (line == "exit")
			return 0;

		/* Parse string */
		std::istringstream iss(line);

		std::vector<std::string> args;
		std::string tmp;
		while (iss >> tmp) {
			args.emplace_back(std::move(tmp));
		}

		/* Fork */
		const int pid = fork();
		if (pid == -1) {
			perror("fork");
			break;
		}

		if (pid == 0) {
			/* Child */
			std::vector<const char *> char_args(args.size() + 1);
			for (size_t i = 0; i < args.size(); i++)
				char_args[i] = args[i].data();
			char_args[args.size()] = nullptr;

			if (execve(char_args[0], const_cast<char* const*>(char_args.data()), envp) == -1) {
				perror("execv");
				exit(1);
			}
		}
		else {
			/* Parent */
			int status;
			if (waitpid(pid, &status, 0) == -1) {
				perror("waitpid");
				break;
			}
			else {
				std::cout << "Return code: " << WEXITSTATUS(status) << '\n';
			}
		}
		std::cout << "> ";
	}
}
