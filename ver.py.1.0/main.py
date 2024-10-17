import numpy as np
import tetris.tetris as tetris

# import time
# import example


def main():
  # Grid = tetris.GridWorld(10, 20)
  # print()


  # Block = tetris.Block("S")

  # Grid.grid[1:(1+4), 3:(3+4)] += Block.block
  # print(Block)

  # Block.__rotate__(True)

  # print(Block)

  profile = tetris.Settings()

  BL = tetris.BlockLists(profile=profile)
  BL.append("L")
  BL.append("O")
  BL.append("T")

  BL.print_list()

  # print(Grid.grid)

 

  


if __name__ == "__main__":
  main()
