"""
Name: unit_classes.py
Version: 0.0.3-alpha
Description: This file holds the classes that manage in game units
Author: Nicolas Martens
"""

import math
from functools import partial

from PySide6.QtCore import (
	QPointF,
	QTimeLine,
	QEvent,
	Slot,
	QObject,
	)

from PySide6.QtWidgets import (
	QGraphicsPixmapItem,
	QGraphicsItemAnimation,
	QGraphicsScene,
	)

from PySide6.QtGui import (
	QPixmap,
	)

import global_storage as gs

class unit_update_type:
	x_target_event = QEvent.registerEventType()
	y_target_event = QEvent.registerEventType()
	full_target_event = QEvent.registerEventType()
	fire_shot_event = QEvent.registerEventType()

class x_target_event(QEvent):
	def __init__(self, x_target):
		super().__init__(QEvent.Type(unit_update_type.x_target_event))
		self.x_target = x_target

class y_target_event(QEvent):
	def __init__(self, y_target):
		super().__init__(QEvent.Type(unit_update_type.y_target_event))
		self.y_target = y_target

class full_target_event(QEvent):
	def __init__(self, full_target:QPointF):
		super().__init__(QEvent.Type(unit_update_type.full_target_event))
		self.full_target = full_target

class fire_shot_event(QEvent):
	def __init__(self, world):
		super().__init__(QEvent.Type(unit_update_type.fire_shot_event))
		self.world = world

def calcDist(start:QPointF, end:QPointF):
	return math.sqrt(pow(end.x() - start.x(), 2) + pow(end.y() - start.y(), 2))

class core_unit(QObject):
	def __init__(self,
			  name:str = "N/A",
			  pos:QPointF = QPointF(0.0, 0.0),
			  orient:float = 0.0,
			  hp:float = 100.0,
			  kills:int = 0,
			  dmg:float = 10.0,
			  speed:float = 100.0,
			  atkspd:float = 1.0,
			  sspeed:float = 500.0,
			  fog:float = 1000.0,
			  srange:float = 500.0,
			  obj:QGraphicsPixmapItem = None
			  ):
		super().__init__();
		obj.setPos(pos)
		obj.setRotation(orient)
		self._name = name
		self._pos = pos
		self._orient = orient
		self._hp = hp
		self._kills = kills
		self._dmg = dmg
		self._speed = speed
		self._atkspd = atkspd
		self._sspeed = sspeed
		self._fog = fog
		self._srange = srange
		self._obj = obj
		self.anim_MOVE = QGraphicsItemAnimation()
		self.anim_ROTATE = QGraphicsItemAnimation()
		self.anim_MOVE.setItem(self._obj)
		self.anim_ROTATE.setItem(self._obj)
		self.anims = []
		return

	def event(self, event):
		if event.type() == unit_update_type.x_target_event:
			self.moveTo(QPointF(float(event.x_target), float(self._pos.y())))
			return True
		if event.type() == unit_update_type.y_target_event:
			self.moveTo(QPointF(float(self._pos.x()), float(event.y_target)))
			return True
		if event.type() == unit_update_type.full_target_event:
			self.moveTo(event.full_target)
			return True
		return self._obj.event(event)

	@Slot(QPointF)
	def moveTo(self, loc:QPointF):
		if self.anim_MOVE.timeLine() is not None and self.anim_MOVE.timeLine().state() == QTimeLine.State.Running: return
		distance = calcDist(self.getLoc(), loc)
		moveTime = 1000 * distance / self._speed
		moveTimer = QTimeLine(moveTime)
		moveTimer.setFrameRange(0, 100)
		posx = self.getLoc().x()
		posy = self.getLoc().y()
		deg = math.atan2(posx - loc.x(), (posy - loc.y()) * -1) * -180 / math.pi - 180
		change = deg - self.getOri()
		rotateTime = 10000 * change / self._speed
		if rotateTime < 0: rotateTime = 1
		rotateTimer = QTimeLine(rotateTime)
		rotateTimer.setFrameRange(0, 100)
		self.anim_MOVE.clear()
		self.anim_ROTATE.clear()
		self.anim_MOVE.setTimeLine(moveTimer)
		self.anim_ROTATE.setTimeLine(rotateTimer)
		xStep = (loc.x() - posx) / 200
		yStep = (loc.y() - posy) / 200
		rotStep = change / 200
		ori = self.getOri()
		for i in range(0, 200):
			self.anim_MOVE.setPosAt(i / 200.0, QPointF(posx + i * xStep, posy + i * yStep))
			self.anim_ROTATE.setRotationAt(i / 200.0, ori + i * rotStep)
		moveTimer.start()
		rotateTimer.start()
		self._pos = loc
		self._orient = deg
		gs.saveData["Units"][self._name]["x"] = self._pos.x()
		gs.saveData["Units"][self._name]["y"] = self._pos.y()
		gs.saveData["Units"][self._name]["orient"] = self._orient
		return

	@Slot()
	def getLoc(self):
		return self._obj.pos()

	@Slot()
	def getOri(self):
		return self._obj.rotation()

class base_unit(core_unit):
	def __init__(self,
			  name:str = "N/A",
			  pos:QPointF = QPointF(0.0, 0.0),
			  orient:float = 0.0,
			  obj:QGraphicsPixmapItem = None
			  ):
		super().__init__(
			name=name,
			pos=pos,
			orient=orient,
			obj=obj
			)
		return

	def event(self, event):
		if event.type() == unit_update_type.fire_shot_event:
			self.fire_shot(event.world)
			return True
		return super().event(event)

	@Slot(QGraphicsScene)
	def fire_shot(self, world:QGraphicsScene):
		pixmap = QPixmap("Images\\base_unit_attack")
		bullet = world.addPixmap(pixmap)
		anim = QGraphicsItemAnimation()
		anim.setItem(bullet)
		timer = QTimeLine(1000 * self._srange / self._sspeed)
		self.anims.append([anim, timer])
		timer.setFrameRange(0, 100)
		bullet.setPos(self.getLoc())
		bullet.setRotation(self.getOri())
		anim.setTimeLine(timer)
		xstep = self._srange * math.sin(math.radians(bullet.rotation())) / 200
		ystep = self._srange * math.cos(math.radians(bullet.rotation())) / 200
		for i in range(0, 200):
			anim.setPosAt(i / 200.0, QPointF(bullet.pos().x() + i * xstep, bullet.pos().y() + i * ystep))
		timer.start()
		timer.finished.connect(partial(self.anims.remove, [anim, timer]))
		return

class enemy_unit(core_unit):
	def __init__(self,
			  name:str = "N/A",
			  pos:QPointF = QPointF(0.0, 0.0),
			  orient:float = 0.0,
			  obj:QGraphicsPixmapItem = None
			  ):
		super().__init__(
			name=name,
			pos=pos,
			orient=orient,
			hp=50.0,
			kills=0,
			dmg=5.0,
			speed=70.0,
			atkspd=1.0,
			sspeed=50.0,
			fog=1000.0,
			srange=600.0,
			obj=obj
			)
		return