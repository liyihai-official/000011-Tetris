# import lux 
import pandas as pd
import numpy as np


class Settings:
  def __init__(self):
    self.CanvasSizeX, self.CanvasSizeY = 10, 8
    self.GameSpeed = 1.0
    self.GameScore = 0.0
    self.GameIsOver = False
    self.GameIsStarted = False
    self.BlockSquare = 4
    self.BlockType = {
      "L" : [(1, 1, 1, 2), (0, 1, 2, 0)],
      "J" : [(1, 1, 1, 2), (0, 1, 2, 2)],
      "O" : [(1, 1, 2, 2), (1, 2, 1, 2)],
      "T" : [(2, 2, 2, 1), (0, 1, 2, 1)],
      "I" : [(1, 1, 1, 1), (0, 1, 2, 3)],
      "Z" : [(1, 1, 2, 2), (0, 1, 1, 2)],
      "S" : [(2, 2, 1, 1), (0, 1, 1, 2)]
    }


class GridWorld:
  def __init__(self, profile : Settings):
    self.Grid = np.zeros((profile.CanvasSizeX, profile.CanvasSizeY))

  def __str__(self):
    re = "  "
    for y in range(self.Grid.shape[1]):
      re += f"{y} "
    re += "\n"

    for x in range(self.Grid.shape[0]):
      re += f"{x} "
      for y in range(self.Grid.shape[1]):
        if self.Grid[x, y] == 1:    re += "\u25A0 "
        elif self.Grid[x, y] == 0:  re += "\u25A1 "
        else: raise ValueError("Invalid Grid Values.")
      re += "\n"
    return re

  def __EraseRows__(self):
    pass
  

  
  


class Block:
  def __init__(self, type : str, profile : Settings):
    if not isinstance(type, (str)):
      raise TypeError("Invalid Block type, must be a string.")
    
    print(f"Constructing Block {type}")

    self.next = None    
    self.xloc, self.yloc = 0, 0
    self.block, self.type = np.zeros((profile.BlockSquare, profile.BlockSquare)), type

    self.block[tuple(profile.BlockType[self.type])] = 1
    
  def __rotate__(self, clockwise : bool = True):
    if clockwise: self.block = np.rot90(self.block, -1)
    else: self.block = np.rot90(self.block, 1)

  def __move__(self, direction : str, speed : float):
    if direction == "N":    self.__rotate__()
    elif direction == "S":  self.yloc += speed
    elif direction == "W":  self.xloc += speed
    elif direction == "E":  self.xloc -= speed
    else: raise ValueError("Invalid Value of Direction.")

  def __str__(self):
    re = ""
    for x in range(self.block.shape[0]):
      for y in range(self.block.shape[1]):
        if    self.block[x, y] == 1: re += "\u25A0 "
        elif  self.block[x, y] == 0: re += "\u25A1 "
        else: raise ValueError("Invalid block values.")  
      re += "\n"
    return re





class BlockLists:
  def __init__(self, profile : Settings):
    self.head = None
    self.profile = profile
  
  def append(self, type : str):
    new = Block(type, self.profile)
    if self.head is None: self.head = new
    else:
      current = self.head
      while current.next: current = current.next
      current.next = new
  
  def join(self, GW : GridWorld):
    xloc, yloc = self.head.xloc, self.head.yloc
    GW.Grid[xloc:(xloc+4), yloc:(yloc+4)] += self.head.block
    self.head = self.head.next

  def TouchBottom(self, GW : GridWorld):
    xloc, yloc = self.head.xloc+1, self.head.yloc
    temp = GW.Grid[xloc:(xloc+4), yloc:(yloc+4)] + self.head.block

    return 1 in temp



  def print_list(self):
    current = self.head
    while current:
      print(current, end="\n -> \n")
      current = current.next
    print(" None ")

      









  
