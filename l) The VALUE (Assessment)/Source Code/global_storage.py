"""
Name: global_storage.py
Version: 0.0.3-alpha
Description: The file that allows me to manage storage across files efficiently
Author: Nicolas Martens
"""

import copy

# The index of the screen we are currently showing
mainCurrentPage = 0

# Default setting values
settingDefault = {
	"GPSet": {
		"InfoUtils": {
			"Mode": "None",
			"UDisplay": "None",
			"FDisplay": "None",
			}
		},
	"AudioSet": {
		"VolSet": {
			"Genval": 50,
			"SFXVal": 50,
			"ABGVal": 50,
			},
		"SoundPacks": {
			"GMusic": ["Pack Name 1"],
			"SFX": ["Pack Name 1"],
			"Amb": ["Pack Name 1"],
			}
		},
	"GraSet": {
		"Themes": {
			"GUI": "Theme Name 1",
			"Uni": "Theme Name 1",
			"Env": "Theme Name 1",
			}
		}
	}
settingData = copy.deepcopy(settingDefault)

# Default save data values
savePlaceholders = {
	"Name": "New Save",
	"Difficulty": -1,
	"Last": "N/A",
	"Index": 0,
	"Quiz": {
		"QAns": 0,
		"Q-RA": 0,
		"Q-WA": 0,
		"AccP": 0
		},
	"Score": 0.00,
	"Kills": 0,
	"Ammo": [
		],
	"Units": {
		}
	}

saveData = copy.deepcopy(savePlaceholders)

# Progress default values
progressDefaults = {
	"Home": False,
	"Save": False,
	"Game": False,
	"Quiz": False
	}

progressData = copy.deepcopy(progressDefaults)