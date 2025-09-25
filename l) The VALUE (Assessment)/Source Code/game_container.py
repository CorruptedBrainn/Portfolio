"""
Name: game_container.py
Version: 0.0.3-alpha
Description: This file holds the class that wraps around the main game page
Author: Nicolas Martens
"""

from functools import partial

from PySide6.QtCore import ( # type: ignore
	Slot,
	QTimer,
	)
from PySide6.QtWidgets import ( # type: ignore
	QStackedWidget,
	QWidget,
	QPushButton,
	QStackedLayout,
	QVBoxLayout,
	QLineEdit,
	QGraphicsView,
	QLabel,
	QProgressBar,
	QGraphicsScene,
	QGraphicsPixmapItem,
	)
from PySide6.QtGui import ( # type: ignore
	QPixmap,
	)

from dialog_container import gameHelper
from widget_helper import (
	loadWidget,
	)
import global_storage as gs

DIFFICULTYSTRING = {
	0: "Easy",
	1: "Normal",
	2: "Advanced",
	3: "Experienced"
	}

# The main game container class
class TVGameContainer(QStackedWidget):
	# Initialising...
	def __init__(self, parent:QStackedLayout):
		# Get some inherited data and load the two main pages (code editor and expanse)
		super().__init__()
		self.parent = parent
		page0:QWidget = loadWidget("main_game.ui")
		self.addWidget(page0)

		# Load the child page structure / heirachy
		page0Layout:QVBoxLayout = page0.layout()
		mainGameLayout:QStackedWidget = QStackedWidget()
		self.theExpanse:QWidget = loadWidget("the_expanse.ui")
		mainGameLayout.addWidget(self.theExpanse)
		page0Layout.addWidget(mainGameLayout)
		page0Layout.setStretch(1, 6)

		self.ammoBox:QGraphicsView = page0.findChild(QGraphicsView, "ammoView")
		self.ammoScene:QGraphicsScene = QGraphicsScene()
		self.ammoScene.setSceneRect(-35, 0, 200, 715)
		self.ammoBox.setScene(self.ammoScene)
		self.ammoList = []
		self.nameDisplay:QLabel = page0.findChild(QLabel, "characterName")
		self.difficultyDisplay:QLabel = page0.findChild(QLabel, "gameDifficulty")
		self.killsDisplay:QLabel = page0.findChild(QLabel, "kills")
		self.scoreDisplay:QLabel = page0.findChild(QLabel, "score")
		self.correctDisplay:QLabel = page0.findChild(QLabel, "correctAnswers")
		self.wrongDisplay:QLabel = page0.findChild(QLabel, "wrongAnswers")
		self.accuracyDisplay:QLabel = page0.findChild(QLabel, "accuracy")

		self.questionText:QLabel = self.theExpanse.findChild(QLabel, "questionLabel")
		self.graphicsView:QGraphicsView = self.theExpanse.findChild(QGraphicsView, "graphicsView")
		self.world = None
		self.answerBox:QStackedWidget = self.theExpanse.findChild(QStackedWidget, "answerBox")

		self.answerText:QLineEdit = self.theExpanse.findChild(QLineEdit, "textEdit")
		self.submitButton:QPushButton = self.theExpanse.findChild(QPushButton, "submit")
		self.button_TL:QPushButton = self.theExpanse.findChild(QPushButton, "TLAnswer")
		self.button_TR:QPushButton = self.theExpanse.findChild(QPushButton, "TRAnswer")
		self.button_BL:QPushButton = self.theExpanse.findChild(QPushButton, "BLAnswer")
		self.button_BR:QPushButton = self.theExpanse.findChild(QPushButton, "BRAnswer")
		
		self.progressBar:QProgressBar = page0.findChild(QProgressBar, "progressBar")
		self.buttonConnections = []
		self.timekeeper:QTimer = QTimer()
		self.progress:QTimer = QTimer()
		self.spawner:QTimer = QTimer()
		self.timekeeper.setSingleShot(True)
		return

	@Slot(int)
	def updateData(self, redundancy:int = 0):
		self.nameDisplay.setText(gs.saveData["Name"])
		self.difficultyDisplay.setText(DIFFICULTYSTRING[gs.saveData["Difficulty"]])
		self.killsDisplay.setText(str(gs.saveData["Kills"]))
		self.scoreDisplay.setText(str(gs.saveData["Score"]))
		self.correctDisplay.setText(str(gs.saveData["Quiz"]["Q-RA"]))
		self.wrongDisplay.setText(str(gs.saveData["Quiz"]["Q-WA"]))
		self.accuracyDisplay.setText(str(gs.saveData["Quiz"]["AccP"]) + "%")
		gameHelper()
		return

	@Slot(int)
	@Slot(int, str, str, str, str, str)
	def refreshQuestion(self, mode:int, text:str = "", TL:str = "", TR:str = "", BL:str = "", BR:str = ""):
		if mode == 0:
			self.questionText.setText("Waiting for question...")
			self.answerText.setText("")
			self.button_TL.setText("")
			self.button_TR.setText("")
			self.button_BL.setText("")
			self.button_BR.setText("")
		elif mode == 1:
			self.answerBox.setCurrentIndex(0)
			self.questionText.setText(text)
			self.button_TL.setText(TL)
			self.button_TR.setText(TR)
			self.button_BL.setText(BL)
			self.button_BR.setText(BR)
		else:
			self.answerBox.setCurrentIndex(1)
			self.questionText.setText(text)
			self.answerText.setText("")
		return

	@Slot(str)
	@Slot(str, int)
	def addAmmo(self, ammo:str, pos:int):
		if pos > 100: return
		obj:QGraphicsPixmapItem = self.ammoScene.addPixmap(QPixmap("Images\\" + ammo + "_ammo"))
		obj.setRotation(90)
		obj.setScale(0.4)
		obj.setPos(55 * (pos % 4), 29 * ((pos - pos % 4) / 4))
		self.ammoList.append(obj)
		return

	@Slot()
	def removeAmmo(self)->bool:
		if len(self.ammoList) == 0: return False
		self.ammoScene.removeItem(self.ammoList[-1])
		self.ammoList.pop()
		return True