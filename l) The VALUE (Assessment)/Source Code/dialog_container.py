"""
Name: dialog_container.py
Version: 0.0.3-alpha
Description: This file contains classes that show the dialog popups when I need them
Author: Nicolas Martens
"""

from functools import partial

from PySide6.QtCore import ( # type: ignore
	Qt,
	Slot,
	)
from PySide6.QtWidgets import ( # type: ignore
	QStackedWidget,
	QPushButton,
	QDialogButtonBox,
	QDialog,
	QListWidget,
	QListWidgetItem,
	QComboBox,
	QSlider,
	QLineEdit,
	QMessageBox,
	QLabel,
	)

from widget_helper import changeScreen, updateSaveStats
from file_helper import (
	closeSettings,
	deleteSave,
	resetSettings,
	applySettings,
	storeSave,
	)
import global_storage as gs

# The class for the settings dialog
class TVSettingsDialog(QDialog):
	# When we create a new object
	def __new__(cls, obj:QDialog):
		# Set some initial data
		buttonBox:QDialogButtonBox = obj.findChild(QDialogButtonBox, "buttonBox") # type: ignore
		stack:QStackedWidget = obj.findChild(QStackedWidget, "stackedWidget") # type: ignore
		obj.setWindowModality(Qt.WindowModality.ApplicationModal)
		stack.setCurrentIndex(0)

		# Set the main page button commands
		gameplayButton:QPushButton = obj.findChild(QPushButton, "gameplayButton") # type: ignore
		gameplayButton.clicked.connect(partial(changeScreen, stack, 1))
		audioButton:QPushButton = obj.findChild(QPushButton, "audioButton") # type: ignore
		audioButton.clicked.connect(partial(changeScreen, stack, 2))
		graphicsButton:QPushButton = obj.findChild(QPushButton, "graphicsButton") # type: ignore
		graphicsButton.clicked.connect(partial(changeScreen, stack, 3))

		# Set the back button commands
		obj.finished.connect(partial(changeScreen, stack, 0))
		back1:QPushButton = obj.findChild(QPushButton, "pushButton_4") # type: ignore
		back2:QPushButton = obj.findChild(QPushButton, "pushButton_5") # type: ignore
		back3:QPushButton = obj.findChild(QPushButton, "pushButton_6") # type: ignore
		back1.clicked.connect(partial(changeScreen, stack, 0))
		back2.clicked.connect(partial(changeScreen, stack, 0))
		back3.clicked.connect(partial(changeScreen, stack, 0))

		# Set the restore default button functionality
		restoreDefaults:QPushButton = buttonBox.button(QDialogButtonBox.StandardButton.RestoreDefaults)
		apply:QPushButton = buttonBox.button(QDialogButtonBox.StandardButton.Apply)
		obj.finished.connect(partial(closeSettings))
		restoreDefaults.clicked.connect(partial(resetSettings, obj))
		apply.clicked.connect(partial(applySettings))

		# Set the gameplay button commands
		debuggingMode:QComboBox = obj.findChild(QComboBox, "DebuggingModeComboBox") # type: ignore
		debuggingMode.currentTextChanged.connect(partial(cls.assignSetting, "GPSet", "InfoUtils", "Mode"))
		unitData:QComboBox = obj.findChild(QComboBox, "UnitDataComboBox") # type: ignore
		unitData.currentTextChanged.connect(partial(cls.assignSetting, "GPSet", "InfoUtils", "UDisplay"))
		foeData:QComboBox = obj.findChild(QComboBox, "FoeDataComboBox") # type: ignore
		foeData.currentTextChanged.connect(partial(cls.assignSetting, "GPSet", "InfoUtils", "FDisplay"))

		# Set the volume slider commands
		musicSlider:QSlider = obj.findChild(QSlider, "MusicSlider") # type: ignore
		musicSlider.valueChanged.connect(partial(cls.assignSetting, "AudioSet", "VolSet", "Genval"))
		effectsSlider:QSlider = obj.findChild(QSlider, "EffectsSlider") # type: ignore
		effectsSlider.valueChanged.connect(partial(cls.assignSetting, "AudioSet", "VolSet", "SFXVal"))
		backgroundSlider:QSlider = obj.findChild(QSlider, "BackgroundSlider") # type: ignore
		backgroundSlider.valueChanged.connect(partial(cls.assignSetting, "AudioSet", "VolSet", "ABGVal"))

		# Set the music option commands
		gameMusic:QListWidget = obj.findChild(QListWidget, "GameMusicList") # type: ignore
		gameMusic.itemSelectionChanged.connect(partial(cls.manageList, "AudioSet", "SoundPacks", "GMusic", gameMusic))
		soundEffects:QListWidget = obj.findChild(QListWidget, "SoundEffectsList") # type: ignore
		soundEffects.itemSelectionChanged.connect(partial(cls.manageList, "AudioSet", "SoundPacks", "SFX", soundEffects))
		ambientMusic:QListWidget = obj.findChild(QListWidget, "AmbientList") # type: ignore
		ambientMusic.itemSelectionChanged.connect(partial(cls.manageList, "AudioSet", "SoundPacks", "Amb", ambientMusic))

		# Set the theme option commands
		interfaceTheme:QListWidget = obj.findChild(QListWidget, "InterfaceThemeList") # type: ignore
		interfaceTheme.currentItemChanged.connect(partial(cls.singleSelect, "GraSet", "Themes", "GUI"))
		unitTheme:QListWidget = obj.findChild(QListWidget, "UnitThemeList") # type: ignore
		unitTheme.currentItemChanged.connect(partial(cls.singleSelect, "GraSet", "Themes", "Uni"))
		environmentTheme:QListWidget = obj.findChild(QListWidget, "EnvironmentThemeList") # type: ignore
		environmentTheme.currentItemChanged.connect(partial(cls.singleSelect, "GraSet", "Themes", "Env"))

		return obj

	# Used when I want to change the value of a setting
	@Slot(str, str, str, str)
	@Slot(str, str, str, int)
	def assignSetting(self, keyI:str, keyII:str, keyIII:str, val):
		gs.settingData[keyI][keyII][keyIII] = val
		return

	# Used to help me manage some lists and indexing
	@Slot(str, str, str, QListWidget)
	def manageList(self, keyI:str, keyII:str, keyIII:str, widget:QListWidget):
		arr:list = widget.selectedItems()
		for i in range(len(arr)):
			arr[i] = arr[i].text()
		gs.settingData[keyI][keyII][keyIII] = arr
		return

	# Used to help me select one item
	@Slot(str, str, str, QListWidgetItem, QListWidgetItem)
	def singleSelect(self, keyI:str, keyII:str, keyIII:str, current:QListWidgetItem, former:QListWidgetItem):
		gs.settingData[keyI][keyII][keyIII] = current.text()
		return

# The class for the new save dialog
class TVNewSaveDialog(QDialog):
	slide = 0
	# When we create a new object
	def __new__(cls, obj:QDialog):
		# Set some initial data
		obj.setWindowModality(Qt.WindowModality.ApplicationModal)

		# Set the command to close the dialog
		buttonbox:QDialogButtonBox = obj.findChild(QDialogButtonBox, "buttonBox")
		buttonbox.accepted.connect(partial(cls.confirm, obj))
		buttonbox.rejected.connect(partial(obj.reject))

		return obj

	@Slot(QDialog)
	def confirm(obj:QDialog):
		nameEdit:QLineEdit = obj.findChild(QLineEdit, "nameEdit") # type: ignore
		if nameEdit.text().isalnum() != True:
			err:QLabel = obj.findChild(QLabel, "err") # type: ignore
			err.setText("Character name must be alphanumeric.")
			return
		difficultyBox:QComboBox = obj.findChild(QComboBox, "difficultyBox") # type: ignore
		gs.saveData["Name"] = nameEdit.text()
		gs.saveData["Difficulty"] = difficultyBox.currentIndex()
		storeSave()
		updateSaveStats(obj.slide.widget(0).saveWidgets[gs.saveData["Index"] - 1], gs.saveData["Index"])
		changeScreen(obj.slide, 1, 0)
		obj.accept()
		return

# The class for the game over dialog
class TVGameOverDialog(QDialog):
	slide = 0
	# When we create a new object
	def __new__(cls, obj:QDialog):
		from game_container import DIFFICULTYSTRING
		# Set some initial data
		obj.setWindowModality(Qt.WindowModality.ApplicationModal)

		# Set the command to close the dialog
		obj.finished.connect(partial(cls.updateData, obj))

		# Load dialog data
		obj.findChild(QLabel, "name").setText(gs.saveData["Name"])
		obj.findChild(QLabel, "difficulty").setText(DIFFICULTYSTRING[gs.saveData["Difficulty"]])
		obj.findChild(QLabel, "kills").setText(str(gs.saveData["Kills"]))
		obj.findChild(QLabel, "score").setText(str(gs.saveData["Score"]))
		obj.findChild(QLabel, "ans").setText(str(gs.saveData["Quiz"]["QAns"]))
		obj.findChild(QLabel, "ratio").setText(str(gs.saveData["Quiz"]["Q-RA"]) + ":" + str(gs.saveData["Quiz"]["Q-WA"]))
		obj.findChild(QLabel, "acc").setText(str(gs.saveData["Quiz"]["AccP"]) + "%")

		return obj

	@Slot(QDialog, int)
	def updateData(obj:QDialog, result:int):
		changeScreen(obj.slide, 0, 0)
		deleteSave(gs.saveData["Index"], obj.slide.widget(0).saveWidgets[gs.saveData["Index"] - 1])
		return

@Slot(int)
def homeHelper(redundancy:int = 0):
	if gs.progressData["Home"]:
		return
	msgbox = QMessageBox()
	msgbox.setIcon(QMessageBox.Icon.Information)
	msgbox.setWindowTitle("The VALUE - Tutorial | Start")
	msgbox.setText("Welome to The VALUE!")
	msgbox.setInformativeText("Press \"Start\" to play the game. Good Luck!")
	msgbox.setDetailedText("This game is designed to help you with math skills by quizzing you on various math concepts.\n" +
						"The start button will start the game.")
	msgbox.setFixedHeight(400)
	msgbox.setFixedWidth(800)
	gs.progressData["Home"] = True
	msgbox.exec()
	return

@Slot(int)
def saveHelper(redundancy:int = 0):
	if gs.progressData["Save"]:
		return
	msgbox = QMessageBox()
	msgbox.setIcon(QMessageBox.Icon.Information)
	msgbox.setWindowTitle("The VALUE - Tutorial | Save Games")
	msgbox.setText("Creating a Save Game")
	msgbox.setInformativeText("Press \"Load Save\" on any of the three save slots to create a new save, " +
						   "then choose your character name and game difficulty.")
	msgbox.setDetailedText("You have three save slots to play with, and four difficulty options to choose from.\n" +
						"The concepts in each difficulty range from arithmetic to algebra.")
	msgbox.setFixedHeight(400)
	msgbox.setFixedWidth(800)
	gs.progressData["Save"] = True
	msgbox.exec()
	return

@Slot(int)
def gameHelper(redundancy:int = 0):
	if gs.progressData["Game"]:
		return
	msgbox = QMessageBox()
	msgbox.setIcon(QMessageBox.Icon.Information)
	msgbox.setWindowTitle("The VALUE - Tutorial | Gameplay")
	msgbox.setText("Core Gameplay Mechanics")
	msgbox.setInformativeText("The object in the middle of the game is your character.\n" +
						   "Kill clusters of foes to survive!")
	msgbox.setDetailedText("You can't move, but your unit will rotate automatically to face the nearest foe.\n" +
						"Answering questions that show up at the top of the screen will give you ammunition to use against your foes.\n" +
						"Getting questions wrong has no penalty, and there is no time limit, so you just need to get questions correct.")
	msgbox.setFixedHeight(400)
	msgbox.setFixedWidth(800)
	gs.progressData["Game"] = True
	msgbox.exec()
	return

@Slot(int)
def quizHelper(redundancy:int = 0):
	if gs.progressData["Quiz"]:
		return
	msgbox = QMessageBox()
	msgbox.setIcon(QMessageBox.Icon.Information)
	msgbox.setWindowTitle("The VALUE - Tutorial | The Quiz")
	msgbox.setText("Answering Math Questions")
	msgbox.setInformativeText("At the top of the screen is a randomly generated question.\n" +
						   "Type your answer below, or press the corresponding button to answer the question. When typing multiple answers, separate them by commas, in any order.\n" +
						   "All answers are integers. (whole numbers)")
	msgbox.setDetailedText("Questions are randomly generated and can be about concepts such as arithmetic, geometry, or algebra.\n" +
						"When you answer a question, you'll get a random type of ammo added to the queue. Your unit will use this automatically.")
	msgbox.setFixedHeight(400)
	msgbox.setFixedWidth(800)
	gs.progressData["Quiz"] = True
	msgbox.exec()
	return