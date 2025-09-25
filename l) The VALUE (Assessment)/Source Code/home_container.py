"""
Name: home_container.py
Version: 0.0.3-alpha
Description: The file that allows me to manage the main home page
Author: Nicolas Martens
"""

from random import randint, choice
from functools import partial

from PySide6.QtCore import ( # type: ignore
	QTimeLine,
	)
from PySide6.QtWidgets import ( # type: ignore
	QStackedWidget,
	QPushButton,
	QStackedLayout,
	QLabel,
	QGridLayout,
	QGraphicsView,
	QGraphicsScene,
	QGraphicsPixmapItem,
	QGraphicsItemAnimation,
	)
from PySide6.QtGui import ( # type: ignore
	QPixmap,
	)

from widget_helper import (
	loadWidget,
	changeScreen,
	updateSaveStats,
	)
from file_helper import (
	createSave,
	updateSaveLoad,
	deleteSave,
	)
from dialog_container import saveHelper

# The main class for the home page
class TVHomeContainer(QStackedWidget):
	# Initialise...
	def __init__(self, parent:QStackedLayout):
		# Load the main pages
		super().__init__()
		page0 = loadWidget("home_page.ui")
		page1 = loadWidget("save_page.ui")
		self.addWidget(page0)
		self.addWidget(page1)

		# Load start button
		startButton:QPushButton = page0.findChild(QPushButton, "startButton") # type: ignore
		startButton.clicked.connect(partial(changeScreen, parent, 0, 1))
		self.currentChanged.connect(partial(saveHelper))

		# Load our save widgets
		page1Layout:QGridLayout = page1.layout() # type: ignore
		self.saveWidgets = []
		saveButtons = []
		saveDeletes = []
		saveNumbers = []
		saveViews:list[QGraphicsView] = []
		saveUnits:list[QGraphicsPixmapItem] = []
		self.anims:list[QGraphicsItemAnimation] = []
		self.timers:list[QTimeLine] = []

		# Connect save widgets to commands
		for i in range(3):
			self.saveWidgets.append(loadWidget("save_slot_widget.ui"))
			updateSaveStats(self.saveWidgets[i], i + 1)
			page1Layout.addWidget(self.saveWidgets[i], 1, i + 1)
			saveButtons.append(self.saveWidgets[i].findChild(QPushButton, "saveLoadButton"))
			saveButtons[i].clicked.connect(partial(updateSaveLoad, i + 1))
			saveButtons[i].clicked.connect(partial(createSave, parent))
			saveDeletes.append(self.saveWidgets[i].findChild(QPushButton, "saveDeleteButton"))
			saveDeletes[i].clicked.connect(partial(deleteSave, i + 1, self.saveWidgets[i]))
			saveDeletes[i].clicked.connect(partial(changeScreen, parent, 0, 1))
			saveNumbers.append(self.saveWidgets[i].findChild(QLabel, "saveNumber"))
			saveNumbers[i].setText("Save " + str(i + 1))
			saveViews.append(self.saveWidgets[i].findChild(QGraphicsView, "graphicsView"))
			saveViews[i].setScene(QGraphicsScene())
			saveUnits.append(saveViews[i].scene().addPixmap(QPixmap("Images\\base_unit")))
			self.anims.append(QGraphicsItemAnimation())
			self.anims[i].setItem(saveUnits[i])
			time = randint(10000, 20000)
			rot = randint(-360, 360)
			self.timers.append(QTimeLine(time))
			self.timers[i].setFrameRange(0, 100)
			saveUnits[i].setOffset(-132, -151)
			saveUnits[i].setRotation(rot)
			saveUnits[i].setScale(0.25)
			self.anims[i].setTimeLine(self.timers[i])
			mult = choice([-1, 1])
			for j in range(0, 200):
				self.anims[i].setRotationAt(j / 200.0, rot + j * 1.8 * mult)
			self.timers[i].setLoopCount(0)
			self.timers[i].start()