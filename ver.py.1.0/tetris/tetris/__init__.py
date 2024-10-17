import lux 
import pandas as pd
import numpy as np

class GridWorld:
  def __init__(self, nx: int, ny: int):
    print(f"Constructing an {nx} by {ny} array for GridWorld")
    self.nx, self.ny = nx, ny
    self.grid = np.zeros((nx, ny))

  # def join(self, Block):


class Block:
  def __init__(self, type : str):
    if not isinstance(type, (str)):
      raise TypeError("Invalid Block type, must be a string.")
    
    print(f"Constructing Block {type}")

    self.next = None    
    self.xloc, self.yloc = 0, 0
    self.block, self.type = np.zeros((4, 4)), type


    if self.type == "L":
      self.block[(1, 1, 1, 2), (0, 1, 2, 0)] = 1
    elif self.type == "J":
      self.block[(1, 1, 1, 2), (0, 1, 2, 2)] = 1
    elif self.type == "O":
      self.block[(1, 1, 2, 2), (1, 2, 1, 2)] = 1
    elif self.type == "T":
      self.block[(2, 2, 2, 1), (0, 1, 2, 1)] = 1
    elif self.type == "I":
      self.block[(1, 1, 1, 1), (0, 1, 2, 3)] = 1
    elif self.type == "Z":
      self.block[(1, 1, 2, 2), (0, 1, 1, 2)] = 1
    elif self.type == "S":
      self.block[(2, 2, 1, 1), (0, 1, 1, 2)] = 1
    else:
      raise ValueError("Invalid Block type.")
    
  def __rotate__(self, clockwise : bool = True):
    if clockwise: self.block = np.rot90(self.block, -1)
    else: self.block = np.rot90(self.block, 1)

  def __move__(self, direction : str):
    if direction == "N":    self.__rotate__()
    elif direction == "S":  self.yloc += self.speed
    elif direction == "W":  self.xloc += self.speed
    elif direction == "E":  self.xloc -= self.speed
    else: raise ValueError("Invalid Value of Direction.")

  def __str__(self):
    return str(self.block)




class BlockLists:
  def __init__(self):
    self.head = None
  
  def append(self, type : str):
    new = Block(type)
    if self.head is None: self.head = new
    else:
      current = self.head
      while current.next: current = current.next
      current.next = new
  
  def join(self, Grid : GridWorld):
    xloc, yloc = self.head.xloc, self.head.yloc
    Grid.grid[xloc:(xloc+4), yloc:(yloc+4)] += self.head
    self.head = self.head.next

  def print_list(self):
    current = self.head
    while current:
      print(current.block, end="\n -> \n")
      current = current.next
    print(" None ")

      









  
