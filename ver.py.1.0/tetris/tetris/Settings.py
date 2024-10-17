


class Settings:
  def __init__(self):
    self.CanvasSizeX, self.CanvasSizeY = 10, 10
    self.GameSpeed = 1.0
    self.GameScore = 0.0
    self.GameIsFinished = False
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
