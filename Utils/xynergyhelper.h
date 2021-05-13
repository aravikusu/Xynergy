#ifndef XYNERGYHELPER_H
#define XYNERGYHELPER_H

#include <string>
#include "enums.h"

/// <summary>
/// Helper functions. From enum conversions to console colors.
/// </summary>
namespace XynergyHelper {

	/// <summary>
	/// Need a Xynergy enum to be a string or vice versa? Use these.
	/// </summary>
	namespace enum_converter {
		inline std::string xynergyGameStateToString(Xynergy_GameState state) {
			switch (state)
			{
			case Xynergy_GameState::XYNERGY_START:
				return "START";
			case Xynergy_GameState::XYNERGY_BOOT:
				return "BOOT";
			case Xynergy_GameState::XYNERGY_LOGIN:
				return "LOGIN";
			case Xynergy_GameState::XYNERGY_DASHBOARD:
				return "DASHBOARD";
			case Xynergy_GameState::XYNERGY_INITSETUP:
				break;
			default:
				throw "Not a valid GameState...";
			}
		}

		inline std::string taskbarOrientationToString(Xynergy_TaskbarOrientation orientation) {
			switch (orientation)
			{
			case Xynergy_TaskbarOrientation::XYNERGY_TASKBAR_TOP:
				return "top";
			case Xynergy_TaskbarOrientation::XYNERGY_TASKBAR_RIGHT:
				return "right";
			case Xynergy_TaskbarOrientation::XYNERGY_TASKBAR_BOTTOM:
				return "bottom";
			case Xynergy_TaskbarOrientation::XYNERGY_TASKBAR_LEFT:
				return "left";
			default:
				throw "Not a valid TaskbarOrientation...";
			}
		}

		inline Xynergy_TaskbarOrientation stringToTaskbarOrientation(std::string orientation) {
			if (orientation == "top") {
				return Xynergy_TaskbarOrientation::XYNERGY_TASKBAR_TOP;
			}
			else if (orientation == "right") {
				return Xynergy_TaskbarOrientation::XYNERGY_TASKBAR_RIGHT;
			}
			else if (orientation == "bottom") {
				return Xynergy_TaskbarOrientation::XYNERGY_TASKBAR_BOTTOM;
			}
			else if (orientation == "left") {
				return Xynergy_TaskbarOrientation::XYNERGY_TASKBAR_LEFT;
			}
			else {
				throw "Not a valid TaskbarOrientation...";
			}
		}
	}

	/// <summary>
	/// Colors and formatting. 
	/// </summary>
	namespace console {
		inline std::string error() {
			return " \033[0;31mError!\033[0;37m ";
		}

		inline std::string warning() {
			return " \033[0;33mWarning!\033[0;37m ";
		}

		inline std::string alert() {
			return " \033[0;36mAlert!\033[0;37m ";
		}

		inline std::string success() {
			return " \033[0;32mSuccess!\033[0;37m ";
		}

		inline std::string question() {
			return " \033[0;36mQuestion:\033[0;37m ";
		}
	}
}

#endif