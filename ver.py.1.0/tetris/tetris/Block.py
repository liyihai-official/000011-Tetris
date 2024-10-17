from . import Settings
from . import Block
from . import GridWorld
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
        if    self.block[x, y] == 1: re += "\u25A0"
        elif  self.block[x, y] == 0: re += "\u25A1"
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
  
  # def join(self, Grid : GridWorld):
  #   xloc, yloc = self.head.xloc, self.head.yloc
  #   Grid.grid[xloc:(xloc+4), yloc:(yloc+4)] += self.head
  #   self.head = self.head.next

  def print_list(self):
    current = self.head
    while current:
      print(current, end="\n -> \n")
      current = current.next
    print(" None ")

      









  
