#include "boot.h"

void Boot::setupBoot(SDL_Renderer* ren) {
	logo.loadFile("Materials/textures/boot/logo.png", ren);

	font = TTF_OpenFont("Materials/fonts/Roboto-Regular.ttf", 16);
	SDL_Color color = { 255, 255, 255 };

	// Eventually check for OS here, but for now just do Windows.
	
	//CPU
	int CPUInfo[4] = { -1 };
	unsigned nExIds, i = 0;
	char CPUBrandString[0x40];
	__cpuid(CPUInfo, 0x80000000);
	nExIds = CPUInfo[0];
	for (i = 0x80000000; i <= nExIds; ++i)
	{
		__cpuid(CPUInfo, i);
		// Interpret CPU brand string
		if (i == 0x80000002)
			memcpy(CPUBrandString, CPUInfo, sizeof(CPUInfo));
		else if (i == 0x80000003)
			memcpy(CPUBrandString + 16, CPUInfo, sizeof(CPUInfo));
		else if (i == 0x80000004)
			memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
	}

	
	cpuName = CPUBrandString;
	cpuName.erase(cpuName.find_last_not_of(" \n\r\t") + 1);

	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	cpuCores = sysInfo.dwNumberOfProcessors;

	// RAM
	MEMORYSTATUSEX statex;
	statex.dwLength = sizeof(statex);
	GlobalMemoryStatusEx(&statex);
	totalRAM = (statex.ullTotalPhys / 1024) / 1024;
	
	ramIncrementer = (totalRAM * 0.02);

	// Storage
	std::string model = wmiQuery("wmic path win32_diskdrive get Model");
	std::string size = wmiQuery("wmic path win32_diskdrive get Size");

	std::vector<std::string> modelVector;
	std::vector<std::string> sizeVector;
	boost::split(modelVector, model, boost::is_any_of("\r\n"), boost::token_compress_on);
	boost::split(sizeVector, size, boost::is_any_of("\r\n"), boost::token_compress_on);
	for (int i = 0; i < std::size(modelVector); i++) {
		if (i > 0 && i < (std::size(modelVector) - 1)) {
			std::string modelName = modelVector[i];
			modelName.erase(modelName.find_last_not_of(" ") + 1);
			std::string sizeString = sizeVector[i];
			sizeString.erase(sizeString.find_last_not_of(" ") + 1);
			int size = (std::stoll(sizeString) / 1024) / 1024;

			storageInfo += "Detected Disk Drive: " + modelName + " " + std::to_string(size) + "MB\n";
		}
	}
	
}

std::string Boot::wmiQuery(const char* query) {
	std::array<char, 128> buffer;
	std::string result;
	std::shared_ptr<FILE> pipe(_popen(query, "r"), _pclose);
	while (!feof(pipe.get())) {
		if (fgets(buffer.data(), 128, pipe.get()) != NULL) {
			result += buffer.data();
		}
	}
	return result;
}

void Boot::renderBootAnimation(SDL_Renderer* ren, int windowWidth, int windowHeight) {
	if (!duration.isStarted()) {
		duration.start();
	}

	if (check1 && check2) {
		bootComplete = true;
	}
	else {
		if (!check1) {
			animationPart1(ren, (windowWidth - logo.getWidth()));
		}
		else if (check1 && !check2) {
			animationPart2(ren, windowWidth, windowHeight);
		}
	}
}

void Boot::animationPart1(SDL_Renderer* ren, int logoX) {
	std::string textToLoad = " ";
	float seconds = (duration.getTicks() / 1000.f);

	if (seconds > 2) {
		textToLoad = "Xynergy Engine\nCopyright (C) 2021, Aravix.\n\n";;
		logo.render(logoX, 5, ren);
	}

	if (seconds > 2.5) {
		textToLoad += cpuName + ", " + std::to_string(cpuCores) + " Processor(s)\n";
	}

	if (seconds > 3) {
		textToLoad += "Memory Test: ";
		if (ramCount < totalRAM) {
			ramCount += ramIncrementer;
			textToLoad += std::to_string(ramCount) + "MB";
		}
		else {
			ramCount = totalRAM;
			textToLoad += std::to_string(ramCount) + "MB OK\n\n";
			if (!memoryCheckOK) {
				memoryCheckClearTime = seconds;
				memoryCheckOK = true;
			}
		}
	}

	if (memoryCheckOK) {
		textToLoad += storageInfo + "\n";

		if (seconds > memoryCheckClearTime + 1 && seconds < memoryCheckClearTime + 4) {
			textToLoad += "\n\n\nXynergy is initializing";

			if (seconds > memoryCheckClearTime + 1) textToLoad += ".";
			if (seconds > memoryCheckClearTime + 2) textToLoad += ".";
			if (seconds > memoryCheckClearTime + 3) textToLoad += ".";

		}
		else if (seconds > memoryCheckClearTime + 4) {
			textToLoad += "\n\n\nXynergy is ready for lift-off!";
		}

		if (seconds > memoryCheckClearTime + 5) {
			check1 = true;
			duration.stop();
			logo.setAlpha(0);
		}
	}

	text.loadText(textToLoad, {255, 255, 255}, font, 16, ren, true, 900);
	text.render(20, 50, ren);
}

void Boot::animationPart2(SDL_Renderer* ren, int windowWidth, int windowHeight) {
	if (alphaIncrementer != 255) {
		alphaIncrementer++;
		logo.setAlpha(alphaIncrementer);
	}
	else {
		float seconds = (duration.getTicks() / 1000.f);
		if (logoAppeared == 0) {
			logoAppeared = seconds;
		}

		if (seconds >= (logoAppeared + 2)) {
			duration.stop();
			check2 = true;
		}
	}

	logo.render((windowWidth / 2) - 100, (windowHeight / 2) - logo.getHeight(), ren);
}

void Boot::clear() {
	font = NULL;
	count = 0;
	check1 = false;
	check2 = false;
	bootComplete = false;
	cpuCores = 0;
	ramCount = 0;
	totalRAM = 0;
	memoryCheckOK = false;
	memoryCheckClearTime = 0;
	ramIncrementer = 0;
	alphaIncrementer = 0;
	logoAppeared = 0;
}

Boot::Boot() {
	clear();
}

Boot::~Boot() {
	logo.kill();
	text.kill();
}