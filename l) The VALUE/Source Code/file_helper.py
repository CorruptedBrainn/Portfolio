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
dataFolder = "../Data/"
settingsFile = dataFolder + "Global.tvsf"
saveAFolder = dataFolder + "I/"
saveAData = saveAFolder + "Standard.andf"
saveAEnv = saveAFolder + "Expanse.tegf"
saveAUnits = saveAFolder + "Units/"
saveBFolder = dataFolder + "II/"
saveBData = saveBFolder + "Standard.andf"
saveBEnv = saveBFolder + "Expanse.tegf"
saveBUnits = saveBFolder + "Units/"
saveCFolder = dataFolder + "III/"
saveCData = saveCFolder + "Standard.andf"
saveCEnv = saveCFolder + "Expanse.tegf"
saveCUnits = saveCFolder + "Units/"

# When the scripts are run, just ensure that we have the required folders
def setupWorkspace():
	if (os.path.exists(dataFolder) == False): os.makedirs(dataFolder)

	if (os.path.exists(settingsFile) == False):
		with open(settingsFile, "x") as file:
			text = json.dumps(gs.settingDefault)
			file.write(text)

	if (os.path.exists(saveAFolder) == False): os.makedirs(saveAFolder)

	if (os.path.exists(saveAData) == False):
		with open(saveAData, "x") as file:
			gs.savePlaceholders["Index"] = 1
			text = json.dumps(gs.savePlaceholders)
			file.write(text)

	if (os.path.exists(saveAEnv) == False):
		with open(saveAEnv, "x") as file:
			text = json.dumps(gs.worldData)
			file.write(text)

	if (os.path.exists(saveAUnits) == False): os.makedirs(saveAUnits)

	if (os.path.exists(saveBFolder) == False): os.makedirs(saveBFolder)

	if (os.path.exists(saveBData) == False):
		with open(saveBData, "x") as file:
			gs.savePlaceholders["Index"] = 2
			text = json.dumps(gs.savePlaceholders)
			file.write(text)

	if (os.path.exists(saveBEnv) == False):
		with open(saveBEnv, "x") as file:
			text = json.dumps(gs.worldData)
			file.write(text)

	if (os.path.exists(saveBUnits) == False): os.makedirs(saveBUnits)

	if (os.path.exists(saveCFolder) == False): os.makedirs(saveCFolder)

	if (os.path.exists(saveCData) == False):
		with open(saveCData, "x") as file:
			gs.savePlaceholders["Index"] = 3
			text = json.dumps(gs.savePlaceholders)
			file.write(text)

	if (os.path.exists(saveCEnv) == False):
		with open(saveCEnv, "x") as file:
			text = json.dumps(gs.worldData)
			file.write(text)

	if (os.path.exists(saveCUnits) == False): os.makedirs(saveCUnits)

	gs.savePlaceholders["Index"] = 0
	loadSettings()

# When I want to create a unit's file
@Slot(int, str)
def createUnit(saveIndex: int, unitName: str, unitClass: str = "base_unit", x: float = 0.0, y: float = 0.0, orient: float = 0.0, script: bool = True):
	object = {unitName: {
		"class": unitClass,
		"x": x,
		"y": y,
		"orient": orient
		}}
	gs.saveData["Units"].update(object)
	if not script: return
	text = gs.defaultScript
	if (saveIndex == 1):
		with open(saveAUnits + unitName + ".vssf", "w") as file: file.write(text)
	elif (saveIndex == 2):
		with open(saveBUnits + unitName + ".vssf", "w") as file: file.write(text)
	elif (saveIndex == 3):
		with open(saveCUnits + unitName + ".vssf", "w") as file: file.write(text)
	return

# When I want to get a unit's script
@Slot(int, str)
def getUnit(saveIndex: int, unitName: str):
	text = gs.defaultScript
	if (saveIndex == 1):
		with open(saveAUnits + unitName + ".vssf", "r") as file: text = file.read()
	elif (saveIndex == 2):
		with open(saveBUnits + unitName + ".vssf", "r") as file: text = file.read()
	elif (saveIndex == 3):
		with open(saveCUnits + unitName + ".vssf", "r") as file: text = file.read()
	return text

# When I want to load data from a save
@Slot(int)
def updateSaveLoad(saveIndex: int):
	text = dict()
	if (saveIndex == 1):
		with open(saveAData, "r") as file: text = file.read()
	elif (saveIndex == 2):
		with open(saveBData, "r") as file: text = file.read()
	elif (saveIndex == 3):
		with open(saveCData, "r") as file: text = file.read()
	else: return
	gs.saveData = json.loads(text)
	loadWorld()
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
		with open(saveAData, "w") as file: file.write(text)
		for unit in os.listdir(saveAUnits):
			os.remove(saveAUnits + unit)
	elif (saveIndex == 2):
		with open(saveBData, "w") as file: file.write(text)
		for unit in os.listdir(saveBUnits):
			os.remove(saveBUnits + unit)
	elif (saveIndex == 3):
		with open(saveCData, "w") as file: file.write(text)
		for unit in os.listdir(saveCUnits):
			os.remove(saveCUnits + unit)
	gs.savePlaceholders["Index"] = 0
	updateSaveStats(saveLoads, saveIndex)
	return

# When I want to store some save data
@Slot()
def storeSave():
	saveIndex:int = gs.saveData["Index"]
	text = json.dumps(gs.saveData)
	env = json.dumps(gs.worldData)
	if (saveIndex == 1):
		with open(saveAData, "w") as file: file.write(text)
		with open(saveAEnv, "w") as file: file.write(env)
	elif (saveIndex == 2):
		with open(saveBData, "w") as file: file.write(text)
		with open(saveBEnv, "w") as file: file.write(env)
	elif (saveIndex == 3):
		with open(saveCData, "w") as file: file.write(text)
		with open(saveCEnv, "w") as file: file.write(env)
	return

# When I want to load the settings data
@Slot()
def loadSettings():
	with open (settingsFile, "r") as file:
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
	with open(settingsFile, "w") as file:
		text = json.dumps(gs.settingData)
		file.write(text)
	return

# Loading a game
@Slot()
def loadWorld():
	saveIndex:int = gs.saveData["Index"]
	world = dict()
	if (saveIndex == 1):
		with open(saveAEnv, "r") as file: world = file.read()
	elif (saveIndex == 2):
		with open(saveBEnv, "r") as file: world = file.read()
	elif (saveIndex == 3):
		with open(saveCEnv, "r") as file: world = file.read()
	else: return
	gs.worldData = json.loads(world)
	return