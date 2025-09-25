"""
Name: dialog_container.py
Version: 0.0.3-alpha
Description: This file contains classes and functions that exist during the game's runtime
Author: Nicolas Martens
"""

from datetime import datetime
from functools import partial
from random import randint, choice
import math

from PySide6.QtCore import (
	Slot,
	QObject,
	QTimer,
	QPointF,
	)
from PySide6.QtWidgets import (
	QStackedWidget,
	QGraphicsScene,
	QApplication,
	QGraphicsPixmapItem,
	)
from PySide6.QtGui import (
	QColor,
	QPen,
	QRadialGradient,
	QGradient,
	QBrush,
	QPixmap,
	)

from game_container import TVGameContainer
import unit_classes as units
import global_storage as gs
from file_helper import storeSave
from cpp_wrapper import Generator, question
from dialog_container import quizHelper, TVGameOverDialog
from widget_helper import loadWidget, showDialog, changeScreen

class gameScene(QGraphicsScene):
	def __init__(self, container:TVGameContainer):
		super().__init__()
		self.container = container
		self.units = {}

		self.unitUpdater:QTimer = QTimer()
		self.unitUpdater.timeout.connect(partial(self.refreshUnits))
		self.gun:QTimer = QTimer()
		self.gun.timeout.connect(partial(self.fireShot))

		self.setBackgroundBrush(QColor.fromHsv(0, 0, 255))
		worldBorder = QPen()
		worldBorder.setWidth(20)
		worldBorderGradient = QRadialGradient(0, 0, 20)
		worldBorderGradient.setColorAt(0, QColor.fromHsv(0, 0, 0))
		worldBorderGradient.setColorAt(1, QColor.fromHsv(0, 0, 255))
		worldBorderGradient.setSpread(QGradient.Spread.ReflectSpread)
		worldBorder.setBrush(QBrush(worldBorderGradient))
		self.addEllipse(-1010.8, -1010.8, 2021.6, 2021.6, worldBorder, QBrush(QColor.fromHsv(0, 0, 0)))

		self.main = units.base_unit(
			name=gs.saveData["Name"],
			obj=self.addPixmap(QPixmap("Images\\base_unit"))
			)
		self.units.update({gs.saveData["Name"]: self.main})
		self.main._obj.setData(0, "main")
		return

	def spawn(self):
		dist = randint(800, 900)
		x = randint(-dist, dist)
		y = pow(pow(dist, 2) - pow(x, 2), 0.5) * choice([-1, 1])
		o = math.degrees(math.atan2(-y, -x)) + 90
		name = "ENEMY_" + str(randint(0, 1000))
		gs.saveData["Units"].update({name: {"x": x, "y": y, "orient": o}})
		self.units.update({name: units.enemy_unit(
			name=name,
			pos=QPointF(x, y),
			orient=o,
			speed=50.0 + 25 * gs.saveData["Difficulty"],
			obj=self.addPixmap(QPixmap("Images\\enemy_unit"))
			)})
		self.units[name]._obj.setData(0, "enemy")
		event = units.full_target_event(QPointF(0, 0))
		QApplication.postEvent(self.units[name], event)
		return

	@Slot()
	def refreshUnits(self):
		for name, unit in self.units.items():
			if type(unit) == units.enemy_unit:
				gs.saveData["Units"][name]["x"] = unit.getLoc().x()
				gs.saveData["Units"][name]["y"] = unit.getLoc().y()
			collisions = unit._obj.collidingItems()
			for collide in collisions:
				if type(unit) == units.base_unit and type(collide) == QGraphicsPixmapItem:
					if collide.data(0) != "enemy": continue
					self.unitUpdater.stop()
					self.gun.stop()
					self.container.timekeeper.stop()
					self.container.spawner.stop()
					self.container.progress.stop()
					for bye in self.units.values():
						self.removeItem(bye._obj)
					dialog = TVGameOverDialog(loadWidget("lost_game_dialog.ui"))
					dialog.slide = self.container.parent
					showDialog(dialog)
					return
				if type(unit) == units.enemy_unit and type(collide) == QGraphicsPixmapItem:
					if collide.data(0) != "ammo": continue
					gs.saveData["Units"].pop(name)
					self.removeItem(collide)
					self.removeItem(unit._obj)
					self.units.pop(name)
					gs.saveData["Kills"] += 1
					gs.saveData["Score"] += gs.saveData["Quiz"]["AccP"] * (4 - gs.saveData["Difficulty"]) / 100
					self.container.updateData()
					return
		return

	@Slot()
	def fireShot(self):
		potentials = [1000000, 0, 0]
		for name, target in self.units.items():
			if type(target) == units.enemy_unit:
				dist = units.calcDist(QPointF(0, 0), target.getLoc())
				if dist < potentials[0]:
					potentials = [dist, target.getLoc().x(), target.getLoc().y()]
		if potentials[0] > self.main._srange: return
		if self.container.removeAmmo() != True: return
		gs.saveData["Ammo"].pop()
		o = math.degrees(math.atan2(potentials[2], potentials[1])) + 90
		self.main._orient = o
		self.main._obj.setRotation(o)
		event = units.fire_shot_event(self)
		QApplication.postEvent(self.main, event)
		return

@Slot(QStackedWidget, int)
def toggleGame(container:TVGameContainer, page:int):
	if page == 0: finishGame(container)
	else: startGame(container)
	return

@Slot(QObject, str, str)
def answered(container:TVGameContainer, correct:str, guess:str):
	if guess == "": guess = container.answerText.text()
	correct = "".join(sorted(correct.split()))
	guess = ",".join(sorted("".join(guess.split()).split(",")))
	gs.saveData["Quiz"]["QAns"] += 1
	if correct == guess:
		gs.saveData["Quiz"]["Q-RA"] += 1
		container.addAmmo("regular", len(gs.saveData["Ammo"]))
		gs.saveData["Ammo"].append("regular")
	else:
		gs.saveData["Quiz"]["Q-WA"] += 1
	gs.saveData["Quiz"]["AccP"] = int(100 * gs.saveData["Quiz"]["Q-RA"] / gs.saveData["Quiz"]["QAns"])
	container.updateData()
	container.refreshQuestion(0)
	for connection in container.buttonConnections:
		QObject.disconnect(connection)
	container.buttonConnections.clear()
	container.timekeeper.start(10000 - 99 * gs.saveData["Quiz"]["AccP"])
	return

@Slot(QObject)
def pushQuestion(container:TVGameContainer):
	quizHelper()
	q:question = question(Generator.create(gs.saveData["Difficulty"]))
	mode = randint(1, 2)
	if gs.saveData["Difficulty"] == q.type: mode = 1
	elif gs.saveData["Difficulty"] >= q.type + 2: mode = 2
	container.refreshQuestion(mode, q.question, q.optionTL, q.optionTR, q.optionBL, q.optionBR)
	container.buttonConnections.append(container.answerText.returnPressed.connect(partial(
		answered, container, q.answer, ""
		)))
	container.buttonConnections.append(container.submitButton.clicked.connect(partial(
		answered, container, q.answer, ""
		)))
	container.buttonConnections.append(container.button_TL.clicked.connect(partial(
		answered, container, q.answer, q.optionTL
		)))
	container.buttonConnections.append(container.button_TR.clicked.connect(partial(
		answered, container, q.answer, q.optionTR
		)))
	container.buttonConnections.append(container.button_BL.clicked.connect(partial(
		answered, container, q.answer, q.optionBL
		)))
	container.buttonConnections.append(container.button_BR.clicked.connect(partial(
		answered, container, q.answer, q.optionBR
		)))
	return

@Slot(QObject)
def progressUpdate(container:TVGameContainer):
	container.progressBar.setValue(100 - 100 * container.timekeeper.remainingTime() / container.timekeeper.interval())
	return

@Slot(QObject)
def spawnEnemy(container:TVGameContainer):
	container.world.spawn()
	return

def startGame(container:TVGameContainer):
	for i in range(len(gs.saveData["Ammo"])):
		container.addAmmo(gs.saveData["Ammo"][i], i)
	container.world = gameScene(container)
	container.graphicsView.setScene(container.world)
	container.world.unitUpdater.start()
	container.world.gun.start(2000 + 1000 * gs.saveData["Difficulty"])
	container.timekeeper.start(5000 - 49 * gs.saveData["Quiz"]["AccP"])
	container.progress.start()
	container.spawner.start(6000 + 500 * gs.saveData["Difficulty"])
	return

def finishGame(container:TVGameContainer):
	gs.saveData["Last"] = datetime.now().isoformat(" ", "minutes")
	storeSave()
	container.timekeeper.stop()
	container.progress.stop()
	container.spawner.stop()
	for ammo in container.ammoScene.items():
		container.ammoScene.removeItem(ammo)
	container.ammoList.clear()
	container.world.units.clear()
	container.world.unitUpdater.stop()
	container.graphicsView.setScene(None)
	container.world = None
	return