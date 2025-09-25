"""
Name: file_helper.py
Version: 0.0.3-alpha
Description: The scripts that allow me to manage anything file related, such as saving game states
Author: Nicolas Martens
"""

import os
import json
import copy

from PySide6.QtCore import ( # type: ignore
	Slot,
	)
from PySide6.QtWidgets import ( # type: ignore
	QDialog,
	QStackedWidget,
	QWidget,
	)

from widget_helper import (
	changeScreen,
	loadWidget,
	showDialog,
	updateSaveStats,
	)
import global_storage as gs

newSaveDialog = 0

# Get the filepaths as strings for ease
DATAFOLDER = "../Data/"
SETTINGSFILE = DATAFOLDER + "Global.tvsf"
PROGRESSFILE = DATAFOLDER + "Stage.tvhp"
SAVEAFOLDER = DATAFOLDER + "I/"
SAVEADATA = SAVEAFOLDER + "Standard.andf"
SAVEAENV = SAVEAFOLDER + "Expanse.tegf"
SAVEAUNITS = SAVEAFOLDER + "Units/"
SAVEBFOLDER = DATAFOLDER + "II/"
SAVEBDATA = SAVEBFOLDER + "Standard.andf"
SAVEBENV = SAVEBFOLDER + "Expanse.tegf"
SAVEBUNITS = SAVEBFOLDER + "Units/"
SAVECFOLDER = DATAFOLDER + "III/"
SAVECDATA = SAVECFOLDER + "Standard.andf"
SAVECENV = SAVECFOLDER + "Expanse.tegf"
SAVECUNITS = SAVECFOLDER + "Units/"

# When the scripts are run, just ensure that we have the required folders
def setupWorkspace():
	if (os.path.exists(DATAFOLDER) == False): os.makedirs(DATAFOLDER)

	if (os.path.exists(SETTINGSFILE) == False):
		with open(SETTINGSFILE, "x") as file:
			text = json.dumps(gs.settingDefault)
			file.write(text)

	if (os.path.exists(PROGRESSFILE) == False):
		with open(PROGRESSFILE, "x") as file:
			text = json.dumps(gs.progressDefaults)
			file.write(text)
	else:
		with open(PROGRESSFILE, "r") as file:
			text = file.read()
			gs.progressData = json.loads(text)

	if (os.path.exists(SAVEAFOLDER) == False): os.makedirs(SAVEAFOLDER)

	if (os.path.exists(SAVEADATA) == False):
		with open(SAVEADATA, "x") as file:
			gs.savePlaceholders["Index"] = 1
			text = json.dumps(gs.savePlaceholders)
			file.write(text)

	if (os.path.exists(SAVEAUNITS) == False): os.makedirs(SAVEAUNITS)

	if (os.path.exists(SAVEBFOLDER) == False): os.makedirs(SAVEBFOLDER)

	if (os.path.exists(SAVEBDATA) == False):
		with open(SAVEBDATA, "x") as file:
			gs.savePlaceholders["Index"] = 2
			text = json.dumps(gs.savePlaceholders)
			file.write(text)

	if (os.path.exists(SAVEBUNITS) == False): os.makedirs(SAVEBUNITS)

	if (os.path.exists(SAVECFOLDER) == False): os.makedirs(SAVECFOLDER)

	if (os.path.exists(SAVECDATA) == False):
		with open(SAVECDATA, "x") as file:
			gs.savePlaceholders["Index"] = 3
			text = json.dumps(gs.savePlaceholders)
			file.write(text)

	if (os.path.exists(SAVECUNITS) == False): os.makedirs(SAVECUNITS)

	gs.savePlaceholders["Index"] = 0
	loadSettings()

# When I want to load data from a save
@Slot(int)
def updateSaveLoad(saveIndex: int):
	text = dict()
	if (saveIndex == 1):
		with open(SAVEADATA, "r") as file: text = file.read()
	elif (saveIndex == 2):
		with open(SAVEBDATA, "r") as file: text = file.read()
	elif (saveIndex == 3):
		with open(SAVECDATA, "r") as file: text = file.read()
	else: return
	gs.saveData = json.loads(text)
	return

# When I want to create a new save
@Slot(QStackedWidget)
def createSave(parent:QStackedWidget):
	if gs.saveData["Difficulty"] != -1:
		changeScreen(parent, 1, 0)
		return
	global newSaveDialog
	from dialog_container import TVNewSaveDialog
	newSaveDialog = TVNewSaveDialog(loadWidget("new_save_dialog.ui"))
	newSaveDialog.slide = parent
	showDialog(newSaveDialog)

# When I want to delete some save data
@Slot(int, QWidget)
def deleteSave(saveIndex:int, saveLoads:QWidget):
	gs.savePlaceholders["Index"] = saveIndex
	text = json.dumps(gs.savePlaceholders)
	if (saveIndex == 1):
		with open(SAVEADATA, "w") as file: file.write(text)
		for unit in os.listdir(SAVEAUNITS):
			os.remove(SAVEAUNITS + unit)
	elif (saveIndex == 2):
		with open(SAVEBDATA, "w") as file: file.write(text)
		for unit in os.listdir(SAVEBUNITS):
			os.remove(SAVEBUNITS + unit)
	elif (saveIndex == 3):
		with open(SAVECDATA, "w") as file: file.write(text)
		for unit in os.listdir(SAVECUNITS):
			os.remove(SAVECUNITS + unit)
	gs.savePlaceholders["Index"] = 0
	updateSaveStats(saveLoads, saveIndex)
	return

# When I want to store some save data
@Slot()
def storeSave():
	prog = json.dumps(gs.progressData)
	with open(PROGRESSFILE, "w") as file: file.write(prog)
	saveIndex:int = gs.saveData["Index"]
	text = json.dumps(gs.saveData)
	if (saveIndex == 1):
		with open(SAVEADATA, "w") as file: file.write(text)
	elif (saveIndex == 2):
		with open(SAVEBDATA, "w") as file: file.write(text)
	elif (saveIndex == 3):
		with open(SAVECDATA, "w") as file: file.write(text)
	return

# When I want to load the settings data
@Slot()
def loadSettings():
	with open (SETTINGSFILE, "r") as file:
		text = file.read()
		gs.settingData = json.loads(text)
	return

# Closing the settings dialog
@Slot(int)
def closeSettings(result:int):
	if result == 1: applySettings()
	loadSettings()
	return

# Reset the settings values
@Slot(QDialog)
def resetSettings(obj:QDialog):
	from widget_helper import showSettings

	gs.settingData = copy.deepcopy(gs.settingDefault)
	showSettings(obj)
	return

# Apply the settings
@Slot()
def applySettings():
	with open(SETTINGSFILE, "w") as file:
		text = json.dumps(gs.settingData)
		file.write(text)
	return