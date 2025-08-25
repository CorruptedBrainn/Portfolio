"""
Name: game_container.py
Version: 0.0.3-alpha
Description: This file holds the class that wraps around the main game page
Author: Nicolas Martens
"""

from random import randint
import threading
from functools import partial

from PySide6.QtCore import ( # type: ignore
	Slot,
	QPointF,
	QThreadPool,
	QRunnable,
	QTimer,
	QTimeLine,
	)
from PySide6.QtWidgets import ( # type: ignore
	QStackedWidget,
	QWidget,
	QPushButton,
	QStackedLayout,
	QVBoxLayout,
	QTextEdit,
	QGraphicsView,
	QGraphicsScene,
	QGraphicsPolygonItem,
	QGraphicsEllipseItem,
	QGraphicsPixmapItem,
	QApplication,
	)
from PySide6.QtGui import ( # type: ignore
	QBrush,
	QPen,
	QPolygonF,
	QColor,
	QGradient,
	QRadialGradient,
	QPixmap,
	)

from widget_helper import (
	loadWidget,
	changeScreen,
	changeMainScreen,
	)
from file_helper import (
	createUnit,
	getUnit,
	)
import unit_classes
import global_storage as gs
from valuescript_wrapper import VSProgramObject

class runtime(QRunnable):
	def __init__(self, fn):
		super().__init__()
		self.fn = fn

	@Slot()
	def run(self):
		return self.fn()

class gameScene(QGraphicsScene):
	def __init__(self, game):
		super().__init__()
		self.manageTimer = QTimer(self)
		self.manageTimer.timeout.connect(self.manageUnits)
		self.manageTimer.start(400)
		self.spawnTimer = QTimer(self)
		self.spawnTimer.timeout.connect(self.spawnEnemy)
		self.spawnTimer.start(30000)
		self.game = game

	@Slot()
	def spawnEnemy(self):
		x = randint(-10000, 10000)
		y = randint(-10000, 10000)
		name = "ENEMY_" + str(randint(0, 1000))
		createUnit(gs.saveData["Index"], name, "enemy_unit", x, y, 0.0, False)
		self.game.units.update({name: unit_classes.enemy_unit(
			name=name,
			pos=QPointF(x, y),
			obj=self.addPixmap(QPixmap("Images\\enemy_unit"))
			)})
		event = unit_classes.full_target_event(QPointF(x / 10, y / 10))
		QApplication.postEvent(self.game.units[name], event)

	@Slot()
	def manageUnits(self):
		for name, unit in self.game.units.items():
			collisions = unit._obj.collidingItems()
			for collide in collisions:
				if type(collide) == QGraphicsEllipseItem: continue
				print("\n-----COLLISION REPORT-----")
				print(name + ": ")
				print("(" + str(unit._obj.pos().x()) + ", " + str(unit._obj.pos().y()) + ")")
				print(unit)
				print("WITH")
				print(collide)
				print("--------------------------\n")
			if type(unit) == unit_classes.enemy_unit:
				if unit.anim_MOVE.timeLine() is None or unit.anim_MOVE.timeLine().state() == QTimeLine.State.Running: continue
				event = unit_classes.full_target_event(self.game.units[gs.saveData["Name"]].getLoc())
				QApplication.postEvent(unit, event)

# The main game container class
class TVGameContainer(QStackedWidget):
	# The object to store my programs in
	programs = VSProgramObject()
	gameState = threading.Event()
	threads = list()

	# Initialising...
	def __init__(self, parent:QStackedLayout):
		# Get some inherited data and load the two main pages (code editor and expanse)
		super().__init__()
		page0 = loadWidget("main_game.ui")
		page1 = loadWidget("editor.ui")
		self.addWidget(page0)
		self.addWidget(page1)

		# Load the child page structure / heirachy
		page0Layout:QVBoxLayout = page0.layout()
		mainGameLayout:QStackedWidget = QStackedWidget()
		self.theExpanse:QWidget = loadWidget("the_expanse.ui")
		theJournal:QWidget = loadWidget("journal.ui")
		theTechTree:QWidget = loadWidget("tech_tree.ui")
		theFleetControl:QWidget = loadWidget("fleet_control.ui")
		mainGameLayout.addWidget(self.theExpanse)
		mainGameLayout.addWidget(theJournal)
		mainGameLayout.addWidget(theTechTree)
		mainGameLayout.addWidget(theFleetControl)
		page0Layout.addWidget(mainGameLayout)
		page0Layout.setStretch(1, 6)
		mainGameLayout.currentChanged.connect(partial(self.changeState))

		# Load the main button navigation settings
		ButtonA:QPushButton = page0.findChild(QPushButton, "GenericButton1") # type: ignore
		ButtonB:QPushButton = page0.findChild(QPushButton, "GenericButton2") # type: ignore
		ButtonC:QPushButton = page0.findChild(QPushButton, "GenericButton3") # type: ignore
		buttonList = [ButtonA, ButtonB, ButtonC]
		ButtonA.clicked.connect(partial(changeMainScreen, mainGameLayout, buttonList, 0))
		ButtonB.clicked.connect(partial(changeMainScreen, mainGameLayout, buttonList, 1))
		ButtonC.clicked.connect(partial(changeMainScreen, mainGameLayout, buttonList, 2))

		# From the fleet panel
		editorButton:QPushButton = theFleetControl.findChild(QPushButton, "EditorButton") # type: ignore
		editorButton.clicked.connect(partial(changeScreen, parent, 1, 1))

		# From the code editor
		self.codeEditor:QTextEdit = page1.findChild(QTextEdit, "codeEditor") # type: ignore
		mainExpanseButton:QPushButton = page1.findChild(QPushButton, "BackButton") # type: ignore
		mainExpanseButton.clicked.connect(partial(self.parseValuescript, self.codeEditor, parent))

	# Parse the text into an Abstract Syntax Tree to be executed
	# REWRITE THIS
	@Slot(QTextEdit, QStackedLayout)
	def parseValuescript(self, codeEditor:QTextEdit, parent:QStackedLayout):
		ret = self.programs.add(gs.saveData["Name"], codeEditor.toPlainText())
		if ret == 0: return changeScreen(parent, 1, 0)
		return

	def changeState(self, page):
		if page == 0:
			self.executeGame()
		else:
			self.codeEditor.setPlainText(getUnit(gs.saveData["Index"], gs.saveData["Name"]))
			self.stopGame()
		return

	def startState(self, page):
		if page == 1:
			self.executeGame()
		else:
			self.codeEditor.setPlainText(getUnit(gs.saveData["Index"], gs.saveData["Name"]))
			self.stopGame()
		return

	def closestUnit(self, item: unit_classes.core_unit):
		ret = [0, 0, 0]
		best = 1000000
		for name, data in self.units.items():
			if name == item._name: continue
			trial = unit_classes.calcDist(item.getLoc(), data.getLoc())
			if trial < best:
				best = trial
				ret[0] = data.getLoc().x()
				ret[1] = data.getLoc().y()
				ret[2] = data.getOri()
		return ret

	def manageData(self):
		self.gameState.wait()
		self.programs.run()
		while self.gameState.is_set():
			exported = self.programs.grab()
			if exported[1] == None: continue
			access = self.units[exported[0]]
			event = None
			if exported[1] == "x_target": event = unit_classes.x_target_event(exported[2])
			elif exported[1] == "y_target": event = unit_classes.y_target_event(exported[2])
			elif exported[1] == "shot_fired": event = unit_classes.fire_shot_event(self.world)
			QApplication.postEvent(access, event)
			self.programs.clean()
		self.programs.kill()
		return

	def manageRequests(self):
		self.gameState.wait()
		while self.gameState.is_set():
			request = self.programs.get()
			if request[1] == None: continue
			access = self.units[request[0]]
			reply = 0
			if request[1] == "x_coordinate": reply = access.getLoc().x()
			elif request[1] == "y_coordinate": reply = access.getLoc().y()
			elif request[1] == "orientation": reply = access.getOri()
			elif request[1] == "cl_en_x": reply = self.closestUnit(access)[0]
			elif request[1] == "cl_en_y": reply = self.closestUnit(access)[1]
			elif request[1] == "cl_en_ori": reply = self.closestUnit(access)[2]
			self.programs.update(request[0], request[1], reply)
		return

	def executeGame(self):
		# Some empty lists for us
		self.rocks = []
		self.units = {}
	
		# Load some data and load the rocks
		data = gs.worldData
		character = gs.saveData
		self.world = gameScene(self)

		# Create the gradient
		self.world.setBackgroundBrush(QColor.fromHsv(0, 0, 255))
		worldBorder = QPen()
		worldBorder.setWidth(1000)
		worldBorderGradient = QRadialGradient(0, 0, 1000)
		worldBorderGradient.setColorAt(0, QColor.fromHsv(0, 0, 0))
		worldBorderGradient.setColorAt(1, QColor.fromHsv(0, 0, 255))
		worldBorderGradient.setSpread(QGradient.Spread.ReflectSpread)
		worldBorder.setBrush(QBrush(worldBorderGradient))
		self.world.addEllipse(-50540, -50540, 101080, 101080, worldBorder, QBrush(QColor.fromHsv(0, 0, 0)))

		# Display the generated rocks
		for rock in data["Rocks"]:
			polygon = QPolygonF()
			for point in rock:
				polygon.append(QPointF(point[0], point[1]))
			self.rocks.append(self.world.addPolygon(polygon, brush = QBrush(QColor.fromHsv(0, 0, 100))))

		# Show the units
		for unit, info in character["Units"].items():
			pixmap = QPixmap("Images\\" + info["class"])
			if info["class"] == "base_unit":
				self.units.update({unit: unit_classes.base_unit(
				name=unit,
				pos=QPointF(info["x"], info["y"]),
				orient=info["orient"],
				obj=self.world.addPixmap(pixmap)
				)})
				self.programs.add(unit, getUnit(gs.saveData["Index"], unit))
			elif info["class"] == "enemy_unit":
				self.units.update({unit: unit_classes.enemy_unit(
				name=unit,
				pos=QPointF(info["x"], info["y"]),
				orient=info["orient"],
				obj=self.world.addPixmap(pixmap)
				)})

		# Show the scene
		graphicsView:QGraphicsView = self.theExpanse.findChild(QGraphicsView, "graphicsView") # type: ignore
		graphicsView.setScene(self.world)

		x = randint(-10000, 10000)
		y = randint(-10000, 10000)
		name = "ENEMY_" + str(randint(0, 1000))
		createUnit(gs.saveData["Index"], name, "enemy_unit", x, y, 0.0, False)
		self.units.update({name: unit_classes.enemy_unit(
			name=name,
			pos=QPointF(x, y),
			obj=self.world.addPixmap(QPixmap("Images\\enemy_unit"))
			)})
		self.units[name].moveTo(QPointF(x / 10, y / 10))

		self.threadpool = QThreadPool.globalInstance()
		dataThread = runtime(self.manageData)
		requestThread = runtime(self.manageRequests)
		self.threads.append(dataThread)
		self.threads.append(requestThread)
		self.threadpool.start(dataThread)
		self.threadpool.start(requestThread)
		self.gameState.set()
		return

	def stopGame(self):
		self.gameState.clear()
		self.threads.clear()
		return